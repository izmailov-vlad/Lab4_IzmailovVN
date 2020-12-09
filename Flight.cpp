#include "Flight.h"
#include <sstream>
#include <iomanip>
std::string Flight::To_String() const
{
	std::ostringstream str;
	str << "\n" << std::setw(20) << _date_time.To_String() << "\t" << std::left << std::setw(40) << _departure_airport + "->" + _arrival_airport << std::setw(20) <<_code.To_String() <<  "\n";
	return str.str();
}
