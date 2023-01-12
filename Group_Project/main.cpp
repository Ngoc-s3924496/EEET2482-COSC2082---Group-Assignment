#include<iostream>
#include<vector>
#include "Member.h"
#include <ctime>
#include "Guest.h"
#include "Admin.h"
#include "Data.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stoi;
using std::stod;

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

int main() {
    Data::loadFullData();
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
    Data::loadFullData();
    string input;
    cout << "Hello fellow travelers!" << endl;
    cout << "Welcome to" << endl;
    cout << "TEAM 925 VACATION HOUSE EXCHANGE APPLICATION" << endl;
    // current epoch time
    time_t raw_time;
    // Current time
    time (&raw_time);
    string today = ctime(&raw_time);
    cout << "---\n Today is: " << today;
    cout << "---" << endl;
    cout << "User the app as:" << endl;
    cout << "[1] Guest" << endl;
    cout << "[2] Member" << endl;
    cout << "[3] Admin" << endl;
    cout << "[4] End program" << endl;
    cout << "Enter your action: ";
    getline(cin, input);
    vector<string> inputList = {"1", "2", "3", "4"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
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
    Data::loadFullData();
    cout << "--------------" << endl;
    cout << "WELCOME GUEST!" << endl;
    cout << "--------------" << endl;
    cout << "[1] View available houses" << endl;
    cout << "[2] Register as a member" << endl;
    cout << "[3] Login" << endl;
    cout << "[4] Go back" << endl;
    cout << "[5] End program" << endl;
    string input;
    cout << "Enter your action: ";
    getline(cin, input);
    vector<string> inputList = {"1", "2", "3", "4", "5"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
    }
    lineBreak();
    int intInput = stoi(input);
    switch (intInput) {
        case 1:
            // Guest view house function
            Guest::showHouse();
            goBackGuest();
            break;
        case 2:
            // Guest registration function
            Guest::registerAccount();
            goBackGuest();
            break;
        case 3:
            pageMember();
            break;
        case 4:
            pageStart();
            break;
        case 5:
            pageEnd();
            break;
    }
}

void pageMember() {
    Data::loadFullData();
    // Check member username and password
    // Change Test value to Admin predefined attribute
    if (!Member::isLoggedIn) {
        if (!Member::login()) {
            string input;
            cout << "[1] Go back" << endl;
            cout << "[2] Try again" << endl;
            cout << "[3] End program" << endl;
            cout << "Enter your action: ";
            getline(cin, input);
            vector<string> inputList = {"1", "2", "3"};
            while (!checkExist(inputList, input)) {
                cout << "Invalid input" << endl;
                cout << "Enter your action: ";
                getline(cin, input);
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
        }
        else {
            cout << "--------------" << endl;
            cout << "WELCOME "<< Member::currentMember->getFullName() << " !" << endl;
            cout << "--------------" << endl;
            // current epoch time
            time_t raw_time;
            // Current time
            time (&raw_time);
            string today = ctime(&raw_time);
            cout << "---\nToday is: " << today;
            cout << "Please note that your rent house will be automatically canceled if the end-date is over" << endl;
            cout << "---" << endl;
            cout << "[1] Show account info" << endl;
            cout << "[2] Add new House" << endl;
            cout << "[3] Show all listing house" << endl;
            cout << "[4] List house for occupation" << endl;
            cout << "[5] Un-list House" << endl;
            cout << "[6] View your request to other house" << endl;
            cout << "[7] View your house request" << endl;
            cout << "[8] Accept request" << endl;
            cout << "[9] Rate occupier" << endl;
            cout << "[10] Search house on listing" << endl;
            cout << "[11] Make request" << endl;
            cout << "[12] View rent status" << endl;
            cout << "[13] Rate house" << endl;
            cout << "[14] Logout" << endl;
            cout << "[15] Go back" << endl;
            cout << "[16] End program" << endl;
            string input;
            cout << "Enter your action: ";
            getline(cin, input);
            vector<string> inputList = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
            while (!checkExist(inputList, input)) {
                cout << "Invalid input" << endl;
                cout << "Enter your action: ";
                getline(cin, input);
            }
            lineBreak();
            int intInput = stoi(input);
            switch (intInput) {
                case 1:
                    // showinfo() function
                    Member::currentMember->showFullInfo();
                    goBackMember();
                    break;
                case 2:
                    Member::addHouse();
                    goBackMember();
                    break;
                case 3:
                    Member::displayListedHouse();
                    goBackMember();
                    break;
                case 4:
                    // listhouse() function
                    Member::listHouse();
                    goBackMember();
                    break;
                case 5:
                    // unlisthouse() function
                    Member::unListHouse(0);
                    goBackMember();
                    break;
                case 6:
                    // viewrequest() function
                    Member::viewPendingRequest();
                    goBackMember();
                    break;
                case 7:
                    Member::showRequests();
                    goBackMember();
                    break;
                case 8:
                    // acceptrequesthouse() function
                    Member::acceptRequest();
                    goBackMember();
                    break;
                case 9:
                    // ratingoccupier() function
                    Member::rateOccupier();
                    goBackMember();
                    break;
                case 10:
                    // searchhouse() function
                    Member::searchHouse();
                    goBackMember();
                    break;
                case 11:
                    // makerequest() function
                    Member::makeRequest();
                    goBackMember();
                    break;
                case 12:
                    // viewstatusrequest() function
                    //Member::viewStatusRequestedHouse();
                    Member::viewRentStatus();
                    goBackMember();
                    break;
                case 13:
                    // ratinghouse() function
                    Member::ratingHouse();
                    goBackMember();
                    break;
                case 14:
                    Member::logout();
                    pageStart();
                    break;
                case 15:
                    pageStart();
                    break;
                case 16:
                    pageEnd();
                    break;
            }
        }
    }
    else {
        cout << "[1] Show account info" << endl;
        cout << "[2] Add new House" << endl;
        cout << "[3] Show all listing house" << endl;
        cout << "[4] List house for occupation" << endl;
        cout << "[5] Un-list House" << endl;
        cout << "[6] View your request to other house" << endl;
        cout << "[7] View your house request" << endl;
        cout << "[8] Accept request" << endl;
        cout << "[9] Rate occupier" << endl;
        cout << "[10] Search house on listing" << endl;
        cout << "[11] Make request" << endl;
        cout << "[12] View rent status" << endl;
        cout << "[13] Rate house" << endl;
        cout << "[14] Logout" << endl;
        cout << "[15] Go back" << endl;
        cout << "[16] End program" << endl;
        string input;
        cout << "Enter your action: ";
        getline(cin, input);
        vector<string> inputList = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
        while (!checkExist(inputList, input)) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            getline(cin, input);
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                // showinfo() function
                Member::currentMember->showFullInfo();
                goBackMember();
                break;
            case 2:
                Member::addHouse();
                goBackMember();
                break;
            case 3:
                Member::displayListedHouse();
                goBackMember();
                break;
            case 4:
                // listhouse() function
                Member::listHouse();
                goBackMember();
                break;
            case 5:
                // unlisthouse() function
                Member::unListHouse(0);
                goBackMember();
                break;
            case 6:
                // viewrequest() function
                Member::viewPendingRequest();
                goBackMember();
                break;
            case 7:
                Member::showRequests();
                goBackMember();
                break;
            case 8:
                // acceptrequesthouse() function
                Member::acceptRequest();
                goBackMember();
                break;
            case 9:
                // ratingoccupier() function
                Member::rateOccupier();
                goBackMember();
                break;
            case 10:
                // searchhouse() function
                Member::searchHouse();
                goBackMember();
                break;
            case 11:
                // makerequest() function
                Member::makeRequest();
                goBackMember();
                break;
            case 12:
                // viewstatusrequest() function
                //Member::viewStatusRequestedHouse();
                Member::viewRentStatus();
                goBackMember();
                break;
            case 13:
                // ratinghouse() function
                Member::ratingHouse();
                goBackMember();
                break;
            case 14:
                Member::logout();
                pageStart();
                break;
            case 15:
                pageStart();
                break;
            case 16:
                pageEnd();
                break;
        }
    }
}

void pageAdmin() {
    Data::loadFullData();
    // Change Test value to Admin predefined attribute
    if (!Admin::isLoggedIn) {
        if (!Admin::login()) {
            string input;
            cout << "Wrong username or password" << endl;
            cout << "[1] Go back" << endl;
            cout << "[2] Try again" << endl;
            cout << "[3] End program" << endl;
            cout << "Enter your action: ";
            getline(cin, input);
            vector<string> inputList = {"1", "2", "3"};
            while (!checkExist(inputList, input)) {
                cout << "Invalid input" << endl;
                cout << "Enter your action: ";
                getline(cin, input);
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
        }
        else {
            cout << "--------------" << endl;
            cout << "WELCOME ADMIN!" << endl;
            cout << "--------------" << endl;
            string input;
            cout << "[1] Show houses information" << endl;
            cout << "[2] Show members information" << endl;
            cout << "[3] Logout" << endl;
            cout << "[4] Go back" << endl;
            cout << "[5] End program" << endl;
            cout << "Enter your action: ";
            getline(cin, input);
            vector<string> inputList = {"1", "2", "3", "4", "5"};
            while (!checkExist(inputList, input)) {
                cout << "Invalid input" << endl;
                cout << "Enter your action: ";
                getline(cin, input);
            }
            lineBreak();
            int intInput = stoi(input);
            switch (intInput) {
                case 1:
                    // Admin view house function
                    Admin::showHouses();
                    goBackAdmin();
                    break;
                case 2:
                    // Admin view member function
                    Admin::showMember();
                    goBackAdmin();
                    break;
                case 3:
                    Admin::logout();
                    pageStart();
                case 4:
                    pageStart();
                    break;
                case 5:
                    pageEnd();
                    break;
            }
        }

    } else {
        cout << "Welcome admin!" << endl;
        string input;
        cout << "[1] Show houses information" << endl;
        cout << "[2] Show members information" << endl;
        cout << "[3] Logout" << endl;
        cout << "[4] Go back" << endl;
        cout << "[5] End program" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
        vector<string> inputList = {"1", "2", "3", "4", "5"};
        while (!checkExist(inputList, input)) {
            cout << "Invalid input" << endl;
            cout << "Enter your action: ";
            getline(cin, input);
        }
        lineBreak();
        int intInput = stoi(input);
        switch (intInput) {
            case 1:
                // Admin view house function
                Admin::showHouses();
                goBackAdmin();
                break;
            case 2:
                // Admin view member function
                Admin::showMember();
                goBackAdmin();
                break;
            case 3:
                Admin::logout();
                pageStart();
            case 4:
                pageStart();
                break;
            case 5:
                pageEnd();
                break;
        }
    }
}

void pageEnd() {
    Data::loadFullData();
    //if not null
    if (Member::currentMember != nullptr) {
        Data::updateUserData(*Member::currentMember);
    }
    cout << "Thank you for using this program" << endl;
    cout << "See you next time!" << endl;
}

void goBackGuest() {
    string input;
    cout << "[1] Go back" << endl;
    cout << "[2] End program" << endl;
    cout << "Enter your action: ";
    getline(cin, input);
    vector<string> inputList = {"1", "2"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
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
    getline(cin, input);
    vector<string> inputList = {"1", "2"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
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
    getline(cin, input);
    vector<string> inputList = {"1", "2"};
    while (!checkExist(inputList, input)) {
        cout << "Invalid input" << endl;
        cout << "Enter your action: ";
        getline(cin, input);
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
    for (string &elementList: stringlist) {
        if (elementList == element) {
            return true;
        }
    }
    return false;
}
