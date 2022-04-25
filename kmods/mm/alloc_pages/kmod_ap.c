#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("This simple kmod allocates a memory page.");
MODULE_VERSION("1.0");

struct page *p;

int load_func(void)
{
	printk("Allocatiog a meory page\n");

	p = alloc_pages(GFP_KERNEL, 0);
	if(!p){
		printk("Memory unavailable!\n");
	}

	return 0;
}

void unload_func(void)
{
	printk("Page flags: %lx\n", p->flags);
	
	printk("Freeing the page allocated\n");
	__free_pages(p, 0);
}

module_init(load_func);
module_exit(unload_func);
