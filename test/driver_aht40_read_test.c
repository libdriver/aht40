/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_aht40_read_test.c
 * @brief     driver aht40 read test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_aht40_read_test.h"

static aht40_handle_t gs_handle;        /**< aht40 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t aht40_read_test(uint32_t times)
{
    uint8_t res;
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    uint32_t i;
    float temperature;
    float humidity;
    aht40_info_t info;
   
    /* link interface function */
    DRIVER_AHT40_LINK_INIT(&gs_handle, aht40_handle_t);
    DRIVER_AHT40_LINK_IIC_INIT(&gs_handle, aht40_interface_iic_init);
    DRIVER_AHT40_LINK_IIC_DEINIT(&gs_handle, aht40_interface_iic_deinit);
    DRIVER_AHT40_LINK_IIC_READ_CMD(&gs_handle, aht40_interface_iic_read_cmd);
    DRIVER_AHT40_LINK_IIC_WRITE_CMD(&gs_handle, aht40_interface_iic_write_cmd);
    DRIVER_AHT40_LINK_DELAY_MS(&gs_handle, aht40_interface_delay_ms);
    DRIVER_AHT40_LINK_DEBUG_PRINT(&gs_handle, aht40_interface_debug_print);

    /* get aht40 information */
    res = aht40_info(&info);
    if (res != 0)
    {
        aht40_interface_debug_print("aht40: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print aht40 information */
        aht40_interface_debug_print("aht40: chip is %s.\n", info.chip_name);
        aht40_interface_debug_print("aht40: manufacturer is %s.\n", info.manufacturer_name);
        aht40_interface_debug_print("aht40: interface is %s.\n", info.interface);
        aht40_interface_debug_print("aht40: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        aht40_interface_debug_print("aht40: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        aht40_interface_debug_print("aht40: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        aht40_interface_debug_print("aht40: max current is %0.2fmA.\n", info.max_current_ma);
        aht40_interface_debug_print("aht40: max temperature is %0.1fC.\n", info.temperature_max);
        aht40_interface_debug_print("aht40: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start basic read test */
    aht40_interface_debug_print("aht40: start read test.\n");
    
    /* aht40 init */
    res = aht40_init(&gs_handle);
    if (res != 0)
    {
        aht40_interface_debug_print("aht40: init failed.\n");
       
        return 1;
    }
    
    /* delay 2000 ms for read */
    aht40_interface_delay_ms(2000);
    for (i = 0; i < times; i++)
    {
        /* read temperature and humidity */
        res = aht40_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature, 
                                             (uint16_t *)&humidity_raw, (float *)&humidity);
        if (res != 0)
        {
            aht40_interface_debug_print("aht40: read failed.\n");
            (void)aht40_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        aht40_interface_debug_print("aht40: temperature: %.01fC.\n", temperature);
        aht40_interface_debug_print("aht40: humidity: %.01f%%.\n", humidity);

        /* delay 2000 ms*/
        aht40_interface_delay_ms(2000);
    }

    /* finish basic read test and exit */
    aht40_interface_debug_print("aht40: finish read test.\n");
    (void)aht40_deinit(&gs_handle);
    
    return 0;
}
