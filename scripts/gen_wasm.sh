#!/bin/bash

# Usage:
#      ./gen_wasm.sh <FILENAME>
# eg.: ./gen_wasm.sh fib

# Mention other functions to be exported around line 29, like this:
#       -Wl,--export=startTimer, -Wl,--export=endTimer \

OUT="$1.c.wasm"
WASM_BIN="$1.wasm"
C_FILE="$1.c"

# Check if file exists
if [ -f "$C_FILE" ]; then
    echo "Found file $C_FILE, compiling to WASM..."
else
    echo "$C_FILE does not exist."
    exit
fi

# Compile.
/opt/wasi-sdk/bin/clang     \
    --target=wasm32 -O3 -z stack-size=4096 -Wl,--initial-memory=65536 \
    --sysroot=../wasm-micro-runtime/wamr-sdk/app/libc-builtin-sysroot  \
    -Wl,--allow-undefined-file=../wasm-micro-runtime/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt \
    -Wl,--strip-all,--no-entry -nostdlib \
    -Wl,--export=main \
    -Wl,--export=__data_end, -Wl,--export=__heap_base \
    -Wl,--allow-undefined \
    -o $WASM_BIN $C_FILE

if [ $? -ne 0 ]; then
    exit
fi

# Convert WASM binary into a C array.
echo "// WASM module compiled from $1.c" > $OUT
echo >> $OUT
echo "unsigned char __aligned(4) wasm_program[] = {" >> $OUT
xxd < $WASM_BIN -i >> $OUT
echo "};" >> $OUT

