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
            int count = 0;
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (count == member.occupierRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
            int count = 0;
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (count == member.pendingRequests.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
        if (member.ownerComments.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: member.ownerComments) {
                saveFile << comment;
                if (count == member.ownerComments.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                }
                count++;
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
            int count = 0;
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (count == member.occupierRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
            int count = 0;
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (count == member.pendingRequests.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
        if (member.ownerComments.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: member.ownerComments) {
                saveFile << comment;
                if (count == member.ownerComments.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                }
                count++;
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
            int count = 0;
            for (int i = 0; i < house.houseRatings.size(); i++) {
                saveFile << house.houseRatings[i];
                if (count == house.houseRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
            int count = 0;
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->username;
                if (count == house.occupiers.size() - 1) {
                    break;
                }
                saveFile << "; ";
            }
            // Save at the end of the occupierRatings list a comma to mark the end
            saveFile << ",";
        }

        // Check the request list, if it is empty which means this person does not request any house or have rented one already, save "none"
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            // Save each of the house id following by a semicolon
            int count = 0;
            for (int i = 0; i < house.requestList.size(); i++) {
                saveFile << house.requestList[i]->username;
                if (count == house.requestList.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Save the occupier comments
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: house.occupierComment) {
                saveFile << comment;
                if (count == house.occupierComment.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                }
                count++;
            }
        }
        saveFile << endl;

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
            int count = 0;
            for (int i = 0; i < house.houseRatings.size(); i++) {
                saveFile << house.houseRatings[i];
                if (count == house.houseRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Save the status
        saveFile << ((house.status == true) ? "Rented" : "Not Rented") << ",";

        // Save the occupiers
        if (house.occupiers.size() == 0) {
            saveFile << "none" << ",";
        } else {
            int count = 0;
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->username;
                if (count == house.occupiers.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Save the request list
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            int count = 0;
            for (int i = 0; i < house.requestList.size(); i++) {
                saveFile << house.requestList[i]->username;
                if (count == house.requestList.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Check the occupier ratings list, if it is empty then save as none
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: house.occupierComment) {
                saveFile << comment;
                if (count == house.occupierComment.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                }
                count++;
            }
        }
        saveFile << endl;
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
    // Delete the existing vector
    userList.clear();

    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        // Declare the variables
        string id, fullName, userName, password, phoneNumber, houseID, readString, creditPoints, keyValueString, key, value;
        bool notEndOfString = true;
        vector<double> occupierRatings {};
        vector<string> commentList {};

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
        // Erase the unnecessary clauses in the data string
        line.erase(0, line.find(',') + 1);
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

        // Erase the unnecessary clauses in the data string
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);


        // Load the owner comments into the local vector
        readString = line;
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                keyValueString = readString.substr(0, readString.find("; "));
                commentList.push_back(keyValueString);
                readString.erase(0, readString.find("; ") + 2);
            } else {
                keyValueString = readString;
                commentList.push_back(keyValueString);
                break;
            }
        }

        // Append a loaded user into the local vector
        userList.push_back(Member(id, fullName, userName, password, phoneNumber, occupierRatings, stoi(creditPoints), commentList));
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

    // Delete the existing vector
    houseList.clear();

    // Skip the title of the database
    getline(openFile, line);

    // Read through each line of the file until it reaches the end of the file
    while (getline(openFile, line)) {
        string houseID, startDate, endDate, address, location, description, consumingPoints, minOccupierRating, readString, memberID, key, value, keyValueString;
        vector<double> houseRatings;
        bool status = false;
        vector<string> occupierComment;

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

        // Erase the unnecessary clauses in the data string
        line.erase(0, line.find(',') + 1);
        line.erase(0, line.find(',') + 1);

        // Load the occupier comments into a local vector
        readString = line;
        while (true) {
            if (readString == "none") {
                break;
            }
            // If there is still a semicolon, which means there are still values
            if (readString.find("; ") < readString.length()) {
                keyValueString = readString.substr(0, readString.find("; "));
                occupierComment.push_back(keyValueString);
                readString.erase(0, readString.find("; ") + 2);
            } else {
                keyValueString = readString;
                occupierComment.push_back(keyValueString);
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

bool Data::checkDataExist(string id, string path) {
    ifstream openFile;
    string line;
    // Open the file for reading
    openFile.open(path);
    openFile.seekg(0, std::ios::beg);
    // Check the file whether it can be opened
    if (!openFile) {
        cerr << "Cannot open file Member!" << endl;
        return -1;
    }
    // Go through each line check for the first information (id)
    while (getline(openFile, line)) {
        if (id == line.substr(0, line.find(','))) {
            openFile.close();
            return 1;
        }
    }
    openFile.close();
    return 0;
}


bool Data::updateUserData(Member member, string memberPath) {
    // Update the latest data
    Data::preloadHouseData();
    Data::preloadUserData();
    Data::loadHouseData();
    Data::loadUserData();
    // Check the file is able to be opened
    ifstream file(memberPath);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return -1;
    }
    file.close();
    // Check if the data is already exist in the file then append it to the end of the file.
    if (checkDataExist(member.id, memberPath)) {
        fstream saveFile;

        // Open the file to write the data
        saveFile.open("./Data/temp.csv", std::ios::out);
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Find the wanted user and replace with the current user
        for (int i = 0; i < userList.size(); i++) {
            if (member.id == userList[i].id) {
                userList.erase(userList.begin() + i, userList.begin() + i + 1);
                userList.insert(userList.begin() + i, member);
            }
        }
        // Save every user to the file temp
        for (Member member: userList) {
            saveUserData(member, "./Data/temp.csv");
        }

        // Close the file
        saveFile.close();
        // Remove the old file
        remove(memberPath.c_str());
        // Rename the temp file's name with the old file name
        rename("./Data/temp.csv", memberPath.c_str());

    } else {
        fstream saveFile;
        // Open the file to write the data
        saveFile.open(memberPath, std::ios::app);
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
            int count = 0;
            for (int i = 0; i < member.occupierRatings.size(); i++) {
                saveFile << member.occupierRatings[i];
                if (count == member.occupierRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
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
            int count = 0;
            for (int i = 0; i < member.pendingRequests.size(); i++) {
                saveFile << member.pendingRequests[i]->houseID;
                if (count == member.pendingRequests.size() - 1) {
                    break;
                }
                saveFile << "; ";
            }
            saveFile << ",";
        }
        // Check if the rentHouse attribute is a null pointer which means there is no rent house, then save "none"
        if (member.rentHouse == nullptr) {
            saveFile << "none" << ",";
        } else {
            saveFile << member.rentHouse->houseID << ",";
        }

        // Check the comment list, if it is empty then save as none
        if (member.ownerComments.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: member.ownerComments) {
                saveFile << comment;
                if (count == member.ownerComments.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                }
                count++;
            }
        }
        saveFile << endl;
    }
    return 1;
}


bool Data::updateHouseData(House house, string housePath) {
    // Update the latest data
    Data::preloadHouseData();
    Data::preloadUserData();
    Data::loadHouseData();
    Data::loadUserData();
    // Check the file is able to be opened
    ifstream file(housePath);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return -1;
    }
    file.close();
    // Check if the data is already exist in the file then append it to the end of the file.
    if (checkDataExist(house.houseID, housePath)) {
        fstream saveFile;

        // Open the file to write the data
        saveFile.open("./Data/housetemp.csv", std::ios::out);
        // Check the file whether it can be opened
        if (!saveFile) {
            cerr << "Cannot open file for saving!" << endl;
            return -1;
        }
        // Find the wanted house and replace the wanted house with the new house
        for (int i = 0; i < houseList.size(); i++) {
            if (house.houseID == houseList[i].houseID) {
                houseList.erase(houseList.begin() + i, houseList.begin() + i + 1);
                houseList.insert(houseList.begin() + i, house);
            }
        }
        // Save each house to the file temp
        for (House house: houseList) {
            saveHouseData(house, "./Data/housetemp.csv");
        }

        // Close the file
        saveFile.close();
        // Remove the old file
        remove(housePath.c_str());
        // Rename the temp file's name with the old file name
        rename("./Data/housetemp.csv", housePath.c_str());

    } else {
        fstream saveFile;
        // Open the file for appending
        saveFile.open(housePath, std::ios::app);
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
            int count = 0;
            for (int i = 0; i < house.houseRatings.size(); i++) {
                saveFile << house.houseRatings[i];
                if (count == house.houseRatings.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Save the status
        saveFile << ((house.status == true) ? "Rented" : "Not Rented") << ",";

        // Save the occupiers
        if (house.occupiers.size() == 0) {
            saveFile << "none" << ",";
        } else {
            int count = 0;
            for (int i = 0; i < house.occupiers.size(); i++) {
                saveFile << house.occupiers[i]->username;
                if (count == house.occupiers.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Save the request list
        if (house.requestList.size() == 0) {
            saveFile << "none" << ",";
        } else {
            int count = 0;
            for (int i = 0; i < house.requestList.size(); i++) {
                saveFile << house.requestList[i]->username;
                if (count == house.requestList.size() - 1) {
                    break;
                }
                saveFile << "; ";
                count++;
            }
            saveFile << ",";
        }

        // Check the occupier ratings list, if it is empty then save as none
        if (house.occupierComment.size() == 0) {
            saveFile << "none" << endl;
        } else {
            int count = 0;
            for (string comment: house.occupierComment) {
                saveFile << comment;
                if (count == house.occupierComment.size() - 1) {
                    break;
                } else {
                    saveFile << "; ";
                    count++;
                }
            }
        }
        saveFile << endl;
        saveFile.close();
    }
    return 1;
}