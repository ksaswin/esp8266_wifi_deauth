#include <ESP8266WiFi.h>


class Sniffer {
  private:
    // TODO: Also store all access points in a list
    int WIFI_LED;
    int detected_access_points_num = 0;
    int aps_list_index = -1;

    // Returns the human readable encryption name
    String get_encryption_type_name(uint8_t encryptionType) {    
      String encryptionName;

      // Source: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/scan-class.html#encryptiontype
      switch(encryptionType) {
        case ENC_TYPE_WEP:
          encryptionName = "WEP";
          break;
        case ENC_TYPE_TKIP:
          encryptionName = "WPA / PSK";
          break;
        case ENC_TYPE_CCMP:
          encryptionName = "WPA2 / PSK";
          break;
        case ENC_TYPE_NONE:
          encryptionName = "Open network";
          break;
        case ENC_TYPE_AUTO:
          encryptionName = "WPA / WPA2 /PSK";
          break;
        default:
          encryptionName = " - ";
      }

      return encryptionName;
    }

    // Setup ESP8266 in Station Mode to scan for available networks
    void station_mode_wifi_setup() {
      Serial.println("Starting WiFi Station mode setup...");
      digitalWrite(WIFI_LED, LOW);

      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      delay(100);

      digitalWrite(WIFI_LED, HIGH);
      Serial.println("WiFi Station mode setup done.\n");
    }

    // Disable ESP8266 scanning
    void set_wifi_off_mode() {
      WiFi.mode(WIFI_OFF);
    }

    void check_for_new_network() {
      Serial.println("Looking for a new network");
    }

  public:
    // Default constructor
    Sniffer () {
      WIFI_LED = 2;
    }

    // Parameterized constructor
    Sniffer(int led_pin) {
      WIFI_LED = led_pin;
    }

    int get_detected_access_points_num() {
      return detected_access_points_num;
    }

    // Prints the access point info to the Serial monitor
    void list_access_points() {
      if (detected_access_points_num == 0) {
        Serial.println("Could not find any networks.");

        return;
      }

      String ssid;
      uint8_t encryptionType;
      int32_t RSSI;
      uint8_t* BSSID;
      int32_t channel;
      bool isHidden;

      Serial.print(detected_access_points_num);
      Serial.println(" Access Points found.\n");

      for (int i = 0; i < detected_access_points_num; i++) {
        WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);

        String encryptionName = get_encryption_type_name(encryptionType);

        Serial.printf("%s\n  MAC: %s\n  Channel: %d\n  Signal Strength: %d dBm\n", ssid.c_str(), WiFi.BSSIDstr(i).c_str(), channel, RSSI);
        Serial.printf("  Encryption Type: %s\n  Network Hidden status: %s\n\n", encryptionName.c_str(), isHidden ? "Hidden network" : "Not hidden network");
      }
    }

    // Scan and list all available access points
    void sniff_access_points() {
      station_mode_wifi_setup();

      Serial.println("Scanning for networks...");

      detected_access_points_num = WiFi.scanNetworks();
      Serial.println("Network scanning done.\n");
      set_wifi_off_mode();

      list_access_points();
    }

    // Scroll through Access Points
    String scroll_to_next_access_point() {
      if (detected_access_points_num == 0) {
        aps_list_index = -1;

        return "No access points";
      }

      if (aps_list_index == detected_access_points_num) {
        aps_list_index = 0;
      } else {
        aps_list_index++;
      }

      if (aps_list_index == detected_access_points_num) {
        return "Exit";
      }

      return WiFi.BSSIDstr(aps_list_index);
    }

    int confirm_ap_selection() {
      if (aps_list_index == detected_access_points_num) {
        return -1;
      }

      Serial.println("Confirming Access Point selection.");
      Serial.println(WiFi.BSSIDstr(aps_list_index));

      return 0;
    }
};