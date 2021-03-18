# How to use
## UART
```cpp
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

To read data you can use
```cpp
uint8_t number0 = uart.peek(); // Peeks UART without removing number from data queue
uint8_t number1 = uart.read(); // reads 8-bit number
uint64_t number2 = uart.parse_uint(); // Reads unsigned integer written as text
int64_t number3 = uart.parse_int(); // Reads signed interger written as text
```
## I2C
```cpp
// You need to define object
IIC iic;

// Then you can start it
iic.begin(i2c0, 100*1000);

// And read/send data
uint8_t* data = iic.read(0x50, 1); // Read byte from addr 50
iic.write(0x51, data, 1); // Write data to addr 50
free_memory(); // Free memory after reading (recommended, automatic on new read)

// Or set Pico as slave device
set_slave(true, 0x70); // Set Pico as slave at address 0x70.
```

## SPI
```cpp
// You need to define object
SPI spi;

// Then  you need to init SPI basing on data given by manufacturer
spi.begin(spi0, 12000000)->cpol(false)->cpha(false)->data_bits(8)->msb_first()->setup(); // Init SPI ;)

// Then you can write/read or readwrite data
spi.write(0x40); // Write byte 0x40, ignore returned data
uint8_t data = spi.read(); // Write 0x0 and read data

uint8_t rwData = spi.read_write(0x40); // Write 0x40 and read data

```
