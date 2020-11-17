#include "SheduleBuilder.h"
#include "VectorTripList.h"
#include "MultiMapTripList.h"

std::unique_ptr<IContainer> SheduleBuilder::BuildFromType(std::string& type)
{
	std::unique_ptr<IContainer> container;

	if (type.compare("VECTOR") == 0) {
		container = Build<VectorTripList>();
	}
	else if (type.compare("MULTIMAP") == 0) {
		container = Build<MultiMapTripList>();
	}

	return container;
}
