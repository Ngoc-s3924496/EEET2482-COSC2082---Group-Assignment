#include "House.h"
#include "Member.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;



 //Constructor
House::House() = default;

House::House(string houseId, string startDate, string endDate, string address,
             string location, string description) : houseID(houseId), startDate(startDate),
                                                                endDate(endDate),
                                                                address(address),
                                                                description(description) {
    this->houseRatings = {};
    this->status = false;
    this->occupiers = {};
    this->requestList = {};
    this->occupierComment = {};
    // Check if location is valid or not
    for (const string& loc: locations) {
        if (location == loc) {
            this->location = location;
        }
    }
    if (this->location == "") {
            cerr << "Invalid location" << endl;
    }
};

// Constructor full
House::House(string houseId, string startDate, string endDate, string address,
             string location, string description, vector<double> houseRatings, bool status,
             vector <Member*> occupiers, vector <Member*> requestList,
             std::map<string, string> occupierComment) : houseID(houseId), startDate(startDate),
                                                                endDate(endDate),
                                                                address(address),
                                                                description(description), houseRatings(houseRatings),
                                                                status(status), occupiers(occupiers),
                                                                requestList(requestList),
                                                                occupierComment(occupierComment) {
    // Check if location is valid or not
    for (const string& loc: locations) {
        if (location == loc) {
            this->location = location;
        }
    }
    if (this->location == "") {
            cerr << "Invalid location" << endl;
    }
};

// Show simple version of the house for Guest viewing
void House::showDemoHouse() {
    cout << "House Information - Guest Version" << endl;
    cout << "House ID: " << houseID << endl;
    cout << "Location: " << location << endl;
    cout << "Approximate House Rating Score: " << this->avgScore() - 1.5 << " ~ " << this->avgScore() + 1.5 << endl;
}

// Show the full version of the house for Admin / Member viewing
void House::showFullHouse() {
    cout << "House Information - Full Version" << endl;
    cout << "House ID: " << houseID << endl;
    cout << "Address: " << address << endl;
    cout << "Location: " << location << endl;
    cout << "Description: " << description << endl;
    if (status) {
        cout << "House Status: occupied by " << occupiers.back()->getFullName() << " - " << occupiers.back()->id
             << endl;
    } else {
        cout << "House Status: empty" << endl;
    }
    cout << "House Rating Score: " << this->avgScore() << endl;
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

