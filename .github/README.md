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

2. **Clone This Repository**:

   - Open a terminal or command prompt.
   - Navigate to your desired directory.
   - Clone the repository using the following command:
     ```sh
     git clone https://github.com/torkzz/Deauth-Esp8266-oled
     ```
   - Navigate into the cloned repository:
     ```sh
     cd Deauth-Esp8266-oled
     ```

3. **Open the Project in PlatformIO**:

   - Open Visual Studio Code.
   - Click on the PlatformIO icon in the sidebar.
   - Click on "Open Project".
   - Navigate to the cloned repository directory and open it.

4. **Build and Upload**:
   - Connect your ESP8266 microcontroller to your computer via USB.
   - In PlatformIO, click on the "PlatformIO: Build" button to compile the code.
   - Once the build is successful, click on the "PlatformIO: Upload" button to upload the code to the ESP8266.
   - Monitor the serial output by clicking on the "PlatformIO: Serial Monitor" button.

## Usage

Once the code is uploaded, the ESP8266 will start scanning for Wi-Fi networks. The OLED display will show the SSIDs and signal strengths of the found networks. The flash button can be used to toggle between the sun and moon icons on the display. The device will automatically avoid deauthenticating any networks listed in the SSID exception list.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request with your improvements.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
