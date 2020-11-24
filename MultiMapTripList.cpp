#include "MultiMapTripList.h"

void MultiMapTripList::Add(const Flight& flight) {
	_indexByDate.insert(std::make_pair(flight.GetInitialDate().GetDate(), flight));
	_indexByTownFrom.insert(std::make_pair(flight.GetInitialTowns().GetFromTown(), flight));
	_indexByTownIn.insert(std::make_pair(flight.GetInitialTowns().GetToTown(), flight));
	_indexByCode.insert(std::make_pair(flight.GetInitialCode().GetCode(), flight));

}

std::string MultiMapTripList::To_String() const
{

	std::stringstream str;
	for (auto& flight : _indexByDate) {
		str << flight.second.To_String() << "\n";
	}
	return str.str();
}

std::vector<Flight> MultiMapTripList::SearchInMap(const std::multimap <std::string, Flight> map, std::string key) {
	auto range = map.equal_range(key);
	std::vector<Flight> finded;

	for (auto i = range.first; i != range.second; i++) {
		finded.push_back(i->second);
	}

	finded.shrink_to_fit();
	return finded;
}

std::vector<Flight> MultiMapTripList::Find(std::string key, int indexOfMap) 
{
	std::vector<Flight> finded;

	switch (indexOfMap) {
	case 1:
		finded = SearchInMap(_indexByDate, key);
		break;
	case 2:
		finded = SearchInMap(_indexByTime, key);
		break;
	case 3:
		finded = SearchInMap(_indexByTownFrom, key);
		break;
	case 4:
		finded = SearchInMap(_indexByTownIn, key);
		break;
	case 5:
		finded = SearchInMap(_indexByCode, key);
		break;
	}
	return finded;
}