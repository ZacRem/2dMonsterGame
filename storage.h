#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <vector>
#include "items.h"

using namespace std;

class storage{
    private: 
        string storageType;
        int storageSize;
        vector<items> stuffInStorage;
    public:
        // Constructors
        storage();
        storage(string setStorageType, int setStorageSize);
        storage(string setStorageType, int setStoreageSize, vector<items> newStuffInStorage);

        // Getters
        string getStorageType();
        int getStorageSize();
        vector<items> getStuffInStorage();
        items getItemInStorage(int location);

        // Setter
        void setStuffInStorage(vector<items> newStuffInStorage);

        // Messing with storage
        vector<items> addStuffToStorage(items newItem);
        items replaceStuffInStorage(items newItem, int location);
        void removeStuffToStorage(int location);
        void addItemToStorage(items thisItem);

        // Displaying the storage
        void displayStorage();
};
#endif