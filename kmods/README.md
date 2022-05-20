# Linux Loadable Kernel Modules


## How to compile

Inside a module's directory:

- `$ make all`: to compile
- `$ make clean`: to clean


## How to use

- `# insmod <kmod>.ko`: to load the module
- `# rmmod <kmod>`: to remove (unload) the module
- `# lsmod`: to check all modules loaded
- `# modinfo <kmod>`: to see information about the module


## How to check the printk outputs

printk write into the kernel ring buffer. Use `$ dmesg` to check that. 
