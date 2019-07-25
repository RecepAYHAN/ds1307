/*
 * ds1307.c
 *
 *  Created on: 25 Tem 2019
 *      Author: recep
 */

#include "ds1307.h"

void ds1307_write(uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}

uint8_t ds1307_read_seconds()
{
	//HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), SECOND_REGISTER, 1, data_rec,6 ,100 );
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), SECOND_REGISTER, 1, data_rec,1,100 );
	return (BCD2BIN(data_rec[0] & SECOND_MASK));
}
uint8_t ds1307_read_minutes()
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), MINUTE_REGISTER, 1, data_rec,1 ,100 );
	return (BCD2BIN(data_rec[0] & MINUTE_MASK));
}
uint8_t ds1307_read_hour()
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), HOUR_REGISTER, 1, data_rec,1 ,100 );
	return (BCD2BIN(data_rec[0] & HOUR_MASK));
}
uint8_t ds1307_read_date()
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), DATE_REGISTER, 1, data_rec,1 ,100 );
	return (BCD2BIN(data_rec[0] & DATE_MASK));
}
uint8_t ds1307_read_month()
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), MONTH_REGISTER, 1, data_rec,1 ,100 );
	return (BCD2BIN(data_rec[0] & MONTH_MASK));
}
uint8_t ds1307_read_year()
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), YEAR_REGISTER, 1, data_rec,1 ,100 );
	return (BCD2BIN(data_rec[0] & YEAR_MASK));
}
void ds1307_get_rtc_datetime (rtc_ds1307_datetime_t *datetime)
{
	HAL_I2C_Mem_Read(&hi2c1,  (DS1307_ADDRESS << 1), SECOND_REGISTER, 1, data_rec,7 ,100 );

	datetime->seconds = BCD2BIN(data_rec[0]&SECOND_MASK);
	datetime->minutes = BCD2BIN(data_rec[1]&MINUTE_MASK);
	datetime->hour    = BCD2BIN(data_rec[2]&HOUR_MASK);
	datetime->day 	  = BCD2BIN(data_rec[3]&DAY_MASK);
	datetime->date    = BCD2BIN(data_rec[4]&DATE_MASK);
	datetime->month   = BCD2BIN(data_rec[5]&MONTH_MASK);
	datetime->year    = BCD2BIN(data_rec[6]&YEAR_MASK);
}

void ds1307_init()
{
	ds1307_write(CONTROL_REGISTER,0);
}
void ds1307_set_seconds(uint8_t value)
{
	uint8_t data[2];
	data[0] = SECOND_REGISTER;
	data[1] = (BIN2BCD(value) & SECOND_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_minutes(uint8_t value)
{
	uint8_t data[2];
	data[0] = MINUTE_REGISTER;
	data[1] = (BIN2BCD(value) & MINUTE_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_hours(uint8_t value)
{
	uint8_t data[2];
	data[0] = HOUR_REGISTER;
	data[1] = (BIN2BCD(value) & HOUR_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_date(uint8_t value)
{
	uint8_t data[2];
	data[0] = DATE_REGISTER;
	data[1] = (BIN2BCD(value) & DATE_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_month(uint8_t value)
{
	uint8_t data[2];
	data[0] = MONTH_REGISTER;
	data[1] = (BIN2BCD(value) & MONTH_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_year(uint8_t value)
{
	uint8_t data[2];
	data[0] = YEAR_REGISTER;
	data[1] = (BIN2BCD(value) & YEAR_MASK);
	HAL_I2C_Master_Transmit(&hi2c1, (DS1307_ADDRESS << 1), data , 2 ,100 );
}
void ds1307_set_date_time(rtc_ds1307_datetime_t* datetime)
{
	ds1307_set_seconds(datetime->seconds);
	ds1307_set_minutes(datetime->minutes);
	ds1307_set_hours(datetime->hour);
	ds1307_set_date(datetime->date);
	ds1307_set_month(datetime->month);
	ds1307_set_year(datetime->year);
}
