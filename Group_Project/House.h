#ifndef HOUSE_H
#define HOUSE_H

#include<iostream>
#include<map>
#include<vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

const string locations[3] = {"HANOI", "HUE", "SAIGON"};

class Member;
class House {
public:
    friend class Member;
    friend class Admin;
    friend class Data;
public:
    string houseID;
    string startDate;
    string endDate;
    string address;
    string location;
    string description;
    double consumingPoints, minOccupierRating;
    vector<double> houseRatings;
    bool status;
    vector<Member*> occupiers;
    vector<Member*> requestList;
    vector<string> occupierComment;
public:
    House();
    House(string houseId, string startDate, string endDate, string address,
          string location, string description, double consumingPoints, double minOccupierRating, vector<double> houseRatings, bool status, vector<string> occupierComment);
    House(string houseId, string startDate, string endDate, string address,
          string location, string description, double consumingPoints, double minOccupierRating, vector<double> houseRatings, bool status,
          vector<Member*> occupiers, vector<Member*> requestList,
          vector<string> occupierComment);


    void showFullHouse();

    void showDemoHouse();

    double avgScore();
};

#endif //HOUSE_H