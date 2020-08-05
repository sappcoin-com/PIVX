#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
	CPU_CORES=1
fi

# Clone SAPP code from SAPP official Github repository
	git clone https://github.com/sappcoin-com/SAPP

# Entering SAPP directory
	cd SAPP

# Compile dependencies
	cd depends
	make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin17 
	cd ..

# Compile SAPP
	./autogen.sh
	./configure --prefix=$(pwd)/depends/x86_64-apple-darwin17 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench
	make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin17
	make deploy HOST=x86_64-apple-darwin17
	cd ..

# Create zip file of binaries
	cp SAPP/src/sapd SAPP/src/sap-cli SAPP/src/sap-tx SAPP/src/qt/sap-qt .
	zip SAPP-MacOS.zip sapd sap-cli sap-tx sap-qt
	rm -f sapd sap-cli sap-tx sap-qt