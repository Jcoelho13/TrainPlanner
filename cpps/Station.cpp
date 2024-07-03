//
// Created by Utilizador on 24/03/2023.
//

#include "../headers/Station.h"

Station::Station() = default;

Station::Station(string name, string district, string municipality, string township, string tline){
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->tline = tline;
}

string Station::getName() const {
    return name;
}

string Station::getDistrict() const {
    return district;
}

string Station::getMunicipality() const {
    return municipality;
}

string Station::getTownship() const {
    return township;
}

string Station::getTline() const {
    return tline;
}

void Station::setName(string name) {
    Station::name = name;
}

void Station::setDistrict(string district) {
    Station::district = district;
}

void Station::setMunicipality(string municipality) {
    Station::municipality = municipality;
}

void Station::setTownship(string township) {
    Station::township = township;
}

void Station::setTline(string tline) {
    Station::tline = tline;
}

