#include "ConsoleInteractor.h"
#include "FlightParser.h"
#include "FlightBuilder.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
template<typename T>
void ConsoleInteractor::ReadVar(T& var) const
{
	string input = "";
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

	PrintCommands();
	
	while (true) {
		try {
				command = ReadCommand();
				switch (command) {
				case 0: return; break;
				case BUILD_FLIGHT_STORE: {
					ReadFileAndBuildFlights();
					break;
				}
				case FIND_FLIGHTS: {
					FindFlights();
					break;
				}
				case UPDATE_FLIGHTS: {
					UpdateStorage();
					break;
				}
				case PRINT_STORAGE: {
					PrintFlightShedule();
					break;
				}
				case PRINT_MENU: {
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



int ConsoleInteractor::ReadCommand() const
{
	int command;
	cout << "Input command: ";
	ReadVar(command);

	return command;
}

void ConsoleInteractor::FindFlights()
{
	FindCommands();
	int indexOfPredicate;
	std::vector<Flight*> finded;
	stringstream buf;

	ReadVar(indexOfPredicate);

	switch (indexOfPredicate) {
		case FIND_BY_DATE_TIME: {

			std::string date_time;
			DateTime date_time_obj;
			FlightBuilder builder;
			cout << "Input Date and Time YY.MM.DD:(HH:mm-HH:mm)" << endl;

			ReadVar(date_time);
			buf << date_time;

			date_time_obj = builder.ParseDateTime(buf);

			finded = _flightsStorage.FindFlightsByDateTime(date_time_obj);

			break; 
		}
		case FIND_BY_ARRIVAL: {
			cout << "Input arrival airport: ";
			std::string arrival_airport;
			ReadVar(arrival_airport);

			finded = _flightsStorage.FindFlightByArrivalAirports(arrival_airport);
			break;
		}
		case FIND_BY_DEPARTURE: {
			cout << "Input departure airport: ";

			std::string departure_airport;
			ReadVar(departure_airport);

			finded = _flightsStorage.FindFlightByDepartureAirports(departure_airport);
			break;
		}
		case FIND_BY_CODE: {
			cout << "Input flight code: ";

			FlightCode flight_code_obj;
			FlightBuilder builder;
			stringstream buf;
			std::string flight_code;

			ReadVar(flight_code);
			buf << flight_code;

			flight_code_obj = builder.ParseCode(buf);

			finded.push_back(_flightsStorage.FindFlightByCode(flight_code_obj));
			break; 
		}
	}

	for (auto& el : finded) {
		cout << el->To_String() << endl;
	}
	cout << endl;
}

void ConsoleInteractor::UpdateStorage()
{
	UpdateCommands();
	int indexOfPredicate;
	std::vector<Flight*> finded;
	ReadVar(indexOfPredicate);


	switch (indexOfPredicate) {


		case UPDATE_DATE_TIME: {
			UpdateDateTime();
			break;
		}

		case UPDATE_ARRIVAL_AIRPORT: {
			UpdateArrivalAirport();
			break;
		}
		case UPDATE_DEPARTURE_AIRPORT: {
			UpdateDepartureAirport();
			break;
		}
		
	}
}

void ConsoleInteractor::ReadFileAndBuildFlights()
{
	std::string file;
	cout << "Enter file name: ";
	cin >> file;

	FlightParser parse;
	FlightBuilder builder;

	auto parsedFile = parse.Parse(file);
	auto buildedFlights = builder.Build(parsedFile);

	for (auto& flight : buildedFlights) {
		_flightsStorage.Add(flight);
	}

	cout << "success" << endl;

}

void ConsoleInteractor::PrintFlightShedule() const
{
	cout << _flightsStorage.To_String() << endl;
}

void ConsoleInteractor::FindCommands() const
{
	cout << "Commands For Find: 1: Find flights by date and time" << endl;
	cout << "					2: Find flights by arrival airport" << endl;
	cout << "					3: Find flights by departure airport" << endl;
	cout << "					4: Find flights by code" << endl;

}
void ConsoleInteractor::UpdateCommands() const
{
	cout << "Commands For Update: 1: Update flights by date and time" << endl;
	cout << "					  2: Update flights by  arrival airport" << endl;
	cout << "					  3: Update flights by departure airport" << endl;
}

void ConsoleInteractor::PrintCommands() const
{
	system("cls");
	cout << "1. Read file" << endl;
	cout << "2. Find Flights" << endl;
	cout << "3. Update Flights" << endl;
	cout << "4. Print Storage" << endl;
	cout << "5. Print Menu" << endl;

}

void ConsoleInteractor::UpdateDateTime()
{
	FlightBuilder builder;
	std::string date_time;
	std::string code;

	cout << "Input FlightCode: ";
	ReadVar(code);

	cout << "Input date and time in format (YY.MM.DD): (HH:mm-HH:mm)" << endl;
	ReadVar(date_time);

	stringstream buf;
	buf << date_time;

	DateTime date_time_obj = builder.ParseDateTime(buf);

	buf.clear();
	buf << code;
	FlightCode flight_code = builder.ParseCode(buf);

	_flightsStorage.UpdateDateTime(flight_code, date_time_obj);
}

void ConsoleInteractor::UpdateArrivalAirport()
{
	std::string arrival_aiport;
	std::string flight_code;
	stringstream buf;

	FlightBuilder builder;
	FlightCode flight_code_obj;
	cout << "Input flight code: ";
	ReadVar(flight_code);


	buf << flight_code;
	flight_code_obj = builder.ParseCode(buf);

	cout << "Input arrival aiport: ";
	ReadVar(arrival_aiport);

	_flightsStorage.UpdateArrivalAirport(flight_code_obj, arrival_aiport);
}

void ConsoleInteractor::UpdateDepartureAirport()
{
	std::string departure_airport;
	std::string flight_code;
	stringstream buf;

	FlightBuilder builder;
	FlightCode flight_code_obj;
	cout << "Input flight code: ";
	ReadVar(flight_code);


	buf << flight_code;
	flight_code_obj = builder.ParseCode(buf);

	cout << "Input arrival aiport: ";
	ReadVar(departure_airport);

	_flightsStorage.UpdateArrivalAirport(flight_code_obj, departure_airport);
}

void ConsoleInteractor::ToUniqueFormat(std::string& typeForFormat) const
{
	for (auto& letter : typeForFormat) {
		letter = toupper(letter);
	}

}
