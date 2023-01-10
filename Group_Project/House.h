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

static string locations[3] = {"HANOI", "HUE", "SAIGON"};

class Member;
class House {
public:
    friend class Member;
    friend class Admin;
    friend class Data;
    inline static int houseCounter {1};
private:
    string houseID {};
    string startDate {};
    string endDate {};
    string address {};
    string location {};
    string description {};
    double consumingPoints {}, minOccupierRating {};
    vector<double> houseRatings {};
    bool status {}, isListed {};

    // List of available houses
    inline static std::vector<House> listingHouse {};

    vector<Member*> occupiers {};
    vector<Member*> requestList {};
    vector<string> occupierComment {};
public:
    House();
    House(string houseId, string startDate, string endDate, string address,
          string location, string description, double consumingPoints, double minOccupierRating, vector<double> houseRatings, bool isListed, bool status, vector<string> occupierComment);
    House(string houseId, string startDate, string endDate, string address,
          string location, string description, double consumingPoints, double minOccupierRating, vector<double> houseRatings, bool isListed, bool status,
          vector<Member*> occupiers, vector<Member*> requestList,
          vector<string> occupierComment);


    void showFullHouse();

    void showDemoHouse();

    double avgScore();

};

#endif //HOUSE_H
