//
// Created by huuqu on 12/26/2022.
//

#include "Admin.h"
    // get password
    std::string Admin::getPassword() {
        return this->password;
    }

    // record new member in admin
    void Admin::add_members(Member &member) {
        members.push_back(member);
    }

    // check if username is available
    bool Admin::check_admin(string &username, string &password) {
        if (username == "admin" && password == "admin") {
            return true;
        }
        return false;
    }

    void Admin::showMember() {
        // enter member name
        std::cout << "Enter a member name: ";
        std::string member_name{};
        std::getline(std::cin, member_name);

        // find member
        for (auto &i: Admin::members) {
            // if found
            if (member_name == i.getFullName()) {
                cout << "Member found!" << std::endl;
                i.showInfo();
                return;
            }
        }
        cout << "Invalid member name!" << std::endl;
    }

    void Admin::showHouses() {

    }