# WASM for Arduino/Mbed

## Uploaded Code

* WAMR • [All commits](https://github.com/utsavm9/wasm-micro-runtime/commits/main)
    - Platform API implementation for MBed OS • [utsavm9/wasm-micro-runtime@4c5eb14](https://github.com/utsavm9/wasm-micro-runtime/commit/4c5eb14a19ed769b355fad0a6c27cde671ef651b)
    - CMake file to build WAMR for MBed • [utsavm9/wasm-micro-runtime@aa954a5](https://github.com/utsavm9/wasm-micro-runtime/commit/aa954a53672d4598da960b0095f413ae5b8401ca)

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
