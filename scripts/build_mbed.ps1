# Make sure current folder is like this:
#   cd mbed-cmake-example-project

# Usage:
# ../build_script.ps1              : To build for Arduino Nano 33
# ../build_script.ps1 -nucleo      : To build for STM32F411 Nucleo
# ../build_script.ps1 -quick       : To quickly resume `make` from last build


Param(
    [Parameter(Mandatory=$false)]
    [Switch]
    $quick,

    [Parameter(Mandatory=$false)]
    [Switch]
    $nucleo
)


if ($quick) {
    cd build
    C:\MinGW\bin\mingw32-make -j4 hello_world
}
else {
    rm -r build
    rm -r mbed-cmake/mbed-src/build
    mkdir build
    cd build

    if ($nucleo) {
        python ../mbed-cmake/configure_for_target.py NUCLEO_F411RE
    } else {
        python ../mbed-cmake/configure_for_target.py ARDUINO_NANO33BLE
    }
    cmake -G "MinGW Makefiles" ../mini-product

    if ($LastExitCode -eq 0) {
        Write-Host "Running minGW make. Last command succeeded"
        C:\MinGW\bin\mingw32-make -j4 wamr_native_app 
    }
}

cd ..
