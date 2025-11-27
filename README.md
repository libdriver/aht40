[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AHT40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/aht40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AHT40 is a new temperature and humidity sensor with significant advantages of low power consumption and high accuracy. It adopts a dual row flat pinless SMD package suitable for reflow soldering, with a sturdy and small-sized shell that can easily be integrated into high difficulty designs. The sensor is equipped with a newly optimized ASIC dedicated chip, improved MEMS semiconductor capacitive humidity sensing element, and standard on-chip temperature sensing element, which greatly improves performance and can maintain stable performance even in harsh environments. The AHT40 temperature and humidity sensor can help application devices reduce power consumption, with high cost-effectiveness, especially suitable for enterprises with strict cost control and emphasis on quality for mass production.

LibDriver AHT40 is a full-featured driver for AHT40, launched by LibDriver.It provides temperature reading, relative humidity reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AHT40 source files.

/interface includes LibDriver AHT40 IIC platform independent template.

/test includes LibDriver AHT40 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AHT40 sample code.

/doc includes LibDriver AHT40 offline document.

/datasheet includes AHT40 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_aht40_basic.h"

uint8_t res;
uint32_t i;
float temperature;
float humidity;

/* basic init */
res = aht40_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    aht40_interface_delay_ms(2000);

    /* read data */
    res = aht40_basic_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)aht40_basic_deinit();

        return 1;
    }

    /* output */
    aht40_interface_debug_print("aht40: temperature is %0.2fC.\n", temperature);
    aht40_interface_debug_print("aht40: humidity is %.01f%%.\n", humidity); 
    
    ...
}

...
    
/* deinit */
(void)aht40_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/aht40/index.html](https://www.libdriver.com/docs/aht40/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.