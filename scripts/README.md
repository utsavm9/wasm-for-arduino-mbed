# Scripts

## `build_mbed.ps1`

Compiling with Mbed involves these three tasks:
* Configuring files for specific target
* Generating the needed make-files using CMake
* Running make to compile code in the correct order and link everything correctly.

All these steps have their own command, and this script runs that in sequence.

## `gen_wasm.sh`

Ensure that WASM SDK is installed in the `opt/` folder. This is the only script that needs WSL Bash to run, and all the rest of the scripts are for Powershell in Windows 10. It takes a C program, and generates a WASM binary module along with a file with C-array representation of that binary module.

## `serial.ps1`

Add the function `Serial-Monitor` to your `profile.ps1`, or execute this script to have that command avaialble. 

`Serial-Monitor` can be used to find which devices are connected to which COM ports. It can also be used to print the serial output when given a COM port and baud rate.