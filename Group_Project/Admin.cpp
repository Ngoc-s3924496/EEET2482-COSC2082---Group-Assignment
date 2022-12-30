//
// Created by huuqu on 12/26/2022.
//

#include "Admin.h"
#include "Data.h"
#include "House.h"

    // check if username is available
    bool Admin::login() {
        string username_val;
        string password_val;
        cout << "Enter admin username: ";
        getline(cin,username_val);
        cout << "Enter admin password: ";
        getline(cin,password_val);
        if (username_val == "admin" && password_val == "admin") {
            Admin::isLoggedIn = true;
            return true;
        }
        return false;
    }
    void Admin::logout() {
        Admin::isLoggedIn = false;
    }
    void Admin::showMember() {
        if(Data::userList.empty()) {
            cout << "No data found!" << endl;
            return;
        }
        for (auto &i: Data::userList) {
            i.showInfo();
        }
    }

    void Admin::showHouses() {
        if(Data::houseList.empty()) {
            cout << "No data found!" << endl;
            return;
        }
        for (auto &i: Data::houseList) {
            i.showFullHouse();
        }
    }