# LoRa32u4II_DorjiDRF1276DM_Wireless_Communication
One of the most delicate problems to solve, and which you may encounter, is that of ensuring a wireless communication between Dorji DRF1276DM module and LoRa32u4 II board (LoRa Technology). Many people face this problem and start looking for the solution on the internet, but the lack of documentation and resources on the internet and the modernity of LoRa technology in the market, are the main reasons that make them unable to solve this problem and find the complete answers for their questions. I was personally one of these people and I struggled for a month to solve this problem which was part of my Master's end-of-study project (from 1 February 2019 to 13 June 2019). After several failed attempts to transfer the data packets through the LoRa network, I finally managed to find the solution and fully understand how I can establish a wireless communication between these two devices. Today I am sharing this solution with you on GitHub to make you able to overcome this problem easily, towards the goal of exploiting this wireless communication in your own applications. I remain at your entire disposal, don't hesitate to contact me at h.taous@ump.ac.ma if you have any questions, remarks, suggestions, or if you need assistance.
## What is LoRa32u4 II ?
LoRa32u4 II is a light and low consumption board based on the Atmega32u4 MCU and HPD13 LoRa module and an USB battery charging circuit. Ideal for creating long range wireless networks that can exceed 2.4 GHz 802.15.4 and similar, it is more flexible than Bluetooth LE, doesn't require high power unlike WiFi and offers long range. For more information about LoRa32u4 II board, click [here](http://www.diymalls.com/index.php?route=product/product&product_id=88).
## What is Dorji DRF1276DM ?
Dorji DRF1276DM is a type of long-range low data rate data radio modem based on SX1276 from Semtech. It is a low cost transceiver module designed for operations in the unlicensed ISM (Industrial Scientific Medical) and LPRD bands. Frequency spectrum modulation/demodulation, multi-channel operation, high bandwidth efficiency and anti-blocking performance make DRF1276DM modules easy to realize the robust and reliable wireless link. For more information about Dorji DRF1276DM module, click [here](http://www.dorji.com/docs/data/DRF1276DM.pdf).
## What do you need ?
- Lora32u4 II board (I use LoRa32u4 II V1.2)
- Dorji DRF1276DM module
- Raspberry Pi board (I use Raspberry Pi 3 Model B V1.2)
- UART-USB converter (to connect Dorji DRF1276DM to Raspberry Pi through usb interface)
- Mini USB cable (to upload the sketch to LoRa32u4 II)
- Two antennas 868 MHz 
- Some FF jumper wires 
## How do you use this work ?
You can use this work as a base for any project using a wireless communication between the two devices mentioned above. You just need to make some minor tweaking before you start coding the interesting part of your project right away.
### Arduino Setup
First, you have to install adafruit driver (adafruit_drivers.exe in LoRa32u4II software folder) if you're running Windows on your computer in order to be able to upload the sketch to LoRa32u4 II using the mini USB cable. On the other hand, you don't have to install this driver if you're using a Linux computer. Second, you should copy the content of hardware folder (in LoRa32u4II software folder) into Documents/Arduino/hadrware folder, and if this last one doesn't already exist, so just copy hardware folder into Documents/Arduino, where libraries folder does exist. This step will make you able to use all the predefined functions of LoRa library in your sketch and you will find LoRa32u4 II board in Tools/Board when you need to upload the Arduino sketch into it. Finally, I think beyond that the uploading of the sketch speaks for itself.   
### Dorji DRF1276DM Setup
Dorji DRF1276DM is a module that needs some configuration before it is ready to be used. To do this, we need to use a DRF tool software (DRF_Tool.exe in DRF Tool folder) and we can only use it on a Windows computer. First, you must connect Dorji DRF1276DM with UART-USB converter using the same wiring shown in Raspberry_Dorji_Connection image, and then connect the USB interface of the converter with one of the USB ports of your Windows computer. After that, you open DRF tool software, you click on "Open", you select the corresponding USB port, then you select the wireless communication parameters as shown in Dorji_DRF1276DM_Configuration image, and you just click on "Write All" once you finish. A success confirmation message should appear below. 
### Raspberry Pi Setup
After connecting Dorji DRF1276DM to one of the USB ports of Raspberry Pi using the UART_USB converter (Raspberry_Dorji_Connection image), You can use Thonny to open and launch the Python script and I think that is easy enough. Anyway, I would like to make some notes regarding the contents of the script. The Raspberry Pi recognises the UART_USB conveter as either a USB device and all you have to do is to find the corresponding serial port in the list of serial ports and then replace it in the Python script. For new people in the world of Raspberry Pi, you can find the name of this serial port by unplugging the UART-USB converter, and typing the following command in your terminal.
```
ls /dev/tty*
```
Now plug in the UART-USB converter, and run the command again. The new serial port that popped up should be your UART-USB converter which is connected with Dorji DRF1276DM. 
### Some Important Notes
The Arduino sketch and the Python script allows an automatic wireless communication between Dorji DRF1276DM and LoRa32u4 II, where :
- LoRa32u4 II sends the message "Hello Dorji" every 20 seconds to Dorji DRF1276DM
- Once Dorji DRF1276DM receives the message "Hello Dorji", it sends automatically "Hello LoRa" message to LoRa32u4 II

Also, the Python script allows you to have the possibilty of sending any message manually, on condition of not exceeding the maximum number of bytes that is already allocated to your message. To do this, all you should do is to type your message in the text box below the "Sending Message" button and then click this last one when you finish. Lora32u4 II will receive your message if it is listening, and you can visualize this received message just by opening the serial monitor already.

I simplified the two codes as much as possible and I improved them by adding comments. These comments will make it easy to understand both of them and modify them quickly. I am sure that you will understand everything you read. 

Finally, you can modify the codes as you want so as to adapt them to your own applications, just be careful with everything concerning the wireless communication side, and once again, I remain at your entire disposal, just contact me at my academic mail h.taous@ump.ac.ma if you have any questions or if you need any kind of assistance. 
