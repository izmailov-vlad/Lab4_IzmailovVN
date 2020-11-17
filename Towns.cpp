#include "Towns.h"
#include <sstream>
#include <iostream>
std::string Towns::To_String() const
{
	std::stringstream buf;
	buf << _from_town << " -> " << _to_town;
	return buf.str();
}
