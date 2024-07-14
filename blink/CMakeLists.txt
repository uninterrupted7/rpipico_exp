cmake_minimum_required(VERSION 3.10.2)

add_executable(blink
    blink.c
        )
add_executable(tempe
        temp.c
            )
# pull in common dependencies
target_link_libraries(blink pico_stdlib)
target_link_libraries(tempe pico_stdlib hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

pico_enable_stdio_usb(tempe 1)
pico_enable_stdio_uart(tempe 0)


# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
pico_add_extra_outputs(tempe)
# add url via pico_set_program_url
#example_auto_set_url(blink)