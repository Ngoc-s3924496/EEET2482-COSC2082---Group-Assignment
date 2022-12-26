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
private:
    string houseID;
    string startDate;
    string endDate;
    string address;
    string location;
    string description;
    std::vector<double> houseRatings;
    bool status;
    std::vector<Member*> occupiers;
    std::vector<Member*> requestList;
    std::map<string, string> occupierComment;
public:
    House();
    House(const string &houseId, const string &startDate, const string &endDate, const string &address,
          const string &location, const string &description, const std::vector<double> &houseRatings, bool status,
          const vector <Member*> &occupiers, const vector <Member*> &requestList,
          const std::map<string, string> &occupierComment);


    void showFullHouse();

    void showDemoHouse();

    double avgScore();

    friend class Member;
    friend class Admin;
    friend class Data;
};


#endif //HOUSE_H