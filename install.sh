#!/bin/bash

# installing dependencies and requirements
sudo apt update -y
sudo apt install libboost-all-dev cmake -y

if [[ `mkdir build` ]]; then
	cd build
else
	cd build
fi

# generating makefiles using cmake and generating the binary using make
if [[ `cmake ..` && `make` ]]; then
	echo -e "\e[0;32mBuild Completed..."
else
	echo -e "\e[0;31mSomething went wrong while making the binary.\e[0m" 1>&2
	exit 1
fi

#Optional Configuration (coping the binary into `/usr/bin/` for easy access as a command)
read -p "Add 'hiddenwave' to '/usr/bin/' [Y/N]: " confirmation

if [[ $confirmation == 'Y' || $confirmation == 'y' ]] ; then
	sudo cp hiddenwave /usr/bin/
	echo -e "\e[0;32mHiddenwave added successfully in /usr/bin, now use hiddenwave as a command... "
else
	echo -e "\e[0;32mHiddedwave Build Successfully..."
fi
