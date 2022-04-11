/*
 *	This is a simple hello kernel space kmod 
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("A simple \"hello kernel space!\" module.");
MODULE_VERSION("0.1");

int load_func(void)
{
	printk("Hello, kernel space!\n");
	
	return 0;
}

void unload_func(void)
{
	printk("Good bye, kernel space!\n");
}

module_init(load_func);
module_exit(unload_func);
