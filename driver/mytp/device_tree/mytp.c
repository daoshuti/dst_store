/****************************************************************************
 @Author: wanghan
 @Created Time : Wed 31 May 2017 02:55:52 PM CST
 @File Name: /home/wanghan/tmp/mytp/mytp.c
 @Description:
 ****************************************************************************
 * Header {{{1 
 ****************************************************************************/
#if 1
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/device.h>
#include <linux/of_gpio.h>
#endif
#if 0
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/firmware.h>
#include <linux/debugfs.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mount.h>
#include <linux/netdevice.h>
#include <linux/unistd.h>
#endif
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
#define PRINT_INFO(fmt, args...) printk(KERN_ERR "[TP][%s]"fmt"\n", __func__, ##args)

#define MYTP_DRIVER_NAME 	"mytp_ft5435"

#define MYTP_MAX_POINTS 	10

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
 * global variable {{{1
 ****************************************************************************/

/****************************************************************************
 * function {{{1
 ****************************************************************************/
static int mytp_parse_dt(struct device *dev, struct mytp_platform_data *pdata)
{
    int rc;
    struct device_node *np = dev->of_node;
    u32 temp_val;
#if 0
    rc = fts_get_dt_coords(dev, "focaltech,display-coords", pdata);
    if (rc)
		PRINT_INFO("Unable to get display-coords");
#endif
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
}

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
        PRINT_INFO("Focaltech touch screen driver init failed!");
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
MODULE_DESCRIPTION("FocalTech Touchscreen Driver (ic:ft5435)");
MODULE_LICENSE("GPL");
