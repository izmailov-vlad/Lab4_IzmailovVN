#pragma once
#include "IStringConvertable.h"
#include <chrono>
using namespace std::chrono;

struct ArrivalDate {
	int _arrival_day, _arrival_month, _arrival_year;
};

struct DepartureDate {
	int _departure_day, _departure_month, _departure_year;
};

struct ArrivalTime {
	hours  _arrival_time_hours;
	minutes  _arrival_time_minutes;
};

struct DepartureTime {
	hours _departure_time_hours;
	minutes _departure_time_minutes;
};
class  DateTime: public IStringConvertable {
public:

	DateTime() = default;
	
	DateTime(int departure_time_hours, int departure_time_minutes,
			 int arrival_time_hours, int arrival_time_minutes,
			 int arrival_day, int arrival_month, int arrival_year,
			 int departure_day, int departure_month, int departure_year) {
		
		_arrival_date._arrival_day = arrival_day;
		_arrival_date._arrival_month = arrival_month;
		_arrival_date._arrival_year = arrival_year;

		_departure_date._departure_day = departure_day;
		_departure_date._departure_month = departure_month;
		_departure_date._departure_year = departure_year;

		_arrival_time._arrival_time_hours = (hours)arrival_time_hours;
		_arrival_time._arrival_time_minutes = (minutes)arrival_time_minutes;

		_departure_time._departure_time_hours = (hours)departure_time_hours;
		_departure_time._departure_time_minutes = (minutes)departure_time_minutes;
	}

	DateTime(int day, int month, int year) {
		_departure_date._departure_day = day;
		_departure_date._departure_month = month;
		_departure_date._departure_year = year;

		_arrival_date._arrival_day = day;
		_arrival_date._arrival_month = month;
		_arrival_date._arrival_year = year;
	}


	bool operator<(const DateTime& date)  const;

	int GetDaysCount() const;

	static int GetDaysCountInMonth(int month, int year);

	static int GetDaysCountInYear(int year);

	std::string To_String() const override;

	const ArrivalDate& GetArrivalDate() const {
		return _arrival_date;
	}

	const DepartureDate& GetDepartureDate() const {
		return _departure_date;
	}

	const ArrivalTime& GetArrivalTime() const {
		return _arrival_time;
	}

	const DepartureTime& GetDepartureTime() const {
		return _departure_time;
	}

	void SetArrivalDate(int arrival_day, int arrival_month, int arrival_year) {
		_arrival_date._arrival_day = arrival_day;
		_arrival_date._arrival_month = arrival_month;
		_arrival_date._arrival_year = arrival_year;
	}

	void SetDepartureDate(int departure_day, int departure_month, int departure_year) {
		_departure_date._departure_day = departure_day;
		_departure_date._departure_month = departure_month;
		_departure_date._departure_year = departure_year;
	}
	
	void SetDepartureTime(hours departure_time_hours, minutes departure_time_minutes) {
		_departure_time._departure_time_hours = departure_time_hours;
		_departure_time._departure_time_minutes = departure_time_minutes;
	}
	
	void SetArrivalTime(hours  arrival_time_hours, minutes arrival_time_minutes) {
		_arrival_time._arrival_time_hours = arrival_time_hours;
		_arrival_time._arrival_time_minutes = arrival_time_minutes;
	}

private:

	ArrivalDate _arrival_date;
	
	DepartureDate _departure_date;

	ArrivalTime _arrival_time;

	DepartureTime _departure_time;
};