#include <iostream>
#include <cstdlib>
#include <ctime>
#include "libsqlite.hpp"
#include <array>
using namespace std;


class player{
    private:
    
    auto dbOpen(){
        sqlite::sqlite db( "Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Player WHERE PlayerName = 'Test'");
        cur->prepare();
        cur->step();
        int num = 1;
        array<int, 9>arrayOfStatsP;
        while(num<10){
            arrayOfStatsP[num-1] = cur->get_int(num-1);;
            num = num +1;
        }   
     return arrayOfStatsP;

    }
    array<int, 9>playerDB;

               
    public:

        int getLevel(){
            return playerDB[1];
        }
        int getHealth(){ 
            return playerDB[2];
        }
        int getAttackStrength(){
            return playerDB[3];
        }
        int getMana(){
            return playerDB[4];                  
        }
        int getMagicStrength(){
            return playerDB[5];
        }
        int getDefence(){
            return playerDB[6];
        }
        int getEXP(){
            return playerDB[7];
        }
        int getGold(){
            return playerDB[8];
        }
        int updateDB(){
            dbOpen();
            return 0;
        }
        int pXPGain(int mEXP){
           int xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cout<<"XP: "<<playerDB[7]<< endl;
            cur->set_sql("UPDATE Player SET EXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, xpGain );

            cur->step();
            cout<<getEXP()<<endl;
            return playerDB[7];
}
    int levelUp(){
        int level = getLevel();
       int EXP = getEXP();
        int levelUpPoint = 30 *(level *1.2);
        if (EXP >= levelUpPoint){
            cout<< "You have leveled up!"<< endl;
            cout<< "You are level " << playerDB[1]<< endl;
            playerDB[1] = playerDB[1]+1;
            
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cout<<"XP: "<<playerDB[7]<< endl;
            cur->set_sql("UPDATE Player SET Level = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[1] );

            cur->step();
            
        }
            else{
             return 0;
         }
}
        
    player(){
        playerDB = dbOpen();
    }
};

class monster{
    private:
    auto dbOpen(){
        sqlite::sqlite db( "Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Monster WHERE MonsterName = 'Goblin'");
        cur->prepare();
        cur->step();
        int num = 1;
        array<int, 9>arrayofstats;
        while(num<10){
            arrayofstats[num-1] = cur->get_int(num-1);
            num = num +1;
        }   
    
     return arrayofstats;
    }
    array<int, 9>monsterDB;
    
    public:
       
        int getLevel(){
            return monsterDB[1];
        }
        int getHealth(){
            return monsterDB[2];
        }
        int getAttackStrength(){
            return monsterDB[3];
        }
        int getMana(){
            return monsterDB[4];                  
        }
        int getMagicStrength(){
            return monsterDB[5];
        }
        int getDefence(){
            return monsterDB[6];
        }
        int getEXP(){
            return monsterDB[7];
        }
        int getGold(){
            return monsterDB[8];
        }
        int updateDB(){
            dbOpen();
            return 0;
        }
    
    monster(){
        monsterDB = dbOpen();
    }
        };
    

int combat(){

    sqlite::sqlite db( "Database.db" );
    auto cur = db.get_statement();
    int ppxp;
player matt;
int pHealth = matt.getHealth();
int pAttackStrength = matt.getAttackStrength();
int pMana = matt.getMana();
int pMagicStrength = matt.getMagicStrength();
int pDef = matt.getMagicStrength();
int pXP = matt.getEXP();
    
monster bob;
int mHealth = bob.getHealth();
int mAttackStrength = bob.getAttackStrength();
int mMana = bob.getMana();
int mMagicStrength = bob.getMagicStrength();
int mDef = bob.getDefence();
int mEXP = bob.getEXP();
    
int choice;
while(mHealth > 0 && pHealth > 0) {
    cout << "Attack Options: \n 1 - Attack \n 2 - Defend" << endl;
    do{cin >> choice;} while(choice > 2 || choice < 1);
    switch(choice){
        case 1:
            mHealth = mHealth - (pAttackStrength * 2);
            cout << "Monsters Health: " << mHealth << endl;
            cout <<"Player Health: "<<pHealth<<endl;
            break;
        case 2:
            pHealth = mAttackStrength - (pDef *0.35);
            break;
    }
     choice = rand()%2;
    switch(choice){
            
        case 1:
            pHealth = pHealth - (mAttackStrength * 2);
            cout << "Monsters Health: " << mHealth << endl;
            cout << "Player Health: " << pHealth << endl;
            break;
        case 2:
            pHealth = mAttackStrength - (pDef *0.35);
            cout << "Monsters Health: " << mHealth << endl;
            break;            
        }
        if (mHealth <1){
        cout<< "You killed the monster!" <<endl;
        matt.pXPGain(mEXP);
            matt.levelUp();
        }
    if (pHealth<=0){
        cout<<"You have died."<<endl;
}
}
};


int main(void){

combat();
    combat();
};
