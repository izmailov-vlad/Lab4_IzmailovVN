#pragma once
#include "IStringConvertable.h"
class Date : public IStringConvertable {
public:
	Date() = default;
	Date(int day, int month, int year) {
		_day = day;
		_month = month;
		_year = year;
	}

	std::string To_String() const override;
	int GetDaysCount() const;

	static int GetDaysCountInMonth(int month, int year);
	static int GetDaysCountInYear(int year);
	int GetDay() const{
		return _day;
	}

	int GetMonth() const {
		return _month;
	}

	int GetYear() const {
		return _year;
	}

	bool operator==(const Date& date) const;
	bool operator<(const Date& date) const;


private:
	int _day;
	int _month;
	int _year;
};