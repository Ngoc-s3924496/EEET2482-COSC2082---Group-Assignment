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

    // admin password
    string password{"admin"};
public:
    // get password
    std::string getPassword();

    // check if username is available
    bool check_admin(string &username, string &password);

    void showMember();

    void showHouses();
};


#endif //ADMIN_H
