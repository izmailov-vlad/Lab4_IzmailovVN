#pragma once
#include "Date.h"
#include "Time.h"
#include "Towns.h"
#include "FlightCode.h"
#include "IStringConvertable.h"

class Flight : public IStringConvertable {
public:
	Flight(const Date &date, const Time &time, const Towns& towns, const FlightCode& code) {
		_date = date;
		_time = time;
		_towns = towns;
		_code = code;
	}

	std::string To_String() const override;

	Date GetInitialDate() const {
		return _date;
	}

	Time GetInitialTime() const {
		return _time;
	}

	Towns GetInitialTowns() const {
		return _towns;
	}

	FlightCode GetInitialCode() const {
		return _code;
	}
private:
	Date _date;
	Time _time;
	Towns _towns;
	FlightCode _code;
};