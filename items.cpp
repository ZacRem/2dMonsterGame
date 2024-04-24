#include <iostream>
#include "items.h"

using namespace std;

//Intializes everything to 0 or to an empty string
items :: items(){
    itemName = "";
    itemType = "";
    itemDescription = "";
    amountHeal = 0;
    restoreThirst = 0;
    restoreHunger = 0;
}

items :: items(string setItemName, string setItemType, int setBonusDamage, int setHeal, int setRestoreThirst, int setRestoreHunger, string setItemDescription){
    itemName = setItemName;
    itemType = setItemType;
    bonusDamage = setBonusDamage;
    itemDescription = setItemDescription;
    amountHeal = setHeal;
    restoreThirst = setRestoreThirst;
    restoreHunger = setRestoreHunger;
}


string items :: getItemName(){
    return itemName;
}

string items :: getItemType(){
    return itemType;
}

string items :: getItemDescription(){
    return itemDescription;
}

int items ::  getBonusDamage(){
    return bonusDamage;
}

int items ::  getAmountHeal(){
    return amountHeal;
}

int items :: getRetoreThirst(){
    return restoreThirst;
}

int items :: getRestoreHunger(){
    return restoreHunger;
}

void items :: setItemName(string newItemName){
    itemName = newItemName;
}

void items :: setItemType(string newItemType){
    itemType = newItemType;
}

void items :: setItemDescription(string newItemDescription){
    itemDescription = newItemDescription;
}

void items:: setItemBonusDamage(int newBonusDamage){
    bonusDamage = newBonusDamage;
}

void items :: setAmountHeal(int newHeal){
    amountHeal = newHeal;
}

void items :: setRestoreThirst(int newThirst){
    restoreThirst = newThirst;
}

void items :: setRestoreHunger(int newHunger){
    restoreHunger = newHunger;
}