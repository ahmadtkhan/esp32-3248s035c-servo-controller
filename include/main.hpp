#pragma once

#include <ESP323248S035.hpp>

// The ESP32-3248S035 library defines View as a pure virtual class, which acts
// as an interface between the library and application GUI code.
//
// We must define a concrete implementation of View to act as the root window
// of the target device's GUI. The content of View is application-defined.
//
// NOTE: Do NOT make any lvgl API calls from the View constructor. These must be
//       performed in the View::init() method.
class Main: public bsp::View {
public:
  Main() = default;
  ~Main() = default;

  bool init(lv_obj_t *root) override {
    if (nullptr == root) {
      root = lv_scr_act();
    }
    lv_obj_t *label = lv_label_create(root);
    lv_obj_center(label);
    lv_label_set_text(label, "Touch the screen!");
    touch_label = lv_label_create(root);
    lv_obj_align(touch_label, LV_ALIGN_BOTTOM_MID, 0, -20);
    return true;
  }


  void update(msecu32_t const now) override {
    // Example touch data display
    lv_indev_t *indev = lv_indev_get_act();
    if (indev) {
        // Read the current state directly from the input device
        lv_indev_state_t state = lv_indev_get_state(indev);
        lv_point_t point;
        lv_indev_get_point(indev, &point);

        if (state == LV_INDEV_STATE_PR) {
            lv_label_set_text_fmt(touch_label, "Touched at (%d, %d)", point.x, point.y);
        } else {
            lv_label_set_text(touch_label, "No touch detected");
        }
    }
}


  std::string title() override {
    return "Main";
  }
  private:
  lv_obj_t *touch_label = nullptr; // Declare and initialize touch_label

};
// };

Main root;
bsp::ESP323248S035C<Main> target(root);

// Main root;
//bsp::ESP323248S035C target(root); // C++17 can deduce template parameter.
// bsp::ESP323248S035C<Main> target(root); // Pre-C++17 requires explicit type.
