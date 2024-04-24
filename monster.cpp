#include "monster.h"

using namespace std;

monster :: monster(){
    monsterName = "";
    monsterMaxHp = 0;
    monsterCurrentHp = 0;
    monsterDamage = 0;
}

monster :: monster(string setMonsterName, int setMonsterHp, int setMonsterDamage){
    monsterName = setMonsterName;
    monsterMaxHp = setMonsterHp;
    monsterCurrentHp = setMonsterHp;
    monsterDamage =  setMonsterDamage;
}

int monster :: getMaxHp(){
    return monsterMaxHp;
}

int monster :: getCurrentHp(){
    return monsterCurrentHp;
}

int monster :: getMonsterDamage(){
    return monsterDamage;
}

void monster :: addMonsterMaxHp(int newHp){
    monsterMaxHp = newHp;
    monsterCurrentHp += newHp - 1;

}

void monster :: addCurrentMonstHp(int addHp){
    monsterCurrentHp += addHp;
}

void monster :: reduceCurrentMonstHp(int reduceHp){
    monsterCurrentHp -= reduceHp;
}

void monster :: setMonsterName(string newName){
    monsterName = newName;
}

string monster :: getMonsterName(){
    return monsterName;
}
