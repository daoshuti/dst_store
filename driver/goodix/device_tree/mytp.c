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
#define PRINT_INFO(fmt, args...)                printk(KERN_ERR "[MYTP][%s]"fmt"\n", __func__, ##args)

#define MYTP_DRIVER_NAME                        "mytp_gt917d"

#define MYTP_COORDS_ARR_SIZE                    4
#define MYTP_MAX_POINTS                         10

#define GTP_CONFIG_MIN_LENGTH                   186
#define GTP_CONFIG_MAX_LENGTH                   240
/****************************************************************************
 * struct {{{1
 ****************************************************************************/
struct mytp_platform_data 
{
	u32 irq_gpio;
	u32 irq_gpio_flags;
	u32 reset_gpio;
	u32 reset_gpio_flags;
	u32 power_ldo_gpio;
	u32 power_ldo_gpio_flags;
	u32 x_max;
	u32 y_max;
	u32 x_min;
	u32 y_min;
	u32 max_touch_number;
};

/****************************************************************************
 * function {{{1
 ****************************************************************************/

/**
 * gtp_parse_dt_cfg - parse config data from devices tree.
 * @dev: device that this driver attached.
 * @cfg: pointer of the config array.
 * @cfg_len: pointer of the config length.
 * @sid: sensor id.
 * Return: 0-succeed, -1-faileds
 */
int gtp_parse_dt_cfg(struct device *dev, u8 *cfg, int *cfg_len, u8 sid)
{/*{{{2*/
	struct device_node *np = dev->of_node;
	struct property *prop;
	char cfg_name[18];

	snprintf(cfg_name, sizeof(cfg_name), "goodix,cfg-group%d", sid);
	prop = of_find_property(np, cfg_name, cfg_len);
	if (!prop || !prop->value || *cfg_len == 0 || *cfg_len > GTP_CONFIG_MAX_LENGTH) {
		PRINT_INFO("Unable get config data form devices tree");
		return -1;/* failed */
	} else {
		memcpy(cfg, prop->value, *cfg_len);
		return 0;
	}
}/*}}}2*/

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

	if (!strcmp(name, "goodix,display-coords"))
	{
		pdata->x_min = coords[0];
		pdata->x_max = coords[1];
		pdata->y_min = coords[2];
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
	rc = mytp_get_dt_coords(dev, "goodix,display-coords", pdata);
	if (rc)
	{
		PRINT_INFO("Unable to get display-coords");
	}

	/* Get reset, irq gpio info {{{3 */
	pdata->reset_gpio = of_get_named_gpio_flags(np, "goodix,reset-gpio", 0, &pdata->reset_gpio_flags);
	if (pdata->reset_gpio < 0)
	{
		PRINT_INFO("Unable to get reset_gpio");
	}

	pdata->irq_gpio = of_get_named_gpio_flags(np, "goodix,irq-gpio", 0, &pdata->irq_gpio_flags);
	if (pdata->irq_gpio < 0)
	{
		PRINT_INFO("Unable to get irq_gpio");
	}

	/* Get power ldo gpio info {{{3 */
	pdata->power_ldo_gpio = of_get_named_gpio(np, "goodix,power_ldo-gpio", 0, &pda->power_ldo_gpio_flags);
	if (power_ldo_gpio < 0)
	{
		PRINT_INFO("Unable to get power_ldo_gpio");
	}

	/* Get max_touch_num {{{3 */
	rc = of_property_read_u32(np, "goodix,max-touch-number", &temp_val);
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

/*****************************************************************************
 * Probe {{{1
 *****************************************************************************/

static int mytp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mytp_platform_data *pdata;
	int err;

	PRINT_INFO("mytp prebo start!");

	/* 1. Get Platform data {{{2*/
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
	{ .compatible = "goodix,gt917d", },
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
MODULE_DESCRIPTION("TP Driver (ic:gt917d)");
MODULE_LICENSE("GPL");
