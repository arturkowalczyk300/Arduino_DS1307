#include "Arduino_DS1307.h"

bool testConnection()
{
	return false;
}

TIME_DATE_STRUCT Arduino_DS1307::readTimeDate()
{
	byte secondsByte;
	byte minutesByte;
	byte hoursByte;
	byte daysByte;
	byte monthsByte;
	byte yearsByte;

	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(0x00); //minutes register
	Wire.endTransmission();

	delay(50);
	Wire.requestFrom(SLAVE_ADDRESS, 7);
	delay(50);
	if (Wire.available() >= 7)
	{
		secondsByte = Wire.read();
		minutesByte = Wire.read();
		hoursByte = Wire.read();
		Wire.read(); //skip day of week register
		daysByte = Wire.read();
		monthsByte = Wire.read();
		yearsByte = Wire.read();
	}

	int hours = 0, minutes = 0, seconds = 0, days = 0, months = 0, years = 0;
	//calculate minutes
	seconds = parse(secondsByte, PARSE_SECONDS);
	minutes = parse(minutesByte, PARSE_MINUTES);
	hours = parse(hoursByte, PARSE_HOURS);
	days = parse(daysByte, PARSE_DAYS);
	months = parse(monthsByte, PARSE_MONTHS);
	years = parse(yearsByte, PARSE_YEARS);

	return TIME_DATE_STRUCT(hours, minutes, seconds, days, months, years);
}

bool Arduino_DS1307::writeTimeDate(TIME_DATE_STRUCT timeDate, byte flagByte)
{
	if ((flagByte & WRITE_SECONDS) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x00);
		Wire.write(toRawByte(timeDate.seconds));
		Wire.endTransmission();
	}

	if ((flagByte & WRITE_MINUTES) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x01);
		Wire.write(toRawByte(timeDate.minutes));
		Wire.endTransmission();
	}

	if ((flagByte & WRITE_HOURS) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x02);
		Wire.write(toRawByte(timeDate.hours));
		Wire.endTransmission();
	}

	if ((flagByte & WRITE_DAYS) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x04);
		Wire.write(toRawByte(timeDate.day));
		Wire.endTransmission();
	}

	if ((flagByte & WRITE_MONTHS) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x05);
		Wire.write(toRawByte(timeDate.month));
		Wire.endTransmission();
	}

	if ((flagByte & WRITE_YEARS) >= 1)
	{
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(0x06);
		Wire.write(toRawByte(timeDate.year));
		Wire.endTransmission();
	}

	return false;
}

int Arduino_DS1307::parse(byte rawByte, byte flagByte)
{
	if ((flagByte & PARSE_SECONDS) >= 1 || (flagByte & PARSE_MINUTES) >= 1)
	{
		byte unitsByte = rawByte & 0b00001111;
		byte tensByte = (rawByte & 0b01110000) >> 4;
		return ((int)tensByte) * 10 + (int)unitsByte;
	}
	if ((flagByte & PARSE_HOURS) >= 1)
	{
		int hours = 0;
		byte onlyUnitsByte = rawByte & 0b00001111;
		bool is12HourMode = (rawByte & 0b01000000) >> 6; //if bit 6 is high, the mode is 12 hour
		if (is12HourMode == false)						 //24hour mode
		{
			byte onlyTensByte = (rawByte & 0b00110000) >> 4;
			hours = ((int)onlyTensByte) * 10 + (int)onlyUnitsByte;
		}
		else //12 hour mode
		{
			bool isPM = (rawByte & 0b00100000) >> 5; //if high, time range is PM
			byte onlyTensByte = (rawByte & 0b00010000) >> 4;
			hours = ((int)onlyTensByte) * 10 + (int)onlyUnitsByte + (isPM ? 12 : 0);
		}
		return hours;
	}
	if ((flagByte & PARSE_DAYS) >= 1)
	{
		byte onlyUnitsByte = rawByte & 0b00001111;
		byte onlyTensByte = (rawByte & 0b00110000) >> 4;
		return ((int)onlyTensByte) * 10 + (int)onlyUnitsByte;
	}
	if ((flagByte & PARSE_MONTHS) >= 1)
	{
		byte onlyUnitsByte = rawByte & 0b00001111;
		byte onlyTensByte = (rawByte & 0b00010000) >> 4;
		return ((int)onlyTensByte) * 10 + (int)onlyUnitsByte;
	}

	if ((flagByte & PARSE_YEARS) >= 1)
	{
		byte onlyUnitsByte = rawByte & 0b00001111;
		byte onlyTensByte = (rawByte & 0b11110000) >> 4;
		return ((int)onlyTensByte) * 10 + (int)onlyUnitsByte;
	}
	return -1; //variable flagByte has no valid format
}

byte Arduino_DS1307::toRawByte(int value)
{
	byte toWrite = 0;

	int units = value % 10;
	int tens = value / 10.0;

	byte unitsByte = units;
	byte tensByte = tens;

	toWrite |= tensByte;
	toWrite <<= 4;
	toWrite |= unitsByte;
	return toWrite;
}
