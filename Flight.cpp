#include "Flight.h"
#include <sstream>
std::string Flight::To_String() const
{
	std::ostringstream str;

	str << _date_time.To_String() << " "  << _arrival_airport << "->" << _departure_airport <<" " <<_code.To_String() <<  "\n";
	return str.str();
}
