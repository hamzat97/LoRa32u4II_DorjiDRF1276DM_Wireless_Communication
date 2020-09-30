# Import of the necessary python modules 
# tkinter module to create simple graphical user interface (GUI)
# serial module to etablish a wired communication between Dorji DRF1276DM and Raspberry Pi using the UART protocol
from tkinter import *  
import serial

Hello_Back = "Hello LoRa"
Validation_Index = 0

# Declaration and initialization of the serial port. Use ls /dev/tty* command in your terminal in order to find the corresponding serial port and then replace it in the port field    
ser = serial.Serial( port='/dev/ttyUSB0', 
                     baudrate=9600,
                     parity=serial.PARITY_NONE,
                     stopbits=serial.STOPBITS_ONE,
                     bytesize=serial.EIGHTBITS,
                     timeout=1
                    )

# This function allows you to receive messages coming from LoRa32u4 II through LoRa wireless     
def Receiving_Message():
    GUI.after(50, Receiving_Message)  # Receiving_Message function is repeatedly executed every 50 ms   
    if ( ser.in_waiting > 0 ):
        Data_Serial = ser.readline()  # Read data from serial port 
        Data = str(Data_Serial[1:len(Data_Serial)])
        RM_Box.configure(state="normal")  # Enable the RM_Box to write the received message
        RM_Box.delete(0, END)
        RM_Box.insert(END, Data)
        RM_Box.configure(state="disabled")  # Disable the RM_Box once you finish
        print("The received message is : ",Data)  # Print the received message
        if ( Data == "Hello Dorji" ):
            ser.write(str.encode(Hello_Back))  # Sending the answer message to LoRa32u4 II (say hello back) 

# By clicking the SM_Button, this function changes the value of Validation Index for sending the message you entered to LoRa32u4 II through LoRa wireless    
def Sending_Message_Validation():
    global Validation_Index
    if ( len(SM_Box.get()) > 0 ):
        Validation_Index = 1

# This function allows you to send the message you entered to LoRa32u4 II through LoRa wireless  
def Sending_Message():
    WindowApp.after(2000, Sending_Message)  # Sending_Message function is repeatedly executed every 2 seconds
    global Validation_Index
    if ( Validation_Index == 1 ):
        ser.write(str.encode(SM_Box.get()))  # Write data to serial port
        Validation_Index = 0 

# Creating a simple GUI using tkinter module. This GUI contains three kinds of widgets : a label, two text boxes (the first one for diplaying the received message coming from LoRa32u4 II, and second one for typing the message you want to send to LoRa32u4 II) and a button to hit in order to send your message once you finish entering it       
GUI = Tk()  # Creating GUI
GUI.title("GUI")  # Choose a title for the GUI 
RM_Label = Label(GUI, text="Received Message from LoRa32u4 II", height=2, width=40, font="fixedsys", bg="#0000ff", fg="#ffffff")  # Label above the received message text box 
RM_Label.pack(padx=0,pady=14)  # Put the label of the received message text box inside the frame of GUI
RM_Box = Entry(GUI, justify="center", width=40)  # Creating text box for visualizing the received message from LoRa32u4 II 
RM_Box.configure(state="disabled")  # Received message text box must be disabled. We enable this text box just when Dorji DRF1276DM receives a message that we want to visualize    
RM_Box.pack(ipady=3)  # Put the received message text box inside the frame of GUI
SM_button = Button(GUI, text="Sending Message", command=Sending_Message_Validation, height=2, width=40, font="fixedsys", bg="#0000ff", fg="#ffffff")  # Creating sending message button
SM_button.pack(padx=0,pady=14)  # Put the sending message button inside the frame of GUI
SM_Box = Entry(GUI, justify="center", width=40)  # Creating text box for typing the message to send to LoRa32u4 II
SM_Box.pack(ipady=3)  # Put the text box of message to send inside the frame of GUI
GUI.geometry("400x200+350+210")  # Choose the sizes of the GUI and move its position on the screen  
GUI.configure(bg="#d1e0e0")  # Choose the background color of GUI        

Receiving_Message()
Sending_Message()
GUI.mainloop()  # Infinite loop to run the GUI. It waits for an event to occur and process the event as long as the GUI is not closed