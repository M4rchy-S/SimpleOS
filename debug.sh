. build.sh

qemu-system-i386 -cdrom myos.iso -S -s & gdb -ex "target remote localhost:1234" -ex "break kernel_main" build/myos.bin