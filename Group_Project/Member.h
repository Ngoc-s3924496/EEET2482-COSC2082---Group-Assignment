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
class Member {
public:
    // allow Admin to access private attribute
    friend class Admin;
    friend class House;
    friend class Data;
private:
    string id;
    string username;
    string password;
    //user full name and mobile phone
    string fullName;
    string phoneNumber;

    // The house of user
    House *myHouse = nullptr;

    // Rent house
    House *rentHouse = nullptr;

    // List of available houses
    inline static std::vector<House> listingHouse;

    // User money
    int creditPoint {};

    // User points
    std::vector<double> occupierRatings {};

    // User requests
    std::vector<House*> pendingRequests {};

    // Comments of others on this user
    std::map<string, string> ownerComments {}; // adjust later
public:
    //Constructor
    Member();
    Member(string id, string fullName, string username, string password, string phoneNumber);
    Member(string id, string fullName, string username, string password, string phoneNumber,
           House *myHouse, std::vector<double> occupierRatings, int creditPoint, std::vector<House*> pendingRequests,
           std::map<string,string> ownerComments);
    Member(string id, string fullName, string username, string password, string phoneNumber,
           House *myHouse, std::vector<double> occupierRatings, int creditPoint, std::vector<House*> pendingRequests,
           House *rentHouse, std::map<string,string> ownerComments);

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


#endif //MEMBER_H
