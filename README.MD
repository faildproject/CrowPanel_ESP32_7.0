# ESP32-S3 Display Control using LovyanGFX

## Projektübersicht

Dieses Projekt zeigt, wie man ein RGB-Display mit einem ESP32-S3-Board unter Verwendung der **LovyanGFX**-Bibliothek steuert, ohne zusätzliche externe Bibliotheken. Es beinhaltet die Konfiguration des Display-Panels, RGB-Bus, Touchscreen und der Hintergrundbeleuchtung sowie die Anzeige von Inhalten auf dem Display.

Basiert auf: https://www.elecrow.com/wiki/CrowPanel_ESP32_7.0-inch_with_PlatformIO.html

### Verwendete Hardware
- **ESP32-S3** (Crow Panel ESP32-S3)
- **800x480 RGB-Display**
- **GT911-Touchcontroller**
- **PWM-gesteuerte Hintergrundbeleuchtung**

### Bezug (**keine** affilate-links)
- https://www.elecrow.com/esp32-display-7-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html
- https://amzn.eu/d/6fE3Ji5

## Voraussetzungen

Stelle sicher, dass folgende Software und Bibliotheken installiert sind:
- **PlatformIO**: für die Entwicklung und das Hochladen des Codes.
- **Arduino-Framework für ESP32**: eingebunden über `platformio.ini`.
- **LovyanGFX**: als Display-Treiberbibliothek.

## PlatformIO Konfigurationsdatei (`platformio.ini`)

Die `platformio.ini`-Datei konfiguriert das Projekt so, dass es das ESP32-S3-Board verwendet und die **LovyanGFX**-Bibliothek zur Display-Ansteuerung nutzt.

Die `crow_panel_esp32-s3.json`, sowie `build_partition.csv` liegen dem Projekt bei. 

```ini
[platformio]
src_dir = src
boards_dir = boards

[env:crow_panel_esp32-s3]
platform = espressif32
platform_packages = framework-arduinoespressif32 @ https://github.com/espressif/arduino-esp32#2.0.3
framework = arduino

board = crow_panel_esp32-s3
board_build.partitions = build_partition.csv

lib_deps = 
    lovyan03/LovyanGFX@^1.1.12
```

