# WASM for Arduino/Mbed

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

---

## Team Members

-   Arelys Navarro (arelysnavarro@g.ucla.edu)
-   Howard Xie (howardx@cs.ucla.edu)
-   Utsav Munendra (utsavm9@g.ucla.edu)
