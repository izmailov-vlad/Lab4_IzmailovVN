#pragma once
#include "DateTime.h"
#include "Time.h"
#include "FlightCode.h"
#include "IStringConvertable.h"

class Flight : public IStringConvertable {
public:
	Flight() = default;
	Flight(const DateTime& date_time, const std::string& arrival_airport, const std::string& departure_airport, const FlightCode& code) {
		_departure_airport = departure_airport;
		_arrival_airport = arrival_airport;
		_date_time = date_time;
		_code = code;
	}

	Flight(const Flight& flight) {
		_date_time = flight._date_time;
		_code = flight._code;
		_arrival_airport = flight._arrival_airport;
		_departure_airport = flight._departure_airport;
	}

	Flight& operator = (const Flight& flight) {
		if (&flight == this) {
			return *this;
		}

		_arrival_airport = flight._arrival_airport;
		_departure_airport = flight._departure_airport;
		_date_time = flight._date_time;
		_code = flight._code;
	}

	std::string To_String() const override;

	const DateTime& GetDateTime() const {
		return _date_time;
	}

	const FlightCode& GetInitialCode() const {
		return _code;
	}

	const std::string& GetArrivalAirport() const {
		return _arrival_airport;
	}

	const std::string& GetDepartureAirport() const {
		return _departure_airport;
	}

	void SetDateTime(const DateTime& new_date_time) {
		_date_time = new_date_time;
	}

	void SetArrivalAirport(const std::string& new_arrival_airport) {
		_arrival_airport = new_arrival_airport;
	}

	void SetDepartureAirport(const std::string& new_departure_airport) {
		_departure_airport = new_departure_airport;
	}

	void SetFlightCode(const FlightCode& new_flight_code) {
		_code = new_flight_code;
	}

	void SetDate(int arrival_day, int arrival_month, int arrival_year) {
		_date_time.SetArrivalDate(
			arrival_day, arrival_month, arrival_year
		);
	}

private:

	DateTime _date_time;
	
	FlightCode _code;
	
	std::string _arrival_airport;
	
	std::string _departure_airport;
};