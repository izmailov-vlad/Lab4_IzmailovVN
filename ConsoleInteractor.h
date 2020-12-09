#pragma once
#include "FlightsStorage.h"
#include <memory>
class ConsoleInteractor {
public:

	void Start();

private:

	FlightsStorage _flightsStorage;

	std::vector<std::string> _find_commands = {
		"Find flights by date and time",
		"Find flights by airports and date",
		"Find flights by arrival airport",
		"Find flights by departure airport",
		"Find flights by code"
	};

	std::vector<std::string> _update_commands = { 
		"Update	date and time of flight",
		"Update date of flight",
		"Update airport of flight",
	};

	std::vector<std::string> _info_menu = { 
		"Read file ",
		"Find Flights",
		"Update Flights",
		"Print Storage",
		"Print Menu" 
	};

	int ReadCommand() const;

	void FindFlights();

	void UpdateStorage();

	void ReadFileAndBuildFlights();

	void PrintFlightShedule();

	void PrintCommands() const;

	void UpdateDateTime();

	void UpdateDate();

	void UpdateAirport();

	std::vector<Flight*> FindFlightByDateTime();

	std::vector<Flight*> FindFlightByAirportsAndDate();

	std::vector<Flight*> FindFlightByArrivalAirport();

	std::vector<Flight*> FindFlightByDepartureAirport();

	Flight* FindFlightByFlightCode();

	void ToUniqueFormat(std::string& typeForFormat) const;

	void FindCommands() const;

	void UpdateCommands() const;

	template<typename T>
	void ReadVar(T& var) const;

	enum {
		UPDATE_DATE_TIME = 1,
		UPDATE_DATE,
		UPDATE_AIRPORT,
		DELETE_FLIGHT
	};

	enum {
		FIND_BY_DATE_TIME = 1,
		FIND_BY_AIRPORTS_AND_DATE,
		FIND_BY_ARRIVAL,
		FIND_BY_DEPARTURE,
		FIND_BY_CODE
	};

	enum {
		BUILD_FLIGHT_STORE = 1,
		FIND_FLIGHTS,
		UPDATE_FLIGHTS,
		PRINT_STORAGE,
		PRINT_MENU,
	};


};