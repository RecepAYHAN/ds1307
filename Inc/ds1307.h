/*
 * ds1307.h
 *
 *  Created on: 25 Tem 2019
 *      Author: recep
 */
#include "stm32f4xx_hal.h"
//#include "stm32f4xx.h"

extern I2C_HandleTypeDef hi2c1;

#ifndef DS1307_H_
#define DS1307_H_

#define DS1307_ADDRESS      0x68

#define SECOND_REGISTER    0x00
#define MINUTE_REGISTER    0x01
#define HOUR_REGISTER      0x02
#define DAY_REGISTER       0x03
#define DATE_REGISTER      0x04
#define MONTH_REGISTER     0x05
#define YEAR_REGISTER      0x06
#define CONTROL_REGISTER   0x07

#define SECOND_MASK        0x7F
#define MINUTE_MASK        0x7F
#define HOUR_MASK          0x3F
#define DAY_MASK           0x0F
#define DATE_MASK          0x3F
#define MONTH_MASK         0x1F
#define YEAR_MASK          0xFF
#define FLAG_MASK          0xFF

#define RESET_FLAG_ON      0x80
#define RESET_FLAG_OFF     0x00
#define TRICKLE_SETTING    0xA7

#define BCD2BIN(val) (((val)&15) + ((val)>>4)*10)
#define BIN2BCD(val) ((((val)/10)<<4) + (val)%10)


typedef struct {
    uint8_t year;       // year (0 - 99)
    uint8_t month;      // month (01 - 12)
    uint8_t date;       // date (01 - 31)
    uint8_t day;        // day (01 - 07)
    uint8_t hour;       // hour (00 - 23)
    uint8_t minutes;    // minutes (00 - 59)
    uint8_t seconds;    // seconds (00 - 59)
} rtc_ds1307_datetime_t;



uint8_t data_rec[6];
uint8_t data_read[1];
void ds1307_write(uint8_t reg, uint8_t value);


uint8_t ds1307_read_seconds();
uint8_t ds1307_read_minutes();
uint8_t ds1307_read_hour();
uint8_t ds1307_read_date();
uint8_t ds1307_read_month();
uint8_t ds1307_read_year();

void ds1307_get_rtc_datetime (rtc_ds1307_datetime_t *datetime);

void ds1307_init();

void ds1307_set_seconds(uint8_t value);
void ds1307_set_minutes(uint8_t value);
void ds1307_set_hours(uint8_t value);
void ds1307_set_date(uint8_t value);
void ds1307_set_month(uint8_t value);
void ds1307_set_year(uint8_t value);

void ds1307_set_date_time(rtc_ds1307_datetime_t* datetime);



#endif /* DS1307_H_ */
