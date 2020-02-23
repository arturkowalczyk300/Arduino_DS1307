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
	
	int hours=0, minutes=0, seconds=0, days=0, months=0, years=0;
	//calculate seconds
	byte onlySecondsByte = secondsByte & 0b00001111;
	byte onlyTenSecondsByte = (secondsByte & 0b01110000) >> 4;
	seconds = ((int)onlyTenSecondsByte) * 10 + (int)onlySecondsByte;
	
	//calculate minutes 
	byte onlyminutesByte = minutesByte & 0b00001111;
	byte onlyTenminutesByte = (minutesByte & 0b01110000) >> 4;
	minutes = ((int)onlyTenminutesByte) * 10 + (int)onlyminutesByte;
	
	//calculate hours
	byte onlyhoursByte = hoursByte & 0b00001111;
	byte onlyTenhoursByte = (hoursByte & 0b01110000) >> 4;
	hours = ((int)onlyTenhoursByte) * 10 + (int)onlyhoursByte;
	
	
	//calculate days
	byte onlyDaysByte = daysByte & 0b00001111;
	byte onlyTenDaysByte = (daysByte & 0b00110000) >> 4;
	days = ((int)onlyTenDaysByte) * 10 + (int)onlyDaysByte;
	
	//calculate months
	byte onlyMonthsByte = monthsByte & 0b00001111;
	byte onlyTenMonthsByte = (monthsByte & 0b00010000) >> 4;
	months = ((int)onlyTenMonthsByte) * 10 + (int)onlyMonthsByte;
	
	//calculate Years
	byte onlyYearsByte = yearsByte & 0b00001111;
	byte onlyTenYearsByte = (yearsByte & 0b11110000) >> 4;
	years = ((int)onlyTenYearsByte) * 10 + (int)onlyYearsByte;
	
	
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
