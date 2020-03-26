# IoT Case Project Source Code Files

## Introduction
This project is to showcase an secure connectivity solutions for IoT as well as the granular protocol control and enforcement. 
The case include an PLC simulation with Modbus based on Arduino. This sends some random generated values to HMI as well ac receive the command form HMI (HomeAssitent) to control the Windmill. Home Assistant is used as a low cost HMI solution while the Arduino including Ethernet and MotorShield is acting as PLC. Furthermore a NodeMCU was used to control the LEDs and visualize the VPN connection and active Remote Access controlled by Barracuda Solutions.

More information on the Barracuda Solutions for OT/IIoT can be found here:
https://www.barracuda.com/products/cloudgenfirewall/use_cases/internet-of-things-security

## Topology
This topology applies to the setup, while the Wind turbine PLC is connected to Secure Connector and through VPN to HQ the Remote access and Protocol Enforcement is performed on the HQ Firewall

 ![](/images/Network.PNG)

 ## Arduino PLC
 Is used to send and receive the Modbus commands. It includes the Network shield and MotorShield to control the turbine and turbine lights. 
 ![](/images/MotorShild.PNG)

## Light Controls
The light is controlled by the (HMI) HomeAssistant. The commands are send via MQTT to the NodeMCU.
The status of VPN or Access Rule for remote control are queried from the Firewall via API "###API Calls for Light Control"
 ![](/images/NodeMCU.PNG)

For any question please contact iot_cgf_team@barracuda.com
