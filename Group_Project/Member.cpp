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
               House *myHouse, vector<double> occupierRatings, int creditPoint, vector<House*> pendingRequests,
               House *rentHouse, vector<string> ownerComments) {
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
    cout << endl;
}
void Member::showMiniInfo() {
    cout << "\tFull name: " << this->fullName << endl;
    cout << "\tPhone number: " << this->phoneNumber << endl;
    cout << "\tCredit point: " << this->creditPoint << endl;
    cout << "\tOccupier rating: " << std::setprecision(2) << std::fixed << this->avgScore() << endl;
}
void Member::listHouse() {
    if (currentMember->myHouse == nullptr){
        cout << "No house to list" << endl;
        return;
    }
    string startDate, endDate, consumingPoint, minRating;
    cout << "Enter your listing start date: ";
    getline(cin, startDate);
    cout << "Enter your listing end date: ";
    getline(cin, endDate);
    cout << "Enter your listing consuming points: ";
    getline(cin, consumingPoint);
    cout << "Do you want to have a occupier rating requirement? (Y/N)" << endl;
    string choice;
    getline(cin, choice);
    if (choice == "Y") {
        cout << "Enter your listing consuming points: " << endl;
        getline(cin, minRating);
        currentMember->myHouse->minOccupierRating = stod(minRating);
    }
    else{
        currentMember->myHouse->minOccupierRating = 0;
    }
    currentMember->myHouse->startDate = startDate;
    currentMember->myHouse->endDate = endDate;
    currentMember->myHouse->consumingPoints = stod(consumingPoint);
    unListHouse(1);
    Member::listingHouse.push_back(*currentMember->myHouse);
}

void Member::removeRequest(Member* member, House* house){
    // Remove member from house requestlist
    int index = 0;
    for (auto &i : house->requestList){
        if (i->id == member->id){
            house->requestList.erase(house->requestList.begin() + index);
            break;
        }
        else{
            index++;
        }
    }
    // Remove House from member pending request
    index = 0;
    for (auto &i : member->pendingRequests){
        if (i->houseID == house->houseID){
            member->pendingRequests.erase(member->pendingRequests.begin() + index);
            break;
        }
        else{
            index++;
        }
    }
}

void Member::unListHouse(int i) {
    int index = 0;
    for (auto &j : Member::listingHouse){
        if (currentMember->myHouse->houseID == j.houseID){
            Member::listingHouse.erase(Member::listingHouse.begin() + index);
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
        cout << "Remove house listing successfully";
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
    if (currentMember->myHouse->requestList.empty()){
        cout << "Your house have no request" << endl;
        return;
    }
    for (auto &i : currentMember->myHouse->requestList){
        cout << "Username: " << i->username << " Point: " << i->avgScore() << endl;
    }
    cout << "Enter username of request you want to accept: ";
    string username_val;
    getline(cin,username_val);
    for (auto i : currentMember->myHouse->requestList){
        if (username_val == i->username){
            i->rentHouse = currentMember->myHouse;
            currentMember->myHouse->status = "Rented";
            removeRequest(i, currentMember->myHouse);
            currentMember->creditPoint += currentMember->myHouse->consumingPoints;
            i->creditPoint -= currentMember->myHouse->consumingPoints;
            currentMember->myHouse->occupiers.push_back(i);
            cout << i->getFullName() << " have successfully rented your house" << endl;
            return;
        }
    }
    cout << "Username not found" << endl;
}

void Member::rateOccupier() {
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
            cout << "Do you want to leave a comment? (Y/N): ";
            string choice;
            getline(cin, choice);
            if (choice == "Y") {
                cout << "Type here: ";
                string comment;
                getline(std::cin,comment);
                i->ownerComments.push_back(Member::currentMember->username + ": "+ comment);
                return;
            }
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
void Member::displayListedHouse(){
    if (Member::listingHouse.empty()){
        cout << "No house on listing" << endl;
    }
    for (auto& i : Member::listingHouse){
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
        cout << "Current rented house information";
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
    cout << "Do you want to leave a comment (Y/N) ?";
    string choice;
    getline(cin, choice);
    if (choice == "Y") {
        cout << "Type here: ";
        string comment;
        getline(std::cin,comment);
        currentMember->rentHouse->occupierComment.push_back(comment);
        return;
    }
    cout << "Thank you for using!" << endl;
}