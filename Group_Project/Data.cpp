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
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }

        // Save the title
        saveFile << "ID,Full Name,Username,Password,Phone Number,Owned House,Occupier Ratings,Credit Points,Pending Requests,Rent House,Comment List" << endl;

        // Save the id, full name, username, password, phone number
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << ",";

        // Check if the myHouse attribute is a null pointer which means there is no House object, save as "none"
        if (member.myHouse != nullptr) {
            // Save the owned house ID
            saveFile << member.myHouse->houseID << ",";
        } else {
            saveFile << "none" << ",";
        }

        // Check the occupier ratings list, if it is empty then save as none
        if (member.occupierRatings.empty()) {
            saveFile << "none" << ",";
        } else {
            // Save each of the rating following by a semicolon
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (i + 1 == member.occupierRatings.size()) {
                    break;
                }
                saveFile << ";";
            }
            // Save the end of the occupier ratings string a comma to indicate the end of the list
            saveFile << ",";
        }
        // Save the credit points
        saveFile << member.creditPoint << ",";

        // Check if the pending request list is empty then save as "none"
        if (member.pendingRequests.empty()) {
            saveFile << "none" << ",";
        } else {
            // Save each of the house ID of each House object in the pending request list following by a semicolon
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (i + 1 == member.pendingRequests.size()) {
                    break;
                }
                saveFile << ";";
            }
            // Save the end of the pending request string a comma to indicate the end of the list
            saveFile << ",";
        }
        // Check if the rentHouse attribute is a null pointer which means there is no rent house, then save "none"
        if (member.rentHouse == nullptr) {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse->houseID << ",";
        }
        // Check the owner comment list is empty, if yes then save "none"
        if (member.ownerComments.empty()) {
            saveFile << "none";
        } else {
            int count = 0;
            // Save each key of the map following by a colon and the value of the map
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
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }

        // Move the pointer to the end of the file for appending into the file
        saveFile.seekg(std::ios::end);

        // Save the id, full name, username, password, phone number
        saveFile << member.id << "," << member.fullName << "," << member.username << "," << member.password << "," << member.phoneNumber << ",";

        // Check if the myHouse attribute is a null pointer which means there is no House object, save as "none"
        if (member.myHouse != nullptr) {
            // Save the owned house ID
            saveFile << member.myHouse->houseID << ",";
        } else {
            saveFile << "none" << ",";
        }

        // Check the occupier ratings list, if it is empty then save as none
        if (member.occupierRatings.empty()) {
            saveFile << "none" << ",";
        } else {
            // Save each of the rating following by a semicolon
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

        // Check if the pending request list is empty then save as "none"
        if (member.pendingRequests.empty()) {
            saveFile << "none" << ",";
        } else {
            // Save each of the house ID of each House object in the pending request list following by a semicolon
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (i + 1 == member.pendingRequests.size()) {
                    break;
                }
                saveFile << ";";
            }
            saveFile << ",";
        }
        // Check if the rentHouse attribute is a null pointer which means there is no rent house, then save "none"
        if (member.rentHouse == nullptr) {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse->houseID << ",";
        }

        // Check the occupier ratings list, if it is empty then save as none
        if (member.ownerComments.empty()) {
            saveFile << "none";
        } else {
            int count = 0;
            // Save each key of the map following by a colon and the value of the map
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
    return true;
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
        // Open the file for writing
        saveFile.open(path, std::ios::out);
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }

        // Save the title
        saveFile << "ID,Start Date,End Date,Address,Location,Description, Consuming Points, Minimum Occupier Rating,House Ratings,Status,Occupiers,Request List,Comment List" << endl;

        // Save the house id, start date, end date, address, location, description, consuming points, minimum occupier rating
        saveFile << house.houseID << "," << house.startDate << "," << house.endDate << "," << house.address << "," << house.location << "," << house.description << "," << house.consumingPoints << "," << house.minOccupierRating << ",";

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

        // Save the status, if it is rented then save as true
        saveFile << ((house.status == true) ? "Rented" : "Not Rented") << ",";

        // Check the occupiers list, if it is empty which means there is nobody rent the house, save "none"
        if (house.occupiers.size() == 0) {
            saveFile << "none" << ",";
        } else {
            // Save each occupier's id following by a semicolon
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->id;
                if (i + 1 == house.occupiers.size()) {
                    break;
                }
                saveFile << ";";
            }
            // Save at the end of the occupierRatings list a comma to mark the end
            saveFile << ",";
        }

        // Check the request list, if it is empty which means this person does not request any house or have rented one already, save "none"
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            // Save each of the house id following by a semicolon
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
        // Open the file for appending
        saveFile.open(path, std::ios::app);
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }

        // Move the pointer to the end of the file for appending into the file
        saveFile.seekg(std::ios::end);

        // Save the house id, start date, end date, address, location, description, consuming points, minimum occupier rating
        saveFile << house.houseID << "," << house.startDate << "," << house.endDate << "," << house.address << "," << house.location << "," << house.description << "," << house.consumingPoints << "," << house.minOccupierRating << ",";

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

        // Check the occupier ratings list, if it is empty then save as none
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            // Save each key of the map following by a colon and the value of the map
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



bool Data::preloadUserData(string memberPath) {
    fstream openFile;
    string line;

    // Open the member file for reading
    openFile.open(memberPath, std::ios::in);
    // Check the file whether it can be opened
    if (!openFile) {
        cerr << "Cannot open file member!" << endl;
        return -1;
    }
    fs::resize_file(memberPath,0);
    openFile.seekp(0);

    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        // Declare the variables
        string id, fullName, userName, password, phoneNumber, houseID, readString, creditPoints, keyValueString, key, value;
        bool notEndOfString = true;
        vector<double> occupierRatings {};
        map<string, string> ownerComment {};
        
        // Load the member id into local variable
        id = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Load the full name into local variable
        fullName = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Load the username into local variable
        userName = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Load the password into local variable
        password = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Load the phone number into the local variable
        phoneNumber = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the House object into the local variable
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        
        // Load the occupier ratings into the local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
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


        // Load the rent house into the local variable
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);


        // Load the owner comments into the local map
        readString = line;
        // cout << readString << endl;
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                // Save the part before the colon as the key
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                // Save the after part of the colon as the value of that key
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                // Save the key value pair into the map
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
        userList.push_back(Member(id, fullName, userName, password, phoneNumber, occupierRatings, stoi(creditPoints), ownerComment));
    }
    // Close the file
    openFile.close();
    return 1;
}

bool Data::preloadHouseData(string housePath) {
    // Open the file for reading
    fstream openFile;
    openFile.open(housePath, std::ios::in);
    string line;
    // Check the file whether it can be opened
    if (!openFile) {
        cerr << "Cannot open file House!" << endl;
        return -1;
    }
    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        string houseID, startDate, endDate, address, location, description, consumingPoints, minOccupierRating, readString, memberID, key, value, keyValueString;
        vector<double> houseRatings;
        bool status = false;
        map<string, string> occupierComment;

        // Load the house id, start date, end date, address, location, description into local variables
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the start date into local variable
        startDate = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the end date into local variable
        endDate = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Check the address whether it contains double quotation, remove them out of the string
        if (line[0] == '\"') {
            // Load the address into local variable
            address = line.substr(1, line.find("\",") - 1);
            line.erase(0, line.find("\",") + 2);
        } else {
            // Load the address into local variable
            address = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
        }

        // Load the location into local variable
        location = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Check the description whether it contains double quotations at two ends, remove them out of the string to guarantee the content.
        if (line[0] == '\"') {
            // Load the description into local variable
            description = line.substr(1, line.find("\",") - 1);
            line.erase(0, line.find("\",") + 2);
        } else {
            // Load the description into local variable
            description = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
        }

        // Load the consuming points into the variable
        consumingPoints = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the minimum occupier rating into the variable
        minOccupierRating = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the house ratings into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
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
        // Check if the string is rented, then the status will be true and vice versa
        if (readString == "Rented") {
            status = true;
        } else {
            status = false;
        }

        // Load the occupiers into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        
        // Load the request list into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Load the occupier comments into a local map
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                // Save the part before the colon to the key
                keyValueString = readString.substr(0, readString.find("; "));
                key = keyValueString.substr(0, keyValueString.find(": "));
                // Save the part after the colon to the value
                keyValueString.erase(0, keyValueString.find(": ") + 2);
                value = keyValueString;
                // Save the key value pair to the map
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
        houseList.push_back(House(houseID, startDate, endDate, address, location, description, stod(consumingPoints), stod(minOccupierRating), houseRatings, status, occupierComment));
    }
    // Close the file
    openFile.close();
    return 1;
}


bool Data::loadUserData(string memberPath) {
    // Data::preloadHouseData();
    fstream openFile;
    string line;

    // Open the member file for reading
    openFile.open(memberPath, std::ios::in);
    // Check the file whether it can be opened
    if (!openFile) {
        cerr << "Cannot open file Member!" << endl;
        return -1;
    }

    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        // Declare the variables
        string id, houseID, readString;
        // Aggregation Relationship between House class and Member class
        House *myHouse = nullptr;
        House *rentHouse = nullptr;
        // Aggregation Relationship between House class and Member class
        vector<House*> pendingRequests {};
        
        // Load the member id to local variable
        id = line.substr(0, line.find(','));
        // Erase the unnecessary clauses in the data string
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);

        // Load the House object into the local variable
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        // Check the house from the house list to validate the House
        for (int i = 0; i < houseList.size(); i++) {
            if (houseID == houseList[i].houseID) {
                myHouse = &houseList[i];
                break;
            }
        }

        // Erase the unnecessary clauses in the data string
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);

        // Load the pending request into the local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                houseID = readString.substr(0, readString.find("; "));
                // Validate the House by comparing the id with the data in the house list
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
        houseID = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (houseID != "none") {
            for (int i = 0; i < houseList.size(); i++) {
                if (houseID == houseList[i].houseID) {
                    rentHouse = &houseList[i];
                    break;
                }
            }
        }
        

        // Load the owner comments into the local map
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);

        // Find the wanted member in the user list and modify it
        for (Member &member: userList) {
            if (id == member.id) {
                // Add the myHouse and rentHouse (House object), pending request to its attribute
                member.myHouse = myHouse;
                member.pendingRequests = pendingRequests;
                member.rentHouse = rentHouse;
                break;
            }
        }
    }
    // Close the file
    openFile.close();
    return 1;
}

bool Data::loadHouseData(string housePath) {
    // Open the file for reading
    fstream openFile;
    openFile.open(housePath, std::ios::in);
    string line;
    // Check the file whether it can be opened
    if (!openFile) {
        cerr << "Cannot open file House!" << endl;
        return -1;
    }

    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        string houseID, readString, memberUsername;
        // Aggregation relationship between Member class and House class
        vector<Member*> occupiers; 
        vector<Member*> requestList;

        // Load the house id
        houseID = line.substr(0, line.find(','));
        // Erase the unnecessary clauses of the data string
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);

        // Load the request list into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                memberUsername = readString.substr(0, readString.find("; "));
                for (int i = 0; i < userList.size(); i++) {
                    if (memberUsername == userList[i].username) {
                        requestList.push_back(&userList[i]);
                        break;
                    }
                }
                readString.erase(0, readString.find("; ") + 2);
            } else {
                memberUsername = readString;
                for (int i = 0; i < userList.size(); i++) {
                    if (memberUsername == userList[i].username) {
                        requestList.push_back(&userList[i]);
                        break;
                    }
                }
                break;
            }
        }

        // Load the occupiers into a local vector
        readString = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                memberUsername = readString.substr(0, readString.find("; "));
                // Validate the House object comparing the id with the houses from the house list
                for (int i = 0; i < userList.size(); i++) {
                    if (memberUsername == userList[i].username) {
                        occupiers.push_back(&userList[i]);
                        break;
                    }
                }
                readString.erase(0, readString.find("; ") + 2);
            } else {
                memberUsername = readString;
                for (int i = 0; i < userList.size(); i++) {
                    if (memberUsername == userList[i].username) {
                        occupiers.push_back(&userList[i]);
                        break;
                    }
                }
                break;
            }
        }

        // Find the wanted House object and modify it
        for (House &house: houseList) {
            if (houseID == house.houseID) {
                // Add the occupiers list and request list to the House object attributes
                house.occupiers = occupiers;
                house.requestList = requestList;
                break;
            }
        }
    }
    // Close the file
    openFile.close();
    return 1;
}