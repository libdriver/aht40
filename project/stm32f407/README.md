### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AHT40

#### 3.1 Command Instruction

1. Show aht40 chip and driver information.

   ```shell
   aht40 (-i | --information)
   ```

2. Show aht40 help.

   ```shell
   aht40 (-h | --help)
   ```

3. Show aht40 pin connections of the current board.

   ```shell
   aht40 (-p | --port)
   ```

4. Run aht40 read test, num means test times.

   ```shell
   aht40 (-t read | --test=read) [--times=<num>]
   ```

5. Run aht40 read function, num means test times.

   ```shell
   aht40 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
aht40 -i

aht40: chip is ASAIR AHT40.
aht40: manufacturer is ASAIR.
aht40: interface is IIC.
aht40: driver version is 1.0.
aht40: min supply voltage is 2.0V.
aht40: max supply voltage is 5.5V.
aht40: max current is 0.46mA.
aht40: max temperature is 120.0C.
aht40: min temperature is -40.0C.
```

```shell
aht40 -p

aht40: SCL connected to GPIOB PIN8.
aht40: SDA connected to GPIOB PIN9.
```

```shell
aht40 -t read --times=3

aht40: chip is ASAIR AHT40.
aht40: manufacturer is ASAIR.
aht40: interface is IIC.
aht40: driver version is 1.0.
aht40: min supply voltage is 2.0V.
aht40: max supply voltage is 5.5V.
aht40: max current is 0.46mA.
aht40: max temperature is 120.0C.
aht40: min temperature is -40.0C.
aht40: start read test.
aht40: temperature: 29.9C.
aht40: humidity: 15.4%.
aht40: temperature: 29.9C.
aht40: humidity: 15.3%.
aht40: temperature: 29.9C.
aht40: humidity: 15.0%.
aht40: finish read test.
```

```shell
aht40 -e read --times=3

aht40: 1/3.
aht40: temperature is 29.69C.
aht40: humidity is 15.1%.
aht40: 2/3.
aht40: temperature is 29.65C.
aht40: humidity is 15.0%.
aht40: 3/3.
aht40: temperature is 29.64C.
aht40: humidity is 15.0%.
```

```shell
aht40 -h

Usage:
  aht40 (-i | --information)
  aht40 (-h | --help)
  aht40 (-p | --port)
  aht40 (-t read | --test=read) [--times=<num>]
  aht40 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <read>, --test=<read>       Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

