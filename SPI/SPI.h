//
// Created by nov11 on 3/18/2021.
//

#ifndef SPI_H
#define SPI_H
#include "hardware/spi.h"
#include <vector>

class SPI {
private:
    spi_inst_t *spi;
    bool cphaMode;
    bool cpolMode;
    uint8_t dataBits;
    bool msbFirst;
public:
    SPI* begin(spi_inst_t *inst, int baudRate);
    SPI* cpha(bool isHigh);
    SPI* cpol(bool isHigh);
    SPI* data_bits(uint8_t bits);
    SPI* msb_first();
    SPI* lsb_first();
    void setup();

    void end();
    void setBaud(int baudRate);

    uint8_t read();
    void write(uint8_t data);
    uint8_t read_write(uint8_t data);
    void set_slave(bool mode);
};



#endif
