#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "storage.h"
#include "items.h"

class player{
    private:
        int maxHp;
        int currentHp;
        int baseDamage;
        int money;
        int maxHunger = 20;
        int maxThirst = 20;
        int currentHunger;
        int currentThirst;
        storage playerStorage;
        items equipped;
        bool itemEquipped = false;
    public:
        // Constructors
        player();
        player(int maxHp, int baseDamage, int money, storage newStorage);

        // Players HP
        void addMaxHp(int newMaxHp);
        void addHp(int hp);
        void reduceHp(int hp);
        void setHp(int hp);
        int getCurrentHp();
        int getMaxHp();

        // Getters for thirst and hunger
        int getCurrentHunger();
        int getCurrentThirst();

        // Players storage/inventory
        storage getStorage();
        void setStorage(storage newStorage);
        void updateStorage(vector<items> newStorage);
        void removeFromPlayerInventory(int location);
        void addFromPlayerInventory(items thisItem);

        // Player Damage
        int getTotalDmg();
        void addBaseDamage(int baseDamage);
        void reduceBaseDamage(int baseDamge);
        void setBaseDamage(int baseDamage);
        int getBaseDamage();

        // Player Hunger
        void reduceHunger(int minusHunger);
        void addHunger(int plusHunger);

        // Player thirst
        void reduceThrist(int minusThirst);
        void addThirst(int plusThirst);

        // Player Money (decided not to implement this but to lazy to take out)
        int getMoney();
        void setMoney(int newMoney);

        // Player Items
        items getEquippedItem();
        items unequipItems();
        void equipItem(items equipping);
        bool getEquipStatus();
};

#endif