#pragma once
#include "Flight.h"
#include "IContainer.h"
#include <utility>
#include <memory>
class SheduleBuilder {
public:
	template<typename TContainer>
	std::unique_ptr<IContainer> Build();

	std::unique_ptr<IContainer> BuildFromType(std::string& type);
};

template<typename TContainer>
inline std::unique_ptr<IContainer> SheduleBuilder::Build()
{
	if (!std::is_base_of<IContainer, TContainer> :: value) {
		throw std::exception("Wrong type of container");
	}

	return std::make_unique<TContainer>();
}
