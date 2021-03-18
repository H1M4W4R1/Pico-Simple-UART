//
// Created by nov11 on 3/18/2021.
//

#include <cstring>
#include <string>

#include "IIC.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "SPI.h"


SPI* SPI::begin(spi_inst_t *inst, int baudRate) {
    spi_init(inst, baudRate);
    spi = inst;

    if(inst == spi0){
        // 16, 18, 19
        gpio_set_function(16, GPIO_FUNC_SPI);
        gpio_set_function(18, GPIO_FUNC_SPI);
        gpio_set_function(19, GPIO_FUNC_SPI);

        gpio_pull_down(16);
        gpio_pull_down(19);
        if(cpolMode)
            gpio_pull_up(18);
        else
            gpio_pull_down(18);
    }
    else if(inst == spi1){
        // 10, 11, 12
        gpio_set_function(10, GPIO_FUNC_SPI);
        gpio_set_function(11, GPIO_FUNC_SPI);
        gpio_set_function(12, GPIO_FUNC_SPI);

        gpio_pull_down(11);
        gpio_pull_down(12);
        if(cpolMode)
            gpio_pull_up(10);
        else
            gpio_pull_down(10);

    }

    return this;
}

SPI* SPI::cpha(bool isHigh) {
    cphaMode = isHigh;
    return this;
}

SPI* SPI::cpol(bool isHigh) {
    cpolMode = isHigh;
    return this;
}

SPI* SPI::data_bits(uint8_t bits) {
    dataBits = bits;
    return this;
}

SPI* SPI::msb_first() {
    msbFirst = true;
    return this;
}

SPI* SPI::lsb_first() {
    msbFirst = false;
    return this;
}

void SPI::setup() {
    spi_set_format(spi, dataBits, cpolMode ? SPI_CPOL_1 : SPI_CPOL_0, cphaMode ? SPI_CPHA_1 : SPI_CPHA_0, msbFirst ? SPI_MSB_FIRST : SPI_LSB_FIRST);
    if(spi == spi0){
        if(cpolMode)
            gpio_pull_up(18);
        else
            gpio_pull_down(18);
    }
    else{
        if(cpolMode)
            gpio_pull_up(10);
        else
            gpio_pull_down(10);
    }
}

void SPI::end() {
    spi_deinit(spi);
}

void SPI::setBaud(int baudRate) {
    spi_set_baudrate(spi, baudRate);
}

uint8_t SPI::read() {
    uint8_t data;
    spi_read_blocking(spi, 0x0, &data, 1);
    return data;
}

void SPI::write(uint8_t data) {
    spi_write_blocking(spi, &data, 1);
}

uint8_t SPI::read_write(uint8_t data) {
    uint8_t result;
    spi_write_read_blocking(spi, &data, &result, 1);
    return result;
}

void SPI::set_slave(bool mode) {
    spi_set_slave(spi, mode);
}

