
#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
#include <map>
#include <vector>
#include "Member.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

const string locations[3] = {"HANOI", "HUE", "SAIGON"};

class House {
protected:
    string houseID;
    string address;
    string location;
    string description;
    bool occupationStatus;
    std::vector<Member> occupiers;
    std::vector<double> occupiersScores;
    std::map<string, string> occupiersComments;
    std::vector<House> listingHouse;
    std::vector<Member> requestsList;
public:
    friend class Member;
    friend class Admin;

    House();
    void showFullHouse();
    void showDemoHouse();
    double avgScore();


};


#endif //HOUSE_H
