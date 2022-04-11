/*
 *	This is a simple kmod to: TODO
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("TODO");
MODULE_VERSION("0.1");

int load_func(void)
{
	// TODO: Will executed while loading the module. 
	
	return 0;
}

void unload_func(void)
{
	// TODO: Will execute before unloading the module. 
	// A tip, undo all you've done on load_func.
}

module_init(load_func);
module_exit(unload_func);
