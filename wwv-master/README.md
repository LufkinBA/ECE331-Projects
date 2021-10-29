ECE 331 S20 Kernel Driver Project

******************************
* Use minicom con /dev/ttyACM0 for data and debugging
* Press SW5 - firmware git commit printed to ttyACM0
* Press any key except 'D' to get sensor data
*   High res temp in celcius
*   IR light
*   Full Light
*   Visible Light
*   Lux
*   temperature*100
*   Pressure millibars*10000
*   humidity*1000

******************************

DFU Update via USB
---------------------------
 - Clone dfu-util from sourceforge, compile, install
 - Download firmware from course website
 - Remove JP13
 - Press SW1 (next to JP11 text).
 - LED7 turns on.
 - Connect micro USB cable to your RPi and 331hat
 - LED7 turns off.
 - Use dfu-util to flash:

  `$ dfu-util -a 0 -s 0x08000000:leave -R -D firmware.bin`
  
where 

-a 0 is the alternate setting (Internal Flash is 0)
  
-s 0x08000000 is the program address

:leave askes for reset after programming
  
-R Issue USB Reset
  
-D firmware.bin is the firmware to download


***** DO NOT COMMIT IN THIS PROJECT *****
