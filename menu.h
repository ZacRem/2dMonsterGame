#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>

using namespace std;

class Menu{
    private:
        string menuName;
        vector<string> menuUnits;
    public:
        // Constructors
        Menu(string menuName, vector<string> menuUnits);

        // Getter
        string getMenuName();

        // Prints menu
        void printMenu();
};

#endif