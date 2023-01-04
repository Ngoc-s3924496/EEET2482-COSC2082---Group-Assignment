#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Member.h"
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
using std::stoi;

#define MEMBER_DATABASE "./Data/Members.csv"
#define HOUSE_DATABASE "./Data/Houses.csv"


class Data {
public:
    friend class Admin;
    friend class Member;
    friend class House;
public:
    inline static vector<Member> userList {};
    inline static vector<House> houseList {};
public:
    Data();
    static bool is_empty(std::ifstream &file);
    static bool saveUserData(Member member, string path = MEMBER_DATABASE);
    static bool saveHouseData(House house, string path = HOUSE_DATABASE);
    static bool loadUserData(string memberPath = MEMBER_DATABASE);
    static bool loadHouseData(string housePath = HOUSE_DATABASE);
    static bool preloadUserData(string memberPath = MEMBER_DATABASE);
    static bool preloadHouseData(string housePath = HOUSE_DATABASE);
    static bool checkDataExist(string id, string path);
    static bool updateUserData(Member member, string memberPath = MEMBER_DATABASE);
    static bool updateHouseData(House house, string housePath = HOUSE_DATABASE);
    static bool loadFullData();
};

#endif