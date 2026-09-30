# Gorlock firmware

PlatformIO + Arduino for early ESP32 bring-up (2× N20 drive, 4× line + 2× IR stubs, edge-avoid + seek).

**MCU:** ESP32-WROOM-32 — PlatformIO `board = esp32dev` (standard WROOM-32 DevKit target).

```bash
cd firmware
pio run                 # build
pio run -t upload       # flash (set upload_port if needed)
pio device monitor      # 115200 baud
```

Pin map: `include/pins.h` (all values TBD defaults). Modules: `motors`, `sensors`, `behavior`, `debug`.
