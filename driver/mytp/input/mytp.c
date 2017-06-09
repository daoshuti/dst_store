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
#include <linux/device.h>
#include <linux/input.h>
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
#define PRINT_INFO(fmt, args...) printk(KERN_ERR "[TP][%s]"fmt"\n", __func__, ##args)

#define MYTP_DRIVER_NAME 	"mytp_ft5435"

#define MYTP_MT_PROTOCOL_B_EN 	1

/****************************************************************************
 * struct {{{1
 ****************************************************************************/
struct mytp_data 
{
	struct i2c_client *client;
	struct input_dev *input_dev;
};

/****************************************************************************
 * function {{{1
 ****************************************************************************/
static int mytp_input_dev_init( struct i2c_client *client, struct mytp_data *data,  struct input_dev *input_dev, struct mytp_platform_data *pdata)
{
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
		FTS_DEBUG("set key capabilities");
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
}

/*****************************************************************************
 * Probe {{{1
 *****************************************************************************/

static int mytp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mytp_data *data;
	struct input_dev *input_dev;
	int err;

	PRINT_INFO("mytp prebo start!");

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

	mytp_input_dev_init(client, data, input_dev, pdata);

	PRINT_INFO("mytp prebo end!");
	return 0;
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
