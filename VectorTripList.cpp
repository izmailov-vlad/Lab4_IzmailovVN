#include "VectorTripList.h"

void VectorTripList::Add(const Flight& flight)
{
	_container.push_back(flight);
}

std::string VectorTripList::To_String() const
{
	std::stringstream str;
	for (auto& flight : _container) {
		str << flight.To_String() << "\n";
	}
	return str.str();
}

std::vector<Flight> VectorTripList::Find(std::function<bool(const Flight&)> predicate) const
{
	std::vector<Flight> finded;

	for (auto& flight : _container) {
		if (predicate(flight)) {
			finded.push_back(flight);
		}
	}
	finded.shrink_to_fit();
	return finded;

}

std::vector<Flight> VectorTripList::FindFlightByKey(const Date& key) const
{
	auto predicate = [key](const Flight& flight) -> bool {
		if (flight.GetInitialDate() == key) {
			return true;
		}
		return false;
	};
	return Find(predicate);
}
