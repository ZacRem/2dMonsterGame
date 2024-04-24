#include <iostream>
#include <vector>
#include "systemDialogue.h"
 
using namespace std;

SystemDialogue :: SystemDialogue(){
    dialogueName = "";
    dialogueContent = "";
}

SystemDialogue :: SystemDialogue(string setDialogueName, string setDialogueContent){
    dialogueName = setDialogueName;
    dialogueContent = setDialogueContent;
}

string SystemDialogue :: getSystemDialgueName(){
    return dialogueName;
}

string SystemDialogue :: getSystemDialgueContent(){
    return dialogueContent;
}

void SystemDialogue :: printDialogueContent(){
    //make a variable that will hold word count//
    int wordCount;
    //check if there are anything in the content//
    if(dialogueContent.size() != 0){
        //if there are then we know that there is at least one word//
        wordCount++;
    }
    //traverse through the string//
    for(int i = 0; i < dialogueContent.size(); i++){
        //check if there is space//
        if(dialogueContent[i] == ' '){
            //if there is space then that was a word//
            wordCount++;
        }
    }
    //make a variable that tracks words//
    int wordTracker = 1;
    //make a variable that tracks the index//
    int stringIndex = 0;
    //make a loop that will print 20 words at a time//
    for(int i = 0; i < wordCount / 20; i++){
        while(wordTracker < 21){
            cout << dialogueContent[stringIndex];
            if(dialogueContent[stringIndex] == ' '){
                wordTracker++;
            }
            stringIndex++;
        }
        cout << "..." << endl;
        cout << "Press anykey to continue" << endl;
        string userInput; cin >> userInput;
        wordTracker = 1;
    }
    //print out the remainder of the contents//
    if(wordCount % 20  != 0){
        while(wordTracker < wordCount % 20){
            cout << dialogueContent[stringIndex];
            if(dialogueContent[stringIndex] == ' '){
                wordTracker++;
            }
            stringIndex++;
        }
    }
    cout << endl;
    cout << "Press any key to continue" << endl;
    string userInput; cin >> userInput;
}