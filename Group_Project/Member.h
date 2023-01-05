#ifndef MEMBER_H
#define MEMBER_H

#include<iostream>
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
    inline static Member* currentMember {};
    inline static bool isLoggedIn {false};
    inline static int memberCounter {1};
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



    // User money
    int creditPoint {};

    // User points
    vector<double> occupierRatings {};

    // User requests
    vector<House*> pendingRequests {};

    // Comments of others on this user
    vector<string> ownerComments {};
public:
    //Constructor
    Member();
    Member(string id, string fullName, string userName, string password, string phoneNumber, std::vector <double> occupierRatings, int creditPoints,vector<string> ownerComment);
    Member(string id, string fullName, string username, string password, string phoneNumber,
           House *myHouse, std::vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
           House *rentHouse, vector<string> ownerComments);

    // Basic Methods
    // login
    static bool login();
    static void logout();
    // calculate average score for the current member
    double avgScore();
    // New user -> register an account
    static bool register_account();
    // show inf
    void showFullInfo();
    void showMiniInfo();
    [[nodiscard]] const string &getFullName() const ;

    // Ngoc
    static void listHouse();

    static void unListHouse(int i);

    static void viewPendingRequest();

    static void acceptRequest() ;

    static void rateOccupier();

    // Quoc
    static void searchHouse();

    static void makeRequest();

    static void viewRentStatus();

    static void ratingHouse();
    static void displayListedHouse();
    static void removeRequest(Member *member, House *house);
};
#endif //MEMBER_H