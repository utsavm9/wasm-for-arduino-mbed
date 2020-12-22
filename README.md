# WASM for Arduino/Mbed

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

## Proposal Abstract

Our goal in this project is to develop a sensor interface that would allow a WebAssembly Runtime to
run WebAssembly application on an nRF5280 board and be able to utilize the sensors present on the
board. Applications run inside a WebAssembly runtime are more secure than C applications compiled to
run natively. We want to use the security features present in a WebAssembly runtime and develop
applications which once compiled to WebAssembly, can execute on different boards. The main challenge
we face in this project is getting WebAssembly to work full-fledged on Arduino/Mbed embedded device
so that the application can access and control the sensors present on the board. We want WebAssembly
running on our embedded device and have it communicate with the proper pinouts on the device.

We also plan to quantify any additional memory overhead or runtime costs that are by using a
WebAssemblytime as opposed to compiling and running executables natively.

<b>Deliverables</b>: A Sensor interface to existing WebAssembly Runtime targeted to run on
Andruino/Mbed.

[Website](https://utsavm9.github.io/wasm-for-arduino-mbed/): Source code in `docs` folder.

---

## Team Members

-   Arelys Navarro (arelysnavarro@g.ucla.edu)
-   Howard Xie (howardx@cs.ucla.edu)
-   Utsav Munendra (utsavm9@g.ucla.edu)
