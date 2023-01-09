#include "Guest.h"
#include "Data.h"

bool Guest::registerAccount() {
    Member::register_account();
    Member::isLoggedIn = false;
    return true;
}
void Guest::showHouse() {
    cout << "House Information - Guest Version" << endl;
    for (auto &i : Data::houseList) {
        i.showDemoHouse();
    }
}