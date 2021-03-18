//
// Created by nov11 on 3/18/2021.
//

#ifndef UART_H
#define UART_H
#include "hardware/uart.h"
#include <vector>

class UART {
private:
    uart_inst_t *uart;
public:
    std::vector<uint8_t> rxData;
public:
    void begin(uart_inst_t *inst, int baudRate);
    void end();
    void setBaud(int baudRate);
    void write_uint(uint64_t value);
    void write_int(int64_t value);
    void write_double(double value);
    void write(const char* data);
    int available();
    uint8_t peek();
    uint8_t read();
    int64_t parse_int();
    uint64_t parse_uint();
    char* parse_text(int length);

    void lock(bool enabled);
};



#endif //UART_H
