# wemos-esp8266-wifi-ap
WiFi access point or WiFi extender using low cost wemos D1 mini pro based on esp8266 chip. Using platform.io as base tool to program and burn. Supports ipv4.

# Pre-requisites
- VSCode installed
- PlatformIO (setup)[https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation]
- Wemos D1 mini pro

# How to run ?
- clone this repo
- connect wemos D1 mini pro to your local machine
- update these values in `src/main.cpp`
  - WIFI_SSID
  - WIFI_PASS
  - SOFT_AP_SSID
  - SOFT_AP_PASS
- build/compile the code (hint: button press in vscode)
- upload it to wemos (hint: button press in vscode)
