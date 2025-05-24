#!/bin/bash
echo "Go to https://wiki.osdev.org/Cross-Compiler_Successful_Builds to view the successful versions of gcc and binutils that worked"

sudo apt update
sudo apt install build-essential
sudo apt install libgmp3-dev libmpfr-dev libmpc-dev gcc

export PREFIX="/home/$USER/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

# Build binutils for cross-compiler
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz # If the link 404's, look for a more recent version
tar xvf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log

# Compile cross-compile gcc
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-4.9.1/gcc-4.9.1.tar.bz2
tar xvf gcc-4.9.1.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-4.9.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

# Add PATH to cross-compiler and TARGET to .bashrc
echo "Adding cross-compiler path to .bashrc ..."
echo "export PATH=\"/home/\$USER/i386elfgcc/bin:\$PATH\"" >> /home/$USER/.bashrc
echo "export TARGET=i386-elf" >> /home/$USER/.bashrc

echo "# Run cross-compiler by \$TARGET-gcc" >> /home/$USER/.bashrc
echo " "
echo "Run cross-compiler by \$TARGET-gcc"
source /home/$USER/.bashrc
echo " "
$TARGET-gcc --version
