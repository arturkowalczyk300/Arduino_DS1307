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
	seconds = parseSeconds(secondsByte);
	minutes= parseMinutes(minutesByte);
	hours = parseHours(hoursByte);
	days = parseDays(daysByte);
	months = parseMonths(monthsByte);
	years = parseYears(yearsByte);
	
	
	
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
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x00);
	Wire.write(timeDate.seconds);
	Wire.endTransmission();
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x01);
	Wire.write(timeDate.minutes);
	Wire.endTransmission();
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x02);
	Wire.write(timeDate.hours);
	Wire.endTransmission();
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x04);
	Wire.write(timeDate.day);
	Wire.endTransmission();
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x05);
	Wire.write(timeDate.month);
	Wire.endTransmission();
	
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x06);
	Wire.write(timeDate.year);
	Wire.endTransmission();
	return false;
	
}


int parseSeconds(byte secondsByte)
{
	byte onlySecondsByte = secondsByte & 0b00001111;
	byte onlyTenSecondsByte = (secondsByte & 0b01110000) >> 4;
	return ((int)onlyTenSecondsByte) * 10 + (int)onlySecondsByte;
}
int parseMinutes(byte minutesByte)
{
	byte onlyminutesByte = minutesByte & 0b00001111;
	byte onlyTenminutesByte = (minutesByte & 0b01110000) >> 4;
	return ((int)onlyTenminutesByte) * 10 + (int)onlyminutesByte;
}
int parseHours(byte hoursByte)
{
	int hours=0;
	byte onlyhoursByte = hoursByte & 0b00001111;
	bool is12HourMode = (hoursByte & 0b01000000) >> 6; //if bit 6 is high, the mode is 12 hour
	if(is12HourMode == false ) //24hour mode
	{
		byte onlyTenhoursByte = (hoursByte & 0b00110000) >> 4;
		hours = ((int)onlyTenhoursByte) * 10 + (int)onlyhoursByte;
	}
	else  //12 hour mode
	{
		bool isPM = (hoursByte & 0b00100000) >> 5; //if high, time range is PM
		byte onlyTenhoursByte = (hoursByte & 0b00010000) >> 4;
		hours = ((int)onlyTenhoursByte) * 10 + (int)onlyhoursByte + (isPM ? 12 : 0 );
	}
	return hours;
}
int parseDays(byte daysByte)
{
	byte onlyDaysByte = daysByte & 0b00001111;
	byte onlyTenDaysByte = (daysByte & 0b00110000) >> 4;
	return ((int)onlyTenDaysByte) * 10 + (int)onlyDaysByte;
}
int parseMonths(byte monthsByte)
{
	byte onlyMonthsByte = monthsByte & 0b00001111;
	byte onlyTenMonthsByte = (monthsByte & 0b00010000) >> 4;
	return ((int)onlyTenMonthsByte) * 10 + (int)onlyMonthsByte;
}
int parseYears(byte yearsByte)
{
	byte onlyYearsByte = yearsByte & 0b00001111;
	byte onlyTenYearsByte = (yearsByte & 0b11110000) >> 4;
	return ((int)onlyTenYearsByte) * 10 + (int)onlyYearsByte;
}

byte toSecondsByte(int seconds);
byte toMinutesByte(int minutes);
byte toHoursByte(int hours);
byte toSecondsByte(int seconds);
byte toMonthsByte(int months);
byte toYearsByte(int years);
