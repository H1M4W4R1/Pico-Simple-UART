//
// Created by nov11 on 3/18/2021.
//

#include <cstring>
#include <string>

#include "IIC.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

void IIC::begin(i2c_inst_t *inst, int baudRate) {
    i2c = inst;
    i2c_init(inst, baudRate);

    if(inst == i2c0) {
        gpio_set_function(4, GPIO_FUNC_I2C);
        gpio_set_function(5, GPIO_FUNC_I2C);
        gpio_pull_up(4);
        gpio_pull_up(5);
    }
    else if(inst == i2c1) {
        gpio_set_function(6, GPIO_FUNC_I2C);
        gpio_set_function(7, GPIO_FUNC_I2C);
        gpio_pull_up(6);
        gpio_pull_up(7);
    }
}

void IIC::end() {
    i2c_deinit(i2c);
}

void IIC::setBaud(int baudRate) {
    i2c_set_baudrate(i2c, baudRate);
}

int IIC::available() {
    return i2c_get_read_available(i2c);
}

uint8_t *IIC::read(uint8_t address, size_t amount) {
    // Free memory!
    if(data != nullptr)
        free(data);

    // Assign new memory
    data = (uint8_t*) calloc(amount, sizeof(uint8_t));
    i2c_read_blocking(i2c, address, data, amount, false);
    return data;
}

void IIC::write(uint8_t address, uint8_t *cdata, size_t amount) {
    i2c_write_blocking(i2c, address, cdata, amount, false);
}

void IIC::free_memory() {
    free(data);
}

void IIC::set_slave(bool mode, uint8_t addr) {
    i2c_set_slave_mode(i2c, mode, addr);
}
