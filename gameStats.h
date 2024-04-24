#ifndef GAMESTATS_H
#define GAMESTATS_H
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
#include "Map.h"

using namespace std;

class gameStats{
    private:
        vector<items> gameItems;
        vector<Menu> gameMenues;
        vector<storage> gameStorage;
        vector<monster> gameMonster;
        vector<SystemDialogue> gameDialogue;
        int numOfTurns;
    public:
        // Constructors
        gameStats();
        gameStats(vector<items> setItems, vector<Menu> setMenues, vector<storage> setStorage, vector<monster> setMonster, vector<SystemDialogue> setDialogue);

        //getters//
        vector<items> getGameItems();
        vector<Menu> getGameMenu();
        vector<storage> getGameStorage();
        vector<monster> getGameMonster();
        vector<SystemDialogue> getGameDialogue();
        int getNumOfTurns();
        Map getGameMap();

        // Turns for player
        void increaseNumOfTurns();
};

#endif