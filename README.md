This project aims to create a remote control system using a NodeMCU ESP8266 microcontroller and a 5V DC relay module to switch devices on and off. The system connects to a WiFi network and is controlled via the Blynk IoT platform. The setup ensures stable operation by periodically checking the WiFi and Blynk connections and restarting the NodeMCU if necessary.

Components Required
NodeMCU ESP8266: A microcontroller with built-in WiFi.
5V DC Relay Module: Used for switching the load.
Load: The device to be controlled (e.g., a PC).
External Power Supply: If required, depending on the load.
Connecting Wires: To make the necessary connections.
Circuit Diagram
NodeMCU Connections:

Connect the D2 pin of the NodeMCU to the IN pin of the relay module.
Connect the GND pin of the NodeMCU to the GND pin of the relay module.
Connect the 3V3 pin of the NodeMCU to the VCC pin of the relay module.
Relay Module Connections:

Connect the COM terminal of the relay module to one terminal of the device's power switch.
Connect the NO (Normally Open) terminal of the relay module to the other terminal of the device's power switch.
NC (Normally Closed) is not used in this setup.
