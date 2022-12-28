//
// Created by huuqu on 12/26/2022.
//

#ifndef ADMIN_H
#define ADMIN_H

#include "Member.h"
#include <iostream>
#include <vector>
using std::string;
class Admin {
private:
    // predefined admins
    string admin {"admin"};

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
