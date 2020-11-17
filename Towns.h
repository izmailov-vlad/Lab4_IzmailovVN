#pragma once
#include "IStringConvertable.h"
#include <string>
class Towns : public IStringConvertable {
public:
	Towns() = default;
	Towns(const std::string& from_town, const std::string& to_town) {
		_from_town = from_town;
		_to_town = to_town;
	}

	std::string To_String() const override;

	std::string GetFromTown() const {
		return _from_town;
	}

	std::string GetToTown() const {
		return _to_town;
	}

private:
	std::string _from_town;
	std::string _to_town;
};