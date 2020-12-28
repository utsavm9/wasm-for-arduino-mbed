# Measurements

`fib_timed.c` will be run on:
* WAMR Interpretor:
    * Zephyr OS (Nordic nRF52840 DK)
    * MBed OS (STM32F411 Nucleo-64 RE)
* WASM3 Interpretor:
    * MBed OS (Arduino Nano 33 BLE)


Compile using `gen_wasm.sh` script in Bash on WSL/Linux.

Computing `fib(24)`.

---

## STM32 Nucleo WAMR 
Runtime:
```
Starting WAMR
fib(24) = 46368
Destroyed WAMR Runtime
The time taken was finding fib() was 954 milliseconds
The time taken for setting up WAMR + finding fib() was 958 milliseconds
```

Memory:
```
| Module                 |           .text |       .data |            .bss |
|------------------------|-----------------|-------------|-----------------|
| [fill]                 |       150(+150) |       9(+9) |         24(+24) |
| [lib]\c.a              |   36076(+36076) | 2472(+2472) |         89(+89) |
| [lib]\gcc.a            |     6492(+6492) |       0(+0) |           0(+0) |
| [lib]\m.a              |     2236(+2236) |       1(+1) |           0(+0) |
| [lib]\mbed-os-static.a |   71870(+71870) | 3220(+3220) |     6715(+6715) |
| [lib]\misc             |       188(+188) |       4(+4) |         28(+28) |
| [lib]\nosys.a          |         32(+32) |       0(+0) |           0(+0) |
| main.cpp.obj           |       392(+392) |   374(+374) | 101120(+101120) |
| Subtotals              | 117436(+117436) | 6080(+6080) | 107976(+107976) |
Total Static RAM memory (data + bss): 114056(+114056) bytes
Total Flash memory (text + data): 123516(+123516) bytes
```

---

## STM32 Nucleo Native 

Runtime:
```
Starting native calculation
fib(24) = 46368
Finished native calculation
The time taken was 22 milliseconds
```

Memory:
```
| Module                 |         .text |       .data |        .bss |
|------------------------|---------------|-------------|-------------|
| Native.cpp.obj         |     138(+138) |       0(+0) |       0(+0) |
| [fill]                 |     110(+110) |       4(+4) |     13(+13) |
| [lib]\c.a              | 32468(+32468) | 2472(+2472) |     89(+89) |
| [lib]\gcc.a            |   3264(+3264) |       0(+0) |       0(+0) |
| [lib]\mbed-os-static.a | 17644(+17644) |   440(+440) | 6670(+6670) |
| [lib]\misc             |     188(+188) |       4(+4) |     28(+28) |
| [lib]\nosys.a          |       32(+32) |       0(+0) |       0(+0) |
| Subtotals              | 53844(+53844) | 2920(+2920) | 6800(+6800) |
Total Static RAM memory (data + bss): 9720(+9720) bytes
Total Flash memory (text + data): 56764(+56764) bytes
```

---


## Nordic Zephyr WAMR 
Runtime:
```
*** Booting Zephyr OS build zephyr-v2.4.0-1800-g79296694c38a  ***
fib(24) = 46368
The time taken was finding fib() was 1655 milliseconds
The time taken for setting up WAMR + finding fib() was 1668 milliseconds
```

---


## Nordic Zephyr Native T
Runtime:
```
*** Booting Zephyr OS build zephyr-v2.4.0-1800-g79296694c38a  ***
fib(24) = 46368
The time taken was finding fib() natively was 35 milliseconds
```