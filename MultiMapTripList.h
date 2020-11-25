#pragma once
#include "IContainer.h"
#include <sstream>
#include <string>
#include <map>
class MultiMapTripList : public IContainer {
public:

	void Add(const Flight& flight) override;

	std::string To_String()const  override;

	std::vector<Flight> Find(std::string& key, int indexOfMap) override;

	std::vector<Flight> SearchInMap(const std::multimap<std::string, Flight>& map, std::string& key);
private:

	std::multimap<std::string, Flight> _indexByDate;
	std::multimap<std::string, Flight> _indexByTownFrom;
	std::multimap<std::string, Flight> _indexByTownIn;
	std::multimap<std::string, Flight> _indexByTime;
	std::multimap<std::string, Flight> _indexByCode;
};