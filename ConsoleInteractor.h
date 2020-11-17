#pragma once
#include "IContainer.h"
#include <memory>
class ConsoleInteractor {
public:
	void Start();

private:

	std::unique_ptr<IContainer> _container;

	bool Init();
	int ReadCommand() const;

	void ChoosePredicateAndFindFlight() const;
	void ReadFileAndBuildFlight();
	void PrintFlightShedule() const;
	void ShowPredicates() const;
	void PrintCommands() const;

	void ToUniqueFormat(std::string& typeForFormat) const;

	template<typename T>
	void ReadVar(T& var) const;


};