#include "Sniffer.h"

#define BAUD_RATE 9600
#define WIFI_LED 2
#define PUSH_BTN D2

Sniffer ap_sniffer(WIFI_LED);

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(WIFI_LED, OUTPUT);
  digitalWrite(WIFI_LED, HIGH);

  pinMode(PUSH_BTN, INPUT);
}

void loop() {
  int button = digitalRead(PUSH_BTN);

  if (button == 1) {
    ap_sniffer.sniff_access_points();
    Serial.println("\n");
  }

  delay(100);
}
