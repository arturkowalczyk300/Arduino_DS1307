#include "Arduino_DS1307.h"

bool testConnection()
{
		return false;
}


TIME_DATE_STRUCT readTime()
{
	byte seconds;
	byte minutes;
	byte hours;
	byte days;
	byte months;
	byte years;
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x00); //seconds register
	Wire.endTransmission();
	
	delay(50);
	Wire.requestFrom(SLAVE_ADDRESS, 7);
	delay(50);
	if(Wire.available()>=7)
	{	
		seconds = Wire.read();
		minutes = Wire.read();
		hours = Wire.read();
		Wire.read(); //skip day of week register
		days = Wire.read();
		months = Wire.read();
		years = Wire.read();
	}
	
	return TIME_DATE_STRUCT(hours, minutes, seconds, days, months, years);
}
TIME_DATE_STRUCT readDate()
{
	return TIME_DATE_STRUCT(0, 0, 0, 2, 6, 1997);
}
TIME_DATE_STRUCT readTimeDate()
{
	return TIME_DATE_STRUCT(12, 30, 59, 2, 6, 1997);
}

bool writeTime(TIME_DATE_STRUCT time)
{
	return false;
}
bool writeDate(TIME_DATE_STRUCT date)
{
	return false;
}
bool writeTimeDate(TIME_DATE_STRUCT timeDate)
{
	return false;
	
}
