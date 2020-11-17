#pragma once
#include <vector>
#include <string>
class FlightParser {
public:
	std::vector<std::string> Parse(std::string& filename);
};