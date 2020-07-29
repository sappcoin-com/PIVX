make clean
cd depends
# make clean
make -j$(nproc) HOST=x86_64-w64-mingw32
cd ..
./autogen.sh 
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --disable-debug CFLAGS='-O3 --param ggc-min-expand=1 --param ggc-min-heapsize=32768' CXXFLAGS='--param ggc-min-expand=1 --param ggc-min-heapsize=32768 -O3' --prefix=/
make -j$(nproc) HOST=x86_64-w64-mingw32