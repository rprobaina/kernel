/*
 *	This is a simple kmod to reproduce
 *	a double free kernel panic.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("A simple kmod to panic the kernel");
MODULE_VERSION("1.0");

#define SIZE 512 // want use kmalloc-512
#define ARRAY_SIZE 100

struct foo{
	char block[SIZE];
};

typedef struct foo foo_t;

foo_t *f;

int load_func(void)
{
	f = kmalloc(sizeof(foo_t), GFP_KERNEL);
	memset(f->block, 'a', SIZE);

	return 0;
}

void unload_func(void)
{
	//bprintf(f->block, SIZE, "%s");
	kfree(f);
}

module_init(load_func);
module_exit(unload_func);
