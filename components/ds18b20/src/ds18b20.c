#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "ds18b20.h"

bool one_wire_reset(void) {
    bool isPresent = false;

    gpio_set_direction(ONE_WIRE_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ONE_WIRE_PIN, 0);    
    esp_rom_delay_us(480);                      

    gpio_set_direction(ONE_WIRE_PIN, GPIO_MODE_INPUT);  // Release the bus line
    esp_rom_delay_us(70);                       

    isPresent = !gpio_get_level(ONE_WIRE_PIN);  // Check presence pulse (should be low if device is present)
    esp_rom_delay_us(410);                      // Wait for the remainder of the reset period (total period time - 960 microseconds)
 
    return isPresent;
}

