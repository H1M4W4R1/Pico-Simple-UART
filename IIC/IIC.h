//
// Created by nov11 on 3/18/2021.
//

#ifndef IIC_H
#define IIC_H
#include "hardware/i2c.h"
#include <vector>

class IIC {
private:
    i2c_inst_t *i2c;
    uint8_t* data;
public:
    void begin(i2c_inst_t *inst, int baudRate);
    void end();
    void setBaud(int baudRate);

    int available();
    uint8_t* read(uint8_t address, size_t amount);
    void write(uint8_t address, uint8_t* data, size_t amount);
    void free_memory();
    void set_slave(bool mode, uint8_t addr);
};



#endif
