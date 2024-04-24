// CSCI 1300 Fall 2021
// Author: Taewoo Hong, Zach Remer
// Secton: 110 Alex Ray, Recitation: 314 – Kayleigh Bishop 
// Project 3 - Create your own

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "time.h"
#include "stdlib.h"
#include "player.h"
#include "items.h"
#include "menu.h"
#include "storage.h"
#include "monster.h"
#include "systemDialogue.h"
#include "gameStats.h"
#include "Map.h"
#include "pivot.h"

using namespace std;

/*
this function takes a string and a char and cuts up the string where each splitters are and stores each of them into vector
and then returns it
*/
vector<string> split(string line, char splitter){
    //set the substring equal to blank//
    string subString = "";
    //create the vector that is going to be returned//
    vector<string> returning;
    //traverse through the string//
    for(int i = 0; i < line.size(); i++){
        //check if the char of that string index is equal to the splitter char//
        if(line[i] != splitter){
            //if it is not then add it to the substring//
            subString += string() + line[i];
        }
        else{
            //if not, then add the substring to the returning vector//
            returning.push_back(subString);
            //reset the substring to blank//
            subString = "";
        }
    }
    //since the traversing does not account for the last substring because theres no splitter at the end, do it manually//
    returning.push_back(subString);
    // return the vector//
    return returning;
}

/*
this function just cuts the vector with given starting index and the ending index
*/
vector<int> cutVector(vector<int> sampleVector, int startingIndex, int endingIndex){
    //set the new vector//
    vector<int> newVector;
    //traverse through index with given starting index and end at the ending index//
    for(int i = startingIndex; i <= endingIndex; i++){
        //add each vector elements to the newVector
        newVector.push_back(sampleVector[i]);
    }
    //return the new vector//
    return newVector;
}

/*
this function switches the location of the two elements in a vector//
*/
vector<int> swapThem(vector<int> needsSwapping, int index, int secondIndex){
    //first make a temp var and store the first element that needs swapping//
    int tempVal = needsSwapping[index];
    //set the first element that needs swapping eqaual to the second element that needs swapping//
    needsSwapping[index] = needsSwapping[secondIndex];
    //set the second element needs swapping equal to the tempVal we created//
    needsSwapping[secondIndex] = tempVal;
    //return the vector//
    return needsSwapping;
}

/*
this function sets a creats 3 object random pivot point 
and then returns the middle value of the pivot
to prevent worse case sorting scenerio and returns the pivor point for quick sort algorithm.
*/
pivot pivotSetter(vector<int> sampleVector){
    //set the seed random based on time//
    srand(time(NULL));
    //create a vector that hols pivot points//
    vector<pivot> pivots;
    //create a int var that is going to hold the random index//
    int randIndex;
    //create a boolean to check if the random picked an already existiing pivot//
    bool alreadyExists;
    //make a while loop keep generating pivots until we have 3 different pivots/
    while(pivots.size() < 3){
        //default the already exist to false//
        alreadyExists = false;
        //picks the random index between 0 and the vector size//
        randIndex = rand() % sampleVector.size();
        //traverse through the pivots vector//
        for(int i = 0; i < pivots.size(); i++){
            //check if the randindex already exists within the vector of pivots//
            if(pivots[i].getIndex() == randIndex){
                //if it does then set the boolean equal to true//
                alreadyExists = true;
                //break out of the loop since we dont need to check anymore//
                break;
            }
        }
        //check if the random index already exists//
        if(!alreadyExists){
            //if it doesn't then add it to the vector//
            pivots.push_back(pivot(sampleVector[randIndex], randIndex));
        }
    }
    //sort them from least greatest//
    //create variables that stores the index of the minimum and the maximum values of the pivots//
    //default them to 0//
    int indexMin = 0;
    int indexMax = 0;
    //traverse through the pivot vector//
    for(int i = 0; i < pivots.size(); i++){
        //check if the the current min index is less than the traversing point of the pivot vector//
        if(pivots[indexMin].getPivot() <= pivots[i].getPivot()){
            //if it is not then update the new min point//
            indexMin = i;
        }
    }
    //travere through the pivot vector//
    for(int i = 0; i <pivots.size(); i++){
        //check if the current max index is greater than the current traversing point of the pivot//
        if(pivots[indexMax].getPivot() >= pivots[i].getPivot()){
            //if it is not then update the new max pivot point//
            indexMax = i;
        }
    }
    //get the middle pivot index//
    int middlePivotIndex;
    //traverse though i with the size of the array//
    for(int i = 0; i < pivots.size(); i++){
        //if the i does not equal the indexMin AND indexMax then thats middle index since theres only 3 indexes//
        if(i != indexMin && i != indexMax){
            middlePivotIndex = i;
        }
    }
    //return the middle pivot//
    return pivots[middlePivotIndex];
}

/*
this function partitions vector meaning it picks a pivot point and re-organizes the the vector where all the values less than the 
pivot value is on the left side of the pivot while vales greater than the pivot is on the right side of the pivot and then returns the vector//
*/
vector<int> partition(vector<int> sampleVector){
    //first get a random valid pivot point//
    pivot randomPivot = pivotSetter(sampleVector);
    //create two vectors that holds left end of the array and the right end of the array of the pivot point//
    vector<int> leftBound;
    vector<int> rightBound;
    //traveres through the vector//
    for(int i = 0; i < sampleVector.size(); i++){
        //check to make sure that you are not checking the pivot itself//
        if(i != randomPivot.getIndex()){
            //check if the the value of the vector element is less than the pivot value//
            if(sampleVector[i] <= randomPivot.getPivot()){
                //if it is then add it to the leftbound of the vector//
                leftBound.push_back(sampleVector[i]);
            }
            else{
                //if not the add it to the right bound vector//
                rightBound.push_back(sampleVector[i]);
            }
        }
    }
    //the index of the pivot is going to be the size of the leftbound array//
    int newPivotIndex = leftBound.size();
    //update the pivot index information//
    randomPivot.setIndex(newPivotIndex);
    //put the pivot value on to the left bound vector//
    leftBound.push_back(randomPivot.getPivot());
    //traverse through the right bound vector//
    for(int i = 0; i < rightBound.size(); i++){
        //add the right bound vector to the left bound vector//
        leftBound.push_back(rightBound[i]);
    }
    //also add the index of the pivot to end of the vector//
    leftBound.push_back(randomPivot.getIndex());
    //return it//
    return leftBound;
}

/*
this algorith sorts the vector in least to greatest order using the quicksort method using recursion. it sorts the the vector values of indexes between the starting
and the ending index
*/
vector<int> quickSort2(vector<int> sampleVector, int startingIndex, int endIndex){
    //update the vector where we are dealing with the given condition//
    vector<int> updatedVector = cutVector(sampleVector, startingIndex, endIndex);
    //check make sure that the ending index is greater than the starting index//
    if(endIndex > startingIndex){
        //if it is then make sure that the vector we are dealing with has a size greater than 2//
        if(updatedVector.size() > 2){
            /*
            if it is then partition it where it returns the vector with all the values less than the randomly selected pivot
            are on the left side of the pivot while greater is on the right side with the pivot index on the end of the vector
            */
            vector<int> cleanUp = partition(updatedVector);
            //take the pivot index and set it to a variable//
            int pivotIndex = cleanUp[cleanUp.size() - 1];
            //delete the pivot index on the end of the vector since we are storing it on the pivot index//
            cleanUp.pop_back();
            //we need to get the end index of the vector and that is equal to the size of vector - 1//
            int endIndex2 = cleanUp.size() - 1;
            //re-run the leftEnd of pivot vector into quick sort//
            vector<int> leftEnd = quickSort2(cleanUp, 0, pivotIndex - 1);
            //re-run the right end of the pivot vector into quick sort//
            vector<int> rightEnd = quickSort2(cleanUp, pivotIndex + 1, endIndex2);
            //re merge the vectors by putitng the pivot to the left end vector first//
            leftEnd.push_back(cleanUp[pivotIndex]);
            //and then add the right end vector to the left end of the vector//
            for(int i = 0; i < rightEnd.size(); i++){
                leftEnd.push_back(rightEnd[i]);
            }
            //return the entire vector//
            return leftEnd;
        }
        //if the size of the vector is not greater than 2 then we can easily sort them by swapping when necessary//
        else{
            //if the second element of the vector is less than the first element then swap//
            if(updatedVector[1] < updatedVector[0]){
                //then just return it//
                return swapThem(updatedVector, 0, 1);
            }
            else{
                //if not then just return//
                return updatedVector;
            }
        }
    }
    //if the ending index is not greater than starting then we know its theres only one element in the vector//
    else{
        //so we just return that//
        return updatedVector;
    }
}

/*
reads the menu text file and stores them into vector filled with menues//
*/
vector<Menu> readMenues(string fileName){
    //make ifstream fin//
    ifstream fin;
    //open the file//
    fin.open(fileName.c_str());
    //check if the file is open//
    if(!fin.is_open()){
        //if not then give error message//
        cout << "Error! " << fileName << " failed to open" << endl;
        //then exit the function//
        exit(EXIT_FAILURE);
    }
    //make a string that is going to store each line of the file//
    string fileLine;
    //make a vector that we are going to return//
    vector<Menu> returningMenu;
    //put it through while loop until we reach the end of the text file//
    while(getline(fin, fileLine)){
        //if the first index char is equal to the '-' then we know that line is the name of the menu//
        if(fileLine[0] == '-'){
            //we store that string into the menuName string without the '-'//
            string menuName = fileLine.substr(1);
            //letting the users know what menu is being added//
            cout << "Adding " << menuName << endl;
            //since we have the menuName we can we run getline to get the menu options//
            getline(fin, fileLine);
            //run that throught the split functions and get it as vector//
            vector<string> contents = split(fileLine, ',');
            //since the menu needs the name and the vector of the contents of the menu option we can just pushback the created menu//
            returningMenu.push_back(Menu(menuName, contents));
            //at this point the menu was sucessfully added so we can let the user know that it was added//
            cout << "Menu " << menuName << " was successfully added!" << endl;
        }
    }
    //close file//
    fin.close();
    //return the vector full of menus//
    return returningMenu;
}

/*
this function reads the system dialogues which is just tutorial and returns the object dialogue
*/
vector<SystemDialogue> readSystemDialogues(string fileName){
    //create inputstream fin//
    ifstream fin;
    //open the file//
    fin.open(fileName.c_str());
    //check if the file opened//
    if(!fin.is_open()){
        //if it failed to open then display error message//
        cout << "Error! " << fileName << " failed to open" << endl;
        //exit function//
        exit(EXIT_FAILURE);
    }
    //rest is just same concept as the readDialogues//
    string fileLine;
    vector<SystemDialogue> returningDialogue;
    bool readFile;
    if(getline(fin, fileLine)){
        readFile = true;
    }
    else{
        readFile = false;
    }
    while(readFile){
        if(fileLine[0] == '-'){
            string dialogueName = fileLine.substr(1);
            cout << "Adding " << dialogueName << endl;
            string stringTotal = "";
            getline(fin, fileLine);
            while(fileLine[0] != '-' && readFile){
                stringTotal += string() + fileLine + " ";
                if(getline(fin, fileLine)){
                    readFile = true;
                }
                else{
                    readFile = false;
                }
            }
            returningDialogue.push_back(SystemDialogue(dialogueName, stringTotal));
            cout << "Dialogue " << dialogueName << " was sucessfully added!" << endl;
        }
    }
    fin.close();
    return returningDialogue;
}

/*
this function reads items and returns the vector full of items
*/
vector<items> readItems(string fileName){
    //basic stuff//
    ifstream fin;
    fin.open(fileName.c_str());
    if(!fin.is_open()){
        cout << "Error! " << fileName << " failed to open" << endl;
        exit(EXIT_FAILURE);
    }
    //same concepts from readingDialogues function//
    string fileLine;
    vector<items> returningVector;
    while(getline(fin, fileLine)){
        vector<string> line = split(fileLine, ',');
        //since the items needs ints for some of the parameters we can convert the strings of certain vectors to ints using stoi//
        returningVector.push_back(items(line[0], line[1], stoi(line[2]), stoi(line[3]), stoi(line[4]), stoi(line[5]), line[6]));
    }
    fin.close();
    return returningVector;
}

/*
reads the monster text file and returns a vector full of monsters
development of the code is the same concept as readItems
*/
vector<monster> readMonster(string fileName){
    ifstream fin;
    fin.open(fileName.c_str());
    if(!fin.is_open()){
        cout << "Error! " << fileName << " failed to open" << endl;
        exit(EXIT_FAILURE);
    }
    string fileLine;
    vector<monster> returningVector;
    while(getline(fin, fileLine)){
        vector<string> line = split(fileLine, ',');
        returningVector.push_back(monster(line[0], stoi(line[1]), stoi(line[2])));
    }
    fin.close();
    return returningVector;
}

/*
reads storage text files and then returns a vector of storages
*/
vector<storage> readStorage(string fileName){
    //developement is the same readMonsters//
    ifstream fin;
    fin.open(fileName.c_str());
    if(!fin.is_open()){
        cout << "Error! " << fileName << " failed to open" << endl;
        exit(EXIT_FAILURE);
    }
    string fileLine;
    vector<storage> returningVector;
    while(getline(fin, fileLine)){
        vector<string> line = split(fileLine, ',');
        returningVector.push_back(storage(line[0], stoi(line[1])));
    }
    fin.close();
    return returningVector;
}

/*
this returns the index location of the vector in the gameStats class
*/
int locateMenu(string menuName, gameStats game){
    //traverse through the gameMenues in the gameStats class//
    for(int i = 0; i < game.getGameMenu().size(); i++){
        //if the gameMenu name matches the string menuName then return the i//
        if(game.getGameMenu()[i].getMenuName() == menuName){
            return i;
        }
    }
    //if it doesnt return i then just return -1//
    return -1;
}

/*
locates the system dialogue in the game class and returns the index of it
*/
int locateSystemDialogue(string dialogueName, gameStats game){
    for(int i = 0; i < game.getGameDialogue().size(); i++){
        if(game.getGameDialogue()[i].getSystemDialgueName() == dialogueName){
            return i;
        }
    }
    return -1;
}

/*
locates the storage in the game<vector> and returns the index
*/
int locateStorage(string storageName, gameStats game){
    for(int i = 0; i < game.getGameStorage().size(); i++){
        if(game.getGameStorage()[i].getStorageType() == storageName){
            return i;
        }
    }
    return -1;
}

/*
this locates the index location of an item in a certain storage
*/
int locateItem(string itemName, storage thisStorage){
    //traverse through the storage but only traversing through exiting items//
    for(int i = 0; i < thisStorage.getStuffInStorage().size(); i++){
        //if the name item name of the storage matches the itemName parameter then return i//
        if(thisStorage.getItemInStorage(i).getItemName() == itemName){
            return i;
        }
    }
    //if it doesnt return i then just return -1//
    return -1;
}

/*
locates the index location of tht item in a player's inventory
*/
int locateItem(string itemName, player currentPlayer){
    for(int i = 0; i < currentPlayer.getStorage().getStorageSize(); i++){
        if(currentPlayer.getStorage().getItemInStorage(i).getItemName() == itemName){
            return i;
        }
    }
    return -1;
}

/*
locates the item from the gameStats class
*/
int locateItem(string itemName, gameStats game){
    for(int i = 0; i < game.getGameItems().size(); i++){
        if(game.getGameItems()[i].getItemName() == itemName){
            return i;
        }
    }
    return -1;
}

/*
generates random item that exists in the game and returns it
*/
items generateItems(gameStats thisGame){
    //get all the items that exists in the game and store each item in the vector//
    vector<items> listOfItems;
    listOfItems = thisGame.getGameItems();
    //select a random index between 0 and the size of the vector of items//
    int randomIndex = rand() % listOfItems.size();
    //return that item in the random index//
    return listOfItems[randomIndex];
}

/*
this generates a random storage with random amount of items//
*/
storage generateStorage(gameStats thisGame){
    //get all the storages in the game and store each storages in a vector//
    vector<storage> listOfStorage;
    listOfStorage = thisGame.getGameStorage();
    //pick a random index of the list of storages//
    int randomIndex = (rand() % (listOfStorage.size() - 1)) + 1;
    //pick a random number of items to put between 1 and size of the storage + 1//
    int randomNumOfItems = (rand() % listOfStorage[randomIndex].getStorageSize()) + 1;
    //fill up the storage with the random amount we picked//
    for(int i = 0; i < randomNumOfItems; i++){
        //call the generate items and add it to the storage//
        listOfStorage[randomIndex].addItemToStorage(generateItems(thisGame));
    }
    //return the storage with the various number of items and items kinds//
    return listOfStorage[randomIndex];
}

/*
generage random monster
developement of this code concept is exactly same as the generateItems function//
*/
monster generateMonster(gameStats thisGame){
    vector<monster> listOfMonster;
    listOfMonster = thisGame.getGameMonster();
    int randomIndex = rand() % (listOfMonster.size());
    return listOfMonster[randomIndex];
}


//since we are changing the data of the class player object we need it to be a reference//
/*
this inventory protocol asks the user what they want do to their player's inventory
they can: 
1. use an item
2. equip an item
3. unquip an item
4. throw away an item
5. cancel the inventory protocol
*/
void inventoryProtocol(gameStats game, player &currentPlayer){
    //first we show the user what the player has//
    currentPlayer.getStorage().displayStorage();
    //then we display the inventory menu option//
    game.getGameMenu()[locateMenu("INVENTORY_MENU", game)].printMenu();
    // we ask the player what option they would like to pick//
    cout << "What would you like to do? ";
    //take the user input//
    int input; cin >> input;
    while(cin.fail()){
        cout << "Invalid input! try again!" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        //first we show the user what the player has//
        currentPlayer.getStorage().displayStorage();
        //then we display the inventory menu option//
        game.getGameMenu()[locateMenu("INVENTORY_MENU", game)].printMenu();
        // we ask the player what option they would like to pick//
        cout << "What would you like to do? ";
        cin >> input;
    }
    //run a switch statement//
    switch(input){
        //if they pick 1 then they want to use an item//
        case 1:{
            //first we want to store the list of items they can use into the vector of items callled available items//
            vector<items> availableItems;
            //list the consumable items the player have in inventory//
            cout << "Consumable Items" << endl;
            cout << "------------------------------------------------------" << endl;
            //traverse through the player's inventory but only up to the total amount of items they have//
            for(int i = 0; i < currentPlayer.getStorage().getStuffInStorage().size(); i++){
                //we check the item type to see if they are either foood, drink, or healing//
                if(currentPlayer.getStorage().getItemInStorage(i).getItemType() == "Food" || currentPlayer.getStorage().getItemInStorage(i).getItemType() == "Drink" || currentPlayer.getStorage().getItemInStorage(i).getItemType() == "Healing"){
                    //if they meet any of the criteria then they can use the item so we add it to the list of available items//
                    availableItems.push_back(currentPlayer.getStorage().getItemInStorage(i));
                }
            }
            //if it turns out none of them are useable items then we let the user know they dont have any by checking the size of avaiable item vector//
            if(availableItems.size() == 0){
                cout << "There are no consumable items. (Press any key to go back)" << endl;
                //put a dummy variable to give user the control to when to continue//
                char dummyVar; cin >> dummyVar;
                //break out of the case 1//
                break;
            }
            //if there are some items in the availableItems vector then proceed normal//
            else{
                //we traverse through the availble items list and then print each items//
                for(int i = 0; i < availableItems.size(); i++){
                    cout << "[" << i + 1 << "]: " << availableItems[i].getItemName() << "(" << availableItems[i].getItemDescription() << ")" << endl;
                }
                //we ask the user which items they want to use but let them know they can cancel by pressing 0//
                cout << "Which item would you like to use? (press 0 to go back)";
                //we implement second input system//
                int input2; cin >> input2;
                while(cin.fail()){
                    cout << "Invalid input! try again!" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    for(int i = 0; i < availableItems.size(); i++){
                        cout << "[" << i + 1 << "]: " << availableItems[i].getItemName() << "(" << availableItems[i].getItemDescription() << ")" << endl;
                    }
                    //we ask the user which items they want to use but let them know they can cancel by pressing 0//
                    cout << "Which item would you like to use? (press 0 to go back)";
                    cin >> input2;
                }
                //first we check if user wants to cancel//
                if(input2 == 0){
                    //if they do then break out of case 1//
                    break;
                }
                //if not proceed normal//
                //check to make sure that the userInput2 range is valid//
                else if(input2 > 0 && input2 <= availableItems.size()){
                    //if it is then we check the item type that they want to use//
                    //if it is food, then we add it to hunger//
                    if(availableItems[input2 - 1].getItemType() == "Food"){
                        //add it to hunger by getting the item restore hunger value//
                        currentPlayer.addHunger(availableItems[input2 - 1].getRestoreHunger());
                        //since we used the item, it must be removed from the players inventory//
                        currentPlayer.removeFromPlayerInventory(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                    }
                    //if it is drink//
                    else if(availableItems[input2 - 1].getItemType() == "Drink"){
                        //then run it through the add thirst and get the thirst value of the item//
                        currentPlayer.addThirst(availableItems[input2 - 1].getRetoreThirst());
                        //remove item once consumed//
                        currentPlayer.removeFromPlayerInventory(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                    }
                    //if not any of those two then it must be healing item//
                    else{
                        //run it through addHp and get the healing value of the item//
                        currentPlayer.addHp(availableItems[input2 - 1].getAmountHeal());
                        //remove after consumed//
                        currentPlayer.removeFromPlayerInventory(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                    }
                    //break out of case 1//
                    break;
                }
                else{
                    //if the input2 is not within the valid range, then let then know and exit case 1//
                    cout << "Invalid choice. Going back to map. (Press any key to continue)";
                    char dummyVar; cin >> dummyVar;
                    break;
                }
            }
        }
        //case 2 means that they want to equip an item//
        case 2:{
            //same thing, make a vector of available items//
            vector<items> availableItems;
            cout << "Equippable Items" << endl;
            cout << "------------------------------------------------------" << endl;
            for(int i = 0; i < currentPlayer.getStorage().getStuffInStorage().size(); i++){
                //if the item type is weapon then we add it to the vector of available items//
                if(currentPlayer.getStorage().getItemInStorage(i).getItemType() == "Weapon"){
                    availableItems.push_back(currentPlayer.getStorage().getItemInStorage(i));
                }
            }
            //check if there are any availble items by checking the size of the vector availble times//
            if(availableItems.size() == 0){
                //let the users know//
                cout << "There are no available items to equip.(Press any key to go back). ";
                //dummy var to give the user a control//
                char dummyVar; cin >> dummyVar;
                //break out of case two//
                break;
            }
            //if it isnt empty then proceed normal//
            else{
                //print out the available items//
                for(int i = 0; i < availableItems.size(); i++){
                    cout << "[" << i + 1 << "]: " << availableItems[i].
                    getItemName() << endl;
                }
                //ask the user for which item they want to equip//
                cout << "Which item would you like to equip?(press 0 to go back) ";
                int input2; cin >> input2;
                while(cin.fail()){
                    cout << "Invalid input! try again!" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    //print out the available items//
                    for(int i = 0; i < availableItems.size(); i++){
                        cout << "[" << i + 1 << "]: " << availableItems[i].
                        getItemName() << endl;
                    }
                    //ask the user for which item they want to equip//
                    cout << "Which item would you like to equip?(press 0 to go back) ";
                    cin >> input2;
                }
                //check if the user wants exit//
                if(input2 == 0){
                    //break out of case 2
                    break;
                }
                //make sure the answer is within the valid range//
                else if(input2 > 0 && input2 <= availableItems.size()){
                    //first check if the player has an item equipped//
                    if(!currentPlayer.getEquipStatus()){
                        //if they dont then just equip item that they inputted//
                        currentPlayer.equipItem(availableItems[input2 - 1]);
                        //after equipped it must be removed from the player's inventory//
                        currentPlayer.removeFromPlayerInventory(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                    }
                    else{
                        //if they already have an item equipped then make a temp item and store the item they want to equip//
                        items tempItem = currentPlayer.getStorage().getItemInStorage(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                        //then delete the item they want to eqiup//
                        currentPlayer.removeFromPlayerInventory(locateItem(availableItems[input2 - 1].getItemName(), currentPlayer));
                        //and then unequip weapon and then add that weapon to the playere's inventory//
                        currentPlayer.addFromPlayerInventory(currentPlayer.unequipItems());
                        //then equip the temp item to the player//
                        currentPlayer.equipItem(tempItem);
                    }
                    //break out of case 2//
                    break;
                }
                //if the input is none of the above then its invalid and let the user know//
                else{
                    cout << "Invalid choice. Going back to map. (Press any key to continue) ";
                    //give temp var to give users control
                    char dummyVar; cin >> dummyVar;
                    //break out fo case 2//
                    break;
                }
            }
        }
        //case 3 means that the player wants to unquip items//
        case 3:{
            //first check if the player has enougb storage space to unquip item//
            if(currentPlayer.getStorage().getStuffInStorage().size() == currentPlayer.getStorage().getStorageSize()){
                //if not then let the user know//
                cout << "------------------------------------------------------" << endl;
                cout << "Error, player inventory full! please delete an item first before unequipping" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << "Press any key to continue... ";
                //give the users control with dummy var//
                char dummyVar; cin >> dummyVar;
                //break out of case 3//
                break;
            }
            //then check if player even has an item//
            else if(!currentPlayer.getEquipStatus()){
                //if not then let the user know//
                cout << "------------------------------------------------------" << endl;
                cout << "No items are equipped currently. Press any key to exit... ";
                cout << "------------------------------------------------------" << endl;
                cout << "Press any key to continue... ";
                //dummy var to give player control//
                char dummyVar; cin >> dummyVar;
                //break out of case 3//
                break;
            }
            //if passing all condition then proceed to remove item//
            else{
                //remove the item and then add it to the player inventory//
                currentPlayer.addFromPlayerInventory(currentPlayer.unequipItems());
                //break out of case 3//
                break;
            }
        }
        //case 4 is player wants to remove an item from storage//
        case 4: {
            //first check if they have any items//
            if(currentPlayer.getStorage().getStuffInStorage().size() != 0){
                //if they do then list out the items they have//
                for(int i = 0; i < currentPlayer.getStorage().getStuffInStorage().size(); i++){
                    cout << "[" << i + 1 << "]: " << currentPlayer.getStorage().getItemInStorage(i).getItemName() << endl;
                }
                //ask the user what they want to remove and give them the option to go back//
                cout << "Which item would you like to remove?(Press 0 to go back) " << endl;
                cout << "------------------------------------------------------" << endl;
                //ask user input//
                int input; cin >> input;
                while(cin.fail()){
                    cout << "Invalid input! try again!" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    //if they do then list out the items they have//
                    for(int i = 0; i < currentPlayer.getStorage().getStuffInStorage().size(); i++){
                        cout << "[" << i + 1 << "]: " << currentPlayer.getStorage().getItemInStorage(i).getItemName() << endl;
                    }
                    //ask the user what they want to remove and give them the option to go back//
                    cout << "Which item would you like to remove?(Press 0 to go back) " << endl;
                    cout << "------------------------------------------------------" << endl;
                    cin >> input;
                }
                //check if they want to cancel//
                if(input == 0){
                    //break out of case 4//
                    break;
                }
                //check if the input is within valid range//
                if(input > 0 && input <= currentPlayer.getStorage().getStuffInStorage().size()){
                    //if it is then remove it from player inventory//
                    currentPlayer.removeFromPlayerInventory(input - 1);
                    //break out of case 4//
                    break;
                }
            }
            //if they dont have anything in their inventory/
            else{
                // let them know that they dont have any items//
                cout << "Nothing in player inventory to remove" << endl;
                //break out of case 4//
                break;
            }
        }
        //case 5 means they want to exit//
        case 5: {
            //let them know that they are exiting the player inventory menu//
            cout << "Exiting" << endl;
            //break out of case 5//
            break;
        }
        //any other answer is not applicable//
        default: {
            //so let them know that the answer is not appliacble and exit//
            cout << "Invalid input, Exiting..." << endl;
            //break out of default//
            break;
        }
    }
}

/*
Shows the random loot you can grab after defeating a monster
Lets you grab loot
add item to storage
swap item
leave with grabbing nothing
*/
void lootingProtocol(gameStats game, player &currentPlayer){
    storage randomLoot = generateStorage(game); // Creates an object that also is equal to a random number of items and random items
    bool keepRunning = true;
    while(keepRunning){ // Make sure this protocol runs until the user chooses to quit looting the monster
        randomLoot.displayStorage(); // Displays the loot the person can grab
        game.getGameMenu()[locateMenu("LOOTING_MENU", game)].printMenu(); // Showing the menu of the looting system showing the choices they can make
        cout << "What would you like to do? (press 0 to access your inventory) ";
        int input; cin >> input;
        while(cin.fail()){
            cout << "Invalid input! try again!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            randomLoot.displayStorage(); // Displays the loot the person can grab
            game.getGameMenu()[locateMenu("LOOTING_MENU", game)].printMenu(); // Showing the menu of the looting system showing the choices they can make
            cout << "What would you like to do? (press 0 to access your inventory) ";
            cin >> input;
        }
        if(input == 0){ // PLayer chose to open there inventory and goes down this string
            inventoryProtocol(game, currentPlayer);
        }
        else{ // Player chose the option to loot the monster or leave the monster or gave an invalid input
            switch(input){
                case 1:{ // Player chose to take an item
                    if(currentPlayer.getStorage().getStuffInStorage().size() >= currentPlayer.getStorage().getStorageSize()){ // Checking to make sure the inventory on the player is full or not so they can't grab more than what's avialable 
                        cout << "Your storage is full!! throw an item away or make room to add more stuff in your inventory!" << endl;
                        break; // Breaks out of switch and reasks user what they want to do with the lot
                    }
                    else{
                        randomLoot.displayStorage(); // Shows loot to player again 
                        cout << "What would you like to add? (press 0 to cancel)" << endl;
                        int input2; cin >> input2;
                        while(cin.fail()){
                            cout << "invalid input! try again!" << endl;
                            cin.clear();
                            cin.ignore(256, '\n');
                            randomLoot.displayStorage(); // Shows loot to player again 
                            cout << "What would you like to add? (press 0 to cancel)" << endl;
                            cin >> input2;
                        }
                        if(input2 == 0){ // User chose to not add anything
                            cout << "canceled" << endl;
                            break;
                        }
                        else{
                            if(input2 > 0 && input2 <= randomLoot.getStuffInStorage().size()){ // Checking to see whether the input is greater than 0 and the input given isn't an empty spot with nothing in it
                                currentPlayer.addFromPlayerInventory(randomLoot.getItemInStorage(input2 - 1)); // Adds the item to the users inventory
                                randomLoot.removeStuffToStorage(locateItem(randomLoot.getItemInStorage(input2 - 1).getItemName(), randomLoot)); // Removes the item from the loot of the monster
                                break;
                            }
                            else{ // Player input a invalid value
                                cout << "Invalid input!!" << endl;
                                break;
                            }
                        }
                    }
                }
                case 2:{ // Player chose to add an item to the storage
                    if(randomLoot.getStuffInStorage().size() >= randomLoot.getStorageSize()){ // Making sure the players inventory isn't full
                        cout << "Looting storage full!! Take some items before adding to the loot storage!" << endl;
                        break;
                    }
                    else{ // Players inventory isn't full and can add an item to storage
                        int input2; cin >> input2;
                        while(cin.fail()){
                            cout << "invalid input! try again!" << endl;
                            cin.clear();
                            cin.ignore(256, '\n');
                            currentPlayer.getStorage().displayStorage(); // shows the player storage and whats in there storage
                            cout << "What would you like to add to the storage? (press 0 to cancel)" << endl;
                            cin >> input2;
                        }
                        if(input2 == 0){ // Player chose to not add anything and cancel the action
                            cout << "canceled;" << endl;
                            break;
                        }
                        else{
                            if(input2 > 0 && input2 <= currentPlayer.getStorage().getStuffInStorage().size()){ // making sure the user choosing the item to swap isn't a blank space with nothing in it
                                randomLoot.addItemToStorage(currentPlayer.getStorage().getItemInStorage(input2 - 1)); // Adding the item to the storage
                                currentPlayer.removeFromPlayerInventory(input2 - 1); // Removes item from the players inventory
                                break;
                            }
                            else{ // User input an invalid value
                                cout << "Invalid input!!" << endl;
                                break;
                            }
                        }
                    }
                }
                case 3:{ // Player chose to swap items
                    randomLoot.displayStorage(); // Displays the storage of the loot box
                    cout << "What would you like to take? (press 0 to cancel)" << endl;
                    int input2; cin >> input2;
                    while(cin.fail()){
                        cout << "invalid input! try again!" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        randomLoot.displayStorage(); // Displays the storage of the loot box
                        cout << "What would you like to take? (press 0 to cancel)" << endl;
                        cin >> input2;
                    }
                    if(input2 == 0){ // User chose to cancel this action
                        cout << "canceled" << endl;
                        break;
                    }
                    else{ // User chose to proceed with this action
                        if(input2 > 0 && input2 <= randomLoot.getStuffInStorage().size()){ // Making sure user isn't trying to swap an item that isn't there
                            items tempItemFromLoot = randomLoot.getItemInStorage(input2 - 1); // sets the item that the player would like to take
                            randomLoot.removeStuffToStorage(locateItem(randomLoot.getItemInStorage(input2 - 1).getItemName(), randomLoot)); // Removes the item to the storage
                            currentPlayer.getStorage().displayStorage(); // Displays the stroage of the player
                            cout << "What would you like to replace it with?(press 0 to cancel)" << endl;
                            int input3; cin >> input3;
                            while(cin.fail()){
                                cout << "invalid input! try again!" << endl;
                                cin.clear();
                                cin.ignore(256, '\n');
                                currentPlayer.getStorage().displayStorage(); // Displays the stroage of the player
                                cout << "What would you like to replace it with?(press 0 to cancel)" << endl;
                                cin >> input3;
                            }
                            if(input3 == 0){ // User chose to not replace it with anything
                                cout << "canceled;" << endl;
                                break;
                            }
                            else{ // User chose to replace the item
                                if(input3 > 0 && input3 <= currentPlayer.getStorage().getStuffInStorage().size()){ // Making sure the item he is exchanging is an actual item and not a blank spot
                                    items tempItemfromInventory = currentPlayer.getStorage().getItemInStorage(input3 - 1); // creates a temp variable of the item the player is swapping from his inventory
                                    currentPlayer.removeFromPlayerInventory(input3 - 1); // Removes the item from the player inventory
                                    randomLoot.addItemToStorage(tempItemfromInventory); // Adds the item to the storage of the loot box
                                    currentPlayer.addFromPlayerInventory(tempItemFromLoot); // Adds the item the player wanted to swap from the loot box into his inventory
                                    break;
                                }
                                else{ // User input an invalid option
                                    cout << "Invalid input!!" << endl;
                                    break;
                                }
                            }
                            break;
                        }
                        else{ // User chose an invalid option
                            cout << "Invalid input!!" << endl;
                            break;
                        }
                    }
                }
                case 4:{ // User chose to not grab anything and go back to moving around the map
                    cout << "Exiting" << endl;
                    keepRunning = false; // Exits loop and leaves lea
                    break;
                }
                default:{
                    cout << "Invalid input!!" << endl;
                    break;
                }
            }
        }
    }
}

/*
Determines a random monster the player is going to fight
Determines what the user wants to do
    attack
    block
    flee
    do nothing
determines a random chance the playerh hits the monster
determines a random chance the monster misses the player
*/
void fightingProtocol(gameStats &thisGame, player &currentPlayer){
    monster randomMonster = generateMonster(thisGame); // Grabs a random monster from the text file of monsters we have
    cout << "You've encountered a " <<  randomMonster.getMonsterName() << "! MAY THE LUCK BE IN YOUR FAVOR O_O" << endl; // Tells user what type of monster they are fighting
    cout << "The " << randomMonster.getMonsterName() << " does " << randomMonster.getMonsterDamage() << " be careful!" << endl; // Tells the user how much damage the monster does
    while(currentPlayer.getCurrentHp() > 0 && randomMonster.getCurrentHp() > 0 ) { // Makes sure to keep running this program till either the player or the monster is dead
        srand(time(NULL)); // Doing this to allow for us to create random chance of attacking
        cout << "======================================================" << endl;
        cout << "HP: " << currentPlayer.getCurrentHp() << "/" << currentPlayer.getMaxHp() << " Dmg: " << currentPlayer.getTotalDmg() << " " << randomMonster.getMonsterName() << " HP: " << randomMonster.getCurrentHp() << "/" << randomMonster.getMaxHp() << endl; // Interface to show the user stats after each move they make against the monster
        thisGame.getGameMenu()[locateMenu("FIGHTING_MENU", thisGame)].printMenu(); // Prints out options on what the player could do against the monster aka attack, defend, do nothing, or flee
        cout << "What would you like to do? (press 0 to access inventory)" << endl; // shows player they can access their inventory
        int userInput; cin >> userInput; // takes user input
        //make sure that the user input is an int rather than anything else//
        while(cin.fail()) {
            cout << "Invalid input! try again!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            srand(time(NULL)); // Doing this to allow for us to create random chance of attacking
            cout << "======================================================" << endl;
            cout << "HP: " << currentPlayer.getCurrentHp() << "/" << currentPlayer.getMaxHp() << " Dmg: " << currentPlayer.getTotalDmg() << " " << randomMonster.getMonsterName() << " HP: " << randomMonster.getCurrentHp() << "/" << randomMonster.getMaxHp() << endl; // Interface to show the user stats after each move they make against the monster
            thisGame.getGameMenu()[locateMenu("FIGHTING_MENU", thisGame)].printMenu(); // Prints out options on what the player could do against the monster aka attack, defend, do nothing, or flee
            cout << "What would you like to do? (press 0 to access inventory)" << endl; // shows player they can access their inventory
            cin >> userInput;
        }
        bool attemptedToFlee = false;
        bool fleeSucessful = false;
        if(userInput == 0){ // determines whether player chose to access their inventory
            inventoryProtocol(thisGame, currentPlayer);
        }
        switch(userInput){ 
            case 1:{ // Player chose to attack
                cout << "Attacking..." << endl;
                int attackChance = rand() % 10; // Chooses a random number between 0 and 9
                if(attackChance >= 0 && attackChance < 7){ // If number is between 0 and 7 then the player will successfully attack the monster
                    cout << "Success!" << endl;
                    randomMonster.reduceCurrentMonstHp(currentPlayer.getTotalDmg()); //reduces monster hp by the total amount of damage the player deals
                }
                else{ // PLayer missed
                    cout << "YOU MISSED!!" << endl;
                }
                if(randomMonster.getCurrentHp() > 0){ // As long as monster is alive it will attack the player
                    int monsterAttackChance = rand() % 2; // Chooses a number randomly between 0 and 1
                    if(monsterAttackChance == 0){ // If number choosen is 0 then the attack is successful
                        currentPlayer.reduceHp(randomMonster.getMonsterDamage()); // Reduces the health of the player by the total amount of damage the monster does
                        cout << "Monster did " << randomMonster.getMonsterDamage()<< " damage to you!" << endl; // prints out the amount of damage the monster did to you
                    }
                    else{ // monster missed
                        cout << "You're a lucky person don't bank on him missing again" << endl;
                    }
                    break;
                }
                else{ // Monster is dead so it breaks the switch and out of the fighting protocol
                    break;
                }
            }
            case 2:{ // Player choose to defend
                cout << "Defending" << endl;

                int monsterAttackChance = rand() % 2; // Chooses number 0 or 1
                if(monsterAttackChance == 0){ // If number is 0 then the monster will attack
                    currentPlayer.reduceHp(randomMonster.getMonsterDamage() / 2); // Monster only does half damage but still reduces players health
                    cout << "Monster did " << randomMonster.getMonsterDamage() / 2 << " damage to you!" << endl; // Shows how much damage the monster did
                }
                else{ // monster missed
                    cout << "You're a lucky person don't bank on him missing again" << endl;
                }
                
                break;
            }
            case 3:{ // Player chose to do nothing
                cout << "Doing nothing..." << endl;

                int monsterAttackChance = rand() % 2; // Chooses either 1 or 2 randomly
                if(monsterAttackChance == 0){ // Number was 0 and the monster will attack
                    currentPlayer.reduceHp(randomMonster.getMonsterDamage()); // Reduces player Hp 
                    cout << "Monster did " << randomMonster.getMonsterDamage() << " damage to you!" << endl; // Shows how much damage was done
                }
                else{ // Monster missed
                    cout << "You're a lucky person don't bank on him missing again" << endl;
                }
                break;
            }
            case 4:{ // Player chose to flee
                cout << "Attempting to Flee..." << endl;
                attemptedToFlee = true;
                int fleeChance = rand() % 4; // Picks a random number between 0 and 3
                if(fleeChance == 0){ // If number is 0 then the player succesfully fleed away from the monster
                    fleeSucessful = true;
                    cout << "You got some ZOOMIES, flee successful" << endl;
                }
                else{ // Flee failed
                    cout << "Flee failed! get faster" << endl;

                }


                if(fleeSucessful){ // determineing whether flee was successful and returns out of this function leaving this protocol since we aren't fighting the monster anymore
                    return;
                }
                else if(!fleeSucessful || attemptedToFlee){ // If flee wasn't successfull then the monster will have a chance at attacking you but at double damage
                    cout << "Monster angry! about to do double damage" << endl;
                    int monsterAtackChance = rand() % 2; // chooses a number between 0 and 1
                    if(monsterAtackChance == 0){ // Number was 0 and the attack by the monster was successful
                        currentPlayer.reduceHp(2 * randomMonster.getMonsterDamage()); // reduces player hp by double the normal amount
                        cout << "Monster did " << 2 * randomMonster.getMonsterDamage() << " damage to you!" << endl; // showing the amount of damage the monster did
                    }
                    else{ // The monster missed
                        cout << "monster missed his attack. you a lucky turd" << endl;
                    }
                }
            }
        }
        thisGame.increaseNumOfTurns(); // Increases the number of turns since fighting a monster and the choice you make will count as one turn
    }
    if(currentPlayer.getCurrentHp() > 0){ // Determining whether the player killed the monster
        lootingProtocol(thisGame, currentPlayer); // Goes into looting protocol if player did kill the monster to get items from the monster
    }
}

/*
Keeps track of your hunger and thirst and decreases it by 1 after every 3 turns also decreases your health once your thirst or hunger is at 0
Also shows stats of the indiviual after each turn including their health, Damage, What turn they are on, plus there thirst and hunger
Allows you access your inventory and show you can access it
Determines when you are on a safe spot
Determines when you are on a spot with a monster
*/
void gameRunning(gameStats &game, player &currentPlayer, Map &map){
    if(game.getNumOfTurns() != 0 && game.getNumOfTurns() % 3 == 0){ // Reduces your hunger and thirst every 3 turns and checks this through this condition and also makes sure you automatically don't lose hunger and thirst right when you start the game
        currentPlayer.reduceHunger(1); // Reduces hunger by 1
        currentPlayer.reduceThrist(1); // Reduces thirst by 1
        if(currentPlayer.getCurrentHunger() <= 1){ // When hunger is 1 it reminds you to eat or you will lose some hp
            cout << "You are starving!! eat something before you lose HP!!" << endl;
        }
        if(currentPlayer.getCurrentThirst() <= 1){ // When thirst is 1 it reminds you to drink or you will lose some hp
            cout << "You are thirsty!! drink something before you lose HP!!" << endl;
        }
    }
    char move;
    cout << "======================================================" << endl;
    map.displayMap(); // Displays the map to the user
    cout << "------------------------------------------------------" << endl;
    cout << "health: " << currentPlayer.getCurrentHp() << "/" << currentPlayer.getMaxHp() << " Dmg: " << currentPlayer.getTotalDmg() << "       Turn:" << game.getNumOfTurns() << " H:" << currentPlayer.getCurrentHunger() << " T:" << currentPlayer.getCurrentThirst() << endl; // Displays the Health, Damage, Turn, Hunger, Thirst of the player at that moment in time
    cout << "------------------------------------------------------" << endl;
    cout << "Valid moves are: " << endl;
    map.displayMoves(); // Displays what moves are available to them at that exact momeny
    cout << "input a move (press 'i' to access player inventory.) " << endl; // Shows player they can access their inventory by pressing i
    cin >> move;
    if(move == 'i'){ // If the person chooses to access their inventory then it brings them to this statement
        inventoryProtocol(game, currentPlayer); // Uses this function to print the inventory to the person and what is stored in it and what they can do with it
    }
    else{
    
        bool validMove = map.executeMove(move); // Allows player to move 
        if(validMove){
            game.increaseNumOfTurns();
        }
        if (map.isSafeSpotLocation()) { // If user lands on a safespot this determines whether they have or not 
            int choice;
            bool valid = true;

            cout << "You're on a Safe Spot! TIME FOR AN UPGRADE" << endl; // Shows them what this means being on the safe spot

            while (valid == true) { // Creates loop to make sure the player chooses an upgrade
                game.getGameMenu()[locateMenu("UPGRADE_MENU", game)].printMenu(); // Prints out the options for the upgrades such as health and damage
                cin >> choice; // takes user choice

                
                switch (choice){ 
                    case 1: // Player chose to increase health
                        currentPlayer.addMaxHp(1); // Increases hp by 1
                        currentPlayer.setHp(currentPlayer.getMaxHp()); // Resets hp back to the max hp
                        valid = false; // breaks out of the loop
                        break;
                    
                    case 2: // Player chose to increase damage
                        currentPlayer.setHp(currentPlayer.getMaxHp()); // Resets user hp back to max
                        currentPlayer.addBaseDamage(1); // Increases user damage by 1
                        valid = false; // Breaks out of the loop
                        break;
                    
                    default: // Player chose an invalid option
                        cout << "Invalid Input." << endl;
                        break;
                        
                }
            }
        }
        if (map.isMonsterLocation()) { // Determines whether the player is on the same spot as a monster
            fightingProtocol(game, currentPlayer); // Uses function to fight monster
        }
    }
    if(currentPlayer.getCurrentHunger() < 1 || currentPlayer.getCurrentThirst() < 1){ // Determines whether hunger or thirst is 0 to subtract hp from the player till both those conditions are higher than 0
        currentPlayer.reduceHp(1); // reduces player hp
    }
}

/*
Reads from the file of scores that were added to it from the addToSCoreList function and prints it to the user in the correct order from lowest to highest
*/
void getScores(){
    ifstream fin; // Creates a file that can read the text file
    fin.open("scoreList.txt"); // Opening the file with all the scores in it
    if(fin.fail()){ // Making sure the file opens and doesn't fail to open
        cout << "Error!! file failed to open!!" << endl;
        exit(EXIT_FAILURE);
    }
    string fileLine; // Creating a temp string
    vector<int> scores; // Creating a vector to store the scores in
    while(getline(fin, fileLine)){ // Using a loop to read through the whole file line by line
        if(fileLine != ""){ // As long as the line isn't empty then it will add the score to the vector
            scores.push_back(stoi(fileLine)); // stores the string and converts to a vector since we want to get it as an integer since its a score that we need to sort
        }
    }
    vector<int> sortedScores = quickSort2(scores, 0, scores.size() - 1); // Creating a vector that set to our function that returns the numbers soreted from least highest to highest
    for(int i = 0; i < sortedScores.size(); i++){ // Prints each score
        cout << sortedScores[i] << endl;
    }
}

/*
Takes the score of the user that they get at the end of a game
creates a file that it can write to
*/
void addToScoreList(int newScore){
    ofstream fout; // creating a file that it can write out too
    fout.open("scoreList.txt", ios :: app); // Opens up the file we want it to write to and making sure that it keeps opening up the same file each time this function is called so it doesn't reopen and make a new file each time
    if(fout.fail()){ // maming sure the file doesn't fail to open
        cout << "File failed to Open!!" << endl;
        exit(EXIT_FAILURE);
    }
    fout << newScore << endl; // prints the score the user got to the file
    fout.close();
}

/*
This will start the game by spawning the monsters and the safespots randomly through the game
It makes sure the game keeps running till player health is less than 0 meaning they are dead
Once player is dead it shows them there score which is the number of turns they lived through or if player hits 999 turns then it exits the game and they won and it will show the score

*/
void startGameProtocol(gameStats game){
    srand(time(NULL)); // Allowing for the use of random number to be generated so the game is different anytime 
    player test = player(); // intiializing test to the class player
    test.setStorage(game.getGameStorage()[locateStorage("Player Inventory", game)]); // Allowing us to access the inventory of the player
    Map map;
    int safeSpotCount = 0;
    int maxMonster = rand() % 101 + 400; // Making a random number of monsters between 401 and 500
    while (safeSpotCount <= 30){ // Makes 30 random generated safespots on the map
        int row = rand() % 20;
        int column = rand() % 30;
 
        map.spawnSafeSpot(row, column); // spawns the safe spots
        safeSpotCount++;
    }
 
    for (int i = 0; i < maxMonster; i++){ // spawning the monsters into the map
        int row = rand() % 20; 
        int column = rand() % 30;
 
        map.spawnMonster(row, column); // spawning them into the map
    }
    
    while(test.getCurrentHp() > 0){ // Makes sure to keep running the game if the player has more than 0 hp
        if (game.getNumOfTurns() == 999){ // If player lives after 999 turns then it will exit the loop even though he is still alive
            break;
        }
        
        gameRunning(game, test, map); // Function that displays the game
    }

    if (test.getCurrentHp() <= 0){ // Checking to see whether the person died
        cout << "you have died! game over!!" << endl;
    }
    else { // Person is still alive and lived for 999 turns
        cout << "You beat our game! CONGRATS GET A LIFE" << endl;
    }

    cout << "Your score was " << game.getNumOfTurns() << "!" << endl; // Displaying the number of turns they lived aka there score
    addToScoreList(game.getNumOfTurns()); // Adding the sturns to a seperate file 
    int input = 0;
    while(input != 1 && input != 2){ // Making a loop to make sure the player enters a valid number that either exits the game or shows them there scores and then exits the game
        cout << "------------------------------------------------------" << endl;
        cout << "Would you like to see your scores?" << endl;
        cout << "------------------------------------------------------" << endl;
        game.getGameMenu()[locateMenu("END_MENU", game)].printMenu(); // Pulling up the end game menu from a text file that we have saved
        cin >> input; // takes user input
        if(input == 1){ //User chose to see there high scores
            cout << "                    HIGHSCORES" << endl;
            cout << "======================================================" << endl;
            getScores(); // Prints the scores to the user
            break;
        }
        else if(input == 2){ // User input a invalid number/option thus it re asks them the question
            break;
        }
        else{
            cout << "It was a yes or no question... how can you mess this up...retry and maybe you won't mess it up this time." << endl;
        }
    }
}

/*
Determining whether the user would like to get a little tutorial of the game before they start or just go right into starting the game
*/
void startProtocol(gameStats game){
    vector<Menu> menues = game.getGameMenu();
    game.getGameMenu()[locateMenu("SECONDARY_MENU", game)].printMenu(); // Grabs the text to determine and show the choices on whether they want to start the game or get a tutorial for the game before starting
    cout << "Enter your choice: " << endl;
    int userInput; cin >> userInput;
    switch(userInput){
        case 1:{ // User chose to get the tutorial
            game.getGameDialogue()[locateSystemDialogue("TUTORIAL", game)].printDialogueContent(); // gets the tutorial dialouge to show to the user
            startGameProtocol(game); // starts the game
            break;        
            }
        case 2:{
            startGameProtocol(game); // starts the game
            break;
        }
    }
}

/*
This asks the user whether they want to start playing the game or to quit out of the game
*/
void mainMenuProtocol(gameStats game){
    game.getGameMenu()[locateMenu("MAIN_MENU", game)].printMenu();
    cout << "Enter your choice: ";
    int userInput; cin >> userInput;
    switch(userInput){
        case 1: {startProtocol(game); break;} // They chose to start the game and the program enters the starting protocol of the game
        case 2: { // Player chose to exit the game and it quits the program
            cout << "Exiting game. Thank you for playing" << endl;
            exit(EXIT_SUCCESS);
            break;}
        default:{ // User inputed a number that wasn't one of the choices and then reruns this code asking whether the player wants to exit or play the game
            cout << "Invalid Input: Please Try again." << endl;
            mainMenuProtocol(game);
        }
    }
}

/*

*/
int main(){
    cout << "Loading game..." << endl;
    vector<Menu> menues = readMenues("mainMenu.txt"); // Reads all the different menus we have and puts them into vectors
    vector<SystemDialogue> systemDialogues = readSystemDialogues("systemDialogues.txt"); // Reads our tutorial text and puts it into a vector
    cout << "Loading storages..." << endl;
    vector<storage> storages = readStorage("storage.txt"); // Reads the different storages such as player inventory and what type of chest and the size of that chest and puts it into a vector
    cout << "Sucess!" << endl;
    cout << "Loading items..." << endl;
    vector<items> item = readItems("items.txt"); // Reads the different items and puts it into a vector
    cout << "Sucess!" << endl;
    cout << "Loading monsters..." << endl;
    vector<monster> monster = readMonster("monsters.txt"); // Reads the different monsters and puts it into a vecoty
    cout << "Sucess!" << endl;
    gameStats test = gameStats(item, menues, storages, monster, systemDialogues); // Creates the game with all the different things needed such as items, the menues displayed, the storage of loot chest and player inventory, the monsters in the game, and the tutorial system
    mainMenuProtocol(test); // Starts the game

    bool valid = true;
    int choice;

    while(valid){ // Creates a loop to allow the user to keep on replaying the game after he dies or beats it
        cout << "------------------------------------------------------" << endl;
        cout << "Do you want to play the game again?" << endl;
        cout << "------------------------------------------------------" << endl;
        test.getGameMenu()[locateMenu("RESTART_GAME", test)].printMenu(); // Shows the menu giving the u
        cin >> choice;

        if (choice == 1){
            mainMenuProtocol(test);
        }
        else{
            cout << "------------------------------------------------------" << endl;
            cout << "Thanks for playing the game!" << endl;
            cout << "------------------------------------------------------" << endl;
            break;
        }
    }
    return -1;
}