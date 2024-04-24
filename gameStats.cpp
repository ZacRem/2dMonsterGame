#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "items.h"
#include "menu.h"
#include "storage.h"
#include "monster.h"
#include "storage.h"
#include "systemDialogue.h"
#include "gameStats.h"

using namespace std;
/*
pretty self explantory with setters and getters and contructors
*/

//this is there because the compiler gets angry when not there//
gameStats :: gameStats(){
    
}

gameStats :: gameStats(vector<items> setItems, vector<Menu> setMenues, vector<storage> setStorage, vector<monster> setMonster, vector<SystemDialogue> setDialogue){
    gameItems = setItems;
    gameMenues = setMenues;
    gameStorage = setStorage;
    gameMonster = setMonster;
    gameDialogue = setDialogue;
    numOfTurns = 0;
}

vector<items> gameStats :: getGameItems(){
    return gameItems;
}

vector<Menu> gameStats :: getGameMenu(){
    return gameMenues;
}

vector<storage> gameStats :: getGameStorage(){
    return gameStorage;
}

vector<monster> gameStats :: getGameMonster(){
    return gameMonster;
}

vector<SystemDialogue> gameStats :: getGameDialogue(){
    return gameDialogue;
}

int gameStats :: getNumOfTurns(){
    return numOfTurns;
}

void gameStats :: increaseNumOfTurns(){
    numOfTurns++;
}
