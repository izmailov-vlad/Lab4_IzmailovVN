#pragma once
#include <string>
class IStringConvertable {
public:
	virtual std::string To_String() const = 0;
};