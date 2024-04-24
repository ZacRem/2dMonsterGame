#ifndef MONSTER_H
#define MONSTER_H

#include <string>

using namespace std;

class monster{
    private:
        string monsterName;
        int monsterMaxHp;
        int monsterCurrentHp;
        int monsterDamage;
    public:
        // Constructors
        monster();
        monster(string setMonsterName, int setMonsterHp, int setMonsterDamage);

        // Getters
        string getMonsterName();
        int getMaxHp();
        int getCurrentHp();
        int getMonsterDamage();

        // Monster Hp
        void addMonsterMaxHp(int newMaxHp);
        void addCurrentMonstHp(int addCurrentHp);
        void reduceCurrentMonstHp(int reduceCurrentHp);

        // Setters
        void setMonsterName(string newName);
};

#endif