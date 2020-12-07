#include "Flight.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
class FlightsStorage {
public:

	FlightsStorage() = default;

	void Add(const Flight& flight);

	std::string To_String() const;

	void DeleteFlightByFlightCode(const FlightCode& FlightCode);

	void UpdateDateTime(const FlightCode& flight_code, const DateTime& new_date_time);
	
	void UpdateArrivalAirport(const FlightCode& flight_code, const std::string& new_arrival_airport);
	
	void UpdateDepartureAirport(const FlightCode& flight_code, const std::string& new_departure_airport);

	std::vector<Flight*> FindFlightsByDateTime(const DateTime& date_time);

	std::vector<Flight*> FindFlightByArrivalAirports(const std::string& arrival_airport);

	std::vector<Flight*> FindFlightByDepartureAirports(const std::string& departure_airport);
	
	Flight* FindFlightByCode(const FlightCode& flight_code);
 


	
private:

	std::map<FlightCode, Flight> _flightRegistry;

	std::map<DateTime, std::set<FlightCode>> _indexByDateTime;

	std::map<std::string, std::set<FlightCode >> _indexByArrivalAirports;
	
	std::map<std::string, std::set<FlightCode >> _indexByDepartureAirports;

	//std::map<FlightCode, std::set<FlightCode>> _indexByFlightCode;

};