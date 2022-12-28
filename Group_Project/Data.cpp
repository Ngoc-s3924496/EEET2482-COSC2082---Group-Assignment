#include "Data.h"
using std::cin;
using std::cout;
using std::vector;
using std::map;
using std::ifstream;
using std::fstream;
using std::endl;
using std::cerr;
using std::string;
using std::stoi;
using std::stod;
// Constructor
Data::Data() = default;

bool Data::is_empty(std::ifstream &file){
    return file.peek() == std::ifstream::traits_type::eof();
}


bool Data::saveUserData(Member member, string path) {
    // Check the file is empty
    ifstream file(path);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return -1;
    }
    bool empty = is_empty(file);
    file.close();

    // Write into the file
    fstream saveFile;
    // Check if the file is empty then write into the file, otherwise append into the file
    if (empty) {
        // Open the file to write
        saveFile.open(path, std::ios::out);
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Save the title
        saveFile << "ID,Full Name,Username,Password,Phone Number,Owned House,Occupier Ratings,Credit Points,Pending Requests,Rent House,Comment List" << endl;
        // Move the pointer to the end of the file for appending into the file
        saveFile.seekg(std::ios::end);
        // Save the id, full name, username, password, phone number
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << ",";
        // Save the owned house ID;
        if (member.myHouse != nullptr) {
            saveFile << member.myHouse->houseID << ",";
        } else {
            saveFile << "none" << ",";
        }
        // Save the occupier ratings
        if (member.occupierRatings.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (i + 1 == member.occupierRatings.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the credit points
        saveFile << member.creditPoint << ",";
        // Save the pending request
        if (member.pendingRequests.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (i + 1 == member.pendingRequests.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the rent house
        if (member.rentHouse == nullptr) {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse->houseID << ",";
        }
        // Save the owner comments
        if (member.ownerComments.size() == 0) {
            saveFile << "none";
        } else {
            int count = 0;
            for (map<string, string>::iterator i = member.ownerComments.begin(); i != member.ownerComments.end(); i++) {
                saveFile << i->first << ": " << i->second;
                count++;
                if (count == member.ownerComments.size() - 1) {
                    break;
                }
                saveFile << ";";
            }
        }
        saveFile << endl;
    } else {
        // Open the file to append the data
        saveFile.open(path, std::ios::app);
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Move the pointer to the end of the file for appending into the file
        saveFile.seekg(std::ios::end);
        // Save the id, full name, username, password, phone number
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << ",";
        // Save the owned house ID;
        if (member.myHouse != nullptr) {
            saveFile << member.myHouse->houseID << ",";
        } else {
            saveFile << "none" << ",";
        }
        // Save the occupier ratings
        if (member.occupierRatings.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (i + 1 == member.occupierRatings.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the credit points
        saveFile << member.creditPoint << ",";
        // Save the pending request
        if (member.pendingRequests.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (i + 1 == member.pendingRequests.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the rent house
        if (member.rentHouse == nullptr) {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse->houseID << ",";
        }
        // Save the owner comments
        if (member.ownerComments.size() == 0) {
            saveFile << "none";
        } else {
            int count = 0;
            for (map<string, string>::iterator i = member.ownerComments.begin(); i != member.ownerComments.end(); i++) {
                saveFile << i->first << ": " << i->second;
                count++;
                if (count == member.ownerComments.size() - 1) {
                    break;
                }
                saveFile << ";";
            }
        }
        saveFile << endl;
    }
    // Close the file
    saveFile.close();
    return 1;
}

bool Data::saveHouseData(House house, string path) {
    // Check the file is empty
    ifstream file(path);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return -1;
    }
    bool empty = is_empty(file);
    file.close();

    // Write into the file
    fstream saveFile;
    // Check if the file is empty then write into the file, otherwise append into the file
    if (empty) {
        // Open the file
        saveFile.open(path, std::ios::out);
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Save the title
        saveFile << "ID,Start Date,End Date,Address,Location,Description,House Ratings,Status,Occupiers,Request List,Comment List" << endl;
        // Save the house id, start date, end date, address, location, description
        saveFile << house.houseID << "," << house.startDate << "," << house.endDate << "," << house.address << "," << house.location << "," << house.description << ",";
        // Save the house ratings
        if (house.houseRatings.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.houseRatings.size(); i++) {
                saveFile << house.houseRatings[i];
                if (i + 1 == house.houseRatings.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the status
        saveFile << ((house.status == true) ? "Rented" : "Not Rented") << ",";
        // Save the occupiers
        if (house.occupiers.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->id;
                if (i + 1 == house.occupiers.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save teh request list
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.requestList.size(); i++) {
                saveFile << house.requestList[i]->id;
                if (i + 1 == house.requestList.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the occupier comments
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (map<string, string>::iterator i = house.occupierComment.begin(); i != house.occupierComment.end(); i++) {
                saveFile << i->first << ": " << i->second;
                count++;
                if (count == house.occupierComment.size() - 1) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << endl;
        }
    } else {
        // Open the file
        saveFile.open(path, std::ios::app);
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Move the pointer to the end of the file for appending into the file
        saveFile.seekg(std::ios::end);
        // Save the house id, start date, end date, address, location, description
        saveFile << house.houseID << "," << house.startDate << "," << house.endDate << "," << house.address << "," << house.location << "," << house.description << ",";
        // Save the house ratings
        if (house.houseRatings.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.houseRatings.size(); i++) {
                saveFile << house.houseRatings[i];
                if (i + 1 == house.houseRatings.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the status
        saveFile << ((house.status == true) ? "Rented" : "Not Rented") << ",";
        // Save the occupiers
        if (house.occupiers.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->id;
                if (i + 1 == house.occupiers.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the request list
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            for (int i = 0; i < house.requestList.size(); i++) {
                saveFile << house.requestList[i]->id;
                if (i + 1 == house.requestList.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Save the occupier comments
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (map<string, string>::iterator i = house.occupierComment.begin(); i != house.occupierComment.end(); i++) {
                saveFile << i->first << ": " << i->second;
                count++;
                if (count == house.occupierComment.size() - 1) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << endl;
        }
    }
    // Close the file
    saveFile.close();
    return 1;
}

bool Data::LoadUserData(string memberPath) {
    fstream openFile;
    string line;
    // Open the member file
    openFile.open(memberPath, std::ios::in);
    if (!openFile) {
        cerr << "Cannot open file member!" << endl;
        return -1;
    }
    // Skip the title of the database
    getline(openFile, line);
    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        // Declare the variables
        string id, fullName, userName, password, phoneNumber, houseID, readString, creditPoints, keyValueString, key, value;
        bool notEndOfString = true;
        // Aggregation Relationship between House class and Member class
        House *myHouse = nullptr;
        House *rentHouse = nullptr;
        vector<double> occupierRatings {};
        // Aggregation Relationship between House class and Member class
        vector<House*> pendingRequests {};
        map<string, string> ownerComment {};
        
        // Load the member id, full name, username, password, phone number to the declared variables
        id = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        fullName = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        userName = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        password = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        phoneNumber = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Load the House object into the local variable
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        for (int i = 0; i < houseList.size(); i++) {
            if (houseID == houseList[i].houseID) {
                *myHouse = houseList[i];
                break;
            }
        }
        
        // Load the occupier ratings into the local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                occupierRatings.push_back(stod(readString.substr(0, readString.find("; "))));
                readString.erase(0, readString.find("; ") + 2);
            } else {
                occupierRatings.push_back(stod(readString));
                break;
            }
        }

        // Load the credit points into the local variable
        creditPoints = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (creditPoints == "none") {
            creditPoints = "0";
        }

        // Load the pending request into the local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                houseID = readString.substr(0, readString.find("; "));
                for (int i = 0; i < houseList.size(); i++) {
                    if (houseID == houseList[i].houseID) {
                        pendingRequests.push_back(&houseList[i]);
                        break;
                    }
                }
                readString.erase(0, readString.find("; ") + 2);
            } else {
                houseID = readString;
                for (int i = 0; i < houseList.size(); i++) {
                    if (houseID == houseList[i].houseID) {
                        pendingRequests.push_back(&houseList[i]);
                        break;
                    }
                }
                break;
            }
        }

        // Load the rent house into the local variable
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        for (int i = 0; i < houseList.size(); i++) {
            if (houseID == houseList[i].houseID) {
                *rentHouse = houseList[i];
                break;
            }
        }

        // Load the owner comments into the local map
        readString = line;
        // cout << readString << endl;
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                ownerComment[key] = value;
                readString.erase(0, readString.find("; ") + 2);
            } else {
                keyValueString = readString;
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                ownerComment[key] = value;
                break;
            }
        }
        // Append a loaded user into the local vector
        userList.push_back(Member(id, fullName, userName, password, phoneNumber, myHouse, occupierRatings, stoi(creditPoints), pendingRequests, rentHouse, ownerComment));
    }
    // Close the file
    openFile.close();
    return 1;
}

bool Data::LoadHouseData(string housePath) {
    fstream openFile;
    openFile.open(housePath, std::ios::in);
    string line;
    if (!openFile) {
        cerr << "Cannot open file House!" << endl;
        return -1;
    }
    // Skip the title of the database
    getline(openFile, line);
    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        string houseID, startDate, endDate, address, location, description, readString, memberID, key, value, keyValueString;
        vector<double> houseRatings;
        bool status = false;
        // Aggregation relationship between Member class and House class
        vector<Member*> occupiers; 
        vector<Member*> requestList;
        map<string, string> occupierComment;

        // Load the house id, start date, end date, address, location, description into local variables
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        startDate = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        endDate = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (line[0] == '\"') {
            address = line.substr(1, line.find("\",") - 1);
            line.erase(0, line.find("\",") + 2);
        } else {
            address = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
        }
        location = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (line[0] == '\"') {
            description = line.substr(1, line.find("\",") - 1);
            line.erase(0, line.find("\",") + 2);
        } else {
            description = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
        }

        // Load the house ratings into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                houseRatings.push_back(stod(readString.substr(0, readString.find("; "))));
                readString.erase(0, readString.find("; ") + 2);
            } else {
                houseRatings.push_back(stod(readString));
                break;
            }
        }

        // Load the status into a local variable
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (readString == "Rented") {
            status = true;
        } else {
            status = false;
        }

        // Load the occupiers into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                memberID = readString.substr(0, readString.find("; "));
                for (int i = 0; i < userList.size(); i++) {
                    if (memberID == userList[i].id) {
                        occupiers.push_back(&userList[i]);
                        break;
                    }
                }
                readString.erase(0, readString.find("; ") + 2);
            } else {
                memberID = readString;
                for (int i = 0; i < userList.size(); i++) {
                    if (memberID == userList[i].id) {
                        occupiers.push_back(&userList[i]);
                        break;
                    }
                }
                break;
            }
        }

        // Load the request list into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                memberID = readString.substr(0, readString.find("; "));
                for (int i = 0; i < userList.size(); i++) {
                    if (memberID == userList[i].id) {
                        requestList.push_back(&userList[i]);
                        break;
                    }
                }
                readString.erase(0, readString.find("; ") + 2);
            } else {
                memberID = readString;
                for (int i = 0; i < userList.size(); i++) {
                    if (memberID == userList[i].id) {
                        requestList.push_back(&userList[i]);
                        break;
                    }
                }
                break;
            }
        }

        // Load the occupier comments into a local map
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            if (readString.find("; ") < readString.length()) {
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                occupierComment[key] = value;
                readString.erase(0, readString.find("; ") + 2);
            } else {
                keyValueString = readString;
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                occupierComment[key] = value;
                break;
            }
        }
        // Append a new House object to the local vector
        houseList.push_back(House(houseID, startDate, endDate, address, location, description, houseRatings, status, occupiers, requestList, occupierComment));
    }
    // Close the file
    openFile.close();
    return 1;
}