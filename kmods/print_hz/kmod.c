/*
 *	This is a simple kmod to show HZ and USER_HZ
 *	on a running system.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <asm-generic/param.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("It prints HZ and USER_HZ when it's loaded.");
MODULE_VERSION("0.1");

int load_func(void)
{
	printk("The kernel tick rate (HZ) is: %d\n", HZ);	
	printk("The user tick rate (USER_HZ) is: %d\n", HZ);
	return 0;
}

void unload_func(void)
{
	// Nothing to do.
}

module_init(load_func);
module_exit(unload_func);
