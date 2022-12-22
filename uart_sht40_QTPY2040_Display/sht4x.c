#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pio_i2c.h"
#include <math.h>

#define INIT_CONFIG 0xFD //enable the sensor and measure temp. and hum.

/*const int addr = 0x44; //address of sht40
#define SDA 22
#define SCL 23
PIO pio = pio0;
uint sm = 0;
*/

void read_temp_hum(int32_t *temp, int32_t *hum, PIO pio, uint sm, uint32_t addr){
    uint8_t tx_bytes[1];
    uint8_t data[6];
    tx_bytes[0] = INIT_CONFIG;
    pio_i2c_write_blocking(pio, sm, addr, tx_bytes, 1, true);  // true to keep master control of bus
    sleep_ms(10);
    pio_i2c_read_blocking(pio, sm, addr, data, 6, false);  // false - finished with bus

    int raw_temperature = data[0]*256 + data[1];
    int raw_humidity = data[3]*256 + data[4];
    
    float termperature = ((175 * (raw_temperature/65536.00)) - 45.00);
    float humidity = ((125 * (raw_temperature/65536.00)) - 6.00);
    
    *temp = termperature;
    *hum = humidity;
}

/*
int main(){
    stdio_init_all();
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, SDA, SCL);
    
    while(1){
        int32_t temp;
        int32_t hum;
        
        read_temp_hum(&temp , &hum, pio, sm, addr);
        printf("temperature: %d\n", temp);
        printf("humidity: %d\n", hum);
        sleep_ms(50);
    }
}
*/