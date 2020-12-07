#include "FlightCode.h"
#include <sstream>

std::string FlightCode::To_String() const
{
	std::ostringstream str(_code);
	return str.str();
}

bool FlightCode::operator<(const FlightCode& flight_code) const
{
	if (_code < flight_code._code) {
		return true;
	}
	return false;
}
