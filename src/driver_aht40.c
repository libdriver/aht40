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
 * @file      driver_aht40.c
 * @brief     driver aht40 source file
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

#include "driver_aht40.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "ASAIR AHT40"        /**< chip name */
#define MANUFACTURER_NAME         "ASAIR"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.0f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                 /**< chip max supply voltage */
#define MAX_CURRENT               0.46f                /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           120.0f               /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief chip address definition
 */
#define AHT40_ADDRESS             0x88U        /**< iic device address */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to an aht40 handle structure
 * @param[out] *data pointer to a data buffer
 * @param[in]  len length of data
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_aht40_iic_read(aht40_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_cmd(AHT40_ADDRESS, data, len) != 0)        /* read the register */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to an aht40 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len length of data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_aht40_iic_write(aht40_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_write_cmd(AHT40_ADDRESS, data, len) != 0)        /* write the register */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     calculate the crc
 * @param[in] *data pointer to a data buffer
 * @param[in] len length of data
 * @return    crc
 * @note      none
 */
static uint8_t a_aht40_calc_crc(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t byte;
    uint8_t crc = 0xFF;
    
    for (byte = 0; byte < len; byte++)          /* len times */
    {
        crc ^= data[byte];                      /* xor byte */
        for (i = 8; i > 0; --i)                 /* one byte */
        {
            if ((crc & 0x80) != 0)              /* if high*/
            {
                crc = (crc << 1) ^ 0x31;        /* xor 0x31 */
            }
            else
            {
                crc = crc << 1;                 /* skip */
            }
        }
    }
    
    return crc;                                 /* return crc */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an aht40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 read status failed
 *            - 5 reset reg failed
 * @note      none
 */
uint8_t aht40_init(aht40_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->iic_init == NULL)                                      /* check iic_init */
    {
        handle->debug_print("aht40: iic_init is null.\n");             /* iic_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_deinit == NULL)                                    /* check iic_deinit */
    {
        handle->debug_print("aht40: iic_deinit is null.\n");           /* iic_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                  /* check iic_read_cmd */
    {
        handle->debug_print("aht40: iic_read_cmd is null.\n");         /* iic_read_cmd is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                 /* check iic_write_cmd */
    {
        handle->debug_print("aht40: iic_write_cmd is null.\n");        /* iic_write_cmd is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("aht40: delay_ms is null.\n");             /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }
    
    if (handle->iic_init() != 0)                                       /* iic init */
    {
        handle->debug_print("aht40: iic init failed.\n");              /* iic init failed */
        
        return 1;                                                      /* return error */
    }
    handle->delay_ms(10);                                              /* delay 10ms */
    handle->inited = 1;                                                /* flag finish initialization */
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an aht40 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t aht40_deinit(aht40_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                 /* iic deinit */
    {
        handle->debug_print("aht40: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                  /* return error */
    }
    handle->inited = 0;                                            /* set closed flag */
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle pointer to an aht40 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t aht40_read_temperature_humidity(aht40_handle_t *handle, uint16_t *temperature_raw, float *temperature_s,
                                        uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t buf[6];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    buf[0] = 0xFD;                                                    /* set the command */
    if (a_aht40_iic_write(handle, buf, 1) != 0)                       /* write the command */
    {
        handle->debug_print("aht40: sent command failed.\n");         /* sent command failed */
        
        return 1;                                                     /* return error */
    }
    handle->delay_ms(85);                                             /* delay 85ms */
    if (a_aht40_iic_read(handle, buf, 6) != 0)                        /* read data */
    {
        handle->debug_print("aht40: read data failed.\n");            /* read data failed */
        
        return 1;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 0, 2) != buf[2])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 3, 2) != buf[5])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    
    *humidity_raw = (((uint16_t)buf[3]) << 8) |
                    (((uint16_t)buf[4]) << 0);                        /* set the humidity */
    *humidity_s = (float)(*humidity_raw) / 65535.0f * 
                          125.0f - 6.0f;                              /* convert the humidity */
    *temperature_raw = (((uint16_t)buf[0]) << 8) |
                       (((uint16_t)buf[1]) << 0);                     /* set the temperature */
    *temperature_s = (float)(*temperature_raw) / 65535.0f *
                             175.0f - 45.0f;                          /* convert the temperature */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief      read the temperature
 * @param[in]  *handle pointer to an aht40 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t aht40_read_temperature(aht40_handle_t *handle, uint16_t *temperature_raw, float *temperature_s)
{
    uint8_t buf[6];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    buf[0] = 0xFD;                                                    /* set the command */
    if (a_aht40_iic_write(handle, buf, 1) != 0)                       /* write the command */
    {
        handle->debug_print("aht40: sent command failed.\n");         /* sent command failed */
        
        return 1;                                                     /* return error */
    }
    handle->delay_ms(85);                                             /* delay 85ms */
    if (a_aht40_iic_read(handle, buf, 6) != 0)                        /* read data */
    {
        handle->debug_print("aht40: read data failed.\n");            /* read data failed */
        
        return 1;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 0, 2) != buf[2])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 3, 2) != buf[5])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    
    *temperature_raw = (((uint16_t)buf[0]) << 8) |
                       (((uint16_t)buf[1]) << 0);                     /* set the temperature */
    *temperature_s = (float)(*temperature_raw) / 65535.0f *
                             175.0f - 45.0f;                          /* convert the temperature */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief      read the humidity data
 * @param[in]  *handle pointer to an aht40 handle structure
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t aht40_read_humidity(aht40_handle_t *handle, uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t buf[6];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    buf[0] = 0xFD;                                                    /* set the command */
    if (a_aht40_iic_write(handle, buf, 1) != 0)                       /* write the command */
    {
        handle->debug_print("aht40: sent command failed.\n");         /* sent command failed */
        
        return 1;                                                     /* return error */
    }
    handle->delay_ms(85);                                             /* delay 85ms */
    if (a_aht40_iic_read(handle, buf, 6) != 0)                        /* read data */
    {
        handle->debug_print("aht40: read data failed.\n");            /* read data failed */
        
        return 1;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 0, 2) != buf[2])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    if (a_aht40_calc_crc(buf + 3, 2) != buf[5])                       /* check the crc */
    {
        handle->debug_print("aht40: crc is error.\n");                /* crc is error */
        
        return 4;                                                     /* return error */
    }
    
    *humidity_raw = (((uint16_t)buf[3]) << 8) |
                    (((uint16_t)buf[4]) << 0);                        /* set the humidity */
    *humidity_s = (float)(*humidity_raw) / 65535.0f * 
                          125.0f - 6.0f;                              /* convert the humidity */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an aht40 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t aht40_set_reg(aht40_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    } 
    
    if (a_aht40_iic_write(handle, buf, len) != 0)        /* write data */
    {
        return 1;                                        /* return error */
    }
    
    return 0;                                            /* success return 0 */
}

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to an aht40 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t aht40_get_reg(aht40_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    } 
    
    if (a_aht40_iic_read(handle, buf, len) != 0)        /* read data */
    {
        return 1;                                       /* return error */
    }
    
    return 0;                                           /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an aht40 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t aht40_info(aht40_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(aht40_info_t));                          /* initialize aht40 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
