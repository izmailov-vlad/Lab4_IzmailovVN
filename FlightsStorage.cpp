#include "FlightsStorage.h"
#include <iomanip>
void FlightsStorage::Add(const Flight& flight) {

	_flightRegistry.insert(std::make_pair(flight.GetInitialCode(), flight));
	
	auto itDateTime = _indexByDateTime.find(flight.GetDateTime());
	if (itDateTime != _indexByDateTime.end()) {
		itDateTime->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByDateTime.insert(std::make_pair(flight.GetDateTime(), std::set<FlightCode>()));
		_indexByDateTime[flight.GetDateTime()].insert(flight.GetInitialCode());
	}

	AirportsAndDepartureDate airports_and_departure_date = {
		flight.GetDateTime().GetDepartureDate(),
		flight.GetDateTime().GetDaysCount(),
		flight.GetArrivalAirport(),
		flight.GetDepartureAirport()
	};

	auto itAirportsAndDepartureDate = _indexByAirportsAndDepartureDate.find(airports_and_departure_date);
	if (itAirportsAndDepartureDate != _indexByAirportsAndDepartureDate.end()) {
		itAirportsAndDepartureDate->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByAirportsAndDepartureDate.insert(std::make_pair(airports_and_departure_date, std::set<FlightCode>()));
		_indexByAirportsAndDepartureDate[airports_and_departure_date].insert(flight.GetInitialCode());
	}

	AirportsAndArrivalDate airports_and_arrival_date = {
		flight.GetDateTime().GetArrivalDate(),
		flight.GetDateTime().GetDaysCount(),
		flight.GetArrivalAirport(),
		flight.GetDepartureAirport()
	};

	auto itAirportsAndArrivalDate = _indexByAirportsAndArrivalDate.find(airports_and_arrival_date);
	if (itAirportsAndArrivalDate != _indexByAirportsAndArrivalDate.end()) {
		itAirportsAndArrivalDate->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByAirportsAndArrivalDate.insert(std::make_pair(airports_and_arrival_date, std::set<FlightCode>()));
		_indexByAirportsAndArrivalDate[airports_and_arrival_date].insert(flight.GetInitialCode());
	}
	
	auto itArrivalAirports = _indexByArrivalAirports.find(flight.GetArrivalAirport());
	if (itArrivalAirports != _indexByArrivalAirports.end()) {
		itArrivalAirports->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByArrivalAirports.insert(std::make_pair(flight.GetArrivalAirport(), std::set<FlightCode>()));
		_indexByArrivalAirports[flight.GetArrivalAirport()].insert(flight.GetInitialCode());
	}


	auto itDepartureAirports = _indexByDepartureAirports.find(flight.GetDepartureAirport());
	if (itDepartureAirports != _indexByDepartureAirports.end()) {
		itDepartureAirports->second.insert(flight.GetInitialCode());
	}
	else {
		_indexByDepartureAirports.insert(std::make_pair(flight.GetDepartureAirport(), std::set<FlightCode>()));
		_indexByDepartureAirports[flight.GetDepartureAirport()].insert(flight.GetInitialCode());
	}

}

std::string FlightsStorage::To_String() const
{

	std::stringstream str;
	str << "\nTime" << std::setw(12) << "\tDate" << std::setw(22) << "\tTowns" << std::setw(40) << "\tCode\n";
	str << std::setfill('-') << std::setw(100) << "\n";
	for (auto& flight : _flightRegistry) {
		str << flight.second.To_String() << "\n";
	}
	return str.str();
}

void FlightsStorage::UpdateDateTime(const FlightCode& flight_code, const DateTime& new_date_time)
{
	auto it = _flightRegistry.find(flight_code);
	if (it != _flightRegistry.end()) {
		_indexByDateTime[it->second.GetDateTime()].erase(flight_code);
		_indexByDateTime[new_date_time].insert(flight_code);
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}

	it->second.SetDateTime(new_date_time);
}

void FlightsStorage::UpdateDate(const FlightCode& flight_code, const std::vector<int>& new_date, char flag)
{
	auto itDate = _flightRegistry.find(flight_code);

	if (itDate != _flightRegistry.end()) {

		DateTime new_date_time = itDate->second.GetDateTime();
		switch (flag) {
			case 'A': {
				new_date_time.SetArrivalDate(
					new_date[0],
					new_date[1],
					new_date[2]
				); 
				break;
			}
			case 'D': {
				new_date_time.SetDepartureDate(
					new_date[0],
					new_date[1],
					new_date[2]
				);
				break;
			}
		}

		_indexByDateTime[itDate->second.GetDateTime()].erase(flight_code);
		_indexByDateTime[new_date_time].insert(flight_code);

		itDate->second.SetDateTime(new_date_time);
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}

	
}

void FlightsStorage::UpdateTime(const FlightCode& flight_code, const std::chrono::hours new_hours, const std::chrono::minutes new_minutes, char flag)
{
	auto itTime = _flightRegistry.find(flight_code);

	if (itTime != _flightRegistry.end()) {

		DateTime new_date_time = itTime->second.GetDateTime();
		switch (flag) {
			case 'A': {
				new_date_time.SetArrivalTime(
					new_hours,
					new_minutes
				);
				break;
			}
			case 'D': {
				new_date_time.SetDepartureTime(
					new_hours,
					new_minutes
				);
				break;
			}
		}

		_indexByDateTime[itTime->second.GetDateTime()].erase(flight_code);
		_indexByDateTime[new_date_time].insert(flight_code);

		itTime->second.SetDateTime(new_date_time);
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}
}

void FlightsStorage::UpdateAirport(const FlightCode& flight_code, const std::string& new_arrival_airport, char flag)
{
	auto it = _flightRegistry.find(flight_code);
	if (it != _flightRegistry.end()) {
		switch (flag) {
			case'A': {
				_indexByArrivalAirports[it->second.GetArrivalAirport()].erase(flight_code);
				_indexByArrivalAirports[new_arrival_airport].insert(flight_code);
				break;
			}
			case 'D': {
				_indexByDepartureAirports[it->second.GetArrivalAirport()].erase(flight_code);
				_indexByDepartureAirports[new_arrival_airport].insert(flight_code);
				break;
			}
		}
	}

	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}

	it->second.SetArrivalAirport(new_arrival_airport);
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
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}
	return finded_flights;
}

std::vector<Flight*> FlightsStorage::FindFlightsByAirportAndDate(const AirportsAndDepartureDate& airports_and_arrival_date)
{
	auto it = _indexByAirportsAndDepartureDate.find(airports_and_arrival_date);
	std::vector<Flight*> finded_flights;
	if (it != _indexByAirportsAndDepartureDate.end()) {

		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}
	return finded_flights;
}
std::vector<Flight*> FlightsStorage::FindFlightsByAirportAndDate(const AirportsAndArrivalDate& airports_and_arrival_date)
{
	auto it = _indexByAirportsAndArrivalDate.find(airports_and_arrival_date);
	std::vector<Flight*> finded_flights;
	if (it != _indexByAirportsAndArrivalDate.end()) {

		for (auto itByFlights = it->second.begin(); itByFlights != it->second.end(); itByFlights++) {
			finded_flights.push_back(&_flightRegistry[*itByFlights]);
		}
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
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
	else {
		throw std::runtime_error("\nNo such flight in list\n");
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
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}
	return finded_flights;
}

Flight* FlightsStorage::FindFlightByCode(const FlightCode& flight_code)
{
	if (_flightRegistry.find(flight_code) != _flightRegistry.end()) {
		return &_flightRegistry.find(flight_code)->second;
	}
	else {
		throw std::runtime_error("\nNo such flight in list\n");
	}
	
}

bool FlightsStorage::IsEmpty()
{
	return _flightRegistry.empty();
}

bool operator<(const AirportsAndDepartureDate& ref1, const AirportsAndDepartureDate& ref2) {
	int day1 = ref1._days_count;
	int day2 = ref2._days_count;

	if (day1 < day2) {
		return true;
	}
	return false;
}

bool operator<(const AirportsAndArrivalDate& ref1, const AirportsAndArrivalDate& ref2) {
	int day1 = ref1._days_count;
	int day2 = ref2._days_count;

	if (day1 < day2) {
		return true;
	}
	return false;
}