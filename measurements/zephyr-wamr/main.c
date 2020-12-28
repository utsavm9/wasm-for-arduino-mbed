/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "bh_assert.h"
#include "bh_log.h"
#include "bh_platform.h"
#include "fib_timed.c.wasm"
#include "wasm_export.h"
#include <stdlib.h>
#include <string.h>
#include <zephyr.h>

/**
 * fib() below is used to measure native performace
 * which will be many times faster than executing the same
 * function from WAMR
 */
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

/* These values three might need tweaking
    They affect the size of the built executable. */
#define CONFIG_GLOBAL_HEAP_BUF_SIZE 131072
#define CONFIG_APP_STACK_SIZE 8192
#define CONFIG_APP_HEAP_SIZE 8192

#ifdef CONFIG_NO_OPTIMIZATIONS
#define CONFIG_MAIN_THREAD_STACK_SIZE 8192
#else
#define CONFIG_MAIN_THREAD_STACK_SIZE 4096
#endif

int64_t time_calc_fib;
int64_t milliseconds_spent_calc_fib;

void startTimer(wasm_exec_env_t exec_env) { time_calc_fib = k_uptime_get(); }
void endTimer(wasm_exec_env_t exec_env) {
    milliseconds_spent_calc_fib = k_uptime_delta(&time_calc_fib);
}

static int app_argc;
static char **app_argv;

/**
 * Find the unique main function from a WASM module instance
 * and execute that function.
 *
 * @param module_inst the WASM module instance
 * @param argc the number of arguments
 * @param argv the arguments array
 *
 * @return true if the main function is called, false otherwise.
 */
bool wasm_application_execute_main(wasm_module_inst_t module_inst, int argc,
                                   char *argv[]);

static void *app_instance_main(wasm_module_inst_t module_inst) {
    const char *exception;
    wasm_application_execute_main(module_inst, app_argc, app_argv);
    if ((exception = wasm_runtime_get_exception(module_inst))) {
        printf("%s\n", exception);
    }
    return NULL;
}

static char global_heap_buf[CONFIG_GLOBAL_HEAP_BUF_SIZE] = {0};

void iwasm_main(void *arg1, void *arg2, void *arg3) {
    int64_t time_overall;
    int64_t milliseconds_spent_overall;
    time_overall = k_uptime_get_32();
    uint8 *wasm_file_buf = NULL;
    uint32 wasm_file_size;
    wasm_module_t wasm_module = NULL;
    wasm_module_inst_t wasm_module_inst = NULL;
    RuntimeInitArgs init_args;
    char error_buf[128];
#if WASM_ENABLE_LOG != 0
    int log_verbose_level = 2;
#endif

    (void)arg1;
    (void)arg2;
    (void)arg3;

    memset(&init_args, 0, sizeof(RuntimeInitArgs));

    static NativeSymbol native_symbols[] = {
        {
            "startTimer", // the name of WASM function name
            startTimer,   // the native function pointer
            "()"          // the function prototype signature
        },
        {
            "endTimer", // the name of WASM function name
            endTimer,   // the native function pointer
            "()"        // the function prototype signature
        }};

    init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

    /* initialize runtime environment */
    if (!wasm_runtime_full_init(&init_args)) {
        printf("Init runtime environment failed.\n");
        return;
    }

#if WASM_ENABLE_LOG != 0
    bh_log_set_verbose_level(log_verbose_level);
#endif

    int n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
    if (!wasm_runtime_register_natives("env", native_symbols,
                                       n_native_symbols)) {
        return;
    }

    /* load WASM byte buffer from byte buffer of include file */
    wasm_file_buf = (uint8 *)wasm_program;
    wasm_file_size = sizeof(wasm_program);

    /* load WASM module */
    if (!(wasm_module = wasm_runtime_load(wasm_file_buf, wasm_file_size,
                                          error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
        goto fail1;
    }

    /* instantiate the module */
    if (!(wasm_module_inst = wasm_runtime_instantiate(
              wasm_module, CONFIG_APP_STACK_SIZE, CONFIG_APP_HEAP_SIZE,
              error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
        goto fail2;
    }

    /* invoke the main function */
    app_instance_main(wasm_module_inst);

    /* destroy the module instance */
    wasm_runtime_deinstantiate(wasm_module_inst);

fail2:
    /* unload the module */
    wasm_runtime_unload(wasm_module);

fail1:
    /* destroy runtime environment */
    wasm_runtime_destroy();

    milliseconds_spent_overall = k_uptime_delta(&time_overall);

    printf("The time taken was finding fib() was %lld milliseconds\n",
           milliseconds_spent_calc_fib);
    printf("The time taken for setting up WAMR + finding fib() was %lld "
           "milliseconds\n",
           milliseconds_spent_overall);
}

#define MAIN_THREAD_STACK_SIZE (CONFIG_MAIN_THREAD_STACK_SIZE)
#define MAIN_THREAD_PRIORITY 5

K_THREAD_STACK_DEFINE(iwasm_main_thread_stack, MAIN_THREAD_STACK_SIZE);
static struct k_thread iwasm_main_thread;

bool iwasm_init(void) {
    k_tid_t tid = k_thread_create(
        &iwasm_main_thread, iwasm_main_thread_stack, MAIN_THREAD_STACK_SIZE,
        iwasm_main, NULL, NULL, NULL, MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
    return tid ? true : false;
}

void main(void) {
    /** During one run, uncomment this block to measure
     * the time taken by WAMR to compute fib(24)
     */
    {
        iwasm_init();
        printf(
            "The time taken was finding fib() in WAMR was %lld milliseconds\n",
            milliseconds_spent_calc_fib);
    }

    /** During another run, uncomment this block to measure
     * the time taken without WAMR to computer fib(24) natively.
     */
    // {
    // 	int64_t time_overall;
    // 	int64_t milliseconds_spent_overall;
    // 	time_overall = k_uptime_get_32();
    // 	printf("fib(24) = %d\n", fib(24));
    // 	milliseconds_spent_overall = k_uptime_delta(&time_overall);

    // 	printf("The time taken was finding fib() natively was %lld
    // milliseconds\n", 	       milliseconds_spent_overall);
    // }
    return;
}
