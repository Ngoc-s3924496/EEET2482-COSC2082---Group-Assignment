//
// Created by huuqu on 12/26/2022.
//



// Consider only load one member at a time.
#include "Member.h"
#include "Admin.h"
#include "Data.h"
#include <string.h>
#include <iomanip>
#include <vector>
    //Constructor
    Member::Member() = default;

    Member::Member(string id, string fullName, string username, string password, string phoneNumber,
                   vector<double> occupierRatings, int creditPoint, map<string,string> ownerComments) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->fullName = std::move(fullName);
        this->phoneNumber = std::move(phoneNumber);
        this->myHouse = nullptr;
        this->occupierRatings = occupierRatings;
        this->creditPoint = creditPoint;
        this->pendingRequests = {};
        this->ownerComments = ownerComments;
    }

    Member::Member(string id, string fullName, string username, string password, string phoneNumber,
        House *myHouse, vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
        House *rentHouse, map<string,string> ownerComments) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->fullName = std::move(fullName);
        this->phoneNumber = std::move(phoneNumber);
        this->myHouse = myHouse;
        this->occupierRatings = std::move(occupierRatings);
        this->creditPoint = creditPoint;
        this->pendingRequests = pendingRequests;
        this->rentHouse = rentHouse;
        this->ownerComments = ownerComments;
    }

    bool Member::login() {
        cin.ignore();
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
        cin >> choice;
        if (choice == "Y" || choice == "y") {
            return register_account();
        }
        isLoggedIn = false;
        return false;
    }

    bool Member::register_account() {
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
        currentMember->username = username_val;
        currentMember->password = password_val;
        cout << "Register successfully!";
        isLoggedIn = true;
        return true;
    }
    double Member::avgScore(vector <double> &occupierRatings) {
        double avgScore {};
        if (occupierRatings.empty()) {
            return 0;
        }
        else if (occupierRatings.size() == 1) {
            return occupierRatings.at(0);
        }
        for (auto &i : occupierRatings) {
             avgScore += i;
        }
        return avgScore / occupierRatings.size();
    }
    const string & Member::getFullName() const {
        return this->fullName;
    }
    void Member::showInfo() {
        if (this != nullptr) {
            // print basic information
            cout << "Full name: " << this->fullName << endl;
            cout << "Phone number: " << this->phoneNumber << endl;
            cout << "Credit point: " << this->creditPoint << endl;
            cout << "Occupier rating: " << this->avgScore(this->occupierRatings) << endl;

            // print all pending requests
            cout << "Pending requests: " << endl;
            if (this-> pendingRequests.empty()) {
                cout << "No request found!" << endl;
            }
            else {
                for (auto &j: this->pendingRequests) {
                    cout << j->houseID << " ";
                    cout << j->address << " ";
                    cout << j->location << " ";
                    cout << j->description << " " << endl;
                }
            }
            // print comments
            cout << "Comments on member: " << endl;
            for (auto &x: this->ownerComments) {
                // x.first = name of commenters, x.second = comments
                for (auto &i : Data::userList) {
                    if (i.username == x.first) {
                        cout << std::setw(10) << x.first << "-" << i.fullName << " comments: " << x.second << "\n";
                    }
                }
            }
            // new line
            cout << endl;

            // add them function de xem thong tin house
        } else {
            cout << "There is no user to be shown" << endl;
        }
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
        cin >> location;
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
        }
        cout << "Enter house id: ";
        string house_id;
        cin >> house_id;
        // check if house_id is valid
        for (auto &j : Member::listingHouse) {
            if (j.houseID == house_id) {
                // assign this house
                this->pendingRequests.push_back(&j);
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
        cin >> score_str;
        this->rentHouse->houseRatings.push_back(strtod(score_str.c_str(), nullptr));
        cout << "Do you want to leave a comment (Y/N) ?";
        string choice;
        cin >> choice;
        if (choice == "Y") {
            cout << "Type here: ";
            string comment;
            getline(std::cin,comment);
            this->rentHouse->occupierComment[this->fullName] = comment;
            return;
        }
        cout << "Thank you for using!" << endl;
    }


