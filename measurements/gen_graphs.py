# libraries
import numpy as np
import matplotlib.pyplot as plt

######################################
# Choose which graph (1 or 2) to generate here:
######################################
gen = 1



# set height of bar
native = [35, 22, 50]
inter_fib_only = [1655, 954, 0]
inter_overall = [1668, 958, 825]

native = np.array(native)
inter_fib_only = np.array(inter_fib_only)
inter_overall = np.array(inter_overall)

inter_fib_only_factor = inter_fib_only / native
inter_overall_factor = inter_overall / native

if gen == 1:
    # set width of bar
    barWidth = 0.25

    # Set position of bar on X axis
    r1 = np.arange(len(native))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, native, width=barWidth, edgecolor='black', label='Native program calculating fib(24)')
    plt.bar(r2, inter_fib_only, width=barWidth, edgecolor='black', label='WASM Interpretor, only calculating fib(24)')
    plt.bar(r3, inter_overall, width=barWidth, edgecolor='black', label='WASM Interpretor, setup + calculating fib(24)')

    # Add xticks on the middle of the group bars
    plt.xlabel('Boards with WASM Interpretors', fontweight='bold')
    plt.ylabel('Executiion time in ms', fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(native))], ['Nordic nRF52840\n(Zephyr + WAMR)',
                                                            'STM32F411 Nucleo\n(MBed + WAMR)', 
                                                            'Arduino Nano 33\n(MBed + WASM3)'])

    plt.legend(loc="upper center", bbox_to_anchor=(0.5, 1.16), prop={'size': 8})


elif gen == 2:
        # set width of bar
    barWidth = 0.25

    # set height of bar
    native = [35, 22, 1]
    inter_fib_only = [1655, 954, 16]
    inter_overall = [1668, 958, 24]

    # Set position of bar on X axis
    r1 = np.arange(len(native))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, inter_fib_only_factor, width=barWidth, edgecolor='black', label='Only calculating fib(24)')
    plt.bar(r2, inter_overall_factor, width=barWidth, edgecolor='black', label='Overall setup + calculating fib(24)')

    # Add xticks on the middle of the group bars
    plt.xlabel('Boards with WASM Interpretors', fontweight='bold')
    plt.ylabel('Factor by which execution time is slower \n as compared to native', fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(native))], ['Nordic nRF52840\n(Zephyr + WAMR)',
                                                            'STM32F411 Nucleo\n(MBed + WAMR)', 'Arduino Nano 33\n(MBed + WASM3)'])


    plt.legend(loc="upper center", bbox_to_anchor=(0.5, 1.16))

# Create legend & Show graphic
plt.show()