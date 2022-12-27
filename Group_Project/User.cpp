#include "User.h"

User::User() = default;

User::User(string id, string username, string password) {
    this->id = id;
    this->username = username;
    this->password = password;
}