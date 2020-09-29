# LoRa32u4II_DorjiDRF1276DM_Wireless_Communication
One of the most delicate problems to solve, and which you could encounter, is that of ensuring wireless communication between Dorji DRF1276DM module and LoRa32u4II board (LoRa Technology). Many people face this problem and start looking for the solution on the internet, but the lack of documentation and resources on the internet and the modernity of LoRa technology in the market, are the main reasons which make them unable to solve this problem and find the correct answers to their questions. I was personally one of these people and I struggled for a month to solve this problem which was part of my Master's end-of-study project (from 1 February 2019 to 13 June 2019). After several failed attempts to transfer the data packets through the network, I finally managed to find the solution and fully understand how I can establish wireless communication between the two boards. Today I am sharing this solution with you on GitHub to let you overcome this problem, towards the goal of exploiting this wireless communication in your own applications. I remain at your entire disposal, don't hesitate to contact me at h.taous@ump.ac.ma if you have any questions, remarks, suggestions, or if you need assistance.     
## What is LoRa32u4 II ?
LoRa32u4 II is a light and low consumption board based on the Atmega32u4 MCU and HPD13 LoRa module and an USB battery charging circuit. Ideal for creating long range wireless networks that can exceed 2.4 GHz 802.15.4 and similar, it is more flexible than Bluetooth LE, doesn't require high power unlike WiFi and offers long range. For more information about LoRa32u4 II board, click [here](http://www.diymalls.com/index.php?route=product/product&product_id=88).
## What is Dorji DRF1276DM ?
Dorji DRF1276DM is a type of long-range low data rate data radio modem based on SX1276 from Semtech. It is a low cost transceiver module designed for operations in the unlicensed ISM (Industrial Scientific Medical) and LPRD bands. Frequency spectrum modulation/demodulation, multi-channel operation, high bandwidth efficiency and anti-blocking performance make DRF1276DM modules easy to realize the robust and reliable wireless link. For more information about Dorji DRF1276DM module, click [here](http://www.dorji.com/docs/data/DRF1276DM.pdf).
## What do you need ?
- Lora32u4 II board
- Dorji DRF1276DM module
- Raspberry Pi board (I use Raspberry Pi 3 Model B V1.2)
- UART-USB converter (to connect Dorji DRF1276DM to Raspberry Pi through usb interface)
- Mini USB cable (to upload the sketch to LoRa32u4 II)
- Two antennas 868 MHz 
## How do you use this work ?
You can use this work as a base for any project using a wireless communication between the two devices mentioned above. you just need to make some minor tweaking before you start coding the interesting part of your project right away.
### Arduino Setup
First, you have to install adafruit driver (adafruit_drivers.exe in folder) if you're running Windows on your computer in order to be able to upload the sketch to LoRa32u4 II using the mini USB cable. On the other hand, you don't have to install this driver if you're using a Linux computer. Second, you should add LoRa library ( folder) in Arduino IDE by clicking to the "Sketch" menu and then Include Library -> Add .ZIP Library and wait for a while. Finally, I think beyond that the uploading of the sketch speaks for itself.     
### Dorji DRF1276DM Setup
Dorji DRF1276DM is a module that needs some configuration before it is ready to be used. To do this this, we need to use a DRF tool software (DRF127xDM_V2.7.exe) and we can only use it on a Windows computer. First, you must connect Dorji DRF1276DM with UART_USB converter using the same wiring shown in Connection_Diagram image, and then connect the USB interface of the converter with one of the USB ports of your Windows computer. After that, you open DRF tool software, you click on "Open" and you select the corresponding USB port, and then you select the wireless communication parameters as shown in image, and when you finish, you just click on "Write All". A success confirmation message should appear below. 
### Raspberry Pi Setup
After connecting Dorji DRF1276DM to one of the USB ports Raspberry Pi by using the UART_USB converter, You can use Thonny to open and launch the Python Script and I think that is easy enough. Anyway, I would like to make some notes regarding the contents of the script. The Raspberry Pi recognises the UART_USB conveter as either a USB device and all you have to do is to find the corresponding serial port in the list of serial ports and then replace it in the Python script. For new people in the world of Raspberry Pi, you can find the name of this serial port by unplugging the UART-USB converter, and typing the following command in your terminal.
```
ls /dev/tty*
```
Now plug in your Arduino, and run the command again. The new device that popped up should be your Arduino. 
