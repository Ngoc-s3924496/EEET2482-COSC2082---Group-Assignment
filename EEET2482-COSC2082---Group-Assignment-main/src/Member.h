//
// Created by quanv on 12/27/2022.
//

#ifndef EEET2482_COSC2082_GROUP_ASSIGNMENT_MAIN_MEMBER_H
#define EEET2482_COSC2082_GROUP_ASSIGNMENT_MAIN_MEMBER_H

#include<iostream>
#include<map>
#include<vector>
#include "User.h"
#include "House.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
class Member: public User {
public:
    // allow Admin to access private attribute
    friend class Admin;
    friend class House;
    friend class Data;
private:
    //user full name and mobile phone
    string fullName{};
    string phoneNumber{};

    // The house of user
    House *myHouse;

    // Rent house
    House rentHouse;
    // List of available houses
    static std::vector<House> listingHouse;

    // User money
    int creditPoint{};

    // User points
    std::vector<double> occupierRatings{};

    // User requests
    std::vector<House*> pendingRequests{};

    // Comments of others on this user
    std::map<string, string> ownerComments{}; // adjust later
public:
    //Constructor
    Member();
    Member(string id, string fullName, string username,string password, string phoneNumber,
           House *myHouse, std::vector<double> occupierRatings, int creditPoint, std::vector<House*> pendingRequests,
           std::map<string,string> ownerComments);

    // Basic Methods
    // login
    bool login(string &username, string &password);
    // calculate average score for the current member
    double avgScore(std::vector <double> &occupierRatings);
    // New user -> register an account
    void register_account();
    // show inf
    void showInfo();
    const string &getFullName() const ;

    // Ngoc
    void listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) ;

    void listHouse(string &start, string &end, double &consumingPoint) ;

    void unlistHouse();

    void viewRequest() ;

    void acceptRequest() ;

    void rateOccupier();

    // Quoc
    void searchHouse();

    void makeRequest();

    void viewStatusRequestedHouse() ;

    void ratingHouse();


};

#endif //EEET2482_COSC2082_GROUP_ASSIGNMENT_MAIN_MEMBER_H
