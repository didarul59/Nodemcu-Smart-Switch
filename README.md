# Remote Control Using NodeMCU and 5V DC Relay Module

## Overview

This project demonstrates how to create a remote control system using a NodeMCU ESP8266 microcontroller and a 5V DC relay module to switch devices on and off. The system connects to a WiFi network and is controlled via the Blynk IoT platform. The setup includes mechanisms to ensure stable operation by periodically checking the WiFi and Blynk connections and restarting the NodeMCU if necessary.

## Components Required

- **NodeMCU ESP8266**: A microcontroller with built-in WiFi.
- **5V DC Relay Module**: Used for switching the load.
- **Load**: The device to be controlled (e.g., a PC).
- **External Power Supply**: If required, depending on the load.
- **Connecting Wires**: To make the necessary connections.

## Circuit Diagram

1. **NodeMCU Connections**:
   - Connect the **D2 pin** of the NodeMCU to the **IN pin** of the relay module.
   - Connect the **GND pin** of the NodeMCU to the **GND pin** of the relay module.
   - Connect the **3V3 pin** of the NodeMCU to the **VCC pin** of the relay module.

2. **Relay Module Connections**:
   - Connect the **COM** terminal of the relay module to one terminal of the device's power switch.
   - Connect the **NO (Normally Open)** terminal of the relay module to the other terminal of the device's power switch.
   - **NC (Normally Closed)** is not used in this setup.

## How It Works

### WiFi and Blynk Initialization

- The NodeMCU connects to the specified WiFi network and initializes the Blynk connection using your provided credentials and Blynk authentication token.

### Relay Control

- The relay is connected to pin D2 of the NodeMCU. The relay state is controlled through a Blynk virtual pin (V0). You can send commands to this pin via the Blynk app to turn the relay on or off, thereby controlling the connected device.

### WiFi and Blynk Connection Management

- The code periodically checks the WiFi and Blynk connections every 30 seconds. If either connection is lost, the NodeMCU attempts to reconnect.
- If the NodeMCU fails to reconnect to WiFi within 1 minute, it restarts itself to attempt reconnection afresh.

### Periodic Restart

- The NodeMCU is set to restart every 6 hours to ensure continued stability and handle any potential issues that may arise from prolonged operation.

## Additional Features

- The project includes mechanisms to force restart the NodeMCU if it fails to reconnect to WiFi after an extended period.
- Using a relay module allows for safe and reliable switching of high-power devices.

## Setup Instructions

1. **Install Arduino IDE**: Ensure you have the Arduino IDE installed on your computer.
2. **Install ESP8266 Board**: Add the ESP8266 board to the Arduino IDE via the Board Manager.
3. **Install Blynk Library**: Install the Blynk library from the Library Manager in the Arduino IDE.
4. **Upload Code**: Use the provided code to configure the NodeMCU. Update the WiFi credentials and Blynk authentication token in the code before uploading.
5. **Connect Hardware**: Follow the circuit diagram to connect the NodeMCU and the relay module.
6. **Test the Setup**: Power on the NodeMCU and use the Blynk app to control the relay. Ensure that the relay switches the connected device on and off as expected.

By following these instructions, you can create a reliable remote control system for your devices using NodeMCU and a 5V DC relay module, controlled through the Blynk IoT platform.
