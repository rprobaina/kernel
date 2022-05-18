/*
 *	This is a simple kmod to panic the system viv BUG macro.
 */

#include <linux/init.h>
#include <linux/module.h>

#define TRUE 1

int load_func(void)
{
	if(TRUE)
		BUG();	
	
	return 0;
}

void unload_func(void)
{
	/* nothing to do. */
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("It will panic the system.");
MODULE_VERSION("0.1");
