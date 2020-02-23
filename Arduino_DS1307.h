#ifndef ARDUINO_DS1307_H
#define ARDUINO_DS1307_H

#include <Arduino.h>
#include <Wire.h>

struct TIME_DATE_STRUCT
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
	unsigned int hour;
	unsigned int day;	
	unsigned int month;
	unsigned int year;
		
	TIME_DATE_STRUCT(unsigned int hours, unsigned int minutes, unsigned int seconds);
	TIME_DATE_STRUCT(unsigned int hours, unsigned int minutes, unsigned int seconds, unsigned int day, unsigned int month, unsigned int year );
	
};

bool testConnection();
TIME_DATE_STRUCT readTime();
TIME_DATE_STRUCT readDate();
TIME_DATE_STRUCT readTimeDate();

bool writeTime(TIME_DATE_STRUCT time);
bool writeDate(TIME_DATE_STRUCT date);
bool writeTimeDate(TIME_DATE_STRUCT timeDate);

#endif