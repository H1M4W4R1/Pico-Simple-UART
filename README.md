# How to use
```c
// You need to create uart object
UART uart;

// Then begin it on specific hardware UART
//uart.begin(<interface>, <baudrate>) eg.
uart.begin(uart0, 115200);

// Then you can write data
uint a = 32;
uart.write_uint(a);

int b = -125;
uart.write_int(b);

float c = 12.5f;
uart.write_float(c);

uart.write("\r\n");

uart.write("Easy?");
```
