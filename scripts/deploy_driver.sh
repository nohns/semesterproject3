#!/bin/bash

echo " ---> Making driver..."
cd ../source/driver
make clean
make
echo "----------------------"

echo " ---> Copying .ko module to lib/modules..."
cp dmc_driver.ko /lib/modules/$(uname -r
echo " ---> Registering module with depmod..."
depmod -a
echo " ---> Creating module conf..."
rm /etc/modules-load.d/dmc_driver.conf
echo "dmc_driver" | sudo tee /etc/modules-load.d/dmc_driver.conf 
echo " ---> Creating boot config backup with timestamp..."
cp /boot/config.txt /boot/config.txt.backup-$(date +%s) 
echo " ---> Adding dtoverlay to /boot/config.txt..."
#Check if /boot/config.txt contains the line "dtoverlay=dmc_driver". If not, add it.
if ! grep -q "dtoverlay=dmc_overlay" /boot/config.txt; then
    echo "dtoverlay=dmc_overlay" | sudo tee -a /boot/config.txt
fi