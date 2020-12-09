#include "Flight.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <chrono>


struct AirportsAndDepartureDate {
	DepartureDate _date_time;
	int _days_count;
	std::string _arrival_airport;
	std::string _departure_airport;
};

struct AirportsAndArrivalDate {
	ArrivalDate _date_time;
	int _days_count;
	std::string _arrival_airport;
	std::string _departure_airport;
};

class FlightsStorage {

public:

	FlightsStorage() = default;

	void Add(const Flight& flight);

	std::string To_String() const;

	void UpdateDateTime(const FlightCode& flight_code, const DateTime& new_date_time);
	
	void UpdateDate(const FlightCode& flight_code, const std::vector<int>& new_arrival_date, char flag);
		
	void UpdateTime(const FlightCode& flight_code, const std::chrono::hours new_hours, const std::chrono::minutes new_minutes, char flag);

	void UpdateAirport(const FlightCode& flight_code, const std::string& new_arrival_airport, char flag);
	
	std::vector<Flight*> FindFlightsByDateTime(const DateTime& date_time);
	
	std::vector<Flight*> FindFlightsByAirportAndDate(const AirportsAndArrivalDate& airports_and_arrival_date);

	std::vector<Flight*> FindFlightsByAirportAndDate(const AirportsAndDepartureDate& airports_and_departure_date);

	std::vector<Flight*> FindFlightByArrivalAirports(const std::string& arrival_airport);

	std::vector<Flight*> FindFlightByDepartureAirports(const std::string& departure_airport);
	
	Flight* FindFlightByCode(const FlightCode& flight_code);
 
	bool IsEmpty();

private:

	std::map<FlightCode, Flight> _flightRegistry;

	std::map<DateTime, std::set<FlightCode>> _indexByDateTime;
	
	std::map<AirportsAndDepartureDate, std::set<FlightCode>> _indexByAirportsAndDepartureDate;

	std::map<AirportsAndArrivalDate, std::set<FlightCode>> _indexByAirportsAndArrivalDate;

	std::map<std::string, std::set<FlightCode>> _indexByArrivalAirports;
	
	std::map<std::string, std::set<FlightCode>> _indexByDepartureAirports;
};

