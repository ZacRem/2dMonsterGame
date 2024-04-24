#include <iostream>
#include "menu.h"

using namespace std;

Menu :: Menu(string setMenuName, vector<string> setMenuUnits){
    menuName = setMenuName;
    menuUnits = setMenuUnits;
}

string Menu :: getMenuName(){
    return menuName;
}

// Prints the name of the menu and the options asociated with that menu to the player
void Menu :: printMenu(){
    cout << "=====================================================" << endl;
    cout << menuName << endl;
    cout << "=====================================================" << endl;
    for(int i = 0; i < menuUnits.size(); i++){
        cout << menuUnits[i] << endl;
    }
    cout << "-----------------------------------------------------" << endl;
}