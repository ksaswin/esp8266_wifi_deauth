#include "Sniffer.h"

Sniffer ap_sniffer;

class ModeConfigurator {
  private:
    String available_modes[3] = { "SCAN_MODE", "SELECT_MODE", "DEAUTH_ATTACK_MODE" };
    int mode_index = 0;
    String current_selected_mode = "SCAN_MODE";

  public:
    String get_current_mode() {
      return current_selected_mode;
    }

    int get_mode_index() {
      return mode_index;
    }

    void reset_mode_to_default() {
      current_selected_mode = "";
    }

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
      current_selected_mode = available_modes[mode_index];

      Serial.print("Confirming action: ");
      Serial.println(available_modes[mode_index]);

      switch(mode_index) {
        case 0: // SCAN MODE
          ap_sniffer.sniff_access_points();
          Serial.println("\n");
          break;
        case 1: // SELECT_MODE
          // ap_sniffer.list_access_points();
          if (ap_sniffer.get_detected_access_points_num() == 0) {
            reset_mode_to_default();
            break;
          }

          Serial.println("\nSelect an Access Point from the list:");
          Serial.println("\n");
          break;
        case 2: // DEAUTH ATTACK MODE
          Serial.println("Deauth attack not implemented yet.");
          break;
        default:
          Serial.println("Invalid command");
      }
    }

    void scroll_ap_list() {
      String option = ap_sniffer.scroll_to_next_access_point();

      Serial.println(option);
    }

    void confirm_ap_selection() {
      int confirmation = ap_sniffer.confirm_ap_selection();

      if (confirmation == -1) {
        reset_mode_to_default();
        // scroll_to_next_mode();
      }
    }
};