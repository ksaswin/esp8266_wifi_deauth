#include <ESP8266WiFi.h>


class Sniffer {
  // TODO: Also store all access points in a list
  // TODO: Only print the access points list if there was a change from the stored list
  int WIFI_LED;
  int detected_access_points_num;

  // Returns the human readable encryption name
  String get_encryption_type_name(uint8_t encryptionType) {    
    String encryptionName;

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

  // Prints the access point info to the Serial monitor
  void list_access_points(int clients_num) {
    if (clients_num == 0) {
      Serial.println("Could not find any networks.");

      return;
    }

    String ssid;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;

    Serial.print(clients_num);
    Serial.println(" Access Points found.\n");

    for (int i = 0; i < clients_num; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);

      String encryptionName = get_encryption_type_name(encryptionType);

      Serial.printf("%s\n  Channel: %d\n  Signal Strength: %d dBm\n", ssid.c_str(), channel, RSSI);
      Serial.printf("  Encryption Type: %s\n  Network Hidden status: %s\n\n", encryptionName.c_str(), isHidden ? "Hidden network" : "Not hidden network");
    }
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

    // Setup ESP8266 in Station Mode to scan for available networks
    void station_mode_wifi_setup() {
      Serial.println("Starting WiFi Station mode setup...");
      digitalWrite(WIFI_LED, LOW);

      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      delay(100);

      digitalWrite(WIFI_LED, HIGH);
      Serial.println("WiFi Station mode setup done.");
    }

    // Scan and list all available access points
    void sniff_access_points() {
      Serial.println("Scanning for networks...");

      // int clients_num = WiFi.scanNetworks();
      detected_access_points_num = WiFi.scanNetworks();
      Serial.println("Network scanning done.");

      // list_access_points(clients_num);
      list_access_points(detected_access_points_num);
    }
};