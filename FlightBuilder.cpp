#include "FlightBuilder.h"
#include <istream>
#include <sstream>
#include <stdexcept>
#include <chrono>
Flight FlightBuilder::Build(const std::string& data) const
{
	std::istringstream sin(data);

	auto date_time = ParseDateTime(sin);
	auto airports = ParseAirports(sin);
	auto code = ParseCode(sin);


	return Flight(date_time, airports[0], airports[1], code);
}

std::vector<Flight> FlightBuilder::Build(const std::vector<std::string>& data) const
{
	std::vector<Flight> flights;

	for (auto& elem : data) {
		flights.push_back(Build(elem));
	}

	flights.shrink_to_fit();

	return flights;
}


DateTime FlightBuilder::ParseDateTime(std::istream& sin) const
{
	char skipSymbol;
	int partOfDateStructure = 0;
	int partOfTimeStructure = 0;
	int date[3];
	int time[4];

	for (int i = 0; i < 3; i++) {
		sin >> date[partOfDateStructure++];
		sin >> skipSymbol;
	}

	for (int i = 0; i < 4; i++) {
		sin >> skipSymbol;
		sin >> time[partOfTimeStructure++];
	}
	sin >> skipSymbol;
	
	return DateTime(date[0],date[1],date[2], time[0], time[2], time[1], time[3]);
}



std::vector<std::string> FlightBuilder::ParseAirports(std::istream& sin) const
{
	

	std::vector<std::string> airports(2);
	std::string buf_airports;

	sin >> buf_airports;

	int i = 0;
	while (buf_airports[i] != '>') {
		airports[0].push_back(buf_airports[i]);
		i++;
	}
	i++;
	while (buf_airports[i] != '\0') {
		airports[1].push_back(buf_airports[i]);
		i++;
	}
	
	return airports;
}

FlightCode FlightBuilder::ParseCode(std::istream& sin) const
{
	std::string code;
	sin >> code;
	return FlightCode(code);
}
