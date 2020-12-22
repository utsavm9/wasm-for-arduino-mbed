#include "bh_platform.h"
#include "fib_timed.c.wasm"
#include "mbed.h"
#include "wasm_export.h"
#include <stdlib.h>
#include <string.h>
using namespace std::chrono;

#define CONFIG_GLOBAL_HEAP_BUF_SIZE 101072
static char global_heap_buf[CONFIG_GLOBAL_HEAP_BUF_SIZE] = {0};
#define CONFIG_APP_STACK_SIZE 8192
#define CONFIG_APP_HEAP_SIZE 8192

Timer tin;
Timer tout;

void startTimer(wasm_exec_env_t exec_env) { tin.start(); }
void endTimer(wasm_exec_env_t exec_env) { tin.stop(); }

int main() {
    printf("Starting WAMR\n");
    tout.start();

    uint8 *wasm_file_buf = NULL;
    uint32 wasm_file_size;
    wasm_module_t wasm_module = NULL;
    wasm_module_inst_t wasm_module_inst = NULL;
    RuntimeInitArgs init_args;
    char error_buf[128];

    memset(&init_args, 0, sizeof(RuntimeInitArgs));

    init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

    /* initialize runtime environment */
    if (!wasm_runtime_full_init(&init_args)) {
        printf("Init runtime environment failed.\n");
        return 0;
    }

    // Initialize native symbols
    static NativeSymbol native_symbols[] = {{"startTimer", (void *) startTimer, "()"},
                                            {"endTimer", (void *) endTimer, "()"}};
    int n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
    if (!wasm_runtime_register_natives("env", native_symbols,
                                       n_native_symbols)) {
        printf("Could not register native symbols\n");
        return 0;
    }

    /* load WASM byte buffer from byte buffer of include file */
    wasm_file_buf = (uint8 *)wasm_program;
    wasm_file_size = sizeof(wasm_program);

    /* load WASM module */
    if (!(wasm_module = wasm_runtime_load(wasm_file_buf, wasm_file_size,
                                          error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
    }

    /* instantiate the module */
    if (!(wasm_module_inst = wasm_runtime_instantiate(
              wasm_module, CONFIG_APP_STACK_SIZE, CONFIG_APP_HEAP_SIZE,
              error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
    }

    /* invoke the main function */
    const char *exception;
    wasm_application_execute_main(wasm_module_inst, 0, NULL);
    if ((exception = wasm_runtime_get_exception(wasm_module_inst))) {
        printf("%s\n", exception);
    }

    /* destroy the module instance */
    wasm_runtime_deinstantiate(wasm_module_inst);

    /* unload the module */
    wasm_runtime_unload(wasm_module);
    wasm_runtime_destroy();

    tout.stop();
    printf("Destroyed WAMR Runtime\n");
    printf("The time taken was finding fib() was %llu milliseconds\n",
           duration_cast<milliseconds>(tin.elapsed_time()).count());
    printf("The time taken for setting up WAMR + finding fib() was %llu milliseconds\n",
           duration_cast<milliseconds>(tout.elapsed_time()).count());
}