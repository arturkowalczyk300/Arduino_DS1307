#include "Arduino_DS1307.h"

bool testConnection()
{
		return false;
}


TIME_DATE_STRUCT readTime()
{
	return TIME_DATE_STRUCT(12, 30, 59, 0, 0, 0);
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
