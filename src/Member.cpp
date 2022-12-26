//
// Created by huuqu on 12/26/2022.
//

#include "Member.h"
    string locations[3] = {"HANOI", "HUE", "SAIGON"};
    //Constructor
    Member::Member() = default;

    bool Member::login(string &username, string &password) {
        for (auto &i: Member::accounts) {
            if (i.first == username && i.second == password) {
                cout << "Login successfully !" << std::endl;
                return true;
            }
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
        accounts[username] = password;
        cout << "Register successfully!";
    }

    void Member::showInfo() {
        // print basic information
        cout << "Full name: " << this->fullName << std::endl;
        cout << "Phone number: " << this->phoneNumber << std::endl;
        cout << "Credit point: " << this->creditPoint << std::endl;
        cout << "Occupied rating: " << this->occupiedRating << std::endl;

        // print all pending requests
        cout << "Pending requests: ";
        for (auto &j: this->pendingRequests) {
            cout << j.fullName << " ";
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
            cout << i.fullName << " ";
        }
    }

    void Member::acceptRequest() {
        cout << "Enter request id: ";
        string id;
        cin >> id;
        for (auto &i: pendingRequests) {
            if (i.id == id) {
                cout << "Accept successfully!" << endl;

                // add the current at the back
                pendingRequests.push_back(i);

                // delete all other request if accept the last
                pendingRequests.erase(pendingRequests.begin(), pendingRequests.end() - 1);
                return;
            }
        }
        cout << "No id found!" << endl;
    }

    void Member::rateOccupier() {
        cout << "Enter a score for " << pendingRequests.at(0).fullName << " : ";
        int score{};
        cin >> score;

        // update score
        pendingRequests.at(0).ownerScore[this->id] = score;
    }

    double Member::avgScore() {
        double tmp{};
        for (auto &i: ownerScore) {
            tmp += i.second;
        }
        return tmp / ownerScore.size();
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
        cout << "Enter score for house " << this -> occupiedHouse.houseId << ": ";
        double score;
        cin >> score;

        // update score of house
        this->occupiedHouse.houseRatingScore = score;
    }

    const string & Member::getFullName() const {
        return fullName;
    }

};
