cmake_minimum_required(VERSION 3.10.2)


add_executable(uart_exp
uart_exp.c
        )

# pull in common dependencies
target_link_libraries(uart_exp pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(uart_exp 1)
pico_enable_stdio_uart(uart_exp 0)


# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(uart_exp)
# add url via pico_set_program_url
#example_auto_set_url(blink)