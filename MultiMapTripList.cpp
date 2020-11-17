#include "MultiMapTripList.h"

void MultiMapTripList::Add(const Flight& flight) {
	_container.insert(std::make_pair(flight.GetInitialDate(), flight));
}

std::string MultiMapTripList::To_String() const
{

	std::stringstream str;
	for (auto& flight : _container) {
		str << flight.second.To_String() << "\n";
	}
	return str.str();
}

std::vector<Flight> MultiMapTripList::Find(std::function<bool(const Flight& flight)> predicate) const
{
	std::vector<Flight> finded;

	for (auto& flight : _container) {
		if (predicate(flight.second)) {
			finded.push_back(flight.second);
		}
	}
	finded.shrink_to_fit();
	return finded;
}

std::vector<Flight> MultiMapTripList::FindFlightByKey(const Date& key) const
{
	auto range = _container.equal_range(key);
	std::vector<Flight> finded;

	for (auto i = range.first; i != range.second; i++) {
		finded.push_back(i->second);
	}

	finded.shrink_to_fit();
	return finded;
}
