#include <iostream>
#include <vector>
#include <string>
#include "storage.h"
#include "items.h"

using namespace std;

// Intializing integers to 0 and string to an empty string
storage :: storage(){
    storageType = "";
    storageSize = 0;
}

storage :: storage(string setStorageType, int setStorageSize){
    storageType = setStorageType;
    storageSize = setStorageSize;
}

storage :: storage(string setStorageType, int setStorageSize, vector<items> newItemsInStorage){
    storageType = setStorageType;
    storageSize = setStorageSize;
    stuffInStorage = newItemsInStorage;
}

string storage :: getStorageType(){
    return storageType;
}
int storage :: getStorageSize(){
    return storageSize;
}

vector<items> storage :: getStuffInStorage(){
    return stuffInStorage;
}

items storage :: getItemInStorage(int location){
    return stuffInStorage[location];
}
void storage :: setStuffInStorage(vector<items> newStuffInStorage){
    stuffInStorage = newStuffInStorage;
}

vector<items> storage :: addStuffToStorage(items newItem){
    stuffInStorage.push_back(newItem);
    return stuffInStorage;

}

// Takes a item in storage and replaces it (this was not used in our code since we found easire ways to change the players stroage and inventory)
items storage :: replaceStuffInStorage(items newItem, int location){
    items beingReplaced = stuffInStorage[location];
    vector<items> tempVector;
    for(int i = 0; i < storageSize; i++){
        if(i != location){
            tempVector.push_back(stuffInStorage[i]);
        }
        else{
            tempVector.push_back(newItem);
        }
    }
    stuffInStorage = tempVector;
    return beingReplaced;
}

// Removes the certain item from the storage
void storage :: removeStuffToStorage(int location){
    stuffInStorage.erase(stuffInStorage.begin() + location); // given the location it erases that certain item
}

// Displays the storage to the player
void storage :: displayStorage(){
    cout << "------------------------------------------------------" << endl;
    cout << storageType << endl; // Displays what storage they are looking at aka there inventory or what type of loot box it is
    cout << "------------------------------------------------------" << endl;
    if(stuffInStorage.size() != 0){ // There are things in storage to show to the user
        int count = 1; // Intilize to 1 because we don't want the first spot in the inventory showing 0
        while(count <= storageSize){ // Does this till it reaches the size of the inventory
            if(count - 1 < stuffInStorage.size()){ // Continues down this till it doesn't have anymore items to display to the user
                cout << "[" << count << "]: " << stuffInStorage[count - 1].getItemName() << endl; // Shows the item to the user
                count++;
            }
            else{ // Does this till it reaches the size of the storage showing blank empty spots for the rest of it
                cout << "[" << count << "]: " << endl;
                count++;
            }
        }
    }
    else{ // Just shows the number of inventory spots but no items in any of them because the player doesn't have any or the loot box doesn't have anymore
        for(int i = 1; i <= storageSize; i++){
            cout << "[" << i << "]: " << endl;
        }
    }
    cout << "------------------------------------------------------" << endl;
}

// Adds an item by adding it to a vector
void storage :: addItemToStorage(items thisItem){
    stuffInStorage.push_back(thisItem); // Pushes the item into the vector
}