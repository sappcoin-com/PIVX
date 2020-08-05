#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
	CPU_CORES=1
fi

# Upgrade the system and install required dependencies
	sudo apt update && sudo apt upgrade
	sudo apt install git zip unzip build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3 -y

# Clone SAPP code from SAPP official Github repository
	git clone https://github.com/sappcoin-com/SAPP

# Entering SAPP directory
	cd SAPP

# Compile dependencies
	cd depends
	chmod +x config.sub
	chmod +x config.guess
	make -j$(echo $CPU_CORES) HOST=x86_64-w64-mingw32 
	cd ..

# Compile SAPP
	chmod +x share/genbuild.sh
	chmod +x autogen.sh
	./autogen.sh
	./configure --prefix=$(pwd)/depends/x86_64-w64-mingw32 --disable-debug --disable-tests --disable-bench CFLAGS="-O3" CXXFLAGS="-O3"
	make -j$(echo $CPU_CORES) HOST=x86_64-w64-mingw32
	cd ..

# Create zip file of binaries
	cp SAPP/src/sapd.exe SAPP/src/sap-cli.exe SAPP/src/sap-tx.exe SAPP/src/qt/sap-qt.exe .
	zip SAPP-Windows.zip sapd.exe sap-cli.exe sap-tx.exe sap-qt.exe
	rm -f sapd.exe sap-cli.exe sap-tx.exe sap-qt.exe
