#pragma once
#include "IStringConvertable.h"
class Time  : public IStringConvertable{
public:
	Time() = default;
	Time(const std::string& time) {
		_time = time;
	}

	std::string To_String() const override;

	std::string GetTime() const {
		return _time;
	}

private:
	std::string _time;
};