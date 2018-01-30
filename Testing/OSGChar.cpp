#include <iostream>
#include <string>

using namespace std;

// All Stats are placeholders untill we get databases working.

class playableCharacter{
    private:

    public:
        int health =20;
        int XP = 0;
    //XP adding function, can be implemented with different monsters later.
    int addXP(int pXP){
        XP= XP + pXP;
    }
    
    //Damage Taking Function, will be changed to accomodate armour and def stats. Need databse for that.
    int damageTaken(int mAttack){
        health = health - mAttack;    
    } 

};


class warrior : public playableCharacter{
    private:

    public:
        int wAttackStr = 55;
        int wDef = 60;
        int wMagAbil = 10;
        int wMana = 20;

};

class mage : public playableCharacter{
    private:

    public:
        int wAttackStr = 30;
        int wDef = 40;
        int wMagAbil = 60;
        int wMana = 50;
    
};



int main() {
//This shows bill being damaged by an enemy.
    
    warrior bill;
    cout << "Health: " << bill.health << "   XP: "<< bill.XP << endl;
    cout << "Bill attacks the monster. (Funtion still to be written)" << endl;
    bill.damageTaken(12);
    cout << "Bill takes damage from the monster." << endl;
    cout << "Health: " << bill.health << endl;
    cout << "Bill attacks again and kills the monster. Bill Gains XP." << endl;
    bill.addXP(500);
    cout << "Total XP: " << bill.XP << endl;

}
