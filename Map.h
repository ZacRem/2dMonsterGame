#ifndef MAP_H
#define MAP_H
 
#include <fstream>
#include <iostream>
#include <ctype.h>
 
using namespace std;

/*
Creates the map for the player
Spawns monsters into the map
Spawns Safe Spots
Checks whether player is on those spots
Displays moves
*/

class Map
{
     private:
          static const int num_rows = 20;
          static const int num_cols = 30;
          static const int num_monster = 500;
          static const int num_SafeSpot = 30;
 
          int playerPosition[2];
          int safeSpotPosition[num_SafeSpot][2];
          int monsterPositions[num_monster][2];
          char mapData[num_rows][num_cols];
 
          int safeSpotCount;
          int monster_count;
          int monsterSlayedCount;
 
     public :
          Map();
 
          void resetMap();
 
          // getters
          int getPlayerRowPosition();
          int getPlayerColPosition();
          int getMonsterCount();
          int getSafeSpotCount();
          int getMonsterSlayedCount();
 
          // setters
          void setPlayerRowPosition(int);
          void setPlayerColPosition(int);
          void setMonsterCount(int);
          void setSafeSpotCount(int);
          void setMonsterSlayedCount(int);
 
          bool spawnMonster(int, int);
          bool spawnSafeSpot(int, int);
 
          void displayMap();
          void displayMoves();  
          bool executeMove(char);
 
          bool isSafeSpotLocation();
          bool isMonsterLocation();
 
};
 
#endif
