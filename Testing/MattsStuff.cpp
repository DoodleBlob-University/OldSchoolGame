#include <iostream>
#include <cstdlib>
#include <ctime>
#include "libsqlite.hpp"
#include <array>
#include <string>
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
        array<int, 13>arrayOfStatsP;
        while(num<14){
            arrayOfStatsP[num-1] = cur->get_int(num-1);;
            num = num +1;
        }   
     return arrayOfStatsP;

    }
    array<int, 13>playerDB;
       int pXPGain(int mEXP){
           int xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET EXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, xpGain );

            cur->step();
            cout<<"XP: " << getEXP()<<endl;
            return playerDB[7];
}
    int pXPSplit(int mEXP,int attackNum,int defenceNum){
            int totalNum = attackNum + defenceNum;
            int equalSplit = mEXP/totalNum;
            int attackXP = equalSplit * attackNum;
            int defenceXP = equalSplit * defenceNum;
            int attackXPGain = playerDB[9] + attackXP;
            int defenceXPGain = playerDB[12] + defenceXP;
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET ASEXP = ?, MEXP = ?, MSEXP = ?, DEXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, attackXPGain );
            cur->bind( 2, 0);
            cur->bind( 3, 0);
            cur->bind( 4, defenceXPGain);

            cur->step();
            cout<< "Attack XP: "<<getASEXP()<<endl;
            cout<<"Defence XP: "<<getDEXP()<<endl;
            
        }
    int levelUp(){
       int level = getLevel();
       int EXP = getEXP();
       int levelUpPoint = 40 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[1] = playerDB[1]+1;
            cout<< "\nYou have leveled up!"<< endl;
            cout<< "You are level " << playerDB[1]<< endl;

            
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Level = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[1] );

            cur->step();
           }

            }
      int healthLevelUp(){
       int level = getHealth();
       int EXP = getEXP();
       int levelUpPoint = 30 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[2] = playerDB[2]+1;
            cout<< "\nYour health has leveled up!"<< endl;
            cout<< "You now have " << playerDB[2]<<" health."<< endl;

            
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Health = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[2] );

            cur->step();
           }

       }
    
int updateDB(int a, int b, int asLevelUpPoint){
    string upgrade;
    playerDB[a] = playerDB[a]+1;
    if(a==3){
        upgrade = "Attack Strength";
    }
    if(a==4){
        upgrade = "Mana";
    }
    if(a==5){
        upgrade = "Magic Strength";
    }
    if(a==6){
        upgrade = "Defence";
    };
            cout<< "\nYour stats have increased!"<< endl;
                cout<<"You are "<<upgrade<<" level "<<playerDB[a]<<endl;
            cout<<"You have  "<<playerDB[b]<<" EXP in "<<upgrade<<"\n"<<endl;            
            cout<<"Next level at " <<asLevelUpPoint<<" EXP."<<endl;
            
             
    }

    int statsLevelUp(int a, int b){
            
            int asLevel = playerDB[a];
            int asEXP = playerDB[b];
            int asLevelUpPoint = 20*(asLevel*1.2);
            if(a==3 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET AttackStrength = ? WHERE PlayerName = 'Test';");
                updateDB(3, 9, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==4 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET Mana = ? WHERE PlayerName = 'Test';");
                updateDB(4, 10, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==5 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET MagicStrength = ? WHERE PlayerName = 'Test';");
                updateDB(5, 11, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==6&& asEXP >= asLevelUpPoint){
               sqlite::sqlite db( "Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET Defence = ? WHERE PlayerName = 'Test';");
                updateDB(6, 12, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
   

            
  
    else{
        return 0;
    }
    
    }
    

     
        
    


               
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
        int getASEXP(){
            return playerDB[9];
        }
        int getDEXP(){
            return playerDB[12];
        } 
        int getXPGain(int mEXP){
            return pXPGain(mEXP);
        }
        int getXPSplit(int mEXP, int attackNum, int defenceNum){
            return pXPSplit(mEXP, attackNum, defenceNum);
        }
        int getLevelUp(){
            return levelUp();
        }
        int getStatsLevelUp(int a, int b){
            return statsLevelUp(a, b);
        }
        int getHealthLevelUp(){
            return healthLevelUp();
        }
        
        int levelingSystem(int mEXP, int numOfAttacks, int numOfDefence){
            getXPGain(mEXP);
            getXPSplit(mEXP, numOfAttacks, numOfDefence);
            getLevelUp();
            getHealthLevelUp();
        int a=3;
        int b = 9;
        while(a<=6){
            
            getStatsLevelUp(a, b);
            a=a+1;
            b=b+1;
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
    int numOfAttacks = 0;
    int numOfDefence = 0;
    bool def;
    int apDef;
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
    cout << "\n Attack Options: \n 1 - Attack \n 2 - Defend" << endl;
    do{cin >> choice;} while(choice > 2 || choice < 1);
    switch(choice){
        case 1:
            mHealth = mHealth - (pAttackStrength * 2);
            cout <<"You attack the monster."<<endl;
            cout << "\nMonsters Health: " << mHealth << endl;
            cout <<"Player Health: "<<pHealth<<endl;
            numOfAttacks = numOfAttacks + 1;
            break;
        case 2:
            apDef = pDef +1;
            def = true;
            cout<<"You choose to defend yourself."<<endl;
            cout << "\nMonsters Health: " << mHealth << endl;
            cout <<"Player Health: "<<pHealth<<endl;
            numOfDefence = numOfDefence + 1;
            break;
    }
     choice = rand()%2;
    switch(choice){
            
        case 1:
            if(def = true){
                pHealth = pHealth +apDef - (mAttackStrength * 1);
            cout << "\nYou've been attacked by the monster."<<endl;
            cout << "\nMonsters Health: " << mHealth << endl;
            cout << "Player Health: " << pHealth << endl;
            cout<<"\n---------------------------\n"<<endl;
           
            }
            else{
            pHealth= pHealth - (mAttackStrength * 1);
            cout << "\nYou've been attacked by the monster."<<endl;
            cout << "\nMonsters Health: " << mHealth << endl;
            cout << "Player Health: " << pHealth << endl;
            cout<<"\n---------------------------\n"<<endl;
            }
            break;
        case 2:
            pHealth = mAttackStrength - (pDef *0.35);
            cout <<"\nThe monster chooses to defend itself."<<endl;
            cout << "Monsters Health: " << mHealth << endl;
            break;            
        }
        if (mHealth <1){
        cout<< "\nYou killed the monster!" <<endl;
   matt.levelingSystem(mEXP, numOfAttacks, numOfDefence);
        }
    if (pHealth<=0){
        cout<<"You have died."<<endl;
}
}
};


int main(void){

combat();
};
