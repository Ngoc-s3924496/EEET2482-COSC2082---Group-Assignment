//
// Created by huuqu on 12/26/2022.
//



// Consider only load one member at a time.
#include "Member.h"
#include "Admin.h"
#include "Data.h"
#include <vector>
    //Constructor
    Member::Member() = default;

    Member::Member(string id, string fullName, string username,string password, string phoneNumber) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->fullName = std::move(fullName);
        this->phoneNumber = std::move(phoneNumber);
        this->myHouse = nullptr;
        this->occupierRatings = {};
        this->creditPoint = 500;
        this->pendingRequests = {};
        this->ownerComments = {};
    }

    Member::Member(string id, string fullName, string username,string password, string phoneNumber,
        House *myHouse, std::vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
        map<string,string> ownerComments) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->fullName = std::move(fullName);
        this->phoneNumber = std::move(phoneNumber);
        this->myHouse = myHouse;
        this->occupierRatings = std::move(occupierRatings);
        this->creditPoint = creditPoint;
        this->pendingRequests = pendingRequests;
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
                return true;
            }
        }
        cout << "Invalid username or password!" << endl;
        cout << "Do you want to register? (Y/N)" << endl;
        string choice;
        cin >> choice;
        if (choice == "Y") {
            register_account();
        }
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
        return currentMember->fullName;
    }
    void Member::showInfo() {
        // print basic information
        cout << "Full name: " << currentMember->fullName << endl;
        cout << "Phone number: " << currentMember->phoneNumber << endl;
        cout << "Credit point: " << currentMember->creditPoint << endl;
        cout << "Occupier rating: " << currentMember->avgScore(currentMember->occupierRatings) << endl;

        // print all pending requests
        cout << "Pending requests: ";
        for (auto &j: currentMember->pendingRequests) {
            cout << j->houseID << " ";
            cout << j->address << " ";
            cout << j->location << " ";
            cout << j->description << " ";
        }

        // print comments
        cout << "Comments on member: ";
        for (auto &x: currentMember->ownerComments) {
            // x.first = name of commenters, x.second = comments
            cout << x.first << " " << x.second << "\n";
        }
        // new line
        cout << endl;

        // add them function de xem thong tin house
    }

    void Member::listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) {

    }

    void Member::listHouse(string &start, string &end, double &consumingPoint) {

    }

    void Member::unlistHouse() {

    }

    void Member::viewRequest() {
        for (auto &i: currentMember->pendingRequests) {
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
            if (i == location) {
                // list of house
                for (auto &j : currentMember->listingHouse) {
                    // print house with that location
                    if (j.location == location) {
                        cout << j.houseID << " " << j.address << " " << j.location << endl;
                        cout << "  '" << j.description << "'" << endl;
                    }
                }
                return;
            }
        }
        cout << "Invalid location!";
    }

    void Member::makeRequest() {
        cout << "Enter house id: ";
        string house_id;
        cin >> house_id;
        // check if house_id is valid
        for (auto &j : currentMember->listingHouse) {
            if (j.houseID == house_id) {
                // assign this house
                currentMember->pendingRequests.push_back(&j);
                return;
            }
        }
        cout << "Invalid house id!" << endl;
    }

    void Member::viewStatusRequestedHouse() {
        for (auto &i : currentMember->pendingRequests) {
            // if no one request this house
            if (i->occupiers.empty()) {
                continue;
            }
            // if at least one people request this house -> the newest rent will be at last
            if (i->occupiers.at(i->occupiers.size() - 1)->fullName == currentMember->fullName) {
                cout << "You have successfully rent this house!" << endl;
                return;
            }
        }
        cout << "Your requested house is still pending or not allocated!" << endl;
        cout << "Please try again later." << endl;
    }

    void Member::ratingHouse() {
        cout << "You are renting this house: " << currentMember->rentHouse->houseID << endl;
        cout << "Please rate it !" << endl;
        cout << "Enter a score: ";
        string score_str;
        cin >> score_str;
        currentMember->rentHouse->houseRatings.push_back(strtod(score_str.c_str(), nullptr));
        cout << "Do you want to leave a comment (Y/N) ?";
        string choice;
        cin >> choice;
        if (choice == "Y") {
            cout << "Type here: ";
            string comment;
            getline(std::cin,comment);
            currentMember->rentHouse->occupierComment[this->fullName] = comment;
            return;
        }
        cout << "Thank you for using!" << endl;
    }


