
This is a small manual on how to connect Buydisplay's 5 inch Touch Panel  with GSL1680F controller to Olimex A20-SOM or A20-SOM-EVB board

1. Use Olimage guide (link below) to get acquainted with kernel building process:
https://github.com/OLIMEX/OLINUXINO/blob/master/DOCUMENTS/OLIMAGE/Olimage-guide.pdf

2. While building kernel, using the above guide, In Kernel Menuconfig, Select **Device drivers->Input device support->Touchscreens->Silead I2C Touchscreen - [Module]**
or, edit .config file and add the following line:
CONFIG_TOUCHSCREEN_SILEAD=m
**Do not select "compiled" or else it won't be able to find firmware!*

3. Build kernel as in the manual
I've used the following make command to build debs on Ubuntu 
*(notice KDEB_COMPRESS=gzip to enable compatible compression for Debian)*
```sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bindeb-pkg LOCALVERSION=-olimex KDEB_PKGVERSION=$(make kernelversion)-$EXTRA_VER KDEB_COMPRESS=gzip DTC_FLAGS=-@```

4. Upload the kernel as in the above manual, reboot

5. run 
```sudo olinuxino-display  ```
and enable 5 inch LCD-OLinuXino-5 display with capacitive touchscreen via olinuxino-display

6. Clone this repository 
```git clone https://github.com/mavstuff/olimex-a20-som-buydisplay-gsl1680-touch.git```

7. Compile & copy additional dts file 
```dtc -O dtb -o som-i2c2-silead.dtbo som-i2c2-silead.dts```
```sudo cp som-i2c2-silead.dtbo /usr/lib/olinuxino-overlays/sun7i-a20```

8. next, add overlay to /boot/uEnv.txt:
```sudo nano /boot/uEnv.txt```
then add :
```/usr/lib/olinuxino-overlays/sun7i-a20/som-i2c2-silead.dtbo```
to the end of ```"fdtoverlays=..."``` line.

9. generate GSL1680 firmware from sources and copy to firmware folder:
```cd SileadFwGen/SileadFwGen```
```gcc SileadFwGen.c -o SileadFwGen```
```./SileadFwGen```
```sudo mkdir -p /usr/lib/firmware/silead```
```sudo cp -f gsl1680.fw /usr/lib/firmware/silead/gsl1680.fw```


May this small guide and tools be helpful to anybody struggling to connect  gsl1680 touch panel to olimex a20-som board
(c) Artem Moroz, 2023, artem.moroz@gmail.com
