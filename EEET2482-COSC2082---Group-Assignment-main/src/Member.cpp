//
// Created by huuqu on 12/26/2022.
//

#include "Member.h"
    //Constructor
    Member::Member() = default;

    Member::Member(string id, string fullName, string username,string password, string phoneNumber,
        House *myHouse, std::vector<double> occupierRatings, int creditPoint, std::vector<House*> pendingRequests,
        std::map<string,string> ownerComments) {
        this->id = id;
        this->fullName = std::move(fullName);
        this->username = std::move(username);
        this->phoneNumber = std::move(phoneNumber);
        this->password = std::move(password);
        this->myHouse = myHouse;
        this->occupierRatings = std::move(occupierRatings);
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
        cout << "Do you want to register? (Y/N)" << std::endl;
        string choice;
        cin >> choice;
        if (choice == "Y") {
            register_account();
        }
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
    double Member::avgScore(std::vector <double> &occupierRatings) {
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
        return fullName;
    }
    void Member::showInfo() {
        // print basic information
        cout << "Full name: " << this->fullName << std::endl;
        cout << "Phone number: " << this->phoneNumber << std::endl;
        cout << "Credit point: " << this->creditPoint << std::endl;
        cout << "Occupier rating: " << this->avgScore(occupierRatings) << std::endl;

        // print all pending requests
        cout << "Pending requests: ";
        for (auto &j: this->pendingRequests) {
            cout << j->houseID << " ";
            cout << j->address << " ";
            cout << j->location << " ";
            cout << j->description << " ";
        }

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
        std::cin >> location;
        // check if location is valid
        for (auto &i : locations) {
            if (i == location) {
                // list of house
                for (auto &j : listingHouse) {
                    // print house with that location
                    if (j.location == location) {
                        cout << j.houseID << " " << j.address << " " << j.location << std::endl;
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
        for (auto &j : listingHouse) {
            if (j.houseID == house_id) {
                // assign this house
                pendingRequests.push_back(&j);
                return;
            }
        }
        cout << "Invalid house id!" << endl;
    }

    void Member::viewStatusRequestedHouse() {
        for (auto &i : pendingRequests) {
            // if no one request this house
            if (i->occupiers.empty()) {
                continue;
            }
            // if at least one people request this house -> the newest rent will be at last
            if (i->occupiers.at(i->occupiers.size() - 1).fullName == this->fullName) {
                cout << "You have successfully rent this house!" << endl;
                return;
            }
        }
        cout << "Your requested house is still pending or not allocated!" << endl;
        cout << "Please try again later." << endl;
    }

    void Member::ratingHouse() {
        cout << "You are renting this house: " << rentHouse.houseID << endl;
        cout << "Please rate it !" << endl;
        cout << "Enter a score: ";
        string score_str;
        cin >> score_str;
        rentHouse.houseRatings.push_back(strtod(score_str.c_str(), nullptr));
        cout << "Do you want to leave a comment (Y/N) ?";
        string choice;
        cin >> choice;
        if (choice == "Y") {
            cout << "Type here: ";
            string comment;
            getline(std::cin,comment);
            rentHouse.occupierComment[this->fullName] = comment;
            return;
        }
        cout << "Thank you for using!" << endl;
    }


