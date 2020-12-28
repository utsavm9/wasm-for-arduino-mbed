# Notes

* Follow instructions from: 
https://docs.zephyrproject.org/latest/getting_started/index.html#getting-started
to install on Windows using PowerShell.


* Ensure that no path ever has a space in it.


- Installing dependencies
    - Installed Chocolately
        - Installing cmake
        - Installing ninja and gperf. Skipping python and git as they were already installed.

            - All of these software are avaialble as commands after terminal restart.


- Getting Zephyr
    - Installing west using pip3.
        - Created West zephyrproject in a clear folder.
        - Updated all of the dependencies
        - Installed python requirements


- Installing a toolchain
    - Chose GNU ARM Embedded toolchain
        - Following this guide: https://docs.zephyrproject.org/latest/getting_started/toolchain_3rd_party_x_compilers.html#toolchain-gnuarmemb
        - GNU ARM Embedded Toolchain can be download from:
            - https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
        
        - Setting environment variables

            - `choco install rapidee`
            - In the User variables panel, add:
            ```
            ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
            GNUARMEMB_TOOLCHAIN_PATH="C:\GNU-ARM-Embedded-Toolchain\bin\"
            ```

 - Building a sample
`choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System' --version=3.17.2 --allow-downgrade`
 - Restart Powershell

After a failed build, do this return to a clean build:
- `rm -r build`
- `rm -r .cache`

- `choco install nrfjprog` before continuing with `west flash`

With this, blinkly builds and flashes.


------------------

## Building WAMR

- Create a soft-link to WAMR folder
Powershell running as Administrator:

`New-Item -Name ./wamr -ItemType SymbolicLink -Value ..\..\..\..\wasm-micro-runtime\`

--------------

# Building a WASM bytecode application

- Follow this tutorial: https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/build_wasm_app.md
- Downloaded WASI SDK from https://github.com/WebAssembly/wasi-sdk/releases

Clang to compile to WASM with main()
```
/opt/wasi-sdk/bin/clang     \
        --target=wasm32 -O3 -z stack-size=4096 -Wl,--initial-memory=65536 \
        --sysroot=../../../../wasm-micro-runtime/wamr-sdk/app/libc-builtin-sysroot  \
        -Wl,--allow-undefined-file=../../../../wasm-micro-runtime/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt \
        -Wl,--strip-all,--no-entry -nostdlib \
        -Wl,--export=main \
        -Wl,--export=__data_end, -Wl,--export=__heap_base \
        -Wl,--export=blink_native \
        -Wl,--allow-undefined \
        -o fib.wasm fib.c

xxd < fib.wasm -i
```

Clang to compile to WASM without main()
```

/opt/wasi-sdk/bin/clang     \
        -O0 -z stack-size=4096 -Wl,--initial-memory=65536 \
        --sysroot=/opt/wasi-sdk/share/wasi-sysroot/  \
        -Wl,--strip-all,--no-entry \
        -Wl,--allow-undefined \
        -o fib.wasm fib.c
```

----------------

## Building mini-product 
- From https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/build_wamr.md#zephyr

Commands:
```
west build -b nrf52840dk_nrf52840 . -p always -- -DWAMR_BUILD_TARGET=THUMB -DWAMR_BUILD_AOT=0
west flash
```
----------------

Error in example at https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/embed_wamr.md
```
unit32 argv[2];
to
uint32 argv[2];
```

Also modified this line:
```
static char global_heap_buf[512 * 1024];
to
static char global_heap_buf[220 * 1024];
```


-----------------------------

## Compiling to MBed


- Step 5: `python mbed-cmake/configure_for_target.py ARDUINO_NANO33BLE`
- Step 6:  
```
mkdir build; cd build
cmake -G "MinGW Makefiles" ..
C:\MinGW\bin\mingw32-make -j2 hello_world
```

- `hello_world.bin` should be avaiable now.

