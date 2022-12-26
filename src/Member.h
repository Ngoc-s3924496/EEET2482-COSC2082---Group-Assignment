//
// Created by huuqu on 12/26/2022.
//

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <map>
#include "House.h"
#include "User.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
class Member : public User {
private:
    static std::map<string, string> accounts;
    string fullName{};
    string phoneNumber{};
    // Implement house class
    // string in 2 below maps are House ID
    House myHouse{};
    vector <House> occupiedHouse{};
    int creditPoint{};
    double occupiedRating{};
    std::vector<Member> pendingRequests{};
    // string in 2 below maps are Member ID
    std::map<string, double> ownerScore{}; // adjust later
    std::map<string, string> ownerComments{}; // adjust later
public:
    // allow Admin to access private attribute
    friend Admin;
    friend House;
    //Constructor
    Member();

    static bool login(string &username, string &password);

    static void register_account();

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


#endif //EEET2482_COSC2082___GROUP_ASSIGNMENT_ESSENSIALS_H
