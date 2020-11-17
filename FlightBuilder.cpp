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
	int date[3];
	char dot;

	for (int i = 0; i < 2; i++)
	{
		if (!(sin >> date[i]) || !(sin >> dot))
		{
			throw std::runtime_error("Parsing data from stream error");
		}
	}

	if (!(sin >> date[2]))
	{
		throw std::runtime_error("Parsing data from stream error");
	}

	if (date[1] <= 0 || date[1] > 12
		|| date[2] <= 1900 || date[2] > 3000)
	{
		throw std::invalid_argument("Invalid data from stream");
	}

	return Date(date[0], date[1], date[2]);
}


Time FlightBuilder::ParseTime(std::istream& sin) const
{
	std::string time;
	char sym;
	sin >> sym;
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
