#include "ModeConfigurator.h"

#define BAUD_RATE 9600
#define WIFI_LED 2
#define SCROLLER_BTN D2
#define CONFIRM_BTN D4


ModeConfigurator mode_config;

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(WIFI_LED, OUTPUT);
  digitalWrite(WIFI_LED, HIGH);

  pinMode(SCROLLER_BTN, INPUT);
  pinMode(CONFIRM_BTN, INPUT);
}

void loop() {
  int scroller_button = digitalRead(SCROLLER_BTN);
  int confirm_button = digitalRead(CONFIRM_BTN);

  if (confirm_button == 1) {
    mode_config.confirm_mode_action();
  }

  if (scroller_button == 1) {
    mode_config.scroll_to_next_mode();
  }

  delay(200);
}
