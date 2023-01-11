#include "House.h"
#include "Member.h"
#include <cstring>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;


//Constructor
House::House() = default;

House::House(string houseId, string startDate, string endDate, string address,
             string location, string description, double consumingPoints, double minOccupierRating,
             vector<double> houseRatings, bool isListed, bool status, vector<string> occupierComment) : houseID(
        houseId),
                                                                                                        startDate(
                                                                                                                startDate),
                                                                                                        endDate(endDate),
                                                                                                        address(address),
                                                                                                        description(
                                                                                                                description),
                                                                                                        consumingPoints(
                                                                                                                consumingPoints),
                                                                                                        minOccupierRating(
                                                                                                                minOccupierRating),
                                                                                                        houseRatings(
                                                                                                                houseRatings),
                                                                                                        isListed(
                                                                                                                isListed),
                                                                                                        status(status),
                                                                                                        occupierComment(
                                                                                                                occupierComment) {
    this->occupiers;
    this->requestList;
    // Check if location is valid or not
    for (string &loc: locations) {
        if (strcasecmp(location.c_str(), loc.c_str()) == 0) {
            this->location = location;
        }
    }
    if (this->location.empty()) {
        cerr << "Invalid location" << endl;
    }

    if (this->isListed) {
        if (listingHouse.empty()) {
            listingHouse.push_back(*this);
        } else {
            for (int i =0 ; i < listingHouse.size(); i++) {
                if (this->houseID == listingHouse.at(i).houseID) {
                    break;
                }
                if (i == listingHouse.size() - 1) {
                    listingHouse.push_back(*this);
                }
            }
        }
    }
    houseCounter++;
};

// Constructor full
House::House(string houseId, string startDate, string endDate, string address,
             string location, string description, double consumingPoints, double minOccupierRating,
             vector<double> houseRatings, bool isListed, bool status,
             vector<Member *> occupiers, vector<Member *> requestList,
             vector<string> occupierComment) : houseID(houseId), startDate(startDate),
                                               endDate(endDate),
                                               address(address), description(description),
                                               consumingPoints(consumingPoints), minOccupierRating(minOccupierRating),
                                               houseRatings(houseRatings),
                                               isListed(isListed), status(status), occupiers(occupiers),
                                               requestList(requestList),
                                               occupierComment(occupierComment) {
    // Check if location is valid or not
    for (const string &loc: locations) {
        if (strcasecmp(loc.c_str(), location.c_str()) == 0) {
            this->location = location;
        }
    }
    if (isListed) {
        listingHouse.push_back(*this);
    }
    if (this->location.empty()) {
        cerr << "Invalid location" << endl;
    }
    houseCounter++;
};

// Show simple version of the house for Guest viewing
void House::showDemoHouse() {
    cout << "--------------------------------------------" << endl;
    cout << "| HOUSE INFORMATION - GUEST VERSION |" << endl;
    cout << endl;
    cout << "House ID: " << this->houseID << endl;
    cout << "Address: " << this->address << endl;
    cout << "Location: " << this->location << endl;
    cout << "Description: " << this->description << endl;
    cout << endl;
    cout << "Consuming Points: " << this->consumingPoints << endl;
    cout << "Minimum Occupier Rating: " << this->minOccupierRating << endl;
    cout << "Approximate House Rating Score: " << this->avgScore() - 1.5 << " ~ " << this->avgScore() + 1.5 << endl;
    cout << "--------------------------------------------" << endl;
}

// Show the full version of the house for Admin / Member viewing
void House::showFullHouse() {
    if (this != nullptr) {
        cout << "--------------------------------------------" << endl;
        cout << "| HOUSE INFORMATION - FULL VERSION |" << endl;
        cout << endl;
        cout << "House ID: " << this->houseID << endl;
        cout << "Address: " << this->address << endl;
        cout << "Location: " << this->location << endl;
        cout << "Description: " << this->description << endl;
        cout << endl;
        cout << "Consuming Points: " << this->consumingPoints << endl;
        cout << "Minimum Occupier Rating: " << this->minOccupierRating << endl;
        cout << "Open For Rent: ";
        if (this->isListed) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        cout << endl;
        if (!isListed) {
            cout << "This house has been occupied at this time" << endl;
            if (this->occupiers.empty()) {
                cout << "House Status: Nobody has rented this house" << endl;
            } else {
                cout << "House Status: Occupied by " << this->occupiers.at(occupiers.size() - 1)->getFullName() << " - "
                     << this->occupiers.back()->id
                     << endl;
            }
        } else {
            cout << "This house is free at the moment" << endl;
            if (occupiers.empty()) {
                cout << "There is no previous occupiers, let's be the first now !!!" << endl;
            } else {
                cout << "Below are previous occupiers" << endl;
                for (int i = 0; i < this->occupiers.size(); ++i) {
                    occupiers.at(i)->showMiniInfo();
                }
            }
        }
        cout << endl;
        cout << "House Rating Score: " << this->avgScore() << endl;
        cout << "Request list: " << endl;
        if (this->requestList.empty()) {
            cout << "Nobody requested this house" << endl;
        } else {
            for (Member *member: this->requestList) {
                member->showMiniInfo();
                cout << endl;
            }
        }
        cout << "Comment List: " << endl;
        if (this->occupierComment.empty()) {
            cout << "Nobody has commented this house" << endl;
        } else {
            for (int i = 0; i < occupierComment.size(); ++i) {
                cout << occupierComment.at(i) << endl;
            }
        }
    } else {
        cout << "There is no house to be shown" << endl;
    }
    cout << "--------------------------------------------" << endl;
    cout << endl;
}


// Calculate house-rating score ( avg rating ) for this house.
double House::avgScore() {
    double avg;
    for (double score: houseRatings) {
        avg += score;
    }
    avg = avg / houseRatings.size();
    return avg;
}


