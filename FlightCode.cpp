#include "FlightCode.h"
#include <sstream>

std::string FlightCode::To_String() const
{
	std::ostringstream str(_code);
	return str.str();
}
