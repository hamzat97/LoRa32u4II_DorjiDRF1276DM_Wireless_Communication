// Include LoRa library    
#include <LoRa.h>

#define SS 8
#define RESET 4
#define DIO0 7
#define Frequency 868E6
#define yes true    
#define SBW 250E3

byte Net_ID = 0x2D;     
byte ID_Msg = 0;
byte Sender;
char space = ' ';
int DEC_SUM;
int SUM_NOR;
String Data;
int Rssi;
int Snr; 
long Last_Time = 0;        
int Time_Range = 20000;

void setup() {  
 Serial.begin(9600);  // Set the communication rate in 9600 baud for serial communication  
 LoRa.setPins(SS,RESET,DIO0);  // Override the default pins used by the LoRa library. This call must be before LoRa.begin() and it is optional and only needs to be used if you need to change the default pins used (SS -> 10, RESET -> 9, DIO0 -> 2)  
 // Initialize LoRa module with the specified frequency, which is 868 MHz
 if (!LoRa.begin(Frequency,yes)) {
                                   Serial.println("Failed to initialize LoRa module !!!");
                                   while(true);  
                                 };
 LoRa.setSpreadingFactor(9);  // Change the spreading factor of the radio, defaults to 7
 LoRa.setSignalBandwidth(SBW);  // Change the signal bandwidth of the radio (in Hz), defaults to 125 KHz                                    
}

void loop() {
 String Message = "Hello Dorji"; 
 DEC_SUM = Sum(Message);
 SUM_NOR = Normalize(DEC_SUM);
 ID_Msg = Request_ByteID(SUM_NOR);
 Sending_Message(Message,ID_Msg); 
 Last_Time = millis();
 while ( millis() - Last_Time <= Time_Range ) { Receive_Message(); }  // Listening mode for 20 seconds 
}

// Receiving packet function
void Receive_Message() {
 int packetSize = LoRa.parsePacket();  // Check if a packet has been received. Returns the packet size in bytes or 0 if no packet was received
 if (packetSize) { 
                   Sender = LoRa.read();  // Read the first byte 
                   while (LoRa.available()) {
                                              Data += (char)LoRa.read();  // Read the packet
                                            }
                   // Check the packet sender                          
                   if ( Sender == 0x2D ) { 
                      // Visualize the received message in the serial monitor     
                      Data.remove(Data.length()-1); 
                      Serial.print("There is a message from Dorji DRF1276DM : ");                                    
                      Serial.println(Data);
                      // Read the estimated RSSI packet in dBm
                      Serial.print("The estimated RSSI packet is : ");
                      Serial.print(LoRa.packetRssi());
                      Serial.println(" dBm");
                      // Read the estimated SNR packet in decibels (dB)
                      Serial.print("The estimated SNR packet is : ");
                      Serial.print(LoRa.packetSnr());
                      Serial.println(" dB");
                   }  
                   else { Serial.println("That's not for me !!!"); }                         
                   Data = "";
                }
}         

// Sending packet function
void Sending_Message( String MSG, int MSG_ID ) {  
 LoRa.beginPacket();  // Start the sequence of sending a packet                  
 LoRa.write(Net_ID);  // Write net_ID byte to the packet              
 LoRa.write(MSG_ID);  // Write msg_ID byte to the packet
 MSG = MSG + space; 
 LoRa.print(MSG);  // Write the message to send "Hello Dorji"                  
 LoRa.endPacket();  // End the sequence of sending a packet              
}

// Decimal sum of the bytes of message to send 
int Sum ( String Message ) {
 int SUM = 0;
 for (int w=0;w<Message.length();w++) {  SUM += byte(Message[w]);  }
 return SUM;
}

// Normalization function
int Normalize ( int S ) {
 if ( S > 288 ) {
 do { 
     S = S - 256;
    } while( S > 288 );   
}
 return S;
}

// normalization function
int Request_ByteID ( int N ) {
 switch(N) {
            case 0 : return 32; break;
            case 1 : return 31; break;
            case 2 : return 30; break;
            case 3 : return 29; break;
            case 4 : return 28; break;
            case 5 : return 27; break;
            case 6 : return 26; break;
            case 7 : return 25; break;
            case 8 : return 24; break;
            case 9 : return 23; break;
            case 10 : return 22; break;
            case 11 : return 21; break;
            case 12 : return 20; break;
            case 13 : return 19; break;
            case 14 : return 18; break;
            case 15 : return 17; break;
            case 16 : return 16; break;
            case 17 : return 15; break;
            case 18 : return 14; break;
            case 19 : return 13; break;
            case 20 : return 12; break;
            case 21 : return 11; break;
            case 22 : return 10; break;
            case 23 : return 9; break;
            case 24 : return 8; break;
            case 25 : return 7; break;
            case 26 : return 6; break;
            case 27 : return 5; break;
            case 28 : return 4; break;
            case 29 : return 3; break;
            case 30 : return 2; break;
            case 31 : return 1; break;
            case 32 : return 0; break;
            case 33 : return 255; break;
            case 34 : return 254; break;
            case 35 : return 253; break;
            case 36 : return 252; break;
            case 37 : return 251; break;
            case 38 : return 250; break;
            case 39 : return 249; break;
            case 40 : return 248; break;
            case 41 : return 247; break;
            case 42 : return 246; break;
            case 43 : return 245; break;
            case 44 : return 244; break;
            case 45 : return 243; break;
            case 46 : return 242; break;
            case 47 : return 241; break;
            case 48 : return 240; break;
            case 49 : return 239; break;
            case 50 : return 238; break;
            case 51 : return 237; break;
            case 52 : return 236; break;
            case 53 : return 235; break;
            case 54 : return 234; break;
            case 55 : return 233; break;
            case 56 : return 232; break;
            case 57 : return 231; break;
            case 58 : return 230; break;
            case 59 : return 229; break;
            case 60 : return 228; break;
            case 61 : return 227; break;
            case 62 : return 226; break;
            case 63 : return 225; break;
            case 64 : return 224; break;
            case 65 : return 223; break;
            case 66 : return 222; break;
            case 67 : return 221; break;
            case 68 : return 220; break;
            case 69 : return 219; break;
            case 70 : return 228; break;
            case 71 : return 217; break;
            case 72 : return 216; break;
            case 73 : return 215; break;
            case 74 : return 214; break;
            case 75 : return 213; break;
            case 76 : return 212; break;
            case 77 : return 211; break;
            case 78 : return 210; break;
            case 79 : return 209; break;
            case 80 : return 208; break;
            case 81 : return 207; break;
            case 82 : return 206; break;
            case 83 : return 205; break;
            case 84 : return 204; break;
            case 85 : return 203; break;
            case 86 : return 202; break;
            case 87 : return 201; break;
            case 88 : return 200; break;
            case 89 : return 199; break;
            case 90 : return 198; break;
            case 91 : return 197; break;
            case 92 : return 196; break;
            case 93 : return 195; break;
            case 94 : return 194; break;
            case 95 : return 193; break;
            case 96 : return 192; break;
            case 97 : return 191; break;
            case 98 : return 190; break;
            case 99 : return 189; break;
            case 100 : return 188; break;
            case 101 : return 187; break;
            case 102 : return 186; break;
            case 103 : return 185; break;
            case 104 : return 184; break;
            case 105 : return 183; break;
            case 106 : return 182; break;
            case 107 : return 181; break;
            case 108 : return 180; break;
            case 109 : return 179; break;
            case 110 : return 178; break;
            case 111 : return 177; break;
            case 112 : return 176; break;
            case 113 : return 175; break;
            case 114 : return 174; break;
            case 115 : return 173; break;
            case 116 : return 172; break;
            case 117 : return 171; break;
            case 118 : return 170; break;
            case 119 : return 169; break;
            case 120 : return 168; break;
            case 121 : return 167; break;
            case 122 : return 166; break;
            case 123 : return 165; break;
            case 124 : return 164; break;
            case 125 : return 163; break;
            case 126 : return 162; break;
            case 127 : return 161; break;
            case 128 : return 160; break;
            case 129 : return 159; break;
            case 130 : return 158; break;
            case 131 : return 157; break;
            case 132 : return 156; break;
            case 133 : return 155; break;
            case 134 : return 154; break;
            case 135 : return 153; break;
            case 136 : return 152; break;
            case 137 : return 151; break;
            case 138 : return 150; break;
            case 139 : return 149; break;
            case 140 : return 148; break;
            case 141 : return 147; break;
            case 142 : return 146; break;
            case 143 : return 145; break;
            case 144 : return 144; break;
            case 145 : return 143; break;
            case 146 : return 142; break;
            case 147 : return 141; break;
            case 148 : return 140; break;
            case 149 : return 139; break;
            case 150 : return 138; break;
            case 151 : return 137; break;
            case 152 : return 136; break;
            case 153 : return 135; break;
            case 154 : return 134; break;
            case 155 : return 133; break;
            case 156 : return 132; break;
            case 157 : return 131; break;
            case 158 : return 130; break;
            case 159 : return 129; break;
            case 160 : return 128; break;
            case 161 : return 127; break;
            case 162 : return 126; break;
            case 163 : return 125; break;
            case 164 : return 124; break;
            case 165 : return 123; break;
            case 166 : return 122; break;
            case 167 : return 121; break;
            case 168 : return 120; break;
            case 169 : return 119; break;
            case 170 : return 118; break;
            case 171 : return 117; break;
            case 172 : return 116; break;
            case 173 : return 115; break;
            case 174 : return 114; break;
            case 175 : return 113; break;
            case 176 : return 112; break;
            case 177 : return 111; break;
            case 178 : return 110; break;
            case 179 : return 109; break;
            case 180 : return 108; break;
            case 181 : return 107; break;
            case 182 : return 106; break;
            case 183 : return 105; break;
            case 184 : return 104; break;
            case 185 : return 103; break;
            case 186 : return 102; break;
            case 187 : return 101; break;
            case 188 : return 100; break;
            case 189 : return 99; break;
            case 190 : return 98; break;
            case 191 : return 97; break;
            case 192 : return 96; break;
            case 193 : return 95; break;
            case 194 : return 94; break;
            case 195 : return 93; break;
            case 196 : return 92; break;
            case 197 : return 91; break;
            case 198 : return 90; break;
            case 199 : return 89; break;
            case 200 : return 88; break;
            case 201 : return 87; break;
            case 202 : return 86; break;
            case 203 : return 85; break;
            case 204 : return 84; break;
            case 205 : return 83; break;
            case 206 : return 82; break;
            case 207 : return 81; break;
            case 208 : return 80; break;
            case 209 : return 79; break;
            case 210 : return 78; break;
            case 211 : return 77; break;
            case 212 : return 76; break;
            case 213 : return 75; break;
            case 214 : return 74; break;
            case 215 : return 73; break;
            case 216 : return 72; break;
            case 217 : return 71; break;
            case 218 : return 70; break;
            case 219 : return 69; break;
            case 220 : return 68; break;
            case 221 : return 67; break;
            case 222 : return 66; break;
            case 223 : return 65; break;
            case 224 : return 64; break;
            case 225 : return 63; break;
            case 226 : return 62; break;
            case 227 : return 61; break;
            case 228 : return 60; break;
            case 229 : return 59; break;
            case 230 : return 58; break;
            case 231 : return 57; break;
            case 232 : return 56; break;
            case 233 : return 55; break;
            case 234 : return 54; break;
            case 235 : return 53; break;
            case 236 : return 52; break;
            case 237 : return 51; break;
            case 238 : return 50; break;
            case 239 : return 49; break;
            case 240 : return 48; break;
            case 241 : return 47; break;
            case 242 : return 46; break;
            case 243 : return 45; break;
            case 244 : return 44; break;
            case 245 : return 43; break;
            case 246 : return 42; break;
            case 247 : return 41; break;
            case 248 : return 40; break;
            case 249 : return 39; break;
            case 250 : return 38; break;
            case 251 : return 37; break;
            case 252 : return 36; break;
            case 253 : return 35; break;
            case 254 : return 34; break;
            case 255 : return 33; break;
            case 256 : return 32; break;
            case 257 : return 31; break;
            case 258 : return 30; break;
            case 259 : return 29; break;
            case 260 : return 28; break;
            case 261 : return 27; break;
            case 262 : return 26; break;
            case 263 : return 25; break;
            case 264 : return 24; break;
            case 265 : return 23; break;
            case 266 : return 22; break;
            case 267 : return 21; break;
            case 268 : return 20; break;
            case 269 : return 19; break;
            case 270 : return 18; break;
            case 271 : return 17; break;
            case 272 : return 16; break;
            case 273 : return 15; break;
            case 274 : return 14; break;
            case 275 : return 13; break;
            case 276 : return 12; break;
            case 277 : return 11; break;
            case 278 : return 10; break;
            case 279 : return 9; break;
            case 280 : return 8; break;
            case 281 : return 7; break;
            case 282 : return 6; break;
            case 283 : return 5; break;
            case 284 : return 4; break;
            case 285 : return 3; break;
            case 286 : return 2; break;
            case 287 : return 1; break;
            case 288 : return 0; break;
           }
}
