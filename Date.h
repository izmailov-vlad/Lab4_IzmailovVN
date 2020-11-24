#pragma once
#include "IStringConvertable.h"
class Date : public IStringConvertable {
public:
	Date() = default;
	Date(std::string  date) {
		_date = date;
	}

	std::string To_String() const override;
	
	std::string GetDate() {
		return _date;
	}

private:
	std::string _date;
};