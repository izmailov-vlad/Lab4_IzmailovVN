#pragma once
#include "Flight.h"
#include <vector>
class FlightBuilder {
public:	
	Flight Build(const std::string& data) const;

	std::vector<Flight> Build(const std::vector<std::string> &data) const;

	DateTime ParseDateTime(std::istream& sin) const;
	DateTime ParseDate(std::istream& sin) const;
	std::vector<std::string> ParseAirports(std::istream& sin) const;
	FlightCode ParseCode(std::istream& sin) const;
};

