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
    inline static string admin {"admin"};

    // admin password
    inline static string password{"admin"};
public:
    inline static bool isLoggedIn {false};

    // check if username is available
    static bool login();
    static void logout();
    static void showMember();

    static void showHouses();
};


#endif //ADMIN_H
