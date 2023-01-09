#include "Member.h"
#include "Admin.h"
#include "Data.h"
#include <cstring>
#include <iomanip>
#include <vector>
//Constructor
Member::Member() = default;
Member::Member(string id, string fullName, string userName, string password, string phoneNumber, std::vector <double> occupierRatings, int creditPoints,vector<string> ownerComment) {
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
               string myHouseID, vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
               House *rentHouse, vector<string> ownerComments) {
    this->id = std::move(id);
    this->username = std::move(username);
    this->password = std::move(password);
    this->fullName = std::move(fullName);
    this->phoneNumber = std::move(phoneNumber);
    for (auto &i : Data::houseList) {
        if (i.houseID == myHouseID) {
            this->myHouse = &i;
        }
    }
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
    Member::currentMember->isLoggedIn = false;
    Data::updateUserData(*Member::currentMember);
    Data::loadFullData();
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
    Data::updateUserData(*Member::currentMember);
    Data::loadFullData();
    return true;
}

void Member::addHouse() {
    if (Member::currentMember->myHouse != nullptr) {
        cout << "You have already registered a house!" << endl;
        return;
    }
    string data;
    Member::currentMember->myHouse = new House();
    if (Member::currentMember->myHouse == nullptr) {
        cout << "Failed to register!" << endl;
        return;
    }
    cout << "Registering your house..." << endl;
    Member::currentMember->myHouse->houseID = "H" + std::to_string(House::houseCounter);
    cout << "Enter location: ";
    getline(cin,data);
    bool isNotValid = true;
    while (isNotValid) {
        for (auto &location : locations) {
            if (strcasecmp(location.c_str(),data.c_str()) == 0) {
                isNotValid = false;
                break;
            }
        }
        if(isNotValid) {
            cout << "Invalid location!" << endl;
            cout << "Only SAIGON, HANOI and HUE are permitted." << endl;
            cout << "Enter location: ";
            getline(cin,data);
        }
    }
    Member::currentMember->myHouse->location = data;
    cout << "Enter address: ";
    getline(cin,data);
    Member::currentMember->myHouse->address = data;
    cout << "Enter description: ";
    getline(cin,data);
    Member::currentMember->myHouse->description = data;
    Data::updateUserData(*Member::currentMember);
    Data::updateHouseData(*Member::currentMember->myHouse);
    Data::loadFullData();
    cout << "Your house is registered successfully!" << endl;
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
    cout << "--------------------------------------------" << endl;
    cout << "Full name: " << this->fullName << endl;
    cout << "Phone number: " << this->phoneNumber << endl;
    cout << "Credit point: " << this->creditPoint << endl;
    cout << "Occupier rating: " << std::setprecision(2) << std::fixed << this->avgScore() << endl;
    if (this->myHouse != nullptr) {
        cout << "Owned House: " << this->myHouse->houseID << endl;
    }
    else {
        cout << "No house registered!" << endl;
    }
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
    if (this->rentHouse == nullptr) {
        cout << "\t" << "There is no house to be shown" << endl;
    } else {
        cout << "\t" <<this->rentHouse->houseID << "\n\t\t" << this->rentHouse->address << "\n\t\t" << this->rentHouse->location << "\n\t\t" << this->rentHouse->description << endl;
    }
    // print comments
    cout << "Comments on this member: " << endl;
    if (this->ownerComments.empty()) {
        cout << "\tThere are no comments" << endl;
        return;
    }
    for (auto &x: this->ownerComments) {
        cout << "\t" << x << endl;
    }
    // new line
    cout << "--------------------------------------------" << endl;
    cout << endl;
}
void Member::showMiniInfo() {
    cout << "\tFull name: " << this->fullName << endl;
    cout << "\tPhone number: " << this->phoneNumber << endl;
    cout << "\tCredit point: " << this->creditPoint << endl;
    cout << "\tOccupier rating: " << std::setprecision(2) << std::fixed << this->avgScore() << endl;
    cout << endl;
}
void Member::listHouse() {
    if (currentMember->myHouse == nullptr){
        cout << "No house to list" << endl;
        return;
    }
    if (currentMember->myHouse->isListed) {
        unListHouse(1);
    }
    string startDate, endDate, consumingPoint, minRating;
    cout << "Enter your listing start date (DD/MM/YYYY): ";
    getline(cin, startDate);
    cout << "Enter your listing end date  (DD/MM/YYYY): ";
    getline(cin, endDate);
    cout << "Enter your listing consuming points: ";
    getline(cin, consumingPoint);
    cout << "Do you want to have a occupier rating requirement? (Y): ";
    string choice;
    getline(cin, choice);
    if (choice == "Y" || choice == "y") {
        cout << "Enter your listing consuming points: ";
        getline(cin, minRating);
        currentMember->myHouse->minOccupierRating = stod(minRating);
    }
    else{
        currentMember->myHouse->minOccupierRating = 0;
    }
    currentMember->myHouse->startDate = startDate;
    currentMember->myHouse->endDate = endDate;
    currentMember->myHouse->consumingPoints = stod(consumingPoint);
    currentMember->myHouse->isListed = true;
    House::listingHouse.push_back(*currentMember->myHouse);
    Data::updateHouseData(*Member::currentMember->myHouse);
    Data::updateUserData(*Member::currentMember);
    Data::loadFullData();
    cout << "List House successfully!" << endl;
}

void Member::removeRequest(Member* member, House* house){
    // Remove House from member pending request
    int index = 0;
    if (member->pendingRequests.empty() || Data::houseList.empty()) {
        return;
    }
    for (auto &i : member->pendingRequests){
        if (i->houseID == house->houseID){
            member->pendingRequests.erase(member->pendingRequests.begin() + index);
            Data::updateHouseData(*Member::currentMember->myHouse);
            Data::updateUserData(*Member::currentMember);
            Data::loadFullData();
            break;
        }
        else{
            index++;
        }
    }
    // remove member from house request list
    for (auto &z : Data::houseList) {
        for (int k = 0; k < z.requestList.size(); k++) {
            if (z.requestList.at(k)->username == member->username) {
                z.requestList.erase(z.requestList.begin() + k);
                Data::updateHouseData(*Member::currentMember->myHouse);
                Data::updateUserData(*Member::currentMember);
                Data::loadFullData();
                break;
            }
        }
    }
}

void Member::unListHouse(int i) {
    int index = 0;
    if (House::listingHouse.empty()) {
        cout << "No house is listed at the moment." << endl;
        return;
    }
    if (currentMember->myHouse == nullptr) {
        cout << "You have no listed house!" << endl;
        return;
    }
    for (auto &j : House::listingHouse){
        if (currentMember->myHouse->houseID == j.houseID){
            House::listingHouse.erase(House::listingHouse.begin() + index);
            break;
        }
        else{
            index++;
        }
    }
    for (auto &j : currentMember->myHouse->requestList){
        removeRequest(j, currentMember->myHouse);
    }
    if (i == 0){
        currentMember->myHouse->isListed = false;
        cout << "Remove house listing successfully" << endl;
    }

}

void Member::viewPendingRequest() {
    if (currentMember->pendingRequests.empty()){
        cout << "No pending request" << endl;
        return;
    }
    cout << "House waiting for respond: " << endl;
    for (auto &i: currentMember->pendingRequests) {
        cout << i->houseID << endl;
    }
}

void Member::acceptRequest() {
    Data::loadHouseData();
    Data::loadUserData();
    currentMember->myHouse->showFullHouse();
    if (currentMember->myHouse == nullptr) {
        cout << "You have no house!" << endl;
        return;
    }
    if (currentMember->myHouse->requestList.empty()){
        cout << "Your house have no request" << endl;
        return;
    }
    cout << "Below are members, who are requesting your house: " << endl;
    for (auto &i : currentMember->myHouse->requestList){
        cout << "\t Username: " << i->username << " Point: " << i->avgScore() << endl;
    }
    cout << "Enter username of request you want to accept: ";
    string username_val;
    getline(cin,username_val);
    for (auto i : currentMember->myHouse->requestList){
        if (username_val == i->username){
            i->rentHouse = currentMember->myHouse;
            currentMember->myHouse->status = "Rented";
            currentMember->myHouse->isListed = false;
            currentMember->creditPoint += currentMember->myHouse->consumingPoints;
            i->creditPoint -= currentMember->myHouse->consumingPoints;
            currentMember->myHouse->occupiers.push_back(i);
            removeRequest(i, currentMember->myHouse);
            cout << i->id << ": " << i->getFullName() << " have successfully rented your house" << endl;
            Data::updateHouseData(*currentMember->myHouse);
            Data::updateUserData(*i);
            Data::updateUserData(*currentMember);
            Data::loadFullData();
            return;
        }
    }
    cout << "Username not found" << endl;
}

void Member::rateOccupier() {
    if (currentMember->myHouse == nullptr) {
        cout << "You have no house!" << endl;
        return;
    }
    for (auto &i : currentMember->myHouse->occupiers){
        cout << i->username << endl;
    }
    cout << "Choose the person you want to rate: ";
    string username_val;
    getline(cin,username_val);
    for (auto &i : currentMember->myHouse->occupiers){
        if (username_val == i->username){
            cout << "Enter their score: ";
            string score_str;
            getline(cin,score_str);
            i->occupierRatings.push_back(stod(score_str));
            cout << "Do you want to leave a comment? (Y): ";
            string choice;
            getline(cin, choice);
            if (choice == "Y" || choice == "y") {
                cout << "Type here: ";
                string comment;
                getline(std::cin,comment);
                i->ownerComments.push_back(Member::currentMember->username + ": "+ comment);
            }
            Data::updateHouseData(*i->myHouse);
            Data::updateUserData(*i);
            Data::loadFullData();
            return;
        }
    }
    cout << "Username not found" << endl;
}
void Member::searchHouse() {
    cout << "Enter location: ";
    string location;
    getline(cin,location);
    // check if location is valid
    for (auto &i : locations) {
        if (strcasecmp(i.c_str(),location.c_str()) == 0) {
            // list of house
            if (House::listingHouse.empty()) {
                cout << "No house available in " << i  << "!" << endl;
            }
            for (auto &j : House::listingHouse) {
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
    Data::loadFullData();
    if (House::listingHouse.empty()) {
        cout << "There is currently no available house!" << endl;
        return;
    }
    for (auto &i : House::listingHouse) {
        cout << std::setw(10) << i.houseID << " " << i.address << " " << i.location << endl;
        cout << std::setw(15) << "Min occupier rating: " <<i.minOccupierRating << endl;
    }
    cout << "Enter house id: ";
    string house_id;
    getline(cin,house_id);
    if (currentMember->myHouse != nullptr && house_id == currentMember->myHouse->houseID) {
        cout << "You cannot request your own house!" << endl;
    }
    else {
        // check if house_id is valid
        for (House &h : Data::houseList) {
            for (House &j : House::listingHouse) {
                if (j.houseID == h.houseID) {
                    if (strcasecmp(j.houseID.c_str(),house_id.c_str()) == 0) {
                        j.requestList = h.requestList;
                        if (currentMember->avgScore() >= j.minOccupierRating) {
                            // assign this house
                            currentMember->pendingRequests.push_back(&j);
                            j.requestList.push_back(currentMember);
                            Data::updateHouseData(j);
//                    for (Member &k : Data::userList) {
//                        if(k.myHouse->houseID == j.houseID) {
//                            Data::updateUserData(k);
//                        }
//                    }
                            Data::updateUserData(*Member::currentMember);
                            Data::loadFullData();
                            cout << "Request successfully!" << endl;
                            return;
                        }
                        cout << "Not enough points!" << endl;
                        return;
                    }
                }
            }
        }

        cout << "Invalid house id!" << endl;
    }
}
void Member::displayListedHouse(){
    if (House::listingHouse.empty()){
        cout << "No house on listing" << endl;
        return;
    }
    for (auto& i : House::listingHouse){
        cout << endl;
        cout << "Name: " << i.houseID << endl;
        cout << "Address: " << i.address << endl;
        cout << "Location: " << i.location << endl;
        cout << "Consuming points: " << i.consumingPoints << endl;
        cout << "Occupier rating requirement: " << i.minOccupierRating << endl;
        cout << " '" << i.description << "'" << endl;
    }
}

void Member::viewRentStatus(){
    if (Member::currentMember->rentHouse == nullptr){
        cout << "You are not renting any house at the moment or they are still pending!" << endl;
        return;
    }
    else{
        cout << "Current rented house information" << endl;
        Member::currentMember->rentHouse->showFullHouse();
    }
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
    cout << "Do you want to leave a comment (Y) ?";
    string choice;
    getline(cin, choice);
    if (choice == "Y" || choice == "y") {
        cout << "Type here: ";
        string comment;
        getline(std::cin,comment);
        currentMember->rentHouse->occupierComment.push_back(comment);
        return;
    }
    cout << "Thank you for using!" << endl;
}