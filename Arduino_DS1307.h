#ifndef ARDUINO_DS1307_H
#define ARDUINO_DS1307_H

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x68

#define WRITE_SECONDS 0x01
#define WRITE_MINUTES 0x02
#define WRITE_HOURS 0x04
#define WRITE_DAYS 0x08
#define WRITE_MONTHS 0x10
#define WRITE_YEARS 0x20
#define WRITE_ALL 0x3F

#define PARSE_SECONDS 0x01
#define PARSE_MINUTES 0x02
#define PARSE_HOURS 0x04
#define PARSE_DAYS 0x08
#define PARSE_MONTHS 0x10
#define PARSE_YEARS 0x20
struct TIME_DATE_STRUCT
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
	unsigned int hour;
	unsigned int day;
	unsigned int month;
	unsigned int year;

	TIME_DATE_STRUCT(unsigned int hours, unsigned int minutes, unsigned int seconds)
	{
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
	}
	TIME_DATE_STRUCT(unsigned int hours, unsigned int minutes, unsigned int seconds, unsigned int day, unsigned int month, unsigned int year)
	{
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
		this->day = day;
		this->month = month;
		this->year = year;
	}
};

class Arduino_DS1307
{
public:
	bool testConnection();
	TIME_DATE_STRUCT readTimeDate();
	bool writeTimeDate(TIME_DATE_STRUCT timeDate, byte flagByte);

	int parse(byte rawByte, byte flagByte);

	byte toRawByte(int value);
};
#endif