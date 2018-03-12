#include <iostream>
#include <string.h>
#include <string>
#include <ncurses.h>
#include <locale>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include "libsqlite.hpp"


using namespace std;
class Combat { 
    private:
    char response[];
    string name;
    int weaponAmount;
    int spellAmount;
  int healingAmount;
    public:
  
    string get_line() //take input from the user and put it in lowercase so that doesn't affect it    
    {
        getstr(response);
        string again(response);
        transform(again.begin(), 
                  again.end(), 
                  again.begin(), 
                  ::tolower);      
        return again;
    }

    string upper_first(string call){ //makes the first letter uppercase (hardcoded purposes)
      call[0] = toupper(call[0]);
      return call;
    }
     
    string database_assign_name(int ID) //gets the name of the weapons and spells used 
      {
        sqlite::sqlite db( "Inventory.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Weapon_name FROM Inventory WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        name = cur->get_text(0);
        return name;
      }
  int database_assign_int_weapon(int ID)
  {
    sqlite::sqlite db( "Inventory.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Weapons.Damage FROM Inventory "
                      "INNER JOIN Weapons ON Inventory.Weapon_name = Weapons.Weapon_name " //change it to item name not just weapon
                      "WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        weaponAmount = cur->get_int(0);
        return weaponAmount;
  }
  /*int database_assign_int_spell(int ID)
  {
    sqlite::sqlite db( "Inventory.db");
    auto cur = db.get_statement();
    cur-> set_sql("SELECT Spells.Damage FROM Inventory "
                  "INNER JOIN Spells ON Inventory.Spell_name = Spells.Spell_name "
                  "WHERE ID = ?");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    spellAmount = cur->get_int(0);
    return spellAmount;
  }
  int database_assign_int_healing(int ID)
  {
    sqlite::sqlite db( "Inventory.db");
    auto cur = db.get_statement();
    cur->set_sql("SELECT Healing.Amount FROM Inventory "
                 "INNER JOIN Healing ON Inventory.Item_name = Healing.Item_name "
                 "WHERE ID = ?");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    healingAmount = cur->get_int(0);
    return healingAmount;
  }*/

  string make_lower(string attach){ //allows user input to match the name of the weapon or spell 
    for(int length = 0; length < attach.length(); ++length){
      attach[length] = tolower(attach[length]);
    }
    return attach;
  }
};

class player{
    private:
  int level;
  int EXP;
  int levelUpPoint;
  int num;
  int xpGain;
    
    auto dbOpen(){
        sqlite::sqlite db( "Database (1).db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Player WHERE PlayerName = 'Test'");
        cur->prepare();
        cur->step();
        num = 1;
        //array<int, 9>arrayOfStatsP;
        while(num<10){
            playerDB[num-1] = cur->get_int(num-1);;
            num = num +1;
        }   
     return playerDB;

    }
    array<int, 9>playerDB;
    //playerDB = dbOpen();

               
    public:

        player()
        {
            playerDB = dbOpen();
        }
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
            xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "Database.db" );
            auto cur = db.get_statement();
            //cout<<"XP: "<<playerDB[7]<< endl;
            //printw("XP: %i\n", playerDB[7]);
            cur->set_sql("UPDATE Player SET EXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, xpGain );

            cur->step();
            //int xp = getEXP();
            //printw("%i", xp);
            //cout<<getEXP()<<endl;
            return playerDB[7];
        }
        int levelUp(){
            level = getLevel();
            EXP = getEXP();
            levelUpPoint = (level *1.2);
            if (EXP >= levelUpPoint){
                //cout<< "You have leveled up!"<< endl;
                //cout<< "You are level " << playerDB[1]<< endl;
                printw("You have leveled up!\n");
                printw("You are level %i\n", playerDB[1]);
                refresh();
                playerDB[1] = playerDB[1]+1;
            
                sqlite::sqlite db( "Database.db" );
                auto cur = db.get_statement();
                //cout<<"XP: "<<playerDB[7]<< endl;
                //printw("XP: %i\n",playerDB[7]);
                cur->set_sql("UPDATE Player SET Level = ? WHERE PlayerName = 'Test';");
                cur->prepare();
    
                cur->bind( 1, playerDB[1] );

                cur->step();
            
            }
            else{
               return 0;
           }
          return 0;
        }
        
    
};

class monster{
    private:
    int num;
    array<int, 9>arrayofstats;
    auto dbOpen(){
        sqlite::sqlite db( "Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Monster WHERE MonsterName = 'Goblin'");
        cur->prepare();
        cur->step();        
        num = 1;
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



class Attack : virtual public Combat{ //array of strings containing the weapon names
    private:
    string attackResponse;    
    string weaponOneString = database_assign_name(1);
    string weaponTwoString = database_assign_name(2);
    string weaponThreeString = database_assign_name(3); //gets weapon name from DB - will make sense with inventory table 
    string weaponOneLower;
    string weaponTwoLower;
    string weaponThreeLower;
    char weaponOne[20];
    char weaponTwo[20];
    char weaponThree[20];
    int weaponStrength;
    int weaponStrengthOne = database_assign_int_weapon(1);
    int weaponStrengthTwo = database_assign_int_weapon(2);
    int weaponStrengthThree = database_assign_int_weapon(3); 
    size_t weaponOptionOne;
    size_t weaponOptionTwo;
    size_t weaponOptionThree;
    public:

    int attack_response() //player chooses desired weapon  
    {
      clear();
      
      strcpy(weaponOne, weaponOneString.c_str());   //can't make a function which returns a char array 
      strcpy(weaponTwo, weaponTwoString.c_str());   //so this is the conversion 
      strcpy(weaponThree, weaponThreeString.c_str());
            
        //printw ("These are the weapon stats %i, %i, %i \n", weaponStrengthOne, weaponStrengthTwo, weaponStrengthThree);
        printw ("These are the weapons you can use:\n" );
        printw ("-    Deal damage with a %s\n", weaponOne );  
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s\n", weaponThree);
        printw ("What weapon would you like to use? \n");
        attackResponse = get_line();
              
        weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter 
        weaponTwoLower = make_lower(weaponTwoString);
        weaponThreeLower = make_lower(weaponThreeString);
        /*strcpy(weaponOneLowerC, weaponOneLower.c_str());
        printw("This is the lower option %s", weaponOneLowerC);*/
       
        refresh();
        
              
        weaponOptionOne = attackResponse.find(weaponOneLower);
        weaponOptionTwo = attackResponse.find(weaponTwoLower);
        weaponOptionThree = attackResponse.find(weaponThreeLower); //result will come out with -1 if it can't find substring 
   
        if (weaponOptionOne != string::npos) 
        {
          return weaponStrengthOne;
        }

        else if (weaponOptionTwo != string::npos) 
        {
          return weaponStrengthTwo;        
        }
        else if (weaponOptionThree != string::npos) 
        {
          return weaponStrengthThree;        
        }
        else{ //make this a catch for a no input section - makes it look better 
            printw ("Please enter the name of your weapon \n");
            attack_response();
        }
    }
                                  
};

class Spells : virtual public Combat{
    private:
    string spellResponse;
    string spellOneString = "decay"; //database_assign_name(4);
    string spellTwoString = "potent"; //database_assign_name(5); 
    string spellThreeString = "loud"; //database_assign_name(6);
    char spellOne[6] = "decay";
    char spellTwo[7] = "potent";
    char spellThree[5] = "loud";
    int spellStrengthOne = 5; //database_assign_int_spell(4);
    int spellStrengthTwo = 6; //database_assign_int_spell(5);
    int spellStrengthThree = 7; //database_assign_int_spell(6);
    size_t spellOptionOne;
    size_t spellOptionTwo;
    size_t spellOptionThree;
    public:  
  
    int spells_response(){
      
      printw ("These are the spells you can use:\n");  
      printw ("-    Cast %s\n", spellOne );  
      printw ("-    Cast %s\n", spellTwo); 
      printw ("-    Cast %s\n", spellThree); 
      printw ("What spell would you like to use?\n");

      spellResponse = get_line();
      clear();   
     
      spellOptionOne = spellResponse.find(spellOneString);
      spellOptionTwo = spellResponse.find(spellTwoString);
      spellOptionThree = spellResponse.find(spellThreeString);
      spellOneString = upper_first(spellOneString);
      spellTwoString = upper_first(spellTwoString);
      spellThreeString = upper_first(spellThreeString);
        
      if (spellOptionOne != string::npos)
      {
        return spellStrengthOne;         
      }                      
      else if (spellOptionTwo != string::npos)
      {         
        return spellStrengthTwo;
      }
      else if (spellOptionThree != string::npos)
      {       
        return spellStrengthThree;
      }
    }
    
};

class Defence : virtual public Combat{
    private:
    string defenceResponse;
    string defenceOneString = "heal";
    string defenceTwoString = "syrup"; //need a table for all of these 
    string defenceThreeString = "potion";
    char defenceOne[5] = "heal"; 
    char defenceTwo[6] = "syrup";
    char defenceThree[7] = "potion";
    int heal = 5;
    int syrup = 10;
    int potion = 15;
    size_t defenceOptionOne;
    size_t defenceOptionTwo;
    size_t defenceOptionThree;
    int num = 0;
    array<int, 3>arrayOfAmountLeft;
    
    public:
    
    int defence_response()
    {
        /*string sqliteFile = "<<whatever the data baseness is>>";
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("SELECT Amount_left FROM Inventory "); subject to change 
        cur->prepare();
        while(cur->step()){
          arrayOfAmountLeft[num] = cur->get_int(0);
          num = num + 1;
        }*/
      printw ("These are the defences you can use: \n"); 
      printw ("-    Use ability %s\n", defenceOne); //%i uses left", arrayOfAmountLeft[0]);
      printw ("-    Use ability %s\n", defenceTwo ); //%i uses left", arrayOfAmountLeft[1]);
      printw ("-    Use ability %s\n", defenceThree); //%i uses left", arrayOfAmountLeft[2]);
      printw ("What defence would you like to do? \n");
       
      defenceResponse = get_line();
      clear();        

      defenceOptionOne = defenceResponse.find(defenceOneString);
      defenceOptionTwo = defenceResponse.find(defenceTwoString);
      defenceOptionThree = defenceResponse.find(defenceThreeString);
      defenceOneString = upper_first(defenceOneString);
      defenceTwoString = upper_first(defenceTwoString);
      defenceThreeString = upper_first(defenceThreeString); //fafing around without a database 


      if (defenceOptionOne != string::npos)
      {
        /*if(arrayOfAmountLeft[0]!=0){
          cur->set_sql("UPDATE Inventory SET Healing_amount = Healing_amount - 1 WHERE Item_name = ?;");
          cur->prepare();
          cur->bind(1, defenceOneString);
          cur->step();
          return healingAmount;
        }
        else{
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }*/
        
        return heal;   
      }      
          
      else if (defenceOptionTwo != string::npos) //get amount of them that you have left in inventory
        
      {
        /*if(arrayOfAmountLeft[1]!=0){
          cur->set_sql("UPDATE Inventory SET Healing_amount = Healing_amount - 1 WHERE Item_name = ?;");
          cur->prepare();
          cur->bind(1, defenceTwoString);
          cur->step();
          return healingAmount;
        }
        else{
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }*/
        return syrup; //can use an update with inbedded if statements 

      }
     
      else if (defenceOptionThree != string::npos)
      {
        /*if(arrayOfAmountLeft[2]!=0){
          cur->set_sql("UPDATE Inventory SET Healing_amount = Healing_amount - 1 WHERE Item_name = ?;");
          cur->prepare();
          cur->bind(1, defenceThreeString);
          cur->step();
          return healingAmount;
        }
        else{
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }*/
        return potion;
       }
      else
      {
        printw("Please enter the name of the spell\n");
        defence_response();
      }
    }
    int healing(int amount, int playerHealth)
    {  
        playerHealth = playerHealth + amount;
        printw ("Your health is now %i \n", playerHealth);
        return playerHealth;
    }
};

class AttackTest : public Attack, public Spells, public Defence, public monster, public player{
    private:
    string choice;
    string response;
    string responseSearch = "engage";
    string attacksearch = "attack";
    string spellsearch = "spell";
    string defencesearch = "defence"; //can stay hardcoded or be json related 
    char attackSearch[7] = "attack"; 
    char spellSearch[6] = "spell"; 
    char defenceSearch[8] = "defence";
    string initialResponse;
    string fightingResponse;  
    int defenceResponse;
    int attackPoint;
    int spellsPoint;
    int weaponStrength;
    int togo;
    size_t nextA;
    size_t nextS;
    bool startFinish;
  
    player matt;
    int pHealth = matt.getHealth();
    //int pHealth = 100;
    int pAttackStrength = matt.getAttackStrength();
    int pMana = matt.getMana();
    int pMagicStrength = matt.getMagicStrength();
    int pDef = matt.getDefence();
    int pXP = matt.getEXP();
        
    monster bob;
    int mHealth = bob.getHealth();
    //int mHealth = 60;
    int mAttackStrength = bob.getAttackStrength();
    int mMana = bob.getMana();
    int mMagicStrength = bob.getMagicStrength();
    int mDef = bob.getDefence();
    int mEXP = bob.getEXP();
  
    
    public:
    
    int attacking_response(){
        
        printw ("What would you like to do? \n"); 
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
      
        fightingResponse = get_line();
        refresh();        
        nextA = fightingResponse.find(attacksearch);
        nextS = fightingResponse.find(spellsearch);
            if (nextA != string::npos) 
            {  
                //attackPoint = attack_response();
                return attack_response();
            }
        
            else if (nextS != string::npos)
            {
                //spellsPoint = spells_response(); 
                return spells_response();
            }
        
            else{
                //initial_response_error();
                //do nothing for now
                //cout << "Still happening" << endl;
                return 0;
            }         
    }
    
   int battle(){
           startFinish = true;
           while(startFinish){
              
                  weaponStrength = attacking_response();
                  printw("Player Health = %i \n", pHealth);
                  printw ("Your weapon's attack is %i\n", weaponStrength);
                  mHealth = mHealth - weaponStrength; // pAttackStrength); //(/mDef); //only an attack or spells option - no defence 
                  printw ("Monsters health after attack is %i\n", mHealth);  
                  printw ("\nMonsters time to attack\n");                                
                  printw ("The monster did %i damage!\n", mAttackStrength);
                  pHealth = pHealth - mAttackStrength; // / pDef); //balance;
                  printw ("\nYour health now is... %i\n", pHealth);  
                  printw ("The monsters health is %i\n", mHealth);                  
                  refresh();
                 
              
              if (pHealth <= 5 && pHealth > 0) //make this optional 
              {                   
                  printw ("You need to heal\n");
                  defenceResponse = defence_response();                  
                  pHealth = healing(defenceResponse, pHealth);
                  refresh();
                      
              }
                                                                
              else if(pHealth <= 0)
              {
                  startFinish = false;
                  printw ("You have died\n");
                  refresh();
                  return startFinish;
                                
              }
              else if(mHealth <= 0) 
              {
                  startFinish = false;
                  
                  printw ("You have killed the monster\n");
                  printw("You have been awarded with %i xp!\n", mEXP);
                  matt.pXPGain(mEXP);
                  matt.levelUp();
                  refresh();
                  return startFinish;
              }
          }
   endwin();
   }
   
   int startGame(){
      
        printw ("There is something blocking your path\n");
        printw ("What would you like to do?\n");
        printw ("-----   ");
        refresh();
        choice = get_line();        
        togo = choice.find(responseSearch);
        refresh();
        if (togo != -1)
        {
          battle();
        }
        else
        {
          printw ("Move along, move along\n");
          refresh();
          endwin();
          
        }
   }
};

int main()
{
    initscr();
    srand(time(NULL));
    //User_Response initialise;
    //initialise.name_selection(); - for the name selection make it part of laod screen to check if name is in db
    AttackTest go;
  
    go.startGame();
    
}
