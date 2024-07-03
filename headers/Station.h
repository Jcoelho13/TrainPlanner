//
// Created by Utilizador on 24/03/2023.
//

#ifndef DATP1_STATION_H
#define DATP1_STATION_H

#include <string>

using namespace std;

class Station{

    /** String with the name of the station*/
    string name;

    /** String with the district of the station*/
    string district;

    /** String with the municipality of the station*/
    string municipality;

    /** String with the township of the station*/
    string township;

    /** String with the tline of the station*/
    string tline;

public:

    /** Default Constructor
     * @brief Complexity O(1)
     */
    Station();

    /** Constructor
     * @param name String with the name of the station
     * @param district String with the district of the station
     * @param municipality String with the municipality of the station
     * @param township String with the township of the station
     * @param tline String with the tline of the station
     * @brief Complexity O(1)
     */
    Station(string name, string district, string municipality, string township, string tline);

    /** Getter
     * @return String with the name of the station
     * @brief Complexity O(1)
     */
    string getName() const;

    /** Getter
     * @return String with the district of the station
     * @brief Complexity O(1)
     */
    string getDistrict() const;

    /** Getter
     * @return String with the municipality of the station
     * @brief Complexity O(1)
     */
    string getMunicipality() const;

    /** Getter
     * @return String with the township of the station
     * @brief Complexity O(1)
     */
    string getTownship() const;

    /** Getter
     * @return String with the tline of the station
     * @brief Complexity O(1)
     */
    string getTline() const;

    /** Setter
     * @param name String with the name of the station
     * @brief Complexity O(1)
     */
    void setName(string name);

    /** Setter
     * @param district String with the district of the station
     * @brief Complexity O(1)
     */
    void setDistrict(string district);

    /** Setter
     * @param municipality String with the municipality of the station
     * @brief Complexity O(1)
     */
    void setMunicipality(string municipality);

    /** Setter
     * @param township String with the township of the station
     * @brief Complexity O(1)
     */
    void setTownship(string township);

    /** Setter
     * @param tline String with the tline of the station
     * @brief Complexity O(1)
     */
    void setTline(string tline);

};

#endif //DATP1_STATION_H
