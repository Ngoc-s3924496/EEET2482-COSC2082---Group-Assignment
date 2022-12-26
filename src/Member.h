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
#include "Data.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
class Member : public User {
private:
    //user full name and mobile phone
    string fullName{};
    string phoneNumber{};

    // The house of user
    House myHouse{};

    // Rent house
    House rentHouse {};
    // List of available houses
    static std::vector<House> listingHouse;

    // User money
    int creditPoint{};

    // User points
    std::vector<double> occupierRatings{};

    // User requests
    std::vector<House> pendingRequests{};

    // Comments of others on this user
    std::map<string, string> ownerComments{}; // adjust later
public:
    // allow Admin to access private attribute
    friend Admin;
    friend House;
    friend Data;

    // Getters and setters
    const string &getFullName() const;

    void setFullName(const string &fullName);

    const string &getPhoneNumber() const;

    void setPhoneNumber(const string &phoneNumber);

    const House &getMyHouse() const;

    void setMyHouse(const House &myHouse);

    const House &getRentHouse() const;

    void setRentHouse(const House &rentHouse);

    static const vector<House> &getListingHouse();

    static void setListingHouse(const vector<House> &listingHouse);

    int getCreditPoint() const;

    void setCreditPoint(int creditPoint);

    const vector<double> &getOccupierRatings() const;

    void setOccupierRatings(const vector<double> &occupierRatings);

    const vector<House> &getPendingRequests() const;

    void setPendingRequests(const vector<House> &pendingRequests);

    const map<string, string> &getOwnerComments() const;

    void setOwnerComments(const map<string, string> &ownerComments);


    //Constructor
    Member();
    Member(string id, string fullName, string username,string password, string phoneNumber,
           House myHouse, std::vector<double> occupierRatings, int creditPoint, std::vector<House> pendingRequests,
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

    void ratingHouse() ;



};


#endif //MEMBER_H
