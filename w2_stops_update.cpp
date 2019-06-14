#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string type;
	cin >> type;

	if (type == "NEW_BUS") {
		q.type = QueryType::NewBus;
		int reps;
		cin >> q.bus >> reps;
		q.stops.clear();
		for (int i = 0; i < reps; i++) {
			string stop_name;
			cin >> stop_name;
			q.stops.push_back(stop_name);
		}
		return is;
	}
	else if (type == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		cin >> q.stop;
		return is;
	}
	else if (type == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		cin >> q.bus;
		return is;
	}
	else if (type == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
		return is;
	}
	return is;
}

struct BusesForStopResponse {
	// Наполните полями эту структуру
	string stop;
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	// Реализуйте эту функцию
	if (r.buses.size() == 0) {
		os << "No stop";
	}
	else {
		for (const string& bus : r.buses) {
			os << bus << " ";
		}
	}
	
	return os;
}

struct StopsForBusResponse {\
	// Наполните полями эту структуру
	string bus;
	vector<string> stops;
	map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	// Реализуйте эту функцию
	if (r.stops.size() == 0) {
		os << "No bus";
	}
	else {
		for (const string& stop : r.stops) {
			os << "Stop " << stop << ": ";

			if (r.stops_to_buses.at(stop).size() == 1) {
				os << "no interchange" << endl;
			}
			else {
				vector <string> a = r.stops_to_buses.at(stop);
				for (const string& other_bus : a) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
				os << endl;
			}
		}
	}
	return os;
}

struct AllBusesResponse {
	// Наполните полями эту структуру
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	// Реализуйте эту функцию
	if (r.buses_to_stops.empty()) {
		os << "No buses";
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (const string& stop : stops) {
			//if (find(stops_to_buses[stop].begin(), stops_to_buses[stop].end(), stop) == stops_to_buses[stop].end())
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse response;
		response.stop = stop;
		if (stops_to_buses.count(stop) == 1) {
			response.buses = stops_to_buses.at(stop);
		}
	
		return response;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse response;
		response.bus = bus;
		if (buses_to_stops.count(bus) == 1) {
			response.stops = buses_to_stops.at(bus);
		}

		response.stops_to_buses = stops_to_buses;

		return response;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse response;
		response.buses_to_stops = buses_to_stops;
		return response;
	}

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	system("pause");
	return 0;
}


