//
// Created by huuqu on 12/28/2022.
//

#include "Guest.h"
#include "Data.h"
#include "House.h"
bool Guest::register_account() {
    Member::register_account();
    Member::isLoggedIn = false;
    return true;
}
void Guest::showHouse() {
    for (auto &i : Data::houseList) {
        i.showDemoHouse();
    }
}