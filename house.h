
#ifndef HOUSE_H
#define HOUSE_H

#include <iostream>
#include <map>
#include <vector>


using std::string;
using std::cout;
using std::cin;
using std::endl;

const string locations[3] = {"HANOI", "HUE", "SAIGON"};

class House {
protected:
    string houseID;
    string startDate;
    string endDate;
    string address;
    string location;
    string description;
    std::vector<double> houseRatings;
    bool status;
    std::vector<Member> occupiers;
    std::vector<Member> requestList;
    std::map<string, string> occupierComment;
public:
    friend class Member;
    friend class Admin;
    House();



    void showFullHouse();

    void showDemoHouse();

    double avgScore();


};


#endif //HOUSE_H
