#include <iostream>
#include <map>
#include <vector>
int main() {
    std::map <std::string,int> test;
    test["Quoc"] = 3;
    test["hehe"] = 1;
    for (auto &i : test) {
        std::cout << i.first << " ";
    }
    std::vector <int> x;
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.erase(x.begin(),x.end() - 1);
    for (auto i : x) {
        std::cout << i << " ";
    }
}