/*
 *	This is a simple kmod to dump the stack during its load and removal.
 */

#include <linux/init.h>
#include <linux/module.h>

int load_func(void)
{
	dump_stack();	
	return 0;
}

void unload_func(void)
{
	dump_stack();
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("TODO");
MODULE_VERSION("0.1");
