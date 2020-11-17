#pragma once
#include "IContainer.h"
#include <sstream>
#include <string>
#include <map>
class MultiMapTripList : public IContainer {
public:
	void Add(const Flight& flight) override;

	std::string To_String()const  override;

	std::vector<Flight> Find(std::function<bool(const Flight&)> predicate) const override;

	std::vector<Flight> FindFlightByKey(const Date& key) const override;

private:
	std::multimap<Date, Flight> _container;
};