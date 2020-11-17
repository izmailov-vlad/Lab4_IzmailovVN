#include "Flight.h"
#include <sstream>
std::string Flight::To_String() const
{
	std::ostringstream str;

	str << _date.To_String() << " " << _time.To_String() << " " << _towns.To_String() << " " << _code.To_String() <<  "\n";
	return str.str();
}
