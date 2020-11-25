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

std::vector<Flight> VectorTripList::Find(std::string& key, int indexOfPredicate)
{
	std::vector<Flight> finded;
	std::function<bool(const Flight&)> predicate;

	switch (indexOfPredicate) {
		case 1: {
			predicate = [key](const Flight& flight) -> bool {
				if (flight.GetInitialDate().GetDate() == key) {
					return true;
				}
				return false;
			};
			break; 
		}
		case 2: {
			predicate = [key](const Flight& flight) -> bool {
				if (flight.GetInitialTime().GetTime() == key) {
					return true;
				}
				return false;
			};
			break;
		}
		case 3: {
			predicate = [key](const Flight& flight) -> bool {
				if (flight.GetInitialTowns().GetFromTown() == key) {
					return true;
				}
				return false;
			};
			break; 
		}
		case 4: {
			predicate = [key](const Flight& flight) -> bool {
				if (flight.GetInitialTowns().GetToTown() == key) {
					return true;
				}
				return false;
			};
			break;
		}
		case 5: {
			predicate = [key](const Flight& flight) -> bool {
				if (flight.GetInitialCode().GetCode() == key) {
					return true;
				}
				return false;
			}; 
			break;
		}
	}

	for (auto& flight : _container) {
		if (predicate(flight)) {
			finded.push_back(flight);
		}
	}
	finded.shrink_to_fit();
	return finded;

}
