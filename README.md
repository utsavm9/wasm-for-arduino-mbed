# WASM for Mbed OS

## Primary Project Contribution

* WAMR • [All commits](https://github.com/utsavm9/wasm-micro-runtime/commits/main)
    - Platform API implementation for Mbed OS • [utsavm9/wasm-micro-runtime@4c5eb14](https://github.com/utsavm9/wasm-micro-runtime/commit/4c5eb14a19ed769b355fad0a6c27cde671ef651b)
    - CMake file to build WAMR for Mbed • [utsavm9/wasm-micro-runtime@aa954a5](https://github.com/utsavm9/wasm-micro-runtime/commit/aa954a53672d4598da960b0095f413ae5b8401ca)
    - Added mini-product for Mbed • [utsavm9/wasm-micro-runtime@0960e82](https://github.com/utsavm9/wasm-micro-runtime/commit/0960e82db2be30b741f5c83e7a57ea9056b2ab59)

* Mbed • [All commits](https://github.com/utsavm9/mbed-cmake/commits/)
    - Remove unnecessary component preventing compilation • [utsavm9/mbed-cmake@24248f5](https://github.com/utsavm9/mbed-cmake/commit/24248f530840f414eb3405bc08a8ba0c85e2d0d5)
    - Seperate build files from source files in CMake • [utsavm9/mbed-cmake@51dd694](https://github.com/utsavm9/mbed-cmake/commit/51dd6941c25823d37ab1cbfc058c262d5419bbbd)
    - Combine build process of WAMR with Mbed  • [utsavm9/mbed-cmake@593affc](https://github.com/utsavm9/mbed-cmake/commit/593affc7f67a8019b80f595165eadf4d72de6c05)

* Scripts • [Folder](https://github.com/utsavm9/wasm-for-arduino-mbed/tree/main/scripts)
    - Serial Monitor for Windows
    - Compiling C programs to WASM modules in C arrays
    - Compiling with Mbed-CMake
---

* Wasm3
    - Wasm3 library with modified driver code ([here](https://github.com/utsavm9/wasm-for-arduino-mbed/tree/main/wasm3-arduino/examples_pio/wasm_fibonnaci_timing))
    - Example WASM program that recursively computes the 24th Fibonnaci number and times it ([here](https://github.com/utsavm9/wasm-for-arduino-mbed/tree/main/wasm3-arduino/wasm_apps/cpp))


[Website](https://utsavm9.github.io/wasm-for-arduino-mbed/): Source code in `docs` folder.

---

## Using WAMR on Zephyr OS

* See `scripts/` directory for help on using [`gen_wasm.sh`](https://github.com/utsavm9/wasm-for-arduino-mbed/blob/main/scripts/gen_wasm.sh) to get C-byte array representing your WASM program.

* Verify that a blinky program can be compiled and flashed to the board. Follow steps in "[Getting Started Guide - Zephyr](https://docs.zephyrproject.org/latest/getting_started/index.html)" or latest guide and get blinkly program flashed to board using `west`.
    - If using the same board as us (Nordic nRF528040), then the target name is `nrf52840dk_nrf52840`

* Copy the Zephyr mini-product files from [`
wasm-micro-runtime/product-mini/platforms/zephyr/simple/
`](https://github.com/bytecodealliance/wasm-micro-runtime/tree/main/product-mini/platforms/zephyr/simple) to a new folder inside [`zephyr/samples/`](https://github.com/zephyrproject-rtos/zephyr/tree/master/samples). Assume we copied the mini-product files into `zephyr/samples/custom_app`.

* Make a soft-link to the root of WAMR repo, inside the `custom_app` directory and name the soft-link as `wamr`.
```bash
# Bash
ln -s ~/wasm-micro-runtime/ custom_app/wamr
```
```powershell
# Powershell run as Admin
New-Item -Name custom_app/wamr -ItemType SymbolicLink -Value ~\wasm-micro-runtime\
```

* Remove all files inside the `custom_app/src` folder and then place these files inside that foler:
    - `measurements/zephyr-wamr/main.c`
    - `measurements/fib_timed.c.wasm`

* With current directory the same as `custom_app`, so that the `CMakeList.txt` file is in the current directory, compile the app. A memory map of the program should be shown when successfully compiled.
```powershell
west build -b nrf52840dk_nrf52840 . -p always -- -DWAMR_BUILD_TARGET=THUMB -DWAMR_BUILD_AOT=0
```

* Connect board to USB with power switched on. Flash to the board using `west flash`. 

* Use [`Serial-Monitor`](https://github.com/utsavm9/wasm-for-arduino-mbed/blob/main/scripts/serial.ps1) script to find the associated COM port of the board. With default baud rate of 115200, `Serial-Monitor` script can be used to see the output from `printf()`.

---

## Team Members

-   Arelys Navarro (arelysnavarro@g.ucla.edu)
-   Howard Xie (howardx@cs.ucla.edu)
-   Utsav Munendra (utsavm9@g.ucla.edu)
