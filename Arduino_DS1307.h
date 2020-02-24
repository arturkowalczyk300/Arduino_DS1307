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

	int parseSecondsMinutes(byte rawByte);
	int parseHours(byte hoursByte);
	int parseDays(byte daysByte);
	int parseMonths(byte monthsByte);
	int parseYears(byte yearsByte);

	byte toRawByte(int value);
};
#endif