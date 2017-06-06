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
/****************************************************************************
 * Define {{{1 
 ****************************************************************************/
#define PRINT_INFO(fmt, args...) printk(KERN_ERR "[TP][%s]"fmt"\n", __func__, ##args)

#define MYTP_DRIVER_NAME 	"mytp_ft5435"

/*****************************************************************************
* Probe {{{1
*****************************************************************************/

static int mytp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	PRINT_INFO("mytp prebo start!");
	
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
