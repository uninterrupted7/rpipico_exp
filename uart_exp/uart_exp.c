#include <stdio.h>
#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN_25 25

int main() {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        sleep_ms(1500);
        gpio_put(LED_PIN_25, GPIO_ON);
        printf("15");
        sleep_ms(1500);
        gpio_put(LED_PIN_25, GPIO_OFF);
        printf("0");
    }
}