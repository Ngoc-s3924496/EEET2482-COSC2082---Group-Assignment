//
// Created by huuqu on 12/26/2022.
//



// Consider only load one member at a time.
#include "Member.h"
#include "Admin.h"
#include "Data.h"
#include <cstring>
#include <iomanip>
#include <vector>
//Constructor
Member::Member() = default;
Member::Member(string id, string fullName, string userName, string password, string phoneNumber, std::vector <double> occupierRatings, int creditPoints,map<string,string> ownerComment) {
    this->id = std::move(id);
    this->fullName = std::move(fullName);
    this->username = std::move(userName);
    this->password = std::move(password);
    this->phoneNumber = std::move(phoneNumber);
    this->ownerComments = std::move(ownerComment);
    this->creditPoint = creditPoints;
    this->occupierRatings = std::move(occupierRatings);
}

Member::Member(string id, string fullName, string username, string password, string phoneNumber,
               House *myHouse, vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
               House *rentHouse, map<string,string> ownerComments) {
    this->id = std::move(id);
    this->username = std::move(username);
    this->password = std::move(password);
    this->fullName = std::move(fullName);
    this->phoneNumber = std::move(phoneNumber);
    this->myHouse = myHouse;
    this->occupierRatings = std::move(occupierRatings);
    this->creditPoint = creditPoint;
    this->pendingRequests = std::move(pendingRequests);
    this->rentHouse = rentHouse;
    this->ownerComments = std::move(ownerComments);
}

bool Member::login() {
    string username_val;
    cout << "Enter username: ";
    std::getline(cin, username_val);
    string password_val;
    cout << "Enter password: ";
    std::getline(cin, password_val);
    for (auto &i : Data::userList) {
        if (i.username == username_val && i.password == password_val) {
            // set current member
            Member::currentMember = &i;

            cout << "Login successfully" << endl;
            isLoggedIn = true;
            return true;
        }
    }
    cout << "Invalid username or password!" << endl;
    cout << "Do you want to register? (Y)" << endl;
    string choice;
    getline(cin, choice);
    if (choice == "Y" || choice == "y") {
        return register_account();
    }
    isLoggedIn = false;
    return false;
}
void Member::logout() {
    Data::saveUserData(*Member::currentMember);
    Data::loadUserData();
    Member::isLoggedIn = false;
    delete currentMember;
}
bool Member::register_account() {
    cout << "Registering..." << endl;
    string username_val;
    cout << "Enter username: ";
    std::getline(cin, username_val);
    string password_val;
    cout << "Enter password: ";
    std::getline(cin, password_val);
    for (auto &i : Data::userList) {
        if (i.username == username_val) {
            cout << "This username has already been taken!" << endl;
            return false;
        }
    }
    string data;
    currentMember = new Member();
    cout << "Enter full name: ";
    getline(cin,data);
    currentMember->fullName = data;

    cout << "Enter phone number: ";
    getline(cin,data);
    currentMember->phoneNumber = data;
    currentMember->id = "New";
    currentMember->username = username_val;
    currentMember->password = password_val;
    currentMember->creditPoint = 500;
    isLoggedIn = true;

    cout << "Register successfully!" << endl;
//    Data::loadUserData();
    cout << Data::userList.size() << endl;
    Data::saveUserData(*Member::currentMember);
    Data::preloadUserData();
    return true;
}

double Member::avgScore(vector <double> &occupierRatings) {
    double avgScore {};
    if (this->occupierRatings.empty()) {
        return 0;
    }
    else if (this->occupierRatings.size() == 1) {
        return this->occupierRatings.at(0);
    }
    for (auto &i : this->occupierRatings) {
        avgScore += i;
    }
    return avgScore / occupierRatings.size();
}
const string & Member::getFullName() const {
    return this->fullName;
}
void Member::showInfo() {
    // print basic information
    cout << "Full name: " << this->fullName << endl;
    cout << "Phone number: " << this->phoneNumber << endl;
    cout << "Credit point: " << this->creditPoint << endl;
    cout << "Occupier rating: " << std::setprecision(2) << std::fixed << this->avgScore(this->occupierRatings) << endl;

    // print all pending requests
    cout << "Pending requests: ";
    if (this-> pendingRequests.empty()) {
        cout << "No request found!" << endl;
    }
    else {
        for (auto &j: this->pendingRequests) {
            cout << j->houseID << " ";
            cout << j->address << " ";
            cout << j->location << " ";
            cout << j->description << " ";
        }
    }
    // print comments
    cout << "Comments on this member: " << endl;
    for (auto &x: this->ownerComments) {
        // x.first = name of commenters, x.second = comments
        for (auto &i : Data::userList) {
            if (i.username == x.first) {
                cout << std::setw(10) << x.first << "-" << i.fullName << " comments: " << x.second << endl;
            }
        }
    }
    // new line
    cout << endl;
}

void Member::listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) {

}

void Member::listHouse(string &start, string &end, double &consumingPoint) {

}

void Member::unlistHouse() {

}

void Member::viewRequest() {
    for (auto &i: this->pendingRequests) {
        cout << i->houseID << " ";
    }
}

void Member::acceptRequest() {
}

void Member::rateOccupier() {
}

void Member::searchHouse() {
    cout << "Enter location: ";
    string location;
    getline(cin,location);
    // check if location is valid
    for (auto &i : locations) {
        if (strcasecmp(i.c_str(),location.c_str()) == 0) {
            // list of house
            if (Member::listingHouse.empty()) {
                cout << "No house available in " << i  << "!" << endl;
            }
            for (auto &j : Member::listingHouse) {
                // print house with that location
                if (strcasecmp(j.location.c_str(),location.c_str()) == 0) {
                    cout << j.houseID << " " << j.address << " " << j.location << endl;
                    cout << "  '" << j.description << "'" << endl;
                }
            }
            return;
        }
    }
    cout << "Invalid location!" <<endl;
}

void Member::makeRequest() {
    if (Member::listingHouse.empty()) {
        cout << "There is currently no available house!" << endl;
        return;
    }
    for (auto &i : Member::listingHouse) {
        cout << std::setw(10) << i.houseID << " " << i.address << " " << i.location << endl;
        cout << std::setw(15) << i.minOccupierRating << endl;
    }
    cout << "Enter house id: ";
    string house_id;
    getline(cin,house_id);
    // check if house_id is valid
    for (auto &j : Member::listingHouse) {
        if (j.houseID == house_id) {
            if (this->avgScore(this->occupierRatings) >= j.minOccupierRating) {
                // assign this house
                this->pendingRequests.push_back(&j);
                cout << "Request successfully!" << endl;
                return;
            }
            cout << "Not enough points!" << endl;
            return;
        }
    }
    cout << "Invalid house id!" << endl;
}

void Member::viewStatusRequestedHouse() {
    for (auto &i : this->pendingRequests) {
        // if no one request this house
        if (i->occupiers.empty()) {
            continue;
        }
        // if at least one people request this house -> the newest rent will be at last
        if (i->occupiers.at(i->occupiers.size() - 1)->fullName == this->fullName) {
            cout << "You have successfully rent this house!" << endl;
            return;
        }
    }
    cout << "Your requested house is still pending or not allocated!" << endl;
    cout << "Please try again later." << endl;
}
void Member::ratingHouse() {
    if (this->rentHouse == nullptr) {
        cout << "You have not rent any house!" << endl;
        return;
    }
    cout << "You are renting this house: " << this->rentHouse->houseID << endl;
    cout << "Please rate it !" << endl;
    cout << "Enter a score: ";
    string score_str;
    getline(cin, score_str);
    this->rentHouse->houseRatings.push_back(strtod(score_str.c_str(), nullptr));
    cout << "Do you want to leave a comment (Y/N) ?";
    string choice;
    getline(cin, choice);
    if (choice == "Y") {
        cout << "Type here: ";
        string comment;
        getline(std::cin,comment);
        this->rentHouse->occupierComment[this->fullName] = comment;
        return;
    }
    cout << "Thank you for using!" << endl;
}


