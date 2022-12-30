//
// Created by huuqu on 12/26/2022.
//

#ifndef MEMBER_H
#define MEMBER_H

#include<iostream>
#include<map>
#include<vector>
#include "House.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
class Member {
public:
    // allow Admin to access private attribute
    friend class Admin;
    friend class House;
    friend class Data;
    inline static Member* currentMember {};
    inline static bool isLoggedIn {false};
private:
    string id {};
    string username {};
    string password {};
    //user full name and mobile phone
    string fullName {};
    string phoneNumber {};
    // The house of user
    House *myHouse = nullptr;

    // Rent house
    House *rentHouse = nullptr;

    // List of available houses
    inline static std::vector<House> listingHouse {};

    // User money
    int creditPoint {};

    // User points
    vector<double> occupierRatings {};

    // User requests
    vector<House*> pendingRequests {};

    // Comments of others on this user
    map<string, string> ownerComments {}; // adjust later
public:
    //Constructor
    Member();
    Member(string id, string fullName, string userName, string password, string phoneNumber, std::vector <double> occupierRatings, int creditPoints,map<string,string> ownerComment);
    Member(string id, string fullName, string username, string password, string phoneNumber,
           House *myHouse, std::vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
           House *rentHouse, map<string,string> ownerComments);

    // Basic Methods
    // login
    static bool login();
    static void logout();
    // calculate average score for the current member
    double avgScore(std::vector <double> &occupierRatings);
    // New user -> register an account
    static bool register_account();
    // show inf
    void showInfo();
    const string &getFullName() const ;

    // Ngoc
    void removeRequest(Member* member, House* house);
    Member getMember();
    void test();
    void listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) ;

    void listHouse(string &start, string &end, double &consumingPoint) ;

    void unlistHouse();

    void viewRequest() ;

    void acceptRequest() ;

    void rateOccupier();

    // Quoc
    void displayListedHouse();

    void searchHouse();

    void makeRequest();

    void viewStatusRequestedHouse() ;

    void ratingHouse();
};


#endif //MEMBER_H
