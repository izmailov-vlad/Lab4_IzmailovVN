#include "Date.h"
#include <iostream>
#include <sstream>
std::string Date::To_String() const
{
	std::stringstream buf;
	buf << _date;
	return buf.str();
}

//bool Date::operator==(const Date& date) const
//{
//	if (_day == date._day && _month == date._month && _year == date._year) {
//		return true;
//	}
//	return false;
//}

//bool Date::operator<(const Date& date) const
//{
//	int date1 = GetDaysCount();
//	int date2 = date.GetDaysCount();
//
//	if (date1 < date2)
//	{
//		return true;
//	}
//	return false;
//}

//int Date::GetDaysCount() const
//{
//	int res = _day;
//
//	for (int i = 1; i < _month; i++)
//	{
//		res += GetDaysCountInMonth(_month, _year);
//	}
//
//	int leapYearsCount = _year / 4;
//	int yearsCount = _year - leapYearsCount;
//
//	res += leapYearsCount * 366 + yearsCount * 365;
//
//	return res;
//}

//int Date::GetDaysCountInMonth(int month, int year)
//{
//	if (month == 4 || month == 6 || month == 9 || month == 11)
//	{
//		return 30;
//	}
//	else if (month == 2)
//	{
//		if (GetDaysCountInYear(year) == 365)
//		{
//			return 28;
//		}
//		else
//		{
//			return 29;
//		}
//	}
//	else
//	{
//		return 31;
//	}
//}

//int Date::GetDaysCountInYear(int year)
//{
//	if (year % 4 != 0 || year % 100 == 0 && year % 400 != 0)
//	{
//		return 365;
//	}
//
//	return 366;
//}

