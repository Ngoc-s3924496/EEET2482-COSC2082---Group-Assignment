//
// Created by huuqu on 12/26/2022.
//

#ifndef USER_H
#define USER_H
#include <iostream>
using std::string;

class User {
protected:
    string id{};
    string username{};
    string password{};
public:
    User();
    User(string id, string username, string password);
};

#endif //EEET2482_COSC2082___GROUP_ASSIGNMENT_USER_H
