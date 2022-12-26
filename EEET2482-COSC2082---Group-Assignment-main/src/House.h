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
using std::vector;

const string locations[3] = {"HANOI", "HUE", "SAIGON"};

class House {
public:
    friend class Member;
    friend class Admin;
    friend class Data;
private:
    string houseID;
    string startDate;
    string endDate;
    string address;
    string location;
    string description;
    vector<double> houseRatings;
    bool status;
    vector<Member*> occupiers;
    vector<Member*> requestList;
    std::map<string, string> occupierComment;
public:
    House();
    House(string houseId, string startDate, string endDate, string address,
          string location, string description, vector<double> houseRatings, bool status,
          vector<Member*> occupiers, vector<Member*> requestList,
          std::map<string, string> occupierComment);


    void showFullHouse();

    void showDemoHouse();

    double avgScore();
};


#endif //HOUSE_H