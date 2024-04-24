#ifndef ITEMS_H
#define ITEMS_H
#include <string>

using namespace std;

class items{
    private:
        string itemName;
        string itemType;
        string itemDescription;
        int amountHeal;
        int restoreThirst;
        int restoreHunger;
        int bonusDamage;

    public:

        // Constructors
        items();
        items(string itemName, string itemType, int bonusDamage, int itemHeal, int setRestoreThirst, int setRestoreHunger, string itemDescription);

        // Getters
        string getItemName();
        string getItemType();
        int getBonusDamage();
        int getAmountHeal();
        int getRetoreThirst();
        int getRestoreHunger();
        string getItemDescription();

        // Setters
        void setItemName(string newItemName);
        void setItemType(string newItemType);
        void setItemBonusDamage(int newBonusDamage);
        void setAmountHeal(int newHeal);
        void setItemDescription(string newItemDescription);
        void setRestoreThirst(int newRestoreThirst);
        void setRestoreHunger(int newRestoreHunger);
};

#endif