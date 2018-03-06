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
    monster(){
        monsterDB = dbOpen();
    }
        };

int main(){
    return 0;
    }
