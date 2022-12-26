//
// Created by huuqu on 12/26/2022.
//

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <map>
#include "House.h"
#include "Admin.h"
#include "User.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
class Member : public User {
private:
    string fullName{};
    string phoneNumber{};
    House myHouse{};
    std::vector <House> rentHouse{};
    static std::vector<House> listingHouse;
    int creditPoint{};
    double occupierRatings{};
    std::vector<House> pendingRequests{};
    // string in 2 below maps are Member ID
    std::map<string, double> ownerScore{}; // adjust later
    std::map<string, string> ownerComments{}; // adjust later
public:
    // allow Admin to access private attribute
    friend Admin;
    friend House;
    //Constructor
    Member();
    Member(string id, string fullName, string username,string password, string phoneNumber,
           House myHouse, double occupierRatings, int creditPoint, std::vector<House> pendingRequests,
           std::map<string,string> ownerComments);
    bool login(string &username, string &password);

    void register_account();

    void showInfo();

    void listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) ;

    void listHouse(string &start, string &end, double &consumingPoint) ;

    void unlistHouse();

    void viewRequest() ;

    void acceptRequest() ;

    void rateOccupier();

    double avgScore();

    static void searchHouse();

    void makeRequest();

    void viewStatusRequestedHouse() ;

    void ratingHouse() ;

    const string &getFullName() const ;

};


#endif //MEMBER_H
