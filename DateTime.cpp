#include "DateTime.h"
#include <iostream>
#include <sstream>
#include <iomanip>
std::string DateTime::To_String() const
{
	std::stringstream buf;
	buf << std::setfill('0') << std::setw(2) << _departure_time._departure_time_hours.count() << ":" 
		<< std::setfill('0') << std::setw(2) << _departure_time._departure_time_minutes.count() << "-"
		<< std::setfill('0') << std::setw(2) << _arrival_time._arrival_time_hours.count() << ":"
		<< std::setfill('0') << std::setw(2) << _arrival_time._arrival_time_minutes.count()
		<< "\t"
		<< std::setfill('0') << std::setw(2) << _departure_date._departure_day << "." 
		<< std::setfill('0') << std::setw(2) << _departure_date._departure_month << "."
		<< std::setfill('0') << std::setw(2) << _departure_date._departure_year << "-"
		<< std::setfill('0') << std::setw(2) << _arrival_date._arrival_day << "." 
		<< std::setfill('0') << std::setw(2) << _arrival_date._arrival_month << "."
		<< std::setfill('0') << std::setw(4) << _arrival_date._arrival_year;

	return buf.str();
}


bool DateTime::operator<(const DateTime& date) const
{
	int date1 = GetDaysCount();
	int date2 = date.GetDaysCount();

	if (date1 < date2)
	{
		return true;
	}
	return false;
}

int DateTime::GetDaysCount() const
{
	int res = _arrival_date._arrival_day;

	for (int i = 1; i < _arrival_date._arrival_month; i++)
	{
		res += GetDaysCountInMonth(_arrival_date._arrival_month, _arrival_date._arrival_year);
	}

	int leapYearsCount = _arrival_date._arrival_year / 4;
	int yearsCount = _arrival_date._arrival_year - leapYearsCount;

	res += leapYearsCount * 366 + yearsCount * 365;

	return res;
}

int DateTime::GetDaysCountInMonth(int month, int year)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return 30;
	}
	else if (month == 2)
	{
		if (GetDaysCountInYear(year) == 365)
		{
			return 28;
		}
		else
		{
			return 29;
		}
	}
	else
	{
		return 31;
	}
}

int DateTime::GetDaysCountInYear(int year)
{
	if (year % 4 != 0 || year % 100 == 0 && year % 400 != 0)
	{
		return 365;
	}

	return 366;
}

