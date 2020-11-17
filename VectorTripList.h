#pragma once
#include "IContainer.h"
#include <string>
#include <sstream>
class VectorTripList : public IContainer{
public:
	void Add(const Flight& flight) override;

	std::string To_String()const  override ;

	std::vector<Flight> Find(std::function<bool(const Flight&)> predicate) const override;

	std::vector<Flight> FindFlightByKey(const Date& key)const override;

private:
	std::vector<Flight> _container;
};