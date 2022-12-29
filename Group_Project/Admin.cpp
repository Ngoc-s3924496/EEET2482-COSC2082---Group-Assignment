//
// Created by huuqu on 12/26/2022.
//

#include "Admin.h"
#include "Data.h"
#include "House.h"
    // get password
    std::string Admin::getPassword() {
        return this->password;
    }

    // check if username is available
    bool Admin::check_admin(string &username, string &password) {
        if (username == "admin" && password == "admin") {
            return true;
        }
        return false;
    }

    void Admin::showMember() {
        if(Data::userList.empty()) {
            cout << "No data found!" << endl;
            return;
        }
        // find member
        for (auto &i: Data::userList) {
            i.showInfo();
        }
    }

    void Admin::showHouses() {
        if(Data::houseList.empty()) {
            cout << "No data found!" << endl;
            return;
        }
        // find member
        for (auto &i: Data::houseList) {
//            // if found
//            if (member_name == i.getFullName()) {
//                cout << "Member found!" << std::endl;
//                i.showInfo();
//                return;
//            }

            i.showFullHouse();
        }
    }