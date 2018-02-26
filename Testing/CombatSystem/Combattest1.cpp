#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

class player{
    private:
           int health = 5;
           int attackStrength = 5;
           int defence = 10;
           int mana = 10;
           int magicStrength = 1;
               
    public:
        int getHealth(){
         return this->health;   
        }

        int getAttackStrength(){
             return this->attackStrength;
        }
        int getMana(){
            return this->mana;            
        }
        int getMagicStrength(){
            
            return this->magicStrength;
        }
        int damageDone(){
            int dd = attackStrength * 2;
                return dd;
        }
};

class monster{
    private:
        int health = 20;
        int attackStrength = 10;
        int defence = 1;
        int mana = 2;
        int magicStrength = 2;
    public:
        int getHealth(){
         return this->health;   
        }

        int getAttackStrength(){
             return this->attackStrength;
        }
        int getMana(){
            return this->mana;            
        }
        int getMagicStrength(){
            
            return this->magicStrength;
        }
        int damageDone(){
            int dd = attackStrength * 2;
                return dd;
        }  
        };

int combat(){

player matt;
int pHealth = matt.getHealth();
int pAttackStrength = matt.getAttackStrength();
int pMana = matt.getMana();
int pMagicStrength = matt.getMagicStrength();

monster bob;
int mHealth = bob.getHealth();
int mAttackStrength = bob.getMagicStrength();
int mMana = bob.getMana();
int mMagicStrength = bob.getMagicStrength();
cout << mHealth << pHealth << endl;
    
int choice;
while(mHealth > 0 && pHealth > 0) {
    cout << "Attack Options: \n 1 - Attack \n 2 - Defend" << endl;
    do{cin >> choice;} while(choice > 2 || choice < 1);
    switch(choice){
        case 1:
            mHealth = mHealth - (pAttackStrength * 2);
            cout << "Monsters Health: " << mHealth << endl;
            break;
        case 2:
            cout << "Defence option [To be written]" << endl;
            break;
    }
     choice = rand()%2;
    switch(choice){
        case 1:
            pHealth = pHealth - (mAttackStrength * 2);
            cout << "Player Health: " << pHealth << endl;
            break;
        case 2:
            cout << "Defence option [To be written]" << endl;
            break;            
        
    }
}
};

int main(){
combat();

 };
