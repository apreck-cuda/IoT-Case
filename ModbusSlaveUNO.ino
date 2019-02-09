#include <AFMotor.h>
#include <Ethernet.h>
#include <SPI.h>

/////////Motor Definition
AF_DCMotor m1(2);

//Network configuration ///Change according your needs
// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };  
//the IP address for the shield:
byte ip[] = { 10, 10, 5, 110 };    
// the router's gateway address:
byte gateway[] = { 10, 10, 5, 254 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };
///////////////////

////Modbus configuratiuon:

int ModbusTCP_port = 502;
//////// Required for Modbus TCP / IP 
#define maxHoldingRegister 20
#define MB_FC_NONE 0
#define MB_FC_READ_REGISTERS 3 //implemented
#define MB_FC_WRITE_REGISTER 6 //implemented
#define MB_FC_WRITE_MULTIPLE_REGISTERS 16 //implemented
//
// MODBUS Error Codes
//
#define MB_EC_NONE 0
#define MB_EC_ILLEGAL_FUNCTION 1
#define MB_EC_ILLEGAL_DATA_ADDRESS 2
#define MB_EC_ILLEGAL_DATA_VALUE 3
#define MB_EC_SLAVE_DEVICE_FAILURE 4
//
// MODBUS MBAP offsets
//
#define MB_TCP_TID 0
#define MB_TCP_PID 2
#define MB_TCP_LEN 4
#define MB_TCP_UID 6
#define MB_TCP_FUNC 7
#define MB_TCP_REGISTER_START 8
#define MB_TCP_REGISTER_NUMBER 10

byte ByteArray[260];
unsigned int MBHoldingRegister[maxHoldingRegister];


//////////////////////////////////////////////////////////////////////////

EthernetServer MBServer(ModbusTCP_port);

void setup() {
 Serial.begin(9600);
 delay(100);
 Serial.print("Initializing Connection!");
 delay(100) ;
 Ethernet.begin(mac, ip, gateway);
 Serial.print("The IP Address of Modbusslave is: ");
 Serial.println(Ethernet.localIP()) ;
 Serial.print("The IP Gateway of Modbusslave is: ");
 Serial.println(Ethernet.gatewayIP());
 Serial.print("The IP Subnet of Modbusslave is: ");
 Serial.println(Ethernet.subnetMask());
 MBServer.begin();
 Serial.println("Staring MB Server Listner ");
 Serial.print("Slave Modbus TCP/IP is listing on port: ");
 Serial.println(String(ModbusTCP_port));
 Serial.println("Modbus TCP/IP Online");

}


void loop() {


 // Check if a client has connected // Modbus TCP/IP
 EthernetClient client = MBServer.available();
 if (!client) {
 return;
 }
 

 boolean flagClientConnected = 0;
 byte byteFN = MB_FC_NONE;
 int Start;
 int WordDataLength;
 int ByteDataLength;
 int MessageLength;
 
 // Modbus TCP/IP
 while (client.connected()) {
 
 if(client.available())
 {
 flagClientConnected = 1;
 int i = 0;
 while(client.available())
 {
 ByteArray[i] = client.read();
 i++;
 }

 client.flush();



///// code here

 ///////// Holding Register [0] A [9] = 10 Holding Registers Writing
 
 MBHoldingRegister[0] = random(19,35);
 MBHoldingRegister[1] = random(1000,2000);
 MBHoldingRegister[2] = random(0,5);
 MBHoldingRegister[3] = random(0,12);
 MBHoldingRegister[4] = random(0,120);
 MBHoldingRegister[5] = random(220,235);
 MBHoldingRegister[6] = random(10,54);
 MBHoldingRegister[7] = random(100,500);
 MBHoldingRegister[8] = random(1,12);
 MBHoldingRegister[9] = random(5,50);

 
 ///// Holding Register [10] A [19] = 10 Holding Registers Reading
 
 int Temp[10];
 
 Temp[0] = MBHoldingRegister[10];
 Temp[1] = MBHoldingRegister[11];
 Temp[2] = MBHoldingRegister[12];
 Temp[3] = MBHoldingRegister[13];
 Temp[4] = MBHoldingRegister[14];
 Temp[5] = MBHoldingRegister[15];
 Temp[6] = MBHoldingRegister[16];
 Temp[7] = MBHoldingRegister[17];
 Temp[8] = MBHoldingRegister[18];
 Temp[9] = MBHoldingRegister[19];

 /// Enable Output 14
 //digitalWrite(14, MBHoldingRegister[14] );


////Contol Servo
///Turn Forward Holding Register [10]
///Turn Backword Hloding Register [11
///Determining Register Change

//Update Morot Values:
int MotForward = Temp[0];
int MotBackward = Temp[1];
if (MotForward!=0 || MotBackward!=0) {
    Serial.println("MotorControlDetected! ");
    if (MotForward>0){
      MotBackward = 0;
      m1.setSpeed(MotForward);
      m1.run(FORWARD);
      //delay(10);
      //m1.setSpeed(128);
      //m1.run(FORWARD);
      Serial.print("MotorTurnForward: ");
      Serial.println(MotForward);
      delay(100);
    }
      else if (MotBackward>0){
      MotForward = 0;
      m1.setSpeed(MotBackward);
      m1.run(BACKWARD);
      Serial.print("MotorTurnBackword: ");
      Serial.println(MotBackward);
      delay(100);
      }
      else{
        Serial.println("Somthing went wrong - Unexpected register behavior");
      }
}

  else {
    Serial.println("All Registers are off!");
    m1.run(RELEASE);
  }



 //// debug

 for (int i = 0; i < 10; i++) {

 Serial.print("[");
 Serial.print(i);
 Serial.print("] ");
 Serial.print(Temp[i]);
 
 }
 Serial.println("");




//// end code
 

 //// rutine Modbus TCP
 byteFN = ByteArray[MB_TCP_FUNC];
 Start = word(ByteArray[MB_TCP_REGISTER_START],ByteArray[MB_TCP_REGISTER_START+1]);
 WordDataLength = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 }
 
 // Handle request

 switch(byteFN) {
 case MB_FC_NONE:
 break;
 
 case MB_FC_READ_REGISTERS: // 03 Read Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 ByteArray[8] = ByteDataLength; //Number of bytes after this one (or number of bytes of data).
 for(int i = 0; i < WordDataLength; i++)
 {
 ByteArray[ 9 + i * 2] = highByte(MBHoldingRegister[Start + i]);
 ByteArray[10 + i * 2] = lowByte(MBHoldingRegister[Start + i]);
 }
 MessageLength = ByteDataLength + 9;
 client.write((const uint8_t *)ByteArray,MessageLength);
 
 byteFN = MB_FC_NONE;
 
 break;
 
 
 case MB_FC_WRITE_REGISTER: // 06 Write Holding Register
 MBHoldingRegister[Start] = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 ByteArray[5] = 6; //Number of bytes after this one.
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength);
 byteFN = MB_FC_NONE;
 break;
 
 case MB_FC_WRITE_MULTIPLE_REGISTERS: //16 Write Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 for(int i = 0; i < WordDataLength; i++)
 {
 MBHoldingRegister[Start + i] = word(ByteArray[ 13 + i * 2],ByteArray[14 + i * 2]);
 }
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength); 
 byteFN = MB_FC_NONE;
 
 break;
 }
 }


 

}
