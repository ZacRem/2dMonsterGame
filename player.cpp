#include <iostream>
#include "player.h"
#include "storage.h"

using namespace std;

// Default player aka what every person will start out as
player :: player(){
    maxHp = 10;
    currentHp = 10;
    baseDamage = 2;
    money = 100;
    currentHunger = maxHunger;
    currentThirst = maxThirst;
}

// If we wanted to create an OP man aka cheat our way through the game we can use this :)
player :: player(int setHp, int setBaseDamage, int setMoney, storage newStorage){
    maxHp = setHp;
    currentHp = setHp;
    baseDamage = setBaseDamage;
    money = setMoney;
    playerStorage = newStorage;
}

 // Allows us add to the users max hp
void player :: addMaxHp(int newMaxHp){
    maxHp += newMaxHp; 
    currentHp += newMaxHp; // Sets the persons current Hp to the new Hp since its like they are leveling up
}

// Adds hp back to the player
void player :: addHp(int hpAdd){
    if(currentHp + hpAdd > maxHp){ // Making sure the player can't over heal
        currentHp = maxHp;
    }
    else{ // adds health back to player
        currentHp += hpAdd;
    }
}

void player :: reduceHp(int hpReduce){
    currentHp -= hpReduce;
}

void player :: setHp(int newHp){
    currentHp = newHp;
}

int player :: getCurrentHp(){
    return currentHp;
}

int player :: getMaxHp(){
    return maxHp;
}

void player :: reduceHunger(int minusHunger){
    if(currentHunger - minusHunger <= 0){ // Makes sure the hunger of the player doesn't go below 0
        currentHunger = 0;
    }
    else{
        currentHunger -= minusHunger;
    }
}


void player :: addHunger(int plusHunger){
    if(currentHunger + plusHunger >= maxHunger){ // Makes sure you can't over hunger yourself
        currentHunger = maxHunger;
    }
    else{
        currentHunger += plusHunger;
    }
}

int player :: getCurrentHunger(){
    return currentHunger;
}

int player :: getCurrentThirst(){
    return currentThirst;
}

// Reduced thirst and make sure it can't go below 0
void player :: reduceThrist(int minusThirst){
    if(currentThirst - minusThirst <= 0){ // Makes sure the thirst can't go below 0
        currentThirst = 0;
    }
    else{
        currentThirst -= minusThirst;
    }
}

// Adds thirst and makes sure thirst can't exceed maximum threshold
void player :: addThirst(int plusThirst){
    if(currentThirst + plusThirst >= maxThirst){ // Makes sure you can't go over the max thirst threshold
        currentThirst = maxThirst;
    }
    else{
        currentThirst += plusThirst;
    }
}

void player :: addBaseDamage(int baseDamageAdd){
    baseDamage += baseDamageAdd;
}

void player :: reduceBaseDamage(int baseDamageReduce){
    baseDamage -= baseDamageReduce;
}

void player :: setBaseDamage(int newBaseDamage){
    baseDamage = newBaseDamage;
}

int player :: getBaseDamage(){
    return baseDamage;
}

storage player :: getStorage(){
    return playerStorage;
}

items player :: getEquippedItem(){
    return equipped;
}

int player :: getMoney(){
    return money;
}

void player :: setMoney(int newMoney){
    money = newMoney;
}

void player :: setStorage(storage newStorage){
    playerStorage = newStorage;
}


//Uses the items class to allow the player to equip the item the player is trying to equip
void player :: equipItem(items newItem){
    if(itemEquipped){
        items temp = equipped; // Intializes variable so it can be accessed
        equipped = newItem; // Equips the new item
    }
    else{
        equipped = newItem;
        itemEquipped = true; // Set to true so you can't equip multiple items at once
    }
}

items player :: unequipItems(){
    itemEquipped = false; // Set to false so you can equip the weapon
    return equipped;
}

// Gets the total amount of damage the player will deal when he has a weapon equipped or not
int player :: getTotalDmg(){
    if(itemEquipped){ // User has weapon equiped and does bonus damage on top of player base damage
        return equipped.getBonusDamage() + baseDamage;
    }
    else{ // User does not have anything equiped and only does base damage
        return baseDamage;
    }
}

// Allows player to update the storage
void player :: updateStorage(vector<items> newStorage){
    playerStorage = storage(playerStorage.getStorageType(), playerStorage.getStorageSize(), newStorage); // Gives access to the private storage class variable
}

// Removes from player inventory to storage
void player :: removeFromPlayerInventory(int location){
    playerStorage.removeStuffToStorage(location);
}

// Adds item to player storage
void player :: addFromPlayerInventory(items thisItem){
    playerStorage.addItemToStorage(thisItem);
}

// Sees whether or not something is equipped
bool player :: getEquipStatus(){
    return itemEquipped;
}