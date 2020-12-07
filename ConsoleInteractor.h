#pragma once
#include "FlightsStorage.h"
#include <memory>
class ConsoleInteractor {
public:
	void Start();

private:

	FlightsStorage _flightsStorage;

	//bool Init();
	int ReadCommand() const;

	void ChoosePredicateAndFindFlight();

	void FindFlights();

	void UpdateStorage();

	void ReadFileAndBuildFlights();

	void PrintFlightShedule() const;

	void ShowPredicates() const;

	void PrintCommands() const;

	void UpdateDateTime();

	void UpdateArrivalAirport();

	void UpdateDepartureAirport();

	void ToUniqueFormat(std::string& typeForFormat) const;

	void FindCommands() const;

	void UpdateCommands() const;

	template<typename T>
	void ReadVar(T& var) const;

	enum {
		UPDATE_DATE_TIME = 1,
		UPDATE_ARRIVAL_AIRPORT,
		UPDATE_DEPARTURE_AIRPORT,
		DELETE_FLIGHT
	};

	enum {
		FIND_BY_DATE_TIME = 1,
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