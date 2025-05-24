make

if grub-file --is-x86-multiboot /build/myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi

mkdir -p isodir/boot/grub
cp build/myos.bin isodir/boot/myos.bin
cp src/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir