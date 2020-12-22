# Builds from Mbed+WAMR

Both the builds set up the WAMR runtime and execute the `fib_timed.c` provided in `measurements/` [here](https://github.com/utsavm9/wasm-for-arduino-mbed/blob/main/measurements/fib_timed.c).



## `wamr_nucleo.bin`

Memory map of the binary file:
```
| Module                 |           .text |       .data |            .bss |
|------------------------|-----------------|-------------|-----------------|
| [fill]                 |       172(+172) |     11(+11) |         33(+33) |
| [lib]\c.a              |   36016(+36016) | 2472(+2472) |         89(+89) |
| [lib]\gcc.a            |     6492(+6492) |       0(+0) |           0(+0) |
| [lib]\m.a              |     2236(+2236) |       1(+1) |           0(+0) |
| [lib]\mbed-os-static.a |   77324(+77324) | 3226(+3226) |     7378(+7378) |
| [lib]\misc             |       188(+188) |       4(+4) |         28(+28) |
| [lib]\nosys.a          |         32(+32) |       0(+0) |           0(+0) |
| main.cpp.obj           |       392(+392) |   374(+374) | 101120(+101120) |
| Subtotals              | 122852(+122852) | 6088(+6088) | 108648(+108648) |
Total Static RAM memory (data + bss): 114736(+114736) bytes
Total Flash memory (text + data): 128940(+128940) bytes
```

STM32 Nucleo boards are Mbed-enabled are therefore support flashing a `.bin` by simply pasting the file to the drive in which the board mounted. The output obtained on serial monitor for the program was:

```
Starting WAMR
fib(24) = 46368
Destroyed WAMR Runtime
The time taken for finding fib() was 954 milliseconds
The time taken for setting up WAMR + finding fib() was 958 milliseconds
```


## `wamr_arduino.bin`

Memory map of the binary file:
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

Compiles with a few warnings. This could not be flashed onto Arduino Nano 33 using `bossac` with neither of offsets `0x00000`, nor `0x10000`.

Arduino also does not support flashing by drag-n-drop to a mounted drive. Our approach was to directly flash the `.bin` file using a J-Link programmer at the correct offsets. However, the metal pins for that purpose were too small on the Arduino board, and we were too inexperienced with soldering.

Charles Walker has investigated this issue before:

1. [Burn bootloader Arduino nano 33 BLE](http://djynet.net/?p=969): His guide to using J-Link EDU Mini on Arduino Nano 33 board. 
2. [ArduinoCore-nRF528x-mbedos#19](ArduinoCore-nRF528x-mbedos): GitHub issue with details how `bossac` fails to upload a `.bin` file from outside of Arduino IDE, and that our `.bin` file needs to be flashed at offset `0x10000`

**Tips:**
- Preferences can be set in Arduino IDE to show verbose output of all the commands it is running to flash. `bossac` command can be determined from there which flashes a `.bin` to Arduino Nano 33.
- However, using that command directly does not work. Find a line similar to this in the verbose output:
```
Forcing reset using 1200bps open/close on port COM9
```
- Before running the `bossac` command, the board needs to be brought in bootloader mode by trying to open a connection to a specific COM port at a specific baud rate. This can be achieved with the scripts provided in this repo:
```
Serial-Monitor COM9 1200
```
- With this, `bossac` command can be run from the terminal to attempt to flash a `.bin` file. However, the issue is that as described in [ArduinoCore-nRF528x-mbedos#19](ArduinoCore-nRF528x-mbedos), our `.bin` file would still not be flashed at the specified offset but would rather be skipped.
-----