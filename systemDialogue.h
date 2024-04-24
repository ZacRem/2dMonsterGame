#ifndef SYSTEMDIALOGUE_H
#define SYSTEMDIALOGUE_H
#include <iostream>
#include <vector>

using namespace std;

class SystemDialogue{
    private:
        string dialogueName;
        string dialogueContent;
    public:
        //basic constructors//
        SystemDialogue();
        SystemDialogue(string setDialogueName, string setDialogueContent);
        //getters//
        string getSystemDialgueName();
        string getSystemDialgueContent();
        //prints out the dialogue content 20 words at a time//
        void printDialogueContent();
};

#endif