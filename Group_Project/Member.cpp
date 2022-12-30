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
    memberCounter++;
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
    memberCounter++;
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
    currentMember->id = "M" + std::to_string(memberCounter);
    currentMember->username = username_val;
    currentMember->password = password_val;
    currentMember->creditPoint = 500;
    isLoggedIn = true;

    cout << "Register successfully!" << endl;
    memberCounter++;
    Data::saveUserData(*Member::currentMember);
    Data::preloadUserData();
    return true;
}

double Member::avgScore() {
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
    return avgScore / this->occupierRatings.size();
}
const string & Member::getFullName() const {
    return this->fullName;
}
void Member::showFullInfo() {
    // print basic information
    cout << "Full name: " << this->fullName << endl;
    cout << "Phone number: " << this->phoneNumber << endl;
    cout << "Credit point: " << this->creditPoint << endl;
    cout << "Occupier rating: " << std::setprecision(2) << std::fixed << this->avgScore() << endl;
    // print all pending requests
    cout << "Pending requests: " << endl;
    if (this-> pendingRequests.empty()) {
        cout << "\tNo request found!" << endl;
    }
    else {
        for (auto &j: this->pendingRequests) {
            cout << "\t";
            cout << j->houseID << "\n\t\t";
            cout << j->address << "\n\t\t";
            cout << j->location << "\n\t\t";
            cout << j->description << endl;
        }
    }
    cout << "Rent house: " << endl;
    if (rentHouse == nullptr) {
        cout << "\t" << "There is no house to be shown" << endl;
    } else {
        cout << "\t" <<rentHouse->houseID << "\n\t\t" << rentHouse->address << "\n\t\t" << rentHouse->location << "\n\t\t" << rentHouse->description << endl;
    }
    // print comments
    cout << "Comments on this member: " << endl;
    if (ownerComments.empty()) {
        cout << "\tThere are no comments" << endl;
        return;
    }
    for (auto &x: this->ownerComments) {
        // x.first = name of commenters, x.second = comments
        cout << "\t";
        for (auto &i : Data::userList) {
            if (i.username == x.first) {
                cout << std::setw(10) << x.first << "-" << i.fullName << " comments: " << x.second << endl;
            }
        }
    }
    // new line
    cout << endl;
}
void Member::showMiniInfo() {
    cout << "\tFull name: " << this->fullName << endl;
    cout << "\tPhone number: " << this->phoneNumber << endl;
    cout << "\tCredit point: " << this->creditPoint << endl;
    cout << "\tOccupier rating: " << std::setprecision(2) << std::fixed << this->avgScore() << endl;
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
            if (currentMember->avgScore() >= j.minOccupierRating) {
                // assign this house
                currentMember->pendingRequests.push_back(&j);
                currentMember->creditPoint -= j.consumingPoints;
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
    if (currentMember->rentHouse == nullptr) {
        cout << "You have not rent any house!" << endl;
        return;
    }
    cout << "You are renting this house: " << currentMember->rentHouse->houseID << endl;
    cout << "Please rate it !" << endl;
    cout << "Enter a score: ";
    string score_str;
    getline(cin, score_str);
    currentMember->rentHouse->houseRatings.push_back(strtod(score_str.c_str(), nullptr));
    cout << "Do you want to leave a comment (Y/N) ?";
    string choice;
    getline(cin, choice);
    if (choice == "Y") {
        cout << "Type here: ";
        string comment;
        getline(std::cin,comment);
        currentMember->rentHouse->occupierComment[currentMember->fullName] = comment;
        return;
    }
    cout << "Thank you for using!" << endl;
}


