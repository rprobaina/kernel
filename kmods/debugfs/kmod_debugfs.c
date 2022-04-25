#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>

static unsigned int cnt = 0;
static unsigned int kmod_control = 0;
static struct dentry *kmod_dir, *kmod_file;

static int kmod_set(void *data, u64 val)
{
	printk("Hello from debugfs: %d, val = %lld\n", ++cnt, val);
	return 0;
}

static int kmod_get(void *data, u64 *val)
{
	*val = cnt;
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(kmod_fops, kmod_get, kmod_set, "%llu\n");

static int __init load_func(void)
{
	if(!debugfs_initialized())
		return -ENODEV;

	kmod_dir = debugfs_create_dir("hellofs", NULL);
	if(!kmod_dir)
		return -ENOMEM;

	kmod_file = debugfs_create_file("hello", S_IRUSR|S_IWUSR, kmod_dir, 
			&kmod_control, &kmod_fops);

	if(!kmod_file)
		goto exit_error;

	printk("kmod_hello loaded!\n");
	return 0;

exit_error:
	debugfs_remove(kmod_dir);
	return -ENOMEM;
}

static void __exit unload_func(void)
{
	debugfs_remove(kmod_file);
	debugfs_remove(kmod_dir);
	printk("kmod_hello unloaded!\n");
}

module_init(load_func);
module_exit(unload_func);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("rprobaina@gmail.com");
MODULE_DESCRIPTION("A hello world from kernel space, using debugfs.");
