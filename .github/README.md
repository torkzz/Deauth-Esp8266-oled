# Wi-Fi Scanner and Deauthentication Tool

This project is a Wi-Fi scanner and deauthentication tool for the ESP8266 microcontroller, equipped with an OLED display. It scans for available Wi-Fi networks, displays their SSIDs and signal strengths on the OLED, and allows you to perform a deauthentication attack on selected networks (excluding those in the exception list).

## Features

- Scans for available Wi-Fi networks
- Displays network SSIDs and signal strengths on an OLED display
- Allows for deauthentication attacks on networks not in the exception list
- Toggle sun/moon icons with the flash button

## Hardware Requirements

- ESP8266 microcontroller (e.g., NodeMCU)
- OLED display (128x64)
- Push button connected to GPIO0

## Software Requirements

- PlatformIO IDE (for building and uploading the code)
- Required libraries: `ESP8266WiFi`, `U8g2`, `Wire`

## Installation

1. **Install PlatformIO**: 
   - Install [Visual Studio Code](https://code.visualstudio.com/).
   - Open Visual Studio Code and go to the Extensions view by clicking on the square icon in the sidebar or pressing `Ctrl+Shift+X`.
   - Search for "PlatformIO IDE" and click "Install".

2. **Create a New PlatformIO Project**:
   - Open PlatformIO IDE in Visual Studio Code.
   - Click on the PlatformIO icon in the sidebar.
   - Click "New Project".
   - Enter your project's name, select the board (e.g., "NodeMCU 1.0" for ESP8266), and the framework (select "Arduino").
   - Click "Finish".

3. **Clone This Repository**:
   - Clone this repository or download the ZIP and extract it.
   - Copy the contents into your new PlatformIO project directory, replacing the `src` folder and `platformio.ini` file.

4. **Build and Upload**:
   - Connect your ESP8266
