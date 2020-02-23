#include "Arduino_DS1307.h"

bool testConnection()
{
		return false;
}


TIME_DATE_STRUCT readTime()
{
	byte secondsByte;
	byte minutesByte;
	byte hoursByte;
	byte daysByte;
	byte monthsByte;
	byte yearsByte;
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x00); //seconds register
	Wire.endTransmission();
	
	delay(50);
	Wire.requestFrom(SLAVE_ADDRESS, 7);
	delay(50);
	if(Wire.available()>=7)
	{	
		secondsByte = Wire.read();
		minutesByte = Wire.read();
		hoursByte = Wire.read();
		Wire.read(); //skip day of week register
		daysByte = Wire.read();
		monthsByte = Wire.read();
		yearsByte = Wire.read();
	}
	
	//calculate seconds
	byte onlySecondsByte = secondsByte & 0b00001111;
	byte onlyTenSecondsByte = (secondsByte & 0b01110000) >> 4;
	int hours=0, minutes=0, seconds=0, days=0, months=0, years=0;
	seconds = ((int)onlyTenSecondsByte) * 10 + (int)onlySecondsByte;
	
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
