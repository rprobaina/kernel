#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("A simple kmalloc() and kfree(), kmod test.");
MODULE_VERSION("1.0");

struct point{
	int x, y;
};

typedef struct point point_t;

point_t *p;

int load_func(void)
{
	printk("Allocating memory to a point, with kmalloc\n");
	
	p = kmalloc(sizeof(point_t), GFP_KERNEL);
	if(!p){
		printk("Memory unavailable!\n");
	}

	p->x = 10;
	p->y = 5;
	return 0;
}

void unload_func(void)
{
	printk("Printing point's data:\n");
	printk("p.x = %d\t, p.y = %d\n", p->x, p->y);

	printk("Freeing the memory allocated\n");
	kfree(p);
}

module_init(load_func);
module_exit(unload_func);
