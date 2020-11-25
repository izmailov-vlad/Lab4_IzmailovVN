#pragma once
#include "IContainer.h"
#include <string>
#include <sstream>
class VectorTripList : public IContainer{
public:
	void Add(const Flight& flight) override;

	std::string To_String()const  override ;

	std::vector<Flight> Find(std::string& key, int indexOfMap) override;

private:
	std::vector<Flight> _container;
};