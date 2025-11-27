### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(aht40 REQUIRED)
```

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
./aht40 -i

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
./aht40 -p

aht40: SCL connected to GPIO3(BCM).
aht40: SDA connected to GPIO2(BCM).
```

```shell
./aht40 -t read --times=3

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
aht40: temperature: 29.0C.
aht40: humidity: 16.5%.
aht40: temperature: 29.1C.
aht40: humidity: 16.4%.
aht40: temperature: 29.1C.
aht40: humidity: 16.4%.
aht40: finish read test.
```

```shell
./aht40 -e read --times=3

aht40: 1/3.
aht40: temperature is 28.90C.
aht40: humidity is 16.4%.
aht40: 2/3.
aht40: temperature is 28.94C.
aht40: humidity is 16.4%.
aht40: 3/3.
aht40: temperature is 28.77C.
aht40: humidity is 16.6%.
```

```shell
./aht40 -h

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

