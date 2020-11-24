#include "FlightBuilder.h"
#include <istream>
#include <sstream>
#include <stdexcept>
Flight FlightBuilder::Build(const std::string& data) const
{
	std::istringstream sin(data);

	auto date = ParseDate(sin);
	auto time = ParseTime(sin);
	auto town = ParseTowns(sin);
	auto code = ParseCode(sin);


	return Flight(date, time, town, code);
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


Date FlightBuilder::ParseDate(std::istream& sin) const
{
	
	std::string date;
	sin >> date;
	date.erase(date.end() - 1);

	return Date(date);
}


Time FlightBuilder::ParseTime(std::istream& sin) const
{
	std::string time;

	if (!(sin >> time))
	{
		throw std::runtime_error("Parsing data from stream error");
	}

	return Time(time);
}


Towns FlightBuilder::ParseTowns(std::istream& sin) const
{
	std::string towns[2];
	std::string town;

	sin >> town;

	int i = 0;
	while (town[i] != '>') {
		towns[0] += town[i];
		i++;
	}
	i++;
	while (town[i] != '\0') {
		towns[1] += town[i];
		i++;
	}
	
	return Towns(towns[0], towns[1]);
}

FlightCode FlightBuilder::ParseCode(std::istream& sin) const
{
	std::string code;
	sin >> code;
	return FlightCode(code);
}
