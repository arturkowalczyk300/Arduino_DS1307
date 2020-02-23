#include "Arduino_DS1307.h"

bool testConnection()
{
		return false;
}


TIME_DATE_STRUCT readTime()
{
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x00); //seconds register
	Wire.endTransmission();
	
	delay(50);
	
	Wire.requestFrom(SLAVE_ADDRESS, 1);
	byte temp;
	if(Wire.available())
	{
		temp = Wire.read();
	}
	
	return TIME_DATE_STRUCT(12, 30, (int)temp, 0, 0, 0);
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
