//
// Created by huuqu on 12/26/2022.
//

#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Member.h"
#include <iostream>
#include <vector>
using std::string;
class Admin : public User {
private:
    // predefined admins
    std::vector<string> admins{"Quoc", "Quan", "Thach", "Ngoc"};

    // members vector array
    inline static std::vector<Member> members {};

    // admin password
    string password{"admin"};
public:
    // get password
    std::string getPassword();

    // record new member in admin
    void add_members(Member &member);

    // check if username is available
    bool check_admin(string &username, string &password);

    void showMember();

    void showHouses();
};


#endif //ADMIN_H
