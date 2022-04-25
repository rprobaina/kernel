#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rprobaina@gmail.com>");
MODULE_DESCRIPTION("A simple kmem_cache allocator kmod test.");
MODULE_VERSION("1.0");

struct point{
	int x, y;
};

typedef struct point point_t;

point_t *p;
struct kmem_cache * point_cache;

int load_func(void)
{
	printk("Allocating a slab cache\n");
	point_cache = kmem_cache_create("point", 
			sizeof(point_t), ARCH_MIN_TASKALIGN, SLAB_POISON, NULL);
	
	printk("Allocating a object of point cache\n");
	p = kmem_cache_alloc(point_cache, GFP_KERNEL);

	printk("Printing p unitialized\n");
	printk("p.x: %d, p.y: %d\n", p->x, p->y);

	p->x = 1;
	p->y = 2;

	return 0;
}

void unload_func(void)
{
	printk("Printing p\n");
	printk("p.x: %d, p.y: %d\n", p->x, p->y);
	
	printk("Freeing p\n");
	kmem_cache_free(point_cache, p);
	
	printk("Freeing point_cache\n");
	kmem_cache_destroy(point_cache);
}

module_init(load_func);
module_exit(unload_func);
