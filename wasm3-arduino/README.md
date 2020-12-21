# Wasm3
🚀 The fastest WebAssembly interpreter

[![WAPM](https://wapm.io/package/vshymanskyy/wasm3/badge.svg)](https://wapm.io/package/vshymanskyy/wasm3) 
[![GitHub issues](https://img.shields.io/github/issues-raw/wasm3/wasm3?style=flat-square&label=issues&color=success)](https://github.com/wasm3/wasm3/issues) 
[![Tests status](https://img.shields.io/github/workflow/status/wasm3/wasm3/tests/master?style=flat-square&logo=github&label=tests)](https://github.com/wasm3/wasm3/actions) 
[![GitHub license](https://img.shields.io/badge/license-MIT-blue?style=flat-square)](https://github.com/wasm3/wasm3)


Original repository: [**Wasm3 Arduino project**](https://github.com/wasm3/wasm3-arduino)

This is a repository for the Arduino library, Wasm3. This is an interpreter that runs on Arduino. My contribution in this repository is `wasm_apps/custom_app`, `examples_pio/vanilla_fibonnaci_timing`, and `examples/wasm_fibonnaci_timing`.

## How to use on Arduino Nano 33 BLE Sense for ECEM202A

1. Download the Arduino IDE from [**here**](https://www.arduino.cc/en/software).
2. Open the Arduino IDE.
3. Find your Arduino library directory that was created when opening the Arduino IDE. (C:\Users\you\Documents\Arduino\libraries on PC)
4. Copy this wasm3-arduino folder into the libraries directory.
5. Plug in your Arduino Nano 33 BLE Sense using a valid data-transferring USB cable. (Some are power-only)
6. On the Arduino IDE, select the Nano 33 BLE board from Tools -> Board -> Arduino MBed OS Boards (might have to go to Tools -> Board -> Boards Manager and install the "Arduino nRF528x Boards" package)
7. Make sure to select the right port that your Arduino is connected to. (Tools -> Port)
8. Open the wasm3 fibonnaci timing code. (File -> Examples -> Wasm3 -> examples_pio -> wasm_fibonnaci_timing)
9. Send the code over to your Arduino by clicking "Upload"
10. Open the serial monitor on the upper right corner of the Arduino IDE
11. You should see a number output and that is the time it took to compute the 24th fibonnaci number using Wasm3 interpreter.

## Supported devices

Wasm3 requires at least **~64Kb** Flash and **~10Kb** RAM even for minimal functionality.

### License
This project is released under The MIT License (MIT)
