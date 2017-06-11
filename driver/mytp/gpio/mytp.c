/****************************************************************************
  @Author: wanghan
  @Created Time : Wed 31 May 2017 02:55:52 PM CST
  @File Name: mytp.c
  @Description:
 ****************************************************************************
 * Header {{{1 
 ****************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <linux/gpio.h>
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
//debug
#define PRINT_INFO(fmt, args...) printk(KERN_ERR "[MYTP][%s]"fmt"\n", __func__, ##args)
//tp info
#define MYTP_DRIVER_NAME 					"mytp_ft5435"
//tp config
#define MYTP_MT_PROTOCOL_B_EN 				1
#define MYTP_MAX_POINTS 					10
//device tree
#define MYTP_COORDS_ARR_SIZE				4
//power
#define MYTP_VTG_MIN_UV                      2600000
#define MYTP_VTG_MAX_UV                      3300000
#define MYTP_I2C_VTG_MIN_UV                  1800000
#define MYTP_I2C_VTG_MAX_UV                  1800000

/****************************************************************************
 * struct {{{1
 ****************************************************************************/
struct mytp_platform_data 
{
	u32 irq_gpio;
	u32 irq_gpio_flags;
	u32 reset_gpio;
	u32 reset_gpio_flags;
	bool have_key;
	u32 key_number;
	u32 keys[4];
	u32 key_y_coord;
	u32 key_x_coords[4];
	u32 x_max;
	u32 y_max;
	u32 x_min;
	u32 y_min;
	u32 max_touch_number;
};

struct mytp_data 
{
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct mytp_platform_data *pdata;
	struct regulator *vdd;
	struct regulator *vcc_i2c;
};

/****************************************************************************
 * function {{{1
 ****************************************************************************/

static int mytp_get_dt_coords(struct device *dev, char *name, struct mytp_platform_data *pdata)
{/*{{{2*/
	u32 coords[MYTP_COORDS_ARR_SIZE];
	struct property *prop;
	struct device_node *np = dev->of_node;
	int coords_size, rc;

	prop = of_find_property(np, name, NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;


	coords_size = prop->length / sizeof(u32);
	if (coords_size != MYTP_COORDS_ARR_SIZE)
	{
		PRINT_INFO("invalid %s", name);
		return -EINVAL;
	}

	rc = of_property_read_u32_array(np, name, coords, coords_size);
	if (rc && (rc != -EINVAL))
	{
		PRINT_INFO("Unable to read %s", name);
		return rc;
	}

	if (!strcmp(name, "focaltech,display-coords"))
	{
		pdata->x_min = coords[0];
		pdata->y_min = coords[1];
		pdata->x_max = coords[2];
		pdata->y_max = coords[3];
	}
	else
	{
		PRINT_INFO("unsupported property %s", name);
		return -EINVAL;
	}

	return 0;
}/*}}}2*/

static int mytp_parse_dt(struct device *dev, struct mytp_platform_data *pdata)
{/*{{{2*/
	int rc;
	struct device_node *np = dev->of_node;
	u32 temp_val;

	rc = mytp_get_dt_coords(dev, "focaltech,display-coords", pdata);
	if (rc)
		PRINT_INFO("Unable to get display-coords");

	/* key */
	pdata->have_key = of_property_read_bool(np, "focaltech,have-key");
	if (pdata->have_key)
	{
		rc = of_property_read_u32(np, "focaltech,key-number", &pdata->key_number);
		if (rc)
		{
			PRINT_INFO("Key number undefined!");
		}
		rc = of_property_read_u32_array(np, "focaltech,keys",
				pdata->keys, pdata->key_number);
		if (rc)
		{
			PRINT_INFO("Keys undefined!");
		}
		rc = of_property_read_u32(np, "focaltech,key-y-coord", &pdata->key_y_coord);
		if (rc)
		{
			PRINT_INFO("Key Y Coord undefined!");
		}
		rc = of_property_read_u32_array(np, "focaltech,key-x-coords",
				pdata->key_x_coords, pdata->key_number);
		if (rc)
		{
			PRINT_INFO("Key X Coords undefined!");
		}
		PRINT_INFO("%d: (%d, %d, %d), [%d, %d, %d][%d]",
				pdata->key_number, pdata->keys[0], pdata->keys[1], pdata->keys[2],
				pdata->key_x_coords[0], pdata->key_x_coords[1], pdata->key_x_coords[2],
				pdata->key_y_coord);
	}

	/* reset, irq gpio info */
	pdata->reset_gpio = of_get_named_gpio_flags(np, "focaltech,reset-gpio", 0, &pdata->reset_gpio_flags);
	if (pdata->reset_gpio < 0)
	{
		PRINT_INFO("Unable to get reset_gpio");
	}

	pdata->irq_gpio = of_get_named_gpio_flags(np, "focaltech,irq-gpio", 0, &pdata->irq_gpio_flags);
	if (pdata->irq_gpio < 0)
	{
		PRINT_INFO("Unable to get irq_gpio");
	}

	rc = of_property_read_u32(np, "focaltech,max-touch-number", &temp_val);
	if (!rc)
	{
		pdata->max_touch_number = temp_val;
		PRINT_INFO("max_touch_number=%d", pdata->max_touch_number);
	}
	else
	{
		PRINT_INFO("Unable to get max-touch-number");
		pdata->max_touch_number = MYTP_MAX_POINTS;
	}

	return 0;
}/*}}}2*/

static int mytp_input_dev_init( struct i2c_client *client, struct mytp_data *data,  struct input_dev *input_dev, struct mytp_platform_data *pdata)
{/*{{{2*/
	int  err, len;

	/* Init and register Input device */
	input_dev->name = MYTP_DRIVER_NAME;
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	input_set_drvdata(input_dev, data);
	i2c_set_clientdata(client, data);

	__set_bit(EV_KEY, input_dev->evbit);
	if (data->pdata->have_key)
	{
		PRINT_INFO("set key capabilities");
		for (len = 0; len < data->pdata->key_number; len++)
		{
			input_set_capability(input_dev, EV_KEY, data->pdata->keys[len]);
		}
	}
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);

#if MYTP_MT_PROTOCOL_B_EN
	input_mt_init_slots(input_dev, pdata->max_touch_number, INPUT_MT_DIRECT);
#else
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, 0x0f, 0, 0);
#endif
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, pdata->x_min, pdata->x_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, pdata->y_min, pdata->y_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 0xFF, 0, 0);

	err = input_register_device(input_dev);
	if (err)
	{
		PRINT_INFO("Input device registration failed");
		goto free_inputdev;
	}

	return 0;

free_inputdev:
	input_free_device(input_dev);
	return err;
}/*}}}2*/

static int mytp_power_init(struct mytp_data *data)
{/*{{{2*/
	int rc;

	data->vdd = regulator_get(&data->client->dev, "vdd");
	if (IS_ERR(data->vdd))
	{
		rc = PTR_ERR(data->vdd);
		PRINT_INFO("Regulator get failed vdd rc=%d", rc);
	}

	if (regulator_count_voltages(data->vdd) > 0)
	{
		rc = regulator_set_voltage(data->vdd, MYTP_VTG_MIN_UV, MYTP_VTG_MAX_UV);
		if (rc)
		{
			PRINT_INFO("Regulator set_vtg failed vdd rc=%d", rc);
			goto reg_vdd_put;
		}
	}

	data->vcc_i2c = regulator_get(&data->client->dev, "vcc_i2c");
	if (IS_ERR(data->vcc_i2c))
	{
		rc = PTR_ERR(data->vcc_i2c);
		PRINT_INFO("Regulator get failed vcc_i2c rc=%d", rc);
		goto reg_vdd_set_vtg;
	}

	if (regulator_count_voltages(data->vcc_i2c) > 0)
	{
		rc = regulator_set_voltage(data->vcc_i2c, MYTP_I2C_VTG_MIN_UV, MYTP_I2C_VTG_MAX_UV);
		if (rc)
		{
			PRINT_INFO("Regulator set_vtg failed vcc_i2c rc=%d", rc);
			goto reg_vcc_i2c_put;
		}
	}

	return 0;

reg_vcc_i2c_put:
	regulator_put(data->vcc_i2c);
reg_vdd_set_vtg:
	if (regulator_count_voltages(data->vdd) > 0)
		regulator_set_voltage(data->vdd, 0, MYTP_VTG_MAX_UV);
reg_vdd_put:
	regulator_put(data->vdd);
	return rc;
}/*}}}2*/

static int mytp_power_ctrl(struct mytp_data *data, int enable)
{/*{{{2*/
	int rc;

	if (enable)
	{
		rc = regulator_enable(data->vdd);
		if (rc)
		{
			PRINT_INFO("Regulator vdd enable failed rc=%d", rc);
		}
		msleep(2);
		rc = regulator_enable(data->vcc_i2c);
		if (rc)
		{
			PRINT_INFO("Regulator vcc_i2c enable failed rc=%d", rc);
		}
	}
	else
	{
		rc = regulator_disable(data->vdd);
		if (rc)
		{
			PRINT_INFO("Regulator vdd disable failed rc=%d", rc);
		}
		rc = regulator_disable(data->vcc_i2c);
		if (rc)
		{
			PRINT_INFO("Regulator vcc_i2c disable failed rc=%d", rc);
		}
	}

	return 0;
}/*}}}2*/

static int mytp_gpio_init(struct mytp_data *data)
{/*{{{2*/
	int err = 0;

	/* request irq gpio */
	if (gpio_is_valid(data->pdata->irq_gpio))
	{
		err = gpio_request(data->pdata->irq_gpio, "fts_irq_gpio");
		if (err)
		{
			PRINT_INFO("[GPIO]irq gpio request failed");
			goto err_irq_gpio_req;
		}

		err = gpio_direction_input(data->pdata->irq_gpio);
		if (err)
		{
			PRINT_INFO("[GPIO]set_direction for irq gpio failed");
			goto err_irq_gpio_dir;
		}
	}
	/* request reset gpio */
	if (gpio_is_valid(data->pdata->reset_gpio))
	{
		err = gpio_request(data->pdata->reset_gpio, "fts_reset_gpio");
		if (err)
		{
			PRINT_INFO("[GPIO]reset gpio request failed");
			goto err_irq_gpio_dir;
		}

		err = gpio_direction_output(data->pdata->reset_gpio, 1);
		if (err)
		{
			PRINT_INFO("[GPIO]set_direction for reset gpio failed");
			goto err_reset_gpio_dir;
		}
	}

	return 0;

err_reset_gpio_dir:
	if (gpio_is_valid(data->pdata->reset_gpio))
		gpio_free(data->pdata->reset_gpio);
err_irq_gpio_dir:
	if (gpio_is_valid(data->pdata->irq_gpio))
		gpio_free(data->pdata->irq_gpio);
err_irq_gpio_req:
	return err;
}/*}}}2*/

static int mytp_reset_proc(struct mytp_data *data, int hdelayms)
{/*{{{2*/
	gpio_direction_output(data->pdata->reset_gpio, 0);
	msleep(20);
	gpio_direction_output(data->pdata->reset_gpio, 1);
	msleep(hdelayms);

	return 0;
}/*}}}2*/

/*****************************************************************************
 * Probe {{{1
 *****************************************************************************/

static int mytp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mytp_platform_data *pdata;
	struct input_dev *input_dev;
	struct mytp_data *data;
	int err;

	PRINT_INFO("mytp prebo start!");

	/* 1. Get Platform data {{{2 */
	if (client->dev.of_node)
	{
		pdata = devm_kzalloc(&client->dev,
				sizeof(struct mytp_platform_data),
				GFP_KERNEL);
		if (!pdata)
		{
			PRINT_INFO("[MEMORY]Failed to allocate memory");
			return -ENOMEM;
		}
		err = mytp_parse_dt(&client->dev, pdata);
		if (err)
		{
			PRINT_INFO("[DTS]DT parsing failed");
		}
	}
	else
	{
		return -1;
	}

	if (!pdata)
	{
		PRINT_INFO("Invalid pdata");
		return -EINVAL;
	}
	/*}}}2*/

	/* 2. Init Input Device {{{2 */
	data = devm_kzalloc(&client->dev, sizeof(struct mytp_data), GFP_KERNEL);
	if (!data)
	{
		PRINT_INFO("[MEMORY]Failed to allocate memory");
		return -ENOMEM;
	}

	input_dev = input_allocate_device();
	if (!input_dev)
	{
		PRINT_INFO("[INPUT]Failed to allocate input device");
		return -ENOMEM;
	}

	data->input_dev = input_dev;
	data->client = client;
	data->pdata = pdata;

	mytp_input_dev_init(client, data, input_dev, pdata);
	/*}}}2*/
   
	/* 3. Power On {{{2 */
	mytp_power_init(data);
	mytp_power_ctrl(data, 1);
	/*}}}2*/

	/* 4. Init GPIO and reset IC {{{2 */
	err = mytp_gpio_init(data);
	if (err < 0)
	{
		PRINT_INFO("[GPIO]Failed to configure the gpios");
		goto free_gpio;
	}

	mytp_reset_proc(data,200);
	/*}}}2*/

	PRINT_INFO("mytp prebo end!");
	return 0;

free_gpio:
	if (gpio_is_valid(data->pdata->reset_gpio))
		gpio_free(data->pdata->reset_gpio);
	if (gpio_is_valid(data->pdata->irq_gpio))
		gpio_free(data->pdata->irq_gpio);
	PRINT_INFO("mytp probe fail!");
	return -1;
}

/*****************************************************************************
 * Remove {{{1
 *****************************************************************************/

static int mytp_remove(struct i2c_client *client)
{
	struct mytp_data *data = i2c_get_clientdata(client);

	PRINT_INFO("mytp remove start!");

	input_unregister_device(data->input_dev);

	PRINT_INFO("mytp remove end!");
	return 0;
}


/*****************************************************************************
 * I2C Driver {{{1
 *****************************************************************************/
static const struct i2c_device_id mytp_id[] =
{
	{MYTP_DRIVER_NAME, 0},
	{},
};

static const struct of_device_id mytp_match_table[] =
{
	{ .compatible = "focaltech,fts", },
	{ },
};

static struct i2c_driver mytp_driver =
{
	.probe = mytp_probe,
	.remove = mytp_remove,
	.driver = {
		.name = MYTP_DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = mytp_match_table,
	},
	.id_table = mytp_id,
};

/*****************************************************************************
 * Module Init {{{1
 *****************************************************************************/
static __init int mytp_init(void)
{
	int ret;
	PRINT_INFO("mytp init start!");
	ret = i2c_add_driver(&mytp_driver);
	if ( ret != 0 )
	{
		PRINT_INFO("TP driver init failed!");
	}
	PRINT_INFO("mytp init end!");
	return 0;
}

/*****************************************************************************
 * Module Exit {{{1
 *****************************************************************************/
static __exit void mytp_exit(void)
{
	PRINT_INFO("mytp exit start!");
	i2c_del_driver(&mytp_driver);
	PRINT_INFO("mytp exit end!");
}

/*****************************************************************************
 * Module Info {{{1
 *****************************************************************************/
module_init(mytp_init);
module_exit(mytp_exit);
MODULE_AUTHOR("wanghan");
MODULE_DESCRIPTION("TP Driver (ic:ft5435)");
MODULE_LICENSE("GPL");
