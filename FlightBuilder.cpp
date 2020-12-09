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

	return Flight(date_time, airports[1], airports[0], code);
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
	int date[6];
	int time[4];

	for (int i = 0; i < 3; i++) {
		sin >> time[partOfTimeStructure++];
		sin >> skipSymbol;
	}
	sin >> time[partOfTimeStructure++];

	for (int i = 0; i < 5; i++) {
		sin >> date[partOfDateStructure++];
		sin >> skipSymbol;
	}
	sin >> date[partOfDateStructure++];
	
	return DateTime(time[0], time[1], time[2], time[3], date[0], date[1], date[2], date[3], date[4],
					date[5]);
}

DateTime FlightBuilder::ParseDate(std::istream& sin) const
{
	int date[3];
	int partOfDateStructure = 0;
	char skipSymbol;

	for (int i = 0; i < 2; i++) {
		sin >> date[partOfDateStructure++];
		sin >> skipSymbol;
	}
	sin >> date[partOfDateStructure++];
	return DateTime(date[0], date[1], date[2]);
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
