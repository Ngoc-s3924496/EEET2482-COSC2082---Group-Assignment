//
// Created by huuqu on 12/26/2022.
//

#include "Member.h"
    //Constructor
    Member::Member() = default;

    Member::Member(string id, string fullName, string username,string password, string phoneNumber,
        House myHouse, double occupierRatings, int creditPoint, std::vector<House> pendingRequests,
        std::map<string,string> ownerComments) {
        this->id = id;
        this->fullName = fullName;
        this->username = username;
        this->phoneNumber = phoneNumber;
        this->password = password;
        this->myHouse = myHouse;
        this->occupierRatings = occupierRatings;
        this->creditPoint = creditPoint;
        for (auto &i : pendingRequests) {
        this->pendingRequests.push_back(i);
        }
        for (const auto& [key, value] : ownerComments) {
        ownerComments[key] = value;
        }
    }
    bool Member::login(string &username, string &password) {
            if (this->username == username && this->password == password) {
                cout << "Login successfully !" << std::endl;
                return true;
            }
        cout << "Invalid username or password!" << std::endl;
        register_account();
        return false;
    }

    void Member::register_account() {
        string username;
        cout << "Enter username: ";
        std::getline(std::cin, username);
        string password;
        cout << "Enter password: ";
        std::getline(std::cin, password);
        this->username = username;
        this->password = password;
        cout << "Register successfully!";
    }

    void Member::showInfo() {
        // print basic information
        cout << "Full name: " << this->fullName << std::endl;
        cout << "Phone number: " << this->phoneNumber << std::endl;
        cout << "Credit point: " << this->creditPoint << std::endl;
        cout << "Occupied rating: " << this->occupierRatings << std::endl;

        // print all pending requests
        cout << "Pending requests: ";
        for (auto &j: this->pendingRequests) {
            cout << j.houseID << " ";
            cout << j.address << " ";
            cout << j.location << " ";
            cout << j.description << " ";
        }

        // average score
        cout << "Average score: " << this->avgScore() << std::endl;

        // print comments
        cout << "Comments on member: ";
        for (auto &x: this->ownerComments) {
            // x.first = name of commenters, x.second = comments
            std::cout << x.first << " " << x.second << "\n";
        }
        // new line
        cout << std::endl;

        // add them function de xem thong tin house
    }

    void Member::listHouse(string &start, string &end, double &consumingPoint, double &minOccupiedRating) {

    }

    void Member::listHouse(string &start, string &end, double &consumingPoint) {

    }

    void Member::unlistHouse() {

    }

    void Member::viewRequest() {
        for (auto &i: pendingRequests) {
            cout << i.houseID << " ";
        }
    }

    void Member::acceptRequest() {
    }

    void Member::rateOccupier() {
    }

    double Member::avgScore() {
    }

    void Member::searchHouse() {
        cout << "Enter location: ";
        string location;
        std::cin >> location;
        for (auto &i: locations) {
            if (i == location) {
                // list house with location
                for (auto &j : House)
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

        // if valid
        // store occupiedHouse with id and its corresponding value in class House

    }

    void Member::viewStatusRequestedHouse() {

    };

    void Member::ratingHouse() {
        cout << "Enter score for house " << this -> rentHouse.at(rentHouse.size() - 1).houseID << ": ";
        double score;
        cin >> score;

        // update score of house
        this -> rentHouse.at(rentHouse.size() - 1).occupiersScores.push_back(score);
    }

    const string & Member::getFullName() const {
        return fullName;
    }
