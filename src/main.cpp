#include<bits/stdc++.h>
#include "Member.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stoi;

void pageStart();

void pageGuest();

void pageMember();

void pageAdmin();

void pageEnd();

void goBackGuest();

void goBackMember();

void goBackAdmin();

void lineBreak();

bool checkExist(vector<string> stringlist, string element);

// location
string locations[3] = {"HANOI", "HUE", "SAIGON"};


class House {
protected:
    string houseID;
    string address;
    string location;
    string description;
    bool occupationStatus;
    double houseRatingScore;
    std::vector<Member> occupiers;
    std::map<string, string> occupiersComments;
    std::vector<House> listingHouse;
    std::vector<Member> requestsList;
public:
    House() = default;
    House(const string &houseId, const string &address, const string& location, const string &description,
          bool occupationStatus, double houseRatingScore, const vector<Member> &occupiers,
          const std::map<string, string> &occupiersComments, const vector<House> &listingHouse,
          const vector<Member> &requestsList) : houseID(houseId), address(address),
                                                description(description), occupationStatus(occupationStatus),
                                                houseRatingScore(houseRatingScore), occupiers(occupiers),
                                                occupiersComments(occupiersComments), listingHouse(listingHouse),
                                                requestsList(requestsList) {
        for (string loc : locations) {
            if (loc == location) {
                this->location = location;
            } else {
                std::cerr << "Invalid house location" << endl;
            }
        }
    }

    void showFullDemo() {
        cout << "House Information - Full Version" << endl;
        cout << "House ID: " << houseID << endl;
        cout << "Address: " << address << endl;
        cout << "Location: " << location << endl;
        cout << "Description: " << description << endl;
        if (occupationStatus) {
            cout << "House Status: occupied by " << occupiers.back().getFullName() << " - " << occupiers.back().id
                 << endl;
        } else {
            cout << "House Status: empty" << endl;
        }
        cout << "House Rating Score: " << houseRatingScore << endl;
    }

    void showDemoInfo() {
        cout << "House Information - Guest Version" << endl;
        cout << "House ID: " << houseID << endl;
        cout << "Location: " << location << endl;
        cout << "Approximate House Rating Score: " << (int) houseRatingScore - 2 << " ~ " << (int) houseRatingScore + 2
             << endl;
    }

};

class Admin : public User {
private:
    // predefined admins
    std::vector<string> admins{"Quoc", "Quan", "Thach", "Ngoc"};

    // members vector array
    static std::vector<Member> members;

    // admin password
    string password{"admin"};
public:

    // get password
    std::string getPassword() {
        return this->password;
    }

    // record new member in admin
    static void add_members(Member &member) {
        members.push_back(member);
    }

    // check if username is available
    bool check_admin(string &username) {
        for (auto &i: admins) {
            if (i == username) {
                return true;
            }
        }
        return false;
    }

    static void showMember() {
        // enter member name
        std::cout << "Enter a member name: ";
        std::string member_name{};
        std::getline(std::cin, member_name);

        // find member
        for (auto &i: Admin::members) {
            // if found
            if (member_name == i.fullName) {
                cout << "Member found!" << std::endl;
                i.showInfo();
                return;
            }
        }
        cout << "Invalid member name!" << std::endl;
    }

    void showHouses() {

    }
};


int main() {
    // Call constructor for classes
    cout << "EEET2482/COSC2082 ASSIGNMENT" << endl;
    cout << "VACATION HOUSE EXCHANGE APPLICATION" << endl;
    cout << "Instructors: Mr. Linh Tran & Phong Ngo" << endl;
    cout << "Group: Team 925" << endl;
    cout << "Duong Vu Thanh Ngoc: s3924496" << endl;
    cout << "Ngo Tran Bao Thach: s3927021" << endl;
    cout << "Nguyen Minh Quan: s3927181" << endl;
    cout << "Doan Huu Quoc: s3927776" << endl;
    lineBreak();
    pageStart();
    return 0;
}

void pageStart() {
    string input;
    cout << "Hello fellow travelers!" << endl;
    cout << "Welcome to" << endl;
    cout << "TEAM 925 VACATION HOUSE EXCHANGE APPLICATION" << endl;
    lineBreak();
    cout << "User the app as:" << endl;
    cout << "[1] Guest" << endl;
    cout << "[2] Member" << endl;
    cout << "[3] Admin" << endl;
    cout << "[4] End program" << endl;
    cout << "Enter your action: ";
    cin >> input;
    vector<string> inputList = {"1", "2", "3", "4"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        cin >> input;
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            pageGuest();
            break;
        case 2:
            pageMember();
            break;
        case 3:
            pageAdmin();
            break;
        case 4:
            pageEnd();
            break;
    }
}

void pageGuest() {
    cout << "Welcome guest!" << endl;
    cout << "[1] View available houses" << endl;
    cout << "[2] Register as a member" << endl;
    cout << "[3] Go back" << endl;
    cout << "[4] End program" << endl;
    string input;
    cout << "Enter your action: ";
    cin >> input;
    vector<string> inputList = {"1", "2", "3", "4"};
    while (checkExist(inputList, input) == false) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        cin >> input;
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            // Guest view house function
            goBackGuest();
            break;
        case 2:
            // Guest registration function
            goBackGuest();
            break;
        case 3:
            pageStart();
            break;
        case 4:
            pageEnd();
            break;
    }
}

void pageMember() {
    string username;
    string password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Check member username and password
    // Change Test value to Admin predefined attribute
    if (username.compare("Test") != 0 && password.compare("Test") != 0) {
        string input;
        cout << "Wrong username or password" << endl;
        cout << "[1] Go back" << endl;
        cout << "[2] Try again" << endl;
        cout << "[3] End program" << endl;
        cout << "Enter your action: ";
        cin >> input;
        vector<string> inputList = {"1", "2", "3"};
        while (checkExist(inputList, input) == false) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            cin >> input;
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                pageStart();
                break;
            case 2:
                pageMember();
                break;
            case 3:
                pageEnd();
                break;
        }
    } else {
        cout << "Hello 'Member name'!" << endl;
        cout << "[1] Show account info" << endl;
        cout << "[2] List house for occupation" << endl;
        cout << "[3] Unlist House" << endl;
        cout << "[4] View house request" << endl;
        cout << "[5] Accept request" << endl;
        cout << "[6] Rate occupier" << endl;
        cout << "[7] Search house on listing" << endl;
        cout << "[8] Make request" << endl;
        cout << "[9] View status of house request" << endl;
        cout << "[10] Rate house" << endl;
        cout << "[11] Go back" << endl;
        cout << "[12] End program" << endl;
        string input;
        cout << "Enter your action: ";
        cin >> input;
        vector<string> inputList = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        while (checkExist(inputList, input) == false) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            cin >> input;
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                // showinfo() function
                goBackMember();
                break;
            case 2:
                // listhouse() function
                goBackMember();
                break;
            case 3:
                // unlisthouse() function
                goBackMember();
                break;
            case 4:
                // viewrequest() function
                goBackMember();
                break;
            case 5:
                // acceptrequesthouse() function
                goBackMember();
                break;
            case 6:
                // ratingoccupier() function
                goBackMember();
                break;
            case 7:
                // searchhouse() function
                goBackMember();
                break;
            case 8:
                // makerequest() function
                goBackMember();
                break;
            case 9:
                // viewstatusrequest() function
                goBackMember();
                break;
            case 10:
                // ratinghouse() function
                goBackMember();
                break;
            case 11:
                pageStart();
                break;
            case 12:
                pageEnd();
                break;
        }
    }
}

void pageAdmin() {
    string username;
    string password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    Admin admin = Admin();
    // Change Test value to Admin predefined attribute
    if (password != admin.getPassword() || !admin.check_admin(username)) {
        string input;
        cout << "Wrong username or password" << endl;
        cout << "[1] Go back" << endl;
        cout << "[2] Try again" << endl;
        cout << "[3] End program" << endl;
        cout << "Enter your action: ";
        cin >> input;
        vector<string> inputList = {"1", "2", "3"};
        while (!checkExist(inputList, input)) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            cin >> input;
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                pageStart();
                break;
            case 2:
                pageAdmin();
                break;
            case 3:
                pageEnd();
                break;
        }
    } else {
        cout << "Welcome admin!" << endl;
        string input;
        cout << "[1] Show houses information" << endl;
        cout << "[2] Show members information" << endl;
        cout << "[3] Go back" << endl;
        cout << "[4] End program" << endl;
        cout << "Enter your action: ";
        cin >> input;
        vector<string> inputList = {"1", "2", "3", "4"};
        while (!checkExist(inputList, input)) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            cin >> input;
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                // Admin view house function
                admin.showHouses();
                goBackAdmin();
                break;
            case 2:
                // Admin view member function
                admin.showMember();
                goBackAdmin();
                break;
            case 3:
                pageStart();
                break;
            case 4:
                pageEnd();
                break;
        }
    }
}

void pageEnd() {
    cout << "Thank you for using this program" << endl;
    cout << "See you next time!" << endl;
}

void goBackGuest() {
    string input;
    cout << "[1] Go back" << endl;
    cout << "[2] End program" << endl;
    cout << "Enter your action: ";
    cin >> input;
    vector<string> inputList = {"1", "2"};
    while (checkExist(inputList, input) == false) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        cin >> input;
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            pageGuest();
            break;
        case 2:
            pageEnd();
            break;
    }
}

void goBackMember() {
    string input;
    cout << "[1] Go back" << endl;
    cout << "[2] End program" << endl;
    cout << "Enter your action: ";
    cin >> input;
    vector<string> inputList = {"1", "2"};
    while (checkExist(inputList, input) == false) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        cin >> input;
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            pageMember();
            break;
        case 2:
            pageEnd();
            break;
    }
}

void goBackAdmin() {
    string input;
    cout << "[1] Go back" << endl;
    cout << "[2] End program" << endl;
    cout << "Enter your action: ";
    cin >> input;
    vector<string> inputList = {"1", "2"};
    while (checkExist(inputList, input) == false) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        cin >> input;
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            pageAdmin();
            break;
        case 2:
            pageEnd();
            break;
    }
}

void lineBreak() {
    cout << endl << endl;
}

bool checkExist(vector<string> stringlist, string element) {
    for (string elementList: stringlist) {
        if (elementList.compare(element) == 0) {
            return true;
        }
    }
    return false;
}