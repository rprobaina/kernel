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

struct foo{
	int x, y, z;
};

typedef struct foo foo_t;

foo_t *f1, *f2, *f3;

int load_func(void)
{
	
	f1 = kmalloc(sizeof(foo_t), GFP_KERNEL);
	if(!f1){
		printk("Memory unavailable!\n");
	}

	f1->x = 1;
	f1->y = 10;
	f1->z = 100;


	f2 = kmalloc(sizeof(foo_t), GFP_KERNEL);
	if(!f2){
		printk("Memory unavailable!\n");
	}

	f2->x = 2;
	f2->y = 20;
	f2->z = 200;

	printk("F1: %d\t%d\t%d\n", f1->x, f1->y, f1->z);
	printk("F2: %d\t%d\t%d\n", f2->x, f2->y, f2->z);

	return 0;
}

void unload_func(void)
{
	//printk("Printing point's data:\n");
	//printk("p.x = %d\t, p.y = %d\n", p->x, p->y);

	//printk("Freeing the memory allocated\n");
	kfree(f1);
	kfree(f2);
	kfree(f1); /* double free */

	
	f3 = kmalloc(sizeof(foo_t), GFP_KERNEL);
	if(!f3){
		printk("Memory unavailable!\n");
	}

	f3->x = 2;
	f3->y = 20;
	f3->z = 200;
}

module_init(load_func);
module_exit(unload_func);
