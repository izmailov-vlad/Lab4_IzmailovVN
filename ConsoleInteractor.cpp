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

				case 0: return;

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
					throw std::runtime_error(R"(Wrong command, try again)");
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
	if (_flightsStorage.IsEmpty()) {
		throw std::runtime_error("\nInclude file with flights first\n");
	}
	
	FindCommands();
	int indexOfPredicate;
	std::vector<Flight*> finded;

	cout << "\nInput index of command: ";
	ReadVar(indexOfPredicate);
	
	switch (indexOfPredicate) {
		case FIND_BY_DATE_TIME: {
			finded = FindFlightByDateTime();
			break; 
		}
		case FIND_BY_AIRPORTS_AND_DATE: {
			finded = FindFlightByAirportsAndDate();
			break;
		}
		
		case FIND_BY_ARRIVAL: {
			finded = FindFlightByArrivalAirport();
			break;
		}
		case FIND_BY_DEPARTURE: {
			finded = FindFlightByDepartureAirport();
			break;
		}
		case FIND_BY_CODE: {
			finded.push_back(FindFlightByFlightCode());
			break; 
		}
		default: {
			std::runtime_error(R"(Wrong command, try again)");
		}
	}

	for (auto& el : finded) {
		cout << el->To_String() << endl;
	}
	cout << endl;
}

void ConsoleInteractor::UpdateStorage()
{

	if (_flightsStorage.IsEmpty()) {
		throw std::runtime_error("\nInclude file with flights first\n");
	}

	UpdateCommands();
	int indexOfPredicate;
	std::vector<Flight*> finded;
	ReadVar(indexOfPredicate);


	switch (indexOfPredicate) {

		case UPDATE_DATE_TIME: {
			UpdateDateTime();
			break;
		}

		case UPDATE_DATE: {
			UpdateDate();
			break;
		}

		case UPDATE_AIRPORT: {
			UpdateAirport();
			break;
		}
		
		default: {
			std::runtime_error(R"(Wrong command, try again)");
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

	cout << "\nSuccess\n" << endl;

}

void ConsoleInteractor::PrintFlightShedule()
{
	if (!_flightsStorage.IsEmpty()) {
		cout << _flightsStorage.To_String() << endl;
	}
	else {
		throw std::runtime_error("List is empty");
	}
}

void ConsoleInteractor::FindCommands() const
{
	cout << "\n";
	for (unsigned long i = 0; i <  _find_commands.size(); i++) {
		cout << "#" << i+1 << "\t" << _find_commands[i] << endl;
	}

}

void ConsoleInteractor::UpdateCommands() const
{
	cout << "\n";
	for (unsigned long i = 0; i < _update_commands.size(); i++) {
		cout<< "#" << i+1 << "\t" << _update_commands[i] << endl;
	}
}

void ConsoleInteractor::PrintCommands() const
{
	system("cls");
	cout << "\n";
	for (unsigned long i = 0; i < _info_menu.size(); i++) {
		cout << "#" << i+1 << "\t" << _info_menu[i] << endl;
	}

}

void ConsoleInteractor::UpdateDateTime()
{
	stringstream buf;
	FlightBuilder builder;
	std::string date;
	std::string time;
	std::string code;

	cout << "Input FlightCode: ";
	ReadVar(code);

	cout << "Input time in format HH:mm-HH:mm: " << endl;
	ReadVar(time);

	cout << "Input date format YY.MM.DD-YY.MM.DD: " << endl;
	ReadVar(date);

	buf << time + " " + date;

	DateTime date_time_obj = builder.ParseDateTime(buf);
	
	buf.clear();
	buf << code;
	FlightCode flight_code = builder.ParseCode(buf);

	_flightsStorage.UpdateDateTime(flight_code, date_time_obj);
}

void ConsoleInteractor::UpdateDate()
{
	stringstream buf;
	std::string date;
	std::string code;
	char flag;

	char skip;
	std::vector<int> new_date(3);

	cout << "Input FlightCode: ";
	ReadVar(code);

	cout << "Input new date: ";
	ReadVar(date);

	cout << "Input flag: (D - Deparutre date, A - Arrival date)";
	ReadVar(flag);

	buf << date;
	buf >> new_date[0] >> skip >> new_date[1] >> skip >> new_date[2];

	_flightsStorage.UpdateDate(code, new_date, flag);
}

void ConsoleInteractor::UpdateAirport()
{
	std::string airport;
	std::string flight_code;
	stringstream buf;
	char flag;

	FlightBuilder builder;
	FlightCode flight_code_obj;
	cout << "Input flight code: ";
	ReadVar(flight_code);


	buf << flight_code;
	flight_code_obj = builder.ParseCode(buf);

	cout << "Input aiport: ";
	ReadVar(airport);

	cout << "Input flag (D - Departure, A - Arrival) : ";
	ReadVar(flag);

	_flightsStorage.UpdateAirport(flight_code_obj, airport, flag);
}

std::vector<Flight*> ConsoleInteractor::FindFlightByDateTime()
{
	std::string time;
	std::string date;
	stringstream buf;
	DateTime date_time_obj;
	FlightBuilder builder;
	cout << "Input Date and Time " << endl;

	ReadVar(time);
	ReadVar(date);
	buf << time << " " << date;

	date_time_obj = builder.ParseDateTime(buf);

	return _flightsStorage.FindFlightsByDateTime(date_time_obj);
}

std::vector<Flight*> ConsoleInteractor::FindFlightByAirportsAndDate()
{
	stringstream buf;
	FlightBuilder builder;
	std::string arrival_airport;
	std::string departure_airport;
	std::string date;
	char flag;


	cout << "\nDeparture town: ";
	ReadVar(departure_airport);
	cout << "\n";

	cout << "Arrival town: ";
	ReadVar(arrival_airport);
	cout << "\n";

	cout << "Date: ";
	ReadVar(date);
	cout << "\n";

	cout << "Input flag (A - Airports and arrival date, D - Airports and departure date) : ";
	ReadVar(flag);

	buf << date;

	DateTime date_time_obj = builder.ParseDate(buf);
	switch (flag) {
		case'A': {
			AirportsAndArrivalDate airports_and_date{ date_time_obj.GetArrivalDate(),date_time_obj.GetDaysCount(), arrival_airport, departure_airport };
			return _flightsStorage.FindFlightsByAirportAndDate(airports_and_date);
			break;
		}
		case 'D': {
			AirportsAndDepartureDate airports_and_date{ date_time_obj.GetDepartureDate(),date_time_obj.GetDaysCount(), arrival_airport, departure_airport };
			return _flightsStorage.FindFlightsByAirportAndDate(airports_and_date);
			break;
		}
	}
}

std::vector<Flight*> ConsoleInteractor::FindFlightByArrivalAirport()
{
	cout << "Input arrival airport: ";
	std::string arrival_airport;
	ReadVar(arrival_airport);

	return _flightsStorage.FindFlightByArrivalAirports(arrival_airport);
}

std::vector<Flight*> ConsoleInteractor::FindFlightByDepartureAirport()
{
	cout << "Input departure airport: ";

	std::string departure_airport;
	ReadVar(departure_airport);

	return _flightsStorage.FindFlightByDepartureAirports(departure_airport);
}

Flight* ConsoleInteractor::FindFlightByFlightCode()
{
	cout << "Input flight code: ";

	FlightCode flight_code_obj;
	FlightBuilder builder;
	stringstream buf;
	std::string flight_code;

	ReadVar(flight_code);
	buf << flight_code;

	flight_code_obj = builder.ParseCode(buf);

	return _flightsStorage.FindFlightByCode(flight_code_obj);
}

void ConsoleInteractor::ToUniqueFormat(std::string& typeForFormat) const
{
	for (auto& letter : typeForFormat) {
		letter = toupper(letter);
	}

}
