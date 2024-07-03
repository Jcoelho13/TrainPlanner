/*! \file */

/**
 * @brief Main file
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <list>
#include "headers/Station.h"
#include "DataStructures/Graph.h"

using namespace std;

Graph g;

/** Struct with the information of a connection: id1, id2, capacity, service */
typedef pair<pair<int, int>, pair<int, string>> edge;

/** Map with the stations, key = station id, value = Station */
unordered_map<int, Station> stations;

/** Map with the names of the stations, key = station name, value = station id */
unordered_map<string, int> stations_name;

/** Map with the connections, key = connection id, value = edge */
unordered_map<int, edge> connections;

/** Map with the districts, key = district name, value = number of stations */
unordered_map<string, int> districts;

/** Map with the municipalities, key = municipality name, value = number of stations */
unordered_map<string, int> municipalities;

/** Function that reads the stations from a file and stores them in the stations, stations_name, districts and municipalities maps
 * @param file String with the name of the file
 * @brief Complexity O(n), where n is the number of stations
 */
void read_stations(const string& file);

/** Function that reads the connections from a file and stores them in the connections map, also adds the numbers of stations in each district and municipality to their respective maps
 * @param file String with the name of the file
 * @brief Complexity O(n), where n is the number of connections
 */
void read_network(const string& file);

/** Function that prints the main menu
 * @brief Complexity O(1)
 */
void print_menu();

/** Function that prints the first menu
 * @brief Complexity O(1)
 */
void print_first_menu_1();

/** Function that prints the second menu
 * @brief Complexity O(1)
 */
void print_first_menu_2();

/** Function that prints the menu of the first option
 * @brief Complexity O(|V||E|^2 + |E|) where |V| is the number of stations and |E| is the number of connections
 */
void print_menu_1();

/** Function that prints the menu of the second option
 * @brief Complexity O(|V|^2+|E|^2) where n is the number of connections
 */
void print_menu_2();

/** Function that prints the menu of the third option
 * @brief Complexity O(|V|^2) where n is the number of connections
 */
void print_menu_3();

/** Function that prints the menu of the fourth option
 * @brief Complexity O(|V|^2*|E|^2) where n is the number of connections
 */
void print_menu_4();

/** Function that prints the menu of the fifth option
 * @brief Complexity O((V+E)*log(V)) where n is the number of connections
 */
void print_menu_5();

/** Function that prints the menu of the sixth option
 * @brief Complexity O(|V|*|E|^2) where n is the number of connections
 */
void print_menu_6();

/** Function that prints the menu of the seventh option
 * @brief Complexity O(|V|^2*|E|^2) where n is the number of connections
 */
void print_menu_7();

/** Function that lists every station for the chosen dataset
 * @brief Complexity O(|V|) where n is the number of stations
 */
void print_menu_2_1();

/** Function that lists every connection for the chosen dataset
 * @brief Complexity O(|E|) where n is the number of connections
 */
void print_menu_2_2();

/** Function that prints the top districts with the most stations
 * @brief Complexity O(nlogn) where n is the number of districts
 */
void top_d();

/** Function that prints the top municipalities with the most stations
 * @brief Complexity O(nlogn) where n is the number of municipalities
 */
void top_m();

/** Function that checks if a station exists in the stations map
 * @param s String with the name of the station
 * @return True if the station exists, false otherwise
 * @brief Complexity O(1)
 */
bool checkStation(const string& s);

/** Function that checks if a connection exists in the connections map
 * @param id1 Integer with the id of the first station
 * @param id2 Integer with the id of the second station
 * @return True if the connection exists, false otherwise
 * @brief Complexity O(1)
 */
bool checkConnection(const int &id1, const int &id2);

/** Function that returns the max flow of a station by extending augmenting the graph to make it with one source and one sink
 * @param station String with the name of the station
 * @return Double with the max flow of the station
 * @brief Complexity O(|V|^2*|E|^2) where n is the number of connections
 */
double superSource(const std::string &station) {
    auto it = stations_name.find(station);

    auto cpy = g;
    cpy.addVertex(1000);
    for (auto v : cpy.getVertexSet()) {
        if (v->getAdj().size() == 1 && v->getId() != 1000) {
            cpy.findVertex(1000)->addEdge(v, INF, 0);
        }
    }

    cpy.edmondsKarp(1000, it->second);

    double maxFlow = 0;
    for (auto e : cpy.findVertex(it->second)->getIncoming()) maxFlow += e->getFlow();
    return maxFlow;
}

void clear() {for (int i = 0; i < 50; i++) cout << endl;}
void wait() {cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();}

string station_ = "../files/stations.csv";
string network_ = "../files/network.csv";

string demo_stations_ = "../files/demo_stations.csv";
string demo_networks_ = "../files/demo_networks.csv";

//int vmm = 0;

void print_main() {
    int choice;
    do{
    clear();
    cout << "------------------------------------------" << endl;
    cout << "|        Railway Network Manager         |" << endl;
    cout << "|                                        |" << endl;
    cout << "| 1. Full Dataset                        |" << endl;
    cout << "| 2. Demo Dataset                        |" << endl;
    cout << "|                                        |" << endl;
    cout << "------------------------------------------" << endl;

    cout << "Choose an option:" << endl;
    cout << endl;
    cin >> choice;


    switch (choice) {
        case 1:
            read_stations(station_);
            read_network(network_);
            choice = 0;
            break;
        case 2:
            read_stations(demo_stations_);
            read_network(demo_networks_);
            choice = 0;
            break;
        default:
            cout << "Invalid option! Try again" << endl;
            cout << "Press enter to continue..." << endl;
            wait();
            choice = 1;
            break;
    }
}while (choice != 0);

    print_menu();
}
int main() {

    print_main();

    return 0;
}



void read_stations(const string& file){
    ifstream stations_file(file);

    string line;

    int i = 1;
    getline(stations_file, line);
    while(getline(stations_file, line)){
        stringstream ss(line);
        string name, district, municipality, township, tline;
        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, tline, ',');

        Station station(name, district, municipality, township, tline);
        stations.insert({i, station});
        stations_name.insert({name, i});
        municipalities.insert({municipality, 0});
        districts.insert({district, 0});

        g.addVertex(i);

        i++;
    }
}

void read_network(const string& file){

    ifstream network_file(file);

    string line;

    int i = 1, price;
    getline(network_file, line);
    while(getline(network_file, line)){
        price = 4;
        istringstream ss(line);
        string station1, station2, service;
        int capacity;
        getline(ss, station1, ',');
        getline(ss, station2, ',');
        ss >> capacity;
        ss.ignore();
        getline(ss, service, ',');

        if(service == "STANDARD") {price = 2;}

        auto it1 = stations_name.find(station1);
        auto it2 = stations_name.find(station2);

        edge temp = {{it1->second, it2->second}, {capacity, service}};
        connections.insert({i, temp});

        districts.find(stations.find(it1->second)->second.getDistrict())->second += capacity;
        districts.find(stations.find(it2->second)->second.getDistrict())->second += capacity;

        municipalities.find(stations.find(it1->second)->second.getMunicipality())->second += capacity;
        municipalities.find(stations.find(it2->second)->second.getMunicipality())->second += capacity;

        g.addBidirectionalEdge(it1->second, it2->second, capacity, price);

        i++;
    }
}




void print_menu() {
    int choice;
    do {
        clear();
        cout << "------------------------------------------" << endl;
        cout << "|        Railway Network Manager         |" << endl;
        cout << "| 1. Use Dataset                         |" << endl;
        cout << "| 2. Check Dataset                       |" << endl;
        cout << "| 0. Exit                                |" << endl;
        cout << "------------------------------------------" << endl;

        cin >> choice;
        if (choice < 0 || choice > 2) {
            cout << "Invalid option! Try again" << endl;
            cin >> choice;
            cout << endl;
        }
        if(choice != 0) {
            switch (choice) {
                case 1:
                    print_first_menu_1();
                    break;
                case 2:
                    print_first_menu_2();
                    break;
                default:
                    break;
            }
        }
    } while (choice != 0);

    clear();
}

void print_first_menu_1() {
    int choice;
    do {
        clear();
        cout << "Choose an option:" << endl;
        cout << endl;
        cout << "  1 - Maximum number of trains that can simultaneously travel between two specific stations" << endl;
        cout << "  2 - The stations that require the most amount of trains when taking full advantage of the existing network capacity" << endl;
        cout << "  3 - Top-k municipalities and districts, regarding their transportation needs" << endl;
        cout << "  4 - Maximum number of trains that can simultaneously arrive at a given station" << endl;
        cout << "  5 - Maximum amount of trains that can simultaneously travel between two stations with minimum cost for the company" << endl;
        cout << "  6 - Maximum amount of trains that can simultaneously travel between two stations in a network of reduced connectivity" << endl;
        cout << "  7 - Top-k most affected stations for each segment failure to be considered" << endl;
        cout << endl;
        cout << "  0 - Go back" << endl;
        cout << endl;

        cin >> choice;
        if (choice < 0 || choice > 7) {
            cout << "Invalid option! Try again" << endl;
            cin >> choice;
            cout << endl;
        }
        if(choice != 0) {
            switch (choice) {
                case 1:
                    clear();
                    print_menu_1();
                    break;
                case 2:
                    clear();
                    print_menu_2();
                    break;
                case 3:
                    clear();
                    print_menu_3();
                    break;
                case 4:
                    clear();
                    print_menu_4();
                    break;
                case 5:
                    clear();
                    print_menu_5();
                    break;
                case 6:
                    clear();
                    print_menu_6();
                    break;
                case 7:
                    clear();
                    print_menu_7();
                    break;
                default:
                    break;
            }
        }
    } while (choice != 0);
}

void print_first_menu_2() {
    int choice3;
    do {
        clear();
        cout << "Choose an option:" << endl;
        cout << endl;
        cout << "   1 - View Stations " << endl;
        cout << "   2 - View Connections " << endl;
        cout << endl;
        cout << "   0 - Go back" << endl;
        cout << endl;
        cout << endl;

        cin >> choice3;
        if (choice3 < 0 || choice3 > 2) {
            cout << "Invalid option! Try again" << endl;
            cin >> choice3;
            cout << endl;
        }

        switch (choice3) {
            case 0:
                choice3 = 0;
                break;
            case 1:
                print_menu_2_1();
                break;
            case 2:
                print_menu_2_2();
                break;
            default:
                break;
        }
    } while (choice3 != 0);
}



void print_menu_1(){
    string station1, station2;
    cout << endl;
    cout << "Enter the name of the first station: ";
    getline(cin >> ws, station1);

    while(!checkStation(station1)){
        clear();
        cout << endl;
        cout << "Station " << station1 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station1);
        cout << endl;
    }

    cout << endl;
    cout << "Enter the name of the second station: ";
    getline(cin >> ws, station2);
    while(!checkStation(station2)){
        clear();
        cout << endl;
        cout << "Station " << station2 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station2);
        cout << endl;
    }

    if(station1 == station2) {
        cout << endl;
        cout << "Stations " << station1 << " and " << station2 << " are the same!" << endl;
        cout << "Try again" << endl;
        print_menu_1();
    }
    cout << endl;

    double sum = 0;

    auto it1 = stations_name.find(station1);
    auto it2 = stations_name.find(station2);
    g.edmondsKarp(it1->second, it2->second);
    for (const auto e : g.findVertex(it1->second)->getAdj()) {
        sum += e->getFlow();
    }
    cout << "Maximum Flow : " << sum << endl; cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}



void print_menu_2() {

    auto lista = g.mostTrains();

    for(auto par : lista) {
        cout << stations.find(par.first)->second.getName() << " - " << stations.find(par.second)->second.getName() << endl;
    }

   /* int max = 0;
    vector<edge> cons;

    for(const auto& con : connections) {
        if(con.second.second.first >= max) {
            max = con.second.second.first;
            cons.push_back(con.second);
        }
    }
    for(const auto& conne : cons) {
        auto st1 = stations.find(conne.first.first);
        auto st2 = stations.find(conne.first.second);
        cout << st1->second.getName() << " - " << st2->second.getName() << " -> " << max << endl;
    }
*/
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}



void print_menu_3(){
    int choice;
    do {
        clear();
        cout << "Choose an option:" << endl;
        cout << endl;
        cout << "   1 - View Districts " << endl;
        cout << "   2 - View Municipalities " << endl;
        cout << endl;
        cout << "   0 - Go back" << endl;
        cout << endl;
        cout << endl;

        cin >> choice;
        if (choice < 0 || choice > 2) {
            cout << "Invalid option! Try again" << endl;
            cin >> choice;
            cout << endl;
        }
        switch (choice) {
            case 0:
                choice = 0;
                break;
            case 1:
                top_d();
                break;
            case 2:
                top_m();
                break;
            default:
                break;
        }
    } while (choice != 0);
}



void print_menu_4(){
    cout << endl;
    string station;
    cout << "Please enter the name of the station: " << endl;
    getline(cin >> ws, station);

    while(!checkStation(station)){
        clear();
        cout << endl;
        cout << "Station " << station << " does not exist! Try again:" << endl;
        getline(cin >> ws, station);
        cout << endl;
    }

    double maxFlow = superSource(station);

    cout << "The maximum number of trains that can simultaneously arrive at " << station << " is " << maxFlow << endl;
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}



void print_menu_5() {
    string station1, station2;
    cout << endl;
    cout << "Enter the name of the first station: ";
    getline(cin >> ws, station1);

    while(!checkStation(station1)){
        clear();
        cout << endl;
        cout << "Station " << station1 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station1);
        cout << endl;
    }
    cout << endl;

    cout << "Enter the name of the second station: ";
    getline(cin >> ws, station2);
    while(!checkStation(station2)){
        clear();
        cout << endl;
        cout << "Station " << station2 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station2);
        cout << endl;
    }

    if(station1 == station2) {
        cout << endl;
        cout << "Stations " << station1 << " and " << station2 << " are the same!" << endl;
        cout << "Try again" << endl;
        print_menu_5();
    }
    cout << endl;

    auto st1 = stations_name.find(station1);
    auto st2 = stations_name.find(station2);

    g.dijkstra(st1->second);

    vector<string> path;
    int id = st2->second;
    while(id != st1->second) {
        path.push_back(stations.find(id)->second.getName());
        auto test = g.findVertex(id);
        if(test == nullptr) break;
        id = test->getPath()->getOrig()->getId(); //BUG
    }

    cout << stations.find(st1->second)->second.getName() << " -> ";
    for(int i = path.size()-1; i >= 0; i--) {
        cout << path[i];
        if(i != 0) cout << " -> ";
    }
    cout << endl; cout << endl;
    auto station = g.findVertex(st2->second);
    cout << station->getDist() << " trains, costing " << station->getCost();

    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}

void print_menu_6(){
    int choice;
    unordered_map<string, string> stations_6;

    cout << "Choose one connection to remove from the network" << endl;
    do{
        cout << endl;
        string station1;
        string station2;
        cout << "Enter the name of the first station: " << endl;
        getline(cin >> ws, station1);
        while(!checkStation(station1)){
            clear();
            cout << endl;
            cout << "Station " << station1 << " does not exist! Try again:" << endl;
            getline(cin >> ws, station1);
            cout << endl;
        }
        cout << endl;
        cout << "Enter the name of the second station: " << endl;
        getline(cin >> ws, station2);
        while(!checkStation(station2)){
            clear();
            cout << endl;
            cout << "Station " << station2 << " does not exist! Try again:" << endl;
            getline(cin >> ws, station2);
            cout << endl;
        }
        cout << endl;
        if(station1 == station2) {
            cout << endl;
            cout << "Stations " << station1 << " and " << station2 << " are the same!" << endl;
            cout << "Try again" << endl;
            print_menu_6();
        }
        cout << endl;

        auto it1 = stations_name.find(station1);
        auto it2 = stations_name.find(station2);

        if(!checkConnection(it1->second, it2->second)){
            cout << endl;
            cout << "There is no connection between " << station1 << " and " << station2 << endl;
            cout << "Try again" << endl;
            print_menu_6();
        }

        stations_6.insert(make_pair(station1, station2));

        clear();
        cout << "What do you want to do?" << endl;
        cout << endl;
        cout << "1 - Add a new connection to remove" << endl;
        cout << "0 - Process the remove requests" << endl;
        cout << endl;

        cin >> choice;
        cout << endl;
        if(choice > 1 || choice < 0){
            cout << "Invalid choice! Try again" << endl;
            cin >> choice;
        }

        switch(choice){
            case 1:
                choice = 1;
                break;
            case 0:
                choice = 0;
                break;
            default:
                break;
        }
    } while (choice != 0);


    Graph tmp = g;
    for(const auto& station : stations_6){
        auto it1 = stations_name.find(station.first);
        auto it2 = stations_name.find(station.second);
        tmp.removeEdge(it1->second, it2->second);
    }

    //prints the remaining edges after removal

    /*while(!stations_6.empty()){
        cout << endl;
        for(auto edge : tmp.findVertex(stations_name.find(stations_6.begin()->first)->second)->getAdj() ){
            cout << stations.find(edge->getDest()->getId())->second.getName() << endl;
        }
        stations_6.erase(stations_6.begin());
    }*/

    cout << "Press enter to continue..." << endl;
    wait();

    clear();
    cout << "Maximum number of trains that can simultaneously travel between two specific stations" << endl;
    string station1, station2;
    cout << endl;
    cout << "Enter the name of the first station: ";
    getline(cin >> ws, station1);

    while(!checkStation(station1)){
        clear();
        cout << endl;
        cout << "Station " << station1 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station1);
        cout << endl;
    }

    cout << endl;
    cout << "Enter the name of the second station: ";
    getline(cin >> ws, station2);
    while(!checkStation(station2)){
        clear();
        cout << endl;
        cout << "Station " << station2 << " does not exist! Try again:" << endl;
        getline(cin >> ws, station2);
        cout << endl;
    }

    if(station1 == station2) {
        cout << endl;
        cout << "Stations " << station1 << " and " << station2 << " are the same!" << endl;
        cout << "Try again" << endl;
        print_menu_1();
    }
    cout << endl;

    double sum = 0;

    auto it1 = stations_name.find(station1);
    auto it2 = stations_name.find(station2);
    g.edmondsKarp(it1->second, it2->second);
    for (const auto e : g.findVertex(it1->second)->getAdj()) {
        sum += e->getFlow();
    }
    cout << "Maximum Flow : " << sum << endl; cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}

void print_menu_7(){
    int choice;
    unordered_map<string, string> stations_7;
    do{
        cout << endl;
        string station1;
        string station2;
        cout << "Enter the name of the first station: " << endl;
        getline(cin >> ws, station1);
        while(!checkStation(station1)){
            clear();
            cout << endl;
            cout << "Station " << station1 << " does not exist! Try again:" << endl;
            getline(cin >> ws, station1);
            cout << endl;
        }
        cout << endl;
        cout << "Enter the name of the second station: " << endl;
        getline(cin >> ws, station2);
        while(!checkStation(station2)){
            clear();
            cout << endl;
            cout << "Station " << station2 << " does not exist! Try again:" << endl;
            getline(cin >> ws, station2);
            cout << endl;
        }
        cout << endl;
        if (station1 == station2) {
            cout << endl;
            cout << "Stations " << station1 << " and " << station2 << " are the same!" << endl;
            cout << "Try again" << endl;
            print_menu_7();
        }
        cout << endl;

        auto it1 = stations_name.find(station1);
        auto it2 = stations_name.find(station2);

        if(!checkConnection(it1->second, it2->second)){
            cout << endl;
            cout << "There is no connection between " << station1 << " and " << station2 << endl;
            cout << "Try again" << endl;
            print_menu_7();
        }

        stations_7.insert(make_pair(station1, station2));

        clear();
        cout << "What do you want to do?" << endl;
        cout << endl;
        cout << "1 - Add a new connection to remove" << endl;
        cout << "0 - Process the remove requests" << endl;
        cout << endl;

        cin >> choice;
        cout << endl;
        if(choice > 1 || choice < 0){
            cout << "Invalid choice! Try again" << endl;
            cin >> choice;
        }

    } while (choice != 0);

    std::vector<double> flowBefore(g.getNumVertex(), 0);
    for (int i = 1; i < g.getNumVertex(); i++) flowBefore[i] = superSource(stations[i].getName());

    Graph tmp = g;
    for(const auto& station : stations_7){
        auto it1 = stations_name.find(station.first);
        auto it2 = stations_name.find(station.second);
        tmp.removeEdge(it1->second, it2->second);
    }

    std::vector<double> flowAfter(tmp.getNumVertex(), 0);
    for (int i = 1; i < tmp.getNumVertex(); i++) flowAfter[i] = superSource(stations[i].getName());

    std::vector<double> diff(tmp.getNumVertex(), 0);
    for (int i = 1; i < tmp.getNumVertex(); i++) diff[i] = flowAfter[i] - flowBefore[i];

    /*while(!stations_7.empty()){
        cout << endl;
        for(auto edge : tmp.findVertex(stations_name.find(stations_7.begin()->first)->second)->getAdj() ){
            cout << stations.find(edge->getDest()->getId())->second.getName() << endl;
        }
        stations_7.erase(stations_7.begin());
    }*/

    cout << "Press enter to continue..." << endl;
    wait();

    cout << "Select an integer between 1 and 10 to see the top x most affected stations" << endl;
    int x;
    cin >> x;
    while(x < 1 || x > 10){
        cout << "Invalid choice! Try again" << endl;
        cin >> x;
    }

    std::vector<std::string> affected;

    for (int i = 0; i < x; i++) {
        int maxDiff = 0;
        for (int j = 1; j < diff.size(); j++) maxDiff = std::abs(diff[j]) > std::abs(diff[maxDiff]) ? j : maxDiff;
        affected.push_back(stations[maxDiff].getName());
        diff[maxDiff] = 0;
    }

    cout << "The most affected stations are:\n";
    for (const auto &station : affected) {
        cout << station << endl;
    }
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}

void print_menu_2_1(){
    // prints every station
    cout << "Here is the name of every station: " << endl;
    cout << endl;
    for(const auto& station : stations){
        cout << station.second.getName() << endl;
    }
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}



void print_menu_2_2(){
    // prints every connection
    cout << "Here is every connection: " << endl;
    cout << endl;
    for(const auto& con : connections){
        auto st1 = stations.find(con.second.first.first);
        auto st2 = stations.find(con.second.first.second);
        cout << st1->second.getName() << " <-> " << st2->second.getName() << endl;
    }
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}

bool checkStation(const string& s) {
    if(stations_name.find(s) == stations_name.end()){
        clear();
        return false;
    }

    return true;
}

void top_d(){
    unordered_map<string, int> tmp = districts;
    vector<string> districts_top;
        cout << "Select an integer between 1 and 18 to see the top x districts" << endl;
        int x;
        cin >> x;


        if (x < 1 || x > 18) {
            cout << "Invalid option! Try again" << endl;
            cin >> x;
            cout << endl;
        }
        cout << "Top " << x << " districts" << endl;


        for (int i = x; i > 0; i--) {
            int max = 0;
            string district;
            for (const auto& d: tmp) {
                if (d.second >= max) {
                    max = d.second;
                    district = d.first;
                }
            }
            tmp.erase(district);
            districts_top.push_back(district);
        }
        for (const auto& d: districts_top) {
            cout << d << endl;
        }
        cout << endl;
        cout << "Press enter to continue..." << endl;
        wait();
}

void top_m(){
    unordered_map<string, int> tmp_m = municipalities;
    vector<string> municipalities_top;
    cout << endl;
    cout << "Select an integer between 1 and 50 to see the top x municipalities" << endl;
    int y;
    cin >> y;


    if (y < 1 || y > 50) {
        cout << "Invalid option! Try again" << endl;
        cin >> y;
        cout << endl;
    }

    cout << "Top " << y << " municipalities" << endl;

    for (int i = y; i > 0; i--) {
        int max = 0;
        string municipality;
        for (const auto& m: tmp_m) {
            if (m.second >= max) {
                max = m.second;
                municipality = m.first;
            }
        }
        tmp_m.erase(municipality);
        municipalities_top.push_back(municipality);
    }
    for (const auto& m: municipalities_top) {
        cout << m << endl;
    }
    cout << endl;
    cout << "Press enter to continue..." << endl;
    wait();
}

bool checkConnection(const int &id1, const int &id2){
    auto t = g;
    auto k = t.findVertex(id1);
    for(auto ed : k->getAdj()){
        if(ed->getDest()->getId() == id2) return true;
    }
    return false;
}




