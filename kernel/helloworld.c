// https://www.jianshu.com/p/d6c7314cdce7

#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
        printk(KERN_INFO "hello world enter\n");
        return 0;
}

module_init(hello_init);

static void __exit hello_exit(void)
{
        printk(KERN_INFO "hello world exit\n");
}

module_exit(hello_exit);

MODULE_AUTHOR("tommy");//作者
MODULE_LICENSE("GPL v2");//模块许可证声明,一般用GPL v2
MODULE_DESCRIPTION("A simple hello world module");//模块描述
MODULE_ALIAS("hw"); //别名