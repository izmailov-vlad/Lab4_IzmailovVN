#include "FlightsStorage.h"

void FlightsStorage::Add(const Flight& flight) {

	_flightRegistry.insert(std::make_pair(flight.GetInitialCode(), flight));
	
	auto itDateTime = _indexByDateTime.find(flight.GetDateTime());
	if (itDateTime != _indexByDateTime.end()) {
		itDateTime->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByDateTime[flight.GetDateTime()] = std::set<FlightCode>();
		_indexByDateTime[flight.GetDateTime()].insert(flight.GetInitialCode());
	}


	auto itArrivalAirports = _indexByArrivalAirports.find(flight.GetArrivalAirport());
	if (itArrivalAirports != _indexByArrivalAirports.end()) {
		itArrivalAirports->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByArrivalAirports[flight.GetArrivalAirport()] = std::set<FlightCode>();
		_indexByArrivalAirports[flight.GetArrivalAirport()].insert(flight.GetInitialCode());
	}


	auto itDepartureAirports = _indexByDepartureAirports.find(flight.GetDepartureAirport());
	if (itDepartureAirports != _indexByDepartureAirports.end()) {
		itDepartureAirports->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByDepartureAirports[flight.GetDepartureAirport()] = std::set<FlightCode>();
		_indexByDepartureAirports[flight.GetDepartureAirport()].insert(flight.GetInitialCode());
	}

}

std::string FlightsStorage::To_String() const
{

	std::stringstream str;
	for (auto& flight : _flightRegistry) {
		str << flight.second.To_String() << "\n";
	}
	return str.str();
}

void FlightsStorage::DeleteFlightByFlightCode(const FlightCode& FlightCode)
{
	auto itById = _flightRegistry.find(FlightCode);
	if (itById != _flightRegistry.end()) {
		_indexByDateTime[itById->second.GetDateTime()].erase(FlightCode);
		_indexByArrivalAirports[itById->second.GetArrivalAirport()].erase(FlightCode);
		_indexByDepartureAirports[itById->second.GetDepartureAirport()].erase(FlightCode);

		_flightRegistry.erase(FlightCode);
	}
}

void FlightsStorage::UpdateDateTime(const FlightCode& flight_code, const DateTime& new_date_time)
{
	auto it = _flightRegistry.find(flight_code);
	if (it != _flightRegistry.end()) {
		_indexByDateTime[it->second.GetDateTime()].erase(flight_code);
		_indexByDateTime[new_date_time].insert(flight_code);
	}

	it->second.SetDateTime(new_date_time);
}

void FlightsStorage::UpdateArrivalAirport(const FlightCode& flight_code, const std::string& new_arrival_airport)
{
	auto it = _flightRegistry.find(flight_code);
	if (it != _flightRegistry.end()) {
		_indexByArrivalAirports[it->second.GetArrivalAirport()].erase(flight_code);
		_indexByArrivalAirports[new_arrival_airport].insert(flight_code);
	}

	it->second.SetArrivalAirport(new_arrival_airport);
}

void FlightsStorage::UpdateDepartureAirport(const FlightCode& flight_code, const std::string& new_departure_airport)
{
	auto it = _flightRegistry.find(flight_code);
	if (it != _flightRegistry.end()) {
		_indexByDepartureAirports[it->second.GetDepartureAirport()].erase(flight_code);
		_indexByDepartureAirports[new_departure_airport].insert(flight_code);
	}

	it->second.SetDepartureAirport(new_departure_airport);
}

std::vector<Flight*> FlightsStorage::FindFlightsByDateTime(const DateTime& date_time)
{
	auto it = _indexByDateTime.find(date_time);
	std::vector<Flight*> finded_flights;
	if (it != _indexByDateTime.end()) {
		
		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	return finded_flights;
}

std::vector<Flight*> FlightsStorage::FindFlightByArrivalAirports(const std::string& arrival_airport)
{
	auto it = _indexByArrivalAirports.find(arrival_airport);
	std::vector<Flight*> finded_flights;
	if (it != _indexByArrivalAirports.end()) {

		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	return finded_flights;
}

std::vector<Flight*> FlightsStorage::FindFlightByDepartureAirports(const std::string& departure_airport)
{
	auto it = _indexByDepartureAirports.find(departure_airport);
	std::vector<Flight*> finded_flights;
	if (it != _indexByDepartureAirports.end()) {

		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	return finded_flights;
}

Flight* FlightsStorage::FindFlightByCode(const FlightCode& flight_code)
{
	/*auto it = _indexByFlightCode.find(flight_code);
	std::vector<Flight*> finded_flights;
	if (it != _indexByFlightCode.end()) {

		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	return finded_flights;*/

	if (_flightRegistry.find(flight_code) != _flightRegistry.end()) {
		return &_flightRegistry.find(flight_code)->second;
	}
}

