
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

    // If house is occupied or not
    bool occupationStatus;

    // list of last occupiers
    std::vector<Member> occupiers;

    // Scores that the previous occupiers give
    std::vector<double> occupiersScores;

    // Comments of previous occupiers
    std::map<string, string> occupiersComments;

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
