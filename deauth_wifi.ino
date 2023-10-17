#include "Sniffer.h"

#define BAUD_RATE 9600
#define WIFI_LED 2

Sniffer ap_sniffer(WIFI_LED);

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(WIFI_LED, OUTPUT);

  ap_sniffer.station_mode_wifi_setup();
}

void loop() {
  ap_sniffer.sniff_access_points();

  Serial.println("\n");
  delay(100);
}
