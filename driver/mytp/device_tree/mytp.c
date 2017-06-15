/****************************************************************************
  @Author: wanghan
  @Created Time : Wed 31 May 2017 02:55:52 PM CST
  @File Name: /home/wanghan/tmp/mytp/mytp.c
  @Description:
 ****************************************************************************
 * Header {{{1 
 ****************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
#define PRINT_INFO(fmt, args...) printk(KERN_ERR "[MYTP][%s]"fmt"\n", __func__, ##args)

#define MYTP_DRIVER_NAME 		"mytp_ft5435"

#define MYTP_MAX_POINTS 		10
#define MYTP_COORDS_ARR_SIZE	4

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

	/* Get display coords {{{3 */
	rc = mytp_get_dt_coords(dev, "focaltech,display-coords", pdata);
	if (rc)
		PRINT_INFO("Unable to get display-coords");

	/* Get key info {{{3 */
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

	/* Get reset, irq gpio info {{{3 */
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

	/* Get max_touch_num {{{3 */
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
	/*}}}3*/

	return 0;
}/*}}}2*/

/*****************************************************************************
 * Probe {{{1
 *****************************************************************************/

static int mytp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mytp_platform_data *pdata;
	int err;

	PRINT_INFO("mytp prebo start!");

	/* 1. Get Platform data */
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


	PRINT_INFO("mytp prebo end!");
	return 0;
}

/*****************************************************************************
 * Remove {{{1
 *****************************************************************************/

static int mytp_remove(struct i2c_client *client)
{
	PRINT_INFO("mytp remove start!");

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
