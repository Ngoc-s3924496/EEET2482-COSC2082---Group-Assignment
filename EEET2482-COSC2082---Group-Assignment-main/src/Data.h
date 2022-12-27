#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Member.h"
#include "User.h"
#include "House.h"

using std::cin;
using std::cout;
using std::vector;
using std::map;
using std::ifstream;
using std::fstream;
using std::endl;
using std::cerr;
using std::string;

#define MEMBER_DATABASE "./Data/Members.csv"
#define HOUSE_DATABASE "./Data/Houses.csv"


class Data {
private:
    vector<Member> userList;
    vector<HOUSE_H House> houseList;
    std::vector<Member> a;
public:
    bool is_empty(std::ifstream &file);
    bool saveUserData(Member member, string path = MEMBER_DATABASE);
    bool saveHouseData(House house, string path = HOUSE_DATABASE);
    bool LoadUserData(string memberPath = MEMBER_DATABASE);
    bool LoadHouseData(string housePath = HOUSE_DATABASE);
};

#endif