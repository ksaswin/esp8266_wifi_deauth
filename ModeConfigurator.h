#include "Sniffer.h"

Sniffer ap_sniffer;

class ModeConfigurator {
  String available_modes[3] = { "SCAN_MODE", "LIST_MODE", "DEAUTH_ATTACK_MODE" };
  int mode_index = 0;

  public:
    void scroll_to_next_mode() {
      if (mode_index == ((sizeof(available_modes) / sizeof(available_modes[0])) - 1)) {
        mode_index = 0;
      } else {
        mode_index++;
      }

      Serial.print("Mode: ");
      Serial.println(available_modes[mode_index]);
    }

    void confirm_mode_action() {
      Serial.print("Confirming action: ");
      Serial.println(available_modes[mode_index]);

      switch(mode_index) {
        case 0:
          ap_sniffer.sniff_access_points();
          Serial.println("\n");
          break;
        case 1:
          ap_sniffer.list_access_points();
          Serial.println("\n");
          break;
        case 3:
          Serial.println("Deauth attack not implemented yet.");
      }
    }
};