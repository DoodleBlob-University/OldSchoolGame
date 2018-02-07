#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class monster{
    int meleeAttackM(int attackStr, int itemAttackStr){
    int attackDamageM = attackStr * itemAttackStr;
    }
    int magicAttackM(int MagAbil, int itemMagAbil){
        int magicDamageM = MagAbil * itemMagAbil;
        int Mana = Mana - 5;
            
    }
    
    int damageTaken(int mAttack){
    int health = health - mAttack;   
        if(health >= 0){
            int v=0;
            //can't do this, im dumb.
        }
    } 
   
    int blockM(int defM,int itemDefM, int mAttack){
        int block = defM * itemDefM;
        int health = health - (health - mAttack) + block;
        
    }
    };


class goblin : public monster{
    public:

    int health = rand()%(8-5+1)+5;
    int attackStr = rand()%(8-5+1)+5;
    int magAbil = rand()%(3-1+1)+1;
    int mana = 10;
    int def = rand()%(6-2+1)+2;
        
};

class wolf : public monster{
    public:
    
    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;
    
};

class ugandanKnuckles : public monster{
    public:
    
    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;
    cout << "We fight for da qween!" << endl;
    cout << "We know de wae." << endl;
    
};
    class rabbit : public monster{
    public:
    
    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;
    
};

class dragon : public monster{
    public:

    int health = rand()%(200-150+1)+150;
    int attackStr = rand()%(500-10+1)+10;
    int magAbil = rand()%(200-20+1)+20;
    int mana = 70;
    int def = rand()%(400-100+1)+100;
    
};


int main(){
    srand(time(NULL));
    /*goblin sam;
    cout << "Health: " << sam.health << endl;    
    dragon toby;
    cout << "Health: " << toby.health <<
    "     Strength: " << toby.attackStr << endl;    */

        

}
