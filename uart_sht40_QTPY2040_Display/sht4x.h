#ifndef SHT4X_H
#define SHT4X_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pio_i2c.h"

void read_temp_hum(int32_t *temp, int32_t *hum, PIO pio, uint sm, uint32_t addr);

#endif