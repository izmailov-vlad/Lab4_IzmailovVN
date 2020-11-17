#include "FlightParser.h"
#include <fstream>
std::vector<std::string> FlightParser::Parse(std::string& filename)
{
	std::ifstream file;
	
	file.open(filename, std::ios_base::in);
	if (!file.good()) {
		throw std::runtime_error("Can't open this file");
	}
	std::vector<std::string> textFromFile;
	std::string textLine;
	
	while (std::getline(file, textLine)) {
		textFromFile.push_back(std::move(textLine));
	}

	textFromFile.shrink_to_fit();

	return textFromFile;
}
