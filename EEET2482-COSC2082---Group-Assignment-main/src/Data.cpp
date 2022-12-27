#include "Data.h"

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
        // Save the id, full name, username, password, phone number, house ID
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << "," << member.myHouse->houseID << ",";
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
        // Save the pending requests
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
        if (member.rentHouse.houseID == "") {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse.houseID << ",";
        }
        // Save the owner comments
        if (member.ownerComments.size() == 0) {
            saveFile << "none" << endl;
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
        // Save the id, full name, username, password, phone number, house ID
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << "," << member.myHouse->houseID << ",";
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
        if (member.rentHouse.houseID == "") {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse.houseID << ",";
        }
        // Save the owner comments
        if (member.ownerComments.size() == 0) {
            saveFile << "none" << endl;
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
    return 0;
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
        saveFile.open(path, std::ios::out);
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
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
    }
    // Close the file
    saveFile.close();
    return 0;
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
    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        string id, fullName, userName, password, phoneNumber, houseID, readString, creditPoints, keyValueString, key, value;
        bool notEndOfString = true;
        // Aggregation Relationship between House class and Member class
        House *myHouse;
        vector<double> occupierRatings;
        // Aggregation Relationship between House class and Member class
        vector<House*> pendingRequests;
        map<string, string> ownerComment;
        
        // Load the member id, full name, username, password, phone number to the declared variables
        getline(openFile, id, ',');
        getline(openFile, fullName, ',');
        getline(openFile, userName, ',');
        getline(openFile, password, ',');
        getline(openFile, phoneNumber, ',');
        // Load the House object into the local variable
        getline(openFile, houseID, ',');
        for (int i = 0; i < houseList.size(); i++) {
            if (houseID == houseList[i].houseID) {
                *myHouse = houseList[i];
                break;
            }
        }
        
        // Load the occupier ratings into the local vector
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
                occupierRatings.push_back(stoi(readString.substr(0, readString.find("; "))));
                readString.erase(0, readString.find("; ") + 2);
            } else {
                occupierRatings.push_back(stoi(readString));
                notEndOfString = false;
            }
        }

        // Load the credit points into the local variable
        getline(openFile, creditPoints, ',');

        // Load the pending request into the local vector
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
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
                notEndOfString = false;
            }
        }

        // Load the owner comments into the local map
        getline(openFile, readString);
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                ownerComment[key] = value;
            } else {
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                ownerComment[key] = value;
                notEndOfString = false;
            }
        }
        // Append a loaded user into the local vector
        userList.push_back(Member(id, fullName, userName, password, phoneNumber, myHouse, occupierRatings, stoi(creditPoints), pendingRequests, ownerComment));
    }
    // Close the file
    openFile.close();
    return 0;
}

bool Data::LoadHouseData(string housePath) {
    fstream openFile;
    openFile.open(housePath, std::ios::in);
    string line;
    if (!openFile) {
        cerr << "Cannot open file House!" << endl;
        return -1;
    }

    while (getline(openFile, line)) {
        string houseID, startDate, endDate, address, location, description, readString, memberID, key, value, keyValueString;
        vector<double> houseRatings;
        bool status, notEndOfString;
        // Aggregation relationship between Member class and House class
        vector<Member*> occupiers; 
        vector<Member*> requestList;
        map<string, string> occupierComment;

        // Load the house id, start date, end date, address, location, description into local variables
        getline(openFile, houseID, ',');
        getline(openFile, startDate, ',');
        getline(openFile, endDate, ',');
        getline(openFile, address, ',');
        getline(openFile, location, ',');
        getline(openFile, description, ',');

        // Load the house ratings into a local vector
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
                houseRatings.push_back(stoi(readString.substr(0, readString.find("; "))));
                readString.erase(0, readString.find("; ") + 2);
            } else {
                houseRatings.push_back(stoi(readString));
                notEndOfString = false;
            }
        }

        // Load the status into a local variable
        getline(openFile, readString, ',');
        if (readString == "Rented") {
            status = true;
        } else {
            status = false;
        }

        // Load the occupiers into a local vector
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
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
                notEndOfString = false;
            }
        }

        // Load the request list into a local vector
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
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
                notEndOfString = false;
            }
        }

        // Load the occupier comments into a local map
        getline(openFile, readString, ',');
        notEndOfString = true;
        while (notEndOfString) {
            if (readString.find("; ")) {
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                occupierComment[key] = value;
            } else {
                key = keyValueString.substr(0, keyValueString.find(": "));
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                occupierComment[key] = value;
                notEndOfString = false;
            }
        }
        // Append a new House object to the local vector
        House h{houseID, startDate, endDate, address, location, description, houseRatings, status, occupiers, requestList, occupierComment};
        houseList.push_back(h);
    }
    // Close the file
    openFile.close();
    return 0;
}