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
#include <linux/interrupt.h>
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
//debug
#define mytp_debug_on                       1
#if mytp_debug_on
#define PRINT_INFO(fmt, args...)            printk(KERN_ERR "[MYTP][%s]"fmt"\n", __func__, ##args)
#else
#define PRINT_INFO(fmt, args...)
#endif

//tp info
#define MYTP_DRIVER_NAME                    "mytp_ft5435"

//tp config
#define MYTP_MT_PROTOCOL_B_EN               1
#define MYTP_MAX_POINTS                     10

//device tree
#define MYTP_COORDS_ARR_SIZE                4

//power
#define MYTP_VTG_MIN_UV                     2600000
#define MYTP_VTG_MAX_UV                     3300000
#define MYTP_I2C_VTG_MIN_UV                 1800000
#define MYTP_I2C_VTG_MAX_UV                 1800000

//tp args
#define FTS_ONE_TCH_LEN                     6
#define POINT_READ_BUF                      (3 + FTS_ONE_TCH_LEN * MYTP_MAX_POINTS)

#define FTS_MAX_ID                          0x0F
#define FTS_TOUCH_X_H_POS                   3
#define FTS_TOUCH_X_L_POS                   4
#define FTS_TOUCH_Y_H_POS                   5
#define FTS_TOUCH_Y_L_POS                   6
#define FTS_TOUCH_PRE_POS                   7
#define FTS_TOUCH_AREA_POS                  8
#define FTS_TOUCH_POINT_NUM                 2
#define FTS_TOUCH_EVENT_POS                 3
#define FTS_TOUCH_ID_POS                    5
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

struct mytp_event
{
	u16 au16_x[MYTP_MAX_POINTS]; /*x coordinate */
	u16 au16_y[MYTP_MAX_POINTS]; /*y coordinate */
	u16 pressure[MYTP_MAX_POINTS];
	u8 au8_touch_event[MYTP_MAX_POINTS]; /* touch event: 0 -- down; 1-- up; 2 -- contact */
	u8 au8_finger_id[MYTP_MAX_POINTS];   /*touch ID */
	u8 area[MYTP_MAX_POINTS];
	u8 touch_point;
	u8 point_num;
};

struct mytp_data 
{
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct mytp_platform_data *pdata;
	struct regulator *vdd;
	struct regulator *vcc_i2c;
	struct mytp_event event;
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

void mytp_irq_disable(struct mytp_data *data)
{
	disable_irq_nosync(data->client->irq);
}

void mytp_irq_enable(struct mytp_data *data)
{
	enable_irq(data->client->irq);
}

static u32 g_count_irq = 0; 
static char g_sz_debug[1024] = {0};
static void mytp_show_touch_buffer(u8 *buf, int point_num);
static int mytp_read_touchdata(struct mytp_data *data);

static irqreturn_t mytp_interrupt(int irq, void *dev_id)
{
	struct mytp_data *data = dev_id;
	int ret = -1;

	if (!data)
	{
		PRINT_INFO("[INTR]: Invalid fts_ts");
		return IRQ_HANDLED;
	}

	g_count_irq++;
	PRINT_INFO(" g_count_irq = %d", g_count_irq);

	ret = mytp_read_touchdata(data);

	return IRQ_HANDLED;
}

/************************************************************************
* Name: fts_i2c_read
* Brief: i2c read
* Input: i2c info, write buf, write len, read buf, read len
* Output: get data in the 3rd buf
* Return: fail <0
***********************************************************************/
int fts_i2c_read(struct i2c_client *client, char *writebuf,int writelen, char *readbuf, int readlen)
{
    int ret;

    if (readlen > 0)
    {
        if (writelen > 0)
        {
            struct i2c_msg msgs[] =
            {
                {
                    .addr = client->addr,
                    .flags = 0,
                    .len = writelen,
                    .buf = writebuf,
                },
                {
                    .addr = client->addr,
                    .flags = I2C_M_RD,
                    .len = readlen,
                    .buf = readbuf,
                },
            };
            ret = i2c_transfer(client->adapter, msgs, 2);
            if (ret < 0)
            {
                PRINT_INFO("[IIC]: i2c_transfer(write) error, ret=%d!!", ret);
            }
        }
        else
        {
            struct i2c_msg msgs[] =
            {
                {
                    .addr = client->addr,
                    .flags = I2C_M_RD,
                    .len = readlen,
                    .buf = readbuf,
                },
            };
            ret = i2c_transfer(client->adapter, msgs, 1);
            if (ret < 0)
            {
                PRINT_INFO("[IIC]: i2c_transfer(read) error, ret=%d!!", ret);
            }
        }
    }

    return ret;
}

static int mytp_read_touchdata(struct mytp_data *data)
{
	u8 buf[POINT_READ_BUF] = { 0 };
	u8 pointid = FTS_MAX_ID;
	int ret = -1;
	int i;
	struct mytp_event *event = &(data->event);

	ret = fts_i2c_read(data->client, buf, 1, buf, POINT_READ_BUF);
	if (ret < 0)
	{
		PRINT_INFO("[B]Read touchdata failed, ret: %d", ret);
		return ret;
	}

	memset(event, 0, sizeof(struct mytp_event));
	event->point_num = buf[FTS_TOUCH_POINT_NUM] & 0x0F;
	if (event->point_num > data->pdata->max_touch_number)
		event->point_num = data->pdata->max_touch_number;
	event->touch_point = 0;

	mytp_show_touch_buffer(buf, event->point_num);

	for (i = 0; i < data->pdata->max_touch_number; i++)
	{
		pointid = (buf[FTS_TOUCH_ID_POS + FTS_ONE_TCH_LEN * i]) >> 4;
		if (pointid >= FTS_MAX_ID)
			break;
		else
			event->touch_point++;

		event->au16_x[i] =
			(s16) (buf[FTS_TOUCH_X_H_POS + FTS_ONE_TCH_LEN * i] & 0x0F) <<
			8 | (s16) buf[FTS_TOUCH_X_L_POS + FTS_ONE_TCH_LEN * i];
		event->au16_y[i] =
			(s16) (buf[FTS_TOUCH_Y_H_POS + FTS_ONE_TCH_LEN * i] & 0x0F) <<
			8 | (s16) buf[FTS_TOUCH_Y_L_POS + FTS_ONE_TCH_LEN * i];
		event->au8_touch_event[i] =
			buf[FTS_TOUCH_EVENT_POS + FTS_ONE_TCH_LEN * i] >> 6;
		event->au8_finger_id[i] =
			(buf[FTS_TOUCH_ID_POS + FTS_ONE_TCH_LEN * i]) >> 4;
		event->area[i] =
			(buf[FTS_TOUCH_AREA_POS + FTS_ONE_TCH_LEN * i]) >> 4;
		event->pressure[i] =
			(s16) buf[FTS_TOUCH_PRE_POS + FTS_ONE_TCH_LEN * i];

		if (0 == event->area[i])
			event->area[i] = 0x09;

		if (0 == event->pressure[i])
			event->pressure[i] = 0x3f;

		if ((event->au8_touch_event[i]==0 || event->au8_touch_event[i]==2)&&(event->point_num==0))
		{
			PRINT_INFO("abnormal touch data from fw");
			return -1;
		}
	}
	if(event->touch_point == 0)
	{
		return -1;
	}
	return 0;
}

static void mytp_show_touch_buffer(u8 *buf, int point_num)
{
	int len = point_num * FTS_ONE_TCH_LEN;
	int count = 0;
	int i;

	memset(g_sz_debug, 0, 1024);
	if (len > (POINT_READ_BUF-3))
	{
		len = POINT_READ_BUF-3;
	}
	else if (len == 0)
	{
		len += FTS_ONE_TCH_LEN;
	}
	count += sprintf(g_sz_debug, "%02X,%02X,%02X", buf[0], buf[1], buf[2]);
	for (i = 0; i < len; i++)
	{
		count += sprintf(g_sz_debug+count, ",%02X", buf[i+3]);
	}
	PRINT_INFO("buffer: %s", g_sz_debug);
}

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

	/* 5. Init irq {{{2*/
	err = devm_request_threaded_irq(&client->dev, client->irq, NULL, mytp_interrupt,
			pdata->irq_gpio_flags | IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
			client->dev.driver->name, data);
	if (err)
	{
		PRINT_INFO("Request irq failed!");
		goto free_gpio;
	}

	//mytp_irq_disable(data);

	//mytp_irq_enable(data);
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

//	free_irq(client->irq, data);

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
