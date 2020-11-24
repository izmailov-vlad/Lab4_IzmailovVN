#include "ConsoleInteractor.h"
#include "FlightParser.h"
#include "FlightBuilder.h"
#include "SheduleBuilder.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
template<typename T>
void ConsoleInteractor::ReadVar(T& var) const
{
	string input;
	cin >> input;
	istringstream sin(input);

	char c;

	if (!(sin >> var) || (sin >> c))
	{
		throw std::runtime_error("Input error. Failed to enter a variable");
	}
}

void ConsoleInteractor::Start()
{
	int command;
	if (!Init()) {
		return;
	}

	PrintCommands();

	
	while (true) {
		try {
				command = ReadCommand();
				switch (command) {
				case 0: return;
				case 1: {
					ReadFileAndBuildFlight();
					break;
				}
				case 2: {
					ChoosePredicateAndFindFlight();
					break;
				}
				case 3: {
					PrintFlightShedule();
					break;
				}
				case 4: {
					system("cls");
					PrintCommands();
					break;
				}
				default: {
					cout << "Wrong command, Try again";
					break;
				}
			}
		}
		catch (std::exception& err) {
			cout << err.what() << endl;
		}
	}

}

bool ConsoleInteractor::Init()
{
	std::string type;
	while (true) {
		try {
			cout << "Input type of container: ";
			cin >> type;

			SheduleBuilder builder;

			ToUniqueFormat(type);

			if (type.compare("EXIT") == 0) {
				return false;
			}

			_container = builder.BuildFromType(type);
			return true;
		}
		catch (std::exception& err) {
			cout << err.what() << endl;
			cout << "Wrong type, try again" << endl;
		}
	}
	

	return false;
}

int ConsoleInteractor::ReadCommand() const
{
	int command;
	cout << "Input command: ";
	ReadVar(command);

	return command;
}

void ConsoleInteractor::ChoosePredicateAndFindFlight() const
{
	ShowPredicates();
	int indexOfPredicate;
	std::vector<Flight> finded;
	ReadVar(indexOfPredicate);

	switch (indexOfPredicate) {
		case 1: {
			std::string date;
			cout << "Input date in format (DD.MM.YY): ";
			ReadVar(date);

			finded = _container->Find(date, indexOfPredicate);

			break;
			
		}
		case 2: {
			std::string time;
			cout << "Input time in format (HH:mm-HH:mm)" << endl;
			ReadVar(time);

			finded = _container->Find(time, indexOfPredicate);
			break;
		}
		

		case 3: {
			std::string town;
			cout << "Input Town From: ";
			ReadVar(town);

			finded = _container->Find(town, indexOfPredicate);
			break;
		}
		case 4: {
			std::string town;
			cout << "Input Town In: ";
			ReadVar(town);

			finded = _container->Find(town, indexOfPredicate);
			break;
		}
		case 5: {
			std::string code;
			cout << "Input flight code: ";
			ReadVar(code);

			finded = _container->Find(code, indexOfPredicate);
		}
	}

	for (auto& el : finded) {
		cout << el.To_String() << endl;
	}
	cout << endl;
}

void ConsoleInteractor::ReadFileAndBuildFlight()
{
	std::string file;
	cout << "Enter file name: ";
	cin >> file;

	FlightParser parse;
	FlightBuilder builder;

	auto parsedFile = parse.Parse(file);
	auto buildedFlights = builder.Build(parsedFile);

	for (auto& flight : buildedFlights) {
		_container->Add(flight);
	}

	cout << "success" << endl;

}

void ConsoleInteractor::PrintFlightShedule() const
{
	cout << _container->To_String() << endl;
}

void ConsoleInteractor::ShowPredicates() const
{
	cout << "Predicates: 1: Find flights by date" << endl;
	cout << "            2: Find flights by time" << endl;
	cout << "            3: Find flights by town from" << endl;
	cout << "            4: Find flights by town in" << endl;
	cout << "            5: Find flights by code" << endl;

}

void ConsoleInteractor::PrintCommands() const
{
	system("cls");
	cout << "1. Read file" << endl;
	cout << "2. Predicates" << endl;
	cout << "3. Show Flgiht Shedule" << endl;
	cout << "4. Clear console" << endl;
}

void ConsoleInteractor::ToUniqueFormat(std::string& typeForFormat) const
{
	for (auto& letter : typeForFormat) {
		letter = toupper(letter);
	}

}
