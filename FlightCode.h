#pragma once
#include <string>
#include "IStringConvertable.h"
class FlightCode :public IStringConvertable {
public:
	FlightCode() = default;
	FlightCode(const std::string& code) {
		_code = code;
	}

	std::string To_String() const override;

	const std::string& GetCode() {
		return _code;
	}

	bool operator < (const FlightCode& flight_code) const;

private:
	std::string _code;
};