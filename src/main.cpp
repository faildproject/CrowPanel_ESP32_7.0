#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;
  lgfx::Touch_GT911 _touch_instance;
  lgfx::Light_PWM _light_instance;

  LGFX(void) {
    // Panel-Config
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width = 800;
      cfg.memory_height = 480;
      cfg.panel_width = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }

    // We have PSRAM
    {
      auto cfg = _panel_instance.config_detail();
      cfg.use_psram = 1;
      _panel_instance.config_detail(cfg);
    }

    // Bus-Config
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      cfg.pin_d0 = GPIO_NUM_15; // B0
      cfg.pin_d1 = GPIO_NUM_7;  // B1
      cfg.pin_d2 = GPIO_NUM_6;  // B2
      cfg.pin_d3 = GPIO_NUM_5;  // B3
      cfg.pin_d4 = GPIO_NUM_4;  // B4

      cfg.pin_d5 = GPIO_NUM_9;  // G0
      cfg.pin_d6 = GPIO_NUM_46; // G1
      cfg.pin_d7 = GPIO_NUM_3;  // G2
      cfg.pin_d8 = GPIO_NUM_8;  // G3
      cfg.pin_d9 = GPIO_NUM_16; // G4
      cfg.pin_d10 = GPIO_NUM_1; // G5

      cfg.pin_d11 = GPIO_NUM_14; // R0
      cfg.pin_d12 = GPIO_NUM_21; // R1
      cfg.pin_d13 = GPIO_NUM_47; // R2
      cfg.pin_d14 = GPIO_NUM_48; // R3
      cfg.pin_d15 = GPIO_NUM_45; // R4

      cfg.pin_henable = GPIO_NUM_41;
      cfg.pin_vsync = GPIO_NUM_40;
      cfg.pin_hsync = GPIO_NUM_39;
      cfg.pin_pclk = GPIO_NUM_0;
      cfg.freq_write = 15000000;

      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch = 40;

      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch = 13;

      cfg.pclk_active_neg = 1;
      cfg.de_idle_high = 0;
      cfg.pclk_idle_high = 0;

      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);

    // Backlight
    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = GPIO_NUM_2;
      _light_instance.config(cfg);
    }
    _panel_instance.light(&_light_instance);

    // Integrate Touch
    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.y_min = 0;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      // I2C connection
      cfg.pin_sda = GPIO_NUM_19;
      cfg.pin_scl = GPIO_NUM_20;
      cfg.pin_int = GPIO_NUM_NC;
      cfg.pin_rst = GPIO_NUM_NC;
      cfg.x_max = 800;
      cfg.y_max = 480;
      cfg.freq = 100000;
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }
};

LGFX lcd;

void setup() {

  Serial.begin(9600);
  Serial.println("Start LCD");
  lcd.begin();
  lcd.setTextSize(2);
  lcd.fillScreen(TFT_RED);
}

lgfx::v1::touch_point_t tp;
// lgfx::touch_point_t points[5]; // Array für 5 Touch-Punkte

void loop() {
  if (lcd.getTouch(&tp)) {
    Serial.printf("%d:%d\r\n", tp.x, tp.y);
    lcd.setCursor(200, 200);
    lcd.setBrightness(map(tp.x, 0, 800, 0, 255));
    lcd.printf("%d:%d\r\n", tp.x, tp.y);
    lcd.qrcode("www.il-kg.de", 0, 0, 100);
  }
  // if (lcd.getTouch(points, 5)) {
  //   for (int i = 0; i < 5; ++i) {
  //     // Verarbeite jeden Touch-Punkt
  //     if (points[i].x != -1 &&
  //         points[i].y != -1) { // Überprüfe, ob der Punkt gültig ist
  //       Serial.printf("Touch %d at: %d, %d\n", i, points[i].x, points[i].y);
  //     }
  //   }
  // }
}
