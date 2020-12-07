#pragma once
#include "IStringConvertable.h"
#include <chrono>
using namespace std::chrono;
class DateTime : public IStringConvertable {
public:
	DateTime() = default;
	DateTime(int day, int month, int year, int departure_time_hours,int arrival_time_hours,
			 int arrival_time_minutes, int departure_time_minutes) {
		
		_day = day;
		_month = month;
		_year = year;

		_arrival_time_hours = (hours)arrival_time_hours;
		_arrival_time_minutes = (minutes)arrival_time_minutes;
		_departure_time_hours = (hours)departure_time_hours;
		_departure_time_minutes = (minutes)departure_time_minutes;
	}

	DateTime(int day, int month, int year) {
		_day = day;
		_month = month;
		_year = year;
	}

	DateTime(int departure_time_hours, int arrival_time_hours,
			 int arrival_time_minutes, int departure_time_minutes) {

		_arrival_time_hours = (hours)arrival_time_hours;
		_arrival_time_minutes = (minutes)arrival_time_minutes;
		_departure_time_hours = (hours)departure_time_hours;
		_departure_time_minutes = (minutes)departure_time_minutes;
	}

	bool operator<(const DateTime& other)  const;
	int GetDaysCount() const;
	static int GetDaysCountInMonth(int month, int year);
	static int GetDaysCountInYear(int year);

	std::string To_String() const override;
	
	
private:
	int _day, _month, _year;
	hours _departure_time_hours, _arrival_time_hours;
	minutes _arrival_time_minutes, _departure_time_minutes;
};