//
// Created by nov11 on 3/18/2021.
//

#include <cstring>
#include <string>

#include "UART.h"
#include "pico/multicore.h"

UART* uart0_obj;
UART* uart1_obj;
bool isRunning = false;
bool uart0_locked = false;
bool uart1_locked = false;

void uart_core1()
{
    isRunning = true;

    uint8_t data;
    while(true) {
        if (uart_is_readable(uart0) && !uart0_locked) {
            uart_read_blocking(uart0, &data, 1);
            uart0_obj->rxData.push_back(data);
        }
        if(uart_is_readable(uart1) && !uart1_locked){
            uart_read_blocking(uart1, &data, 1);
            uart1_obj->rxData.push_back(data);
        }
    }
}


void UART::begin(uart_inst_t *inst, int baudRate) {
    uart = inst;
    uart_init(inst, baudRate);
    if(inst == uart0) uart0_obj = this;
    else uart1_obj = this;

    // Run core reading
    if(!isRunning)
        multicore_launch_core1(uart_core1);
}

void UART::setBaud(int baudRate) {
    uart_set_baudrate(uart, baudRate);
}

void UART::write_uint(uint64_t value) {
    std::string val = std::to_string(value);
    const char* data = val.c_str();
    write(data);
}

void UART::write_int(int64_t value) {
    std::string val = std::to_string(value);
    const char* data = val.c_str();
    write(data);
}

void UART::write_double(double value) {
    std::string val = std::to_string(value);
    const char* data = val.c_str();
    write(data);
}

void UART::write(const char *data) {
    uart_write_blocking(uart, reinterpret_cast<const uint8_t*>(data), strlen(data));
}

void UART::end() {
    uart_deinit(uart);
}

int UART::available() {
    return rxData.size();
}

uint8_t UART::peek() {
    if(available() > 0)
        return rxData[0];
    else
        return 0x0;
}

void UART::lock(bool enabled){
    if(uart == uart0)
        uart0_locked = enabled;
    if(uart == uart1)
        uart1_locked = enabled;
}

uint8_t UART::read() {
    uint8_t data = 0;
    if(available() > 0){
        data = rxData[0];
        rxData.erase(rxData.begin());

    }
    return data;
}

int64_t UART::parse_int()
{
    lock(true);
    int64_t value = 0;
    uint8_t c = peek();
    bool minus = false;

    if(c == '-') {
        minus = true;
        read();
        c = peek();
    }

    while(c >= '0' && c <= '9')
    {
        value *= 10;
        value += c - '0';
        read();
        c = peek();
    }

    lock(false);
    if(minus) value = -value;
    return value;
}

uint64_t UART::parse_uint()
{
    lock(true);
    uint64_t value = 0;
    uint8_t c = peek();

    while(c >= '0' && c <= '9')
    {
        value *= 10;
        value += c - '0';
        read();
        c = peek();
    }

    lock(false);
    return value;
}

char *UART::parse_text(int length) {
    char* text = (char*) calloc(length + 1, sizeof(char));

    int i = 0;
    for(; i < length; i++){
        text[i] = read();
    }
    text[i] = '\0';
    return text;
}




