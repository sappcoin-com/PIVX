#!/bin/bash
# Upgrade the system and install required dependencies
	sudo apt update && apt upgrade
	sudo apt install git zip unzip build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3 -y

# Clone SAPP code from SAPP official Github repository
	git clone https://github.com/sappcoin-com/SAPP

# Entering SAPP directory
	cd SAPP

# Compile dependencies
	cd depends
	chmod +x config.sub
	chmod +x config.guess
	make
	cd ..

# Compile SAPP
	chmod +x share/genbuild.sh
	chmod +x autogen.sh
	./autogen.sh
	./configure --enable-glibc-back-compat --prefix=$(pwd)/depends/x86_64-pc-linux-gnu LDFLAGS="-static-libstdc++"  --enable-cxx --disable-shared --with-pic CXXFLAGS="-fPIC -O" CPPFLAGS="-fPIC -O"
	make
	cd ..

# Create zip file of binaries
	cp SAPP/src/sapd SAPP/src/sap-cli SAPP/src/sap-tx SAPP/src/qt/sap-qt .
	zip SAPP-Linux.zip sapd sap-cli sap-tx sap-qt
	rm -f sapd sap-cli sap-tx sap-qt
