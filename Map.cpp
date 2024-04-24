#include "Map.h"
 
using namespace std;
 
Map::Map()
{
    resetMap();
}
 
// resets player position, count values, and initializes values in position arrays to -1
void Map::resetMap() {
    playerPosition[0] = 0;
    playerPosition[1] = 0;
 
    for (int i = 0; i < num_SafeSpot; i++){
        safeSpotPosition[i][0] = -1;
        safeSpotPosition[i][1] = -1;
    }
 
    safeSpotCount = 0;
    monster_count = 0;
    monsterSlayedCount = 0;
 
    for (int i = 0; i < num_monster; i++) {
        monsterPositions[i][0] = -1;
        monsterPositions[i][1] = -1;
    }
 
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            mapData[i][j] = '-';
        }
    }
}
 
// return player's row position
int Map::getPlayerRowPosition() {
    return playerPosition[0];
}
 
// return player's column position
int Map::getPlayerColPosition() {
    return playerPosition[1];
}
 
int Map::getMonsterCount() {
    return monster_count;
}
 
int Map::getSafeSpotCount() {
    return safeSpotCount;
}

int Map::getMonsterSlayedCount() {
    return monsterSlayedCount;
}
 
// set player's row position to parameter row
void Map::setPlayerRowPosition(int row) {
    playerPosition[0] = row;
}
 
// set player's column position to parameter row
void Map::setPlayerColPosition(int col) {
    playerPosition[1] = col;
}
 
void Map::setMonsterCount(int count) {
    monster_count = count;
}
 
void Map::setSafeSpotCount(int count) {
    safeSpotCount = count;
}

void Map::setMonsterSlayedCount(int count){
    monsterSlayedCount = count;
}
 
 
/* add Monster to map
 * Parameters: where to spawn Monster -- row (int), col (int)
 * Return: (bool) false if no more space in monsterPositions array
 *                      or if (row, col) is an invalid position
 *                      or if (row, col) is already populated; else true
 */
bool Map::spawnMonster(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }
 
    if (monster_count >= num_monster) {
        return false;
    }
 
    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }
 
    if (monsterPositions[monster_count][0] == -1 && monsterPositions[monster_count][1] == -1) {
        monsterPositions[monster_count][0] = row;
        monsterPositions[monster_count][1] = col;
        mapData[row][col] = '-';
        monster_count++;
        return true;
    }
 
    return false;
}
 
/* add Monster to map
 * Parameters: where to spawn Monster -- row (int), col (int)
 * Return: (bool) false if no more space in monsterPositions array
 *                      or if (row, col) is an invalid position
 *                      or if (row, col) is already populated; else true
 */
bool Map::spawnSafeSpot(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }
 
    if (safeSpotCount >= num_SafeSpot) {
        return false;
    }
 
    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }
 
    if (safeSpotPosition[safeSpotCount][0] == -1 && safeSpotPosition[safeSpotCount][1] == -1) {
        safeSpotPosition[safeSpotCount][0] = row;
        safeSpotPosition[safeSpotCount][1] = col;
        mapData[row][col] = 'S';
        safeSpotCount++;
        return true;
    }
 
    return false;
}
/*
return true if x, y position has a Safe Spot there
removes the safe spot location from the map after player has landed on it once
*/
bool Map::isSafeSpotLocation(){
    
    for (int i = 0; i < num_SafeSpot; i++){
        if(safeSpotPosition[i][0] == playerPosition[0] && safeSpotPosition[i][1] == playerPosition[1]){
            mapData[safeSpotPosition[i][0]][safeSpotPosition[i][1]] = '-'; // Sets space back to a blank space
            safeSpotPosition[i][0] = -1; // Makes postion -1 so it will always return false since player can never be at a -1 postion
            return true;
        }
    }
    return false;
}
 
/* 
return true if x, y position has an Monster there
if monster is there then it removes the monster off the map
*/
bool Map::isMonsterLocation(){
    for(int i = 0; i < num_monster; i++){
        if(monsterPositions[i][0] == playerPosition[0] && monsterPositions[i][1] == playerPosition[1]){
            monsterPositions[i][0] = -1; // Makes postion -1 so it will always return false since player can never be at a -1 postion
            monsterSlayedCount++;
            return true;
        }
    }
    return false;
}
 
/*
 * This function prints a menu of valid moves based on playerPosition
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMoves(){
    if(!(playerPosition[0] == 0)){
        cout << "w (Up)" << endl;
    }
    if(!(playerPosition[0] == (num_rows - 1))){
        cout << "s (Down)" << endl;
    }
    if(!(playerPosition[1] == 0)){
        cout << "a (Left)" << endl;
    }
    if(!(playerPosition[1] == (num_cols - 1))){
        cout << "d (Right)" << endl;
    }
}
 
/*
 * This function takes in user input
 * and updates playerPosition on the map.
 * Parameters: move (char) -- 'w' (up), 'a' (left), 's' (down), 'd' (right)
 * Return: (bool) if move is valid, then true, else false
 */
bool Map::executeMove(char move){
    // if user inputs w, move up if it is an allowed move
    if(!(playerPosition[0] == 0) && (tolower(move) == 'w')){
        playerPosition[0] -= 1;
        return true;
    }
    // if user inputs s, move down if it is an allowed move
    else if(!(playerPosition[0] == (num_rows - 1))&& (tolower(move) == 's')){
        playerPosition[0] += 1;
        return true;
    }
    // if user inputs a, move left if it is an allowed move
    else if(!(playerPosition[1] == 0)&& (tolower(move) == 'a')){
        playerPosition[1] -= 1;
        return true;
    }
    // if user inputs d, move right if it is an allowed move
    else if(!(playerPosition[1] == (num_cols - 1))&& (tolower(move) == 'd')){
        playerPosition[1] += 1;
        return true;
    }
    else{
        cout << "Invalid Move" << endl;
        return false;
    }
}
 
/*
 * This function prints a 2D map in the terminal.
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMap() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (playerPosition[0] == i && playerPosition[1] == j) {
                cout << "x";
            }
            else {
                cout << mapData[i][j];
            }
        }
        cout << endl;
    }
}
