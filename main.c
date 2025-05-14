#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <string.h>

// Include the driver header/code you shared before
// (assume all nrf24_t functions and definitions are already available)

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CE   17
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_CSN  20

int main() {
    stdio_init_all();

    // SPI setup
    spi_init(SPI_PORT, 1000 * 1000); // 1 MHz
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Declare and initialize the NRF module
    nrf24_t nrf;
    nrf24_init(&nrf, SPI_PORT, PIN_CSN, PIN_CE, false); // false = TX mode

    // Sample payload to transmit
    const char *msg = "Hello";
    while (true) {
        nrf24_send(&nrf, (const uint8_t *)msg, strlen(msg));
        printf("Sent: %s\n", msg);
        sleep_ms(1000);
    }

    return 0;
}
