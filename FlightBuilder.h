#pragma once
#include "Flight.h"
#include <vector>
class FlightBuilder {
public:	
	Flight Build(const std::string& data) const;

	std::vector<Flight> Build(const std::vector<std::string> &data) const;

	//template<typename T>
	Date ParseDate(std::istream& sin) const;
	Time ParseTime(std::istream& sin) const;
	Towns ParseTowns(std::istream& sin) const;
	FlightCode ParseCode(std::istream& sin) const;
};

