#!/bin/bash

make clean
cd depends
# make clean
make -j$(nproc) HOST=x86_64-pc-linux-gnu 
cd ..
./autogen.sh 
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure --enable-glibc-back-compat --enable-static --disable-shared --disable-debug CFLAGS='-O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768' CXXFLAGS='--param ggc-min-expand=1 --param ggc-min-heapsize=32768 -O3' LDFLAGS='-static-libstdc++' --prefix=/
make -j$(nproc) HOST=x86_64-pc-linux-gnu
zip ../SAPP-X.X.X-Linux-qt.zip src/qt/sap-qt
zip ../SAPP-X.X.X-Linux.zip src/sapd src/sap-cli src/sap-tx
