#ifndef ARDUINO_DS1307_H
#define ARDUINO_DS1307_H

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x68

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
	TIME_DATE_STRUCT(unsigned int hours, unsigned int minutes, unsigned int seconds, unsigned int day, unsigned int month, unsigned int year )
	{
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
		this->day = day;
		this->month = month;
		this->year = year;
	}
	
};

bool testConnection();
TIME_DATE_STRUCT readTime();
TIME_DATE_STRUCT readDate();
TIME_DATE_STRUCT readTimeDate();

bool writeTime(TIME_DATE_STRUCT time);
bool writeDate(TIME_DATE_STRUCT date);
bool writeTimeDate(TIME_DATE_STRUCT timeDate);

int parseSeconds(byte secondsByte);
int parseMinutes(byte minutesByte);
int parseHours(byte hoursByte);
int parseDays(byte daysByte);
int parseMonths(byte monthsByte);
int parseYears(byte yearsByte);

byte toSecondsByte(int seconds);
byte toMinutesByte(int minutes);
byte toHoursByte(int hours);
byte toDaysByte(int seconds);
byte toMonthsByte(int months);
byte toYearsByte(int years);

#endif