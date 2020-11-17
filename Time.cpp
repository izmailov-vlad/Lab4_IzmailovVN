#include "Time.h"
#include <iostream>
#include <sstream>
std::string Time::To_String() const
{
	std::stringstream buf;
	buf << _time << " ";
	return buf.str();
}
