#include <iostream>
#include <string.h>
#include <string>
#include <ncurses.h>
#include <locale>
#include <algorithm>
#include "libsqlite.hpp"


using namespace std;
class Combat { 
    private:
    char response[];
    char* charResponse;
    int size;
    string name;
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
     
    string database_assign(int ID) //gets the name of the weapons and spells used 
      {
        sqlite::sqlite db( "Database.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Name FROM Weapon WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        name = cur->get_text(0);
        return name;
      }

  string make_lower(string attach){ //allows user input to match the name of the weapon or spell 
    for(int length = 0; length < attach.length(); ++length){
      attach[length] = tolower(attach[length]);
    }
    return attach;
  }
};

class Dragon{
private:
    int health = 223; 
    int attackStr = 20; 
public:
    int get_health(){
        return health;
    }
    int get_attack(){
        return attackStr;        
    }
};

class Attack : virtual public Combat{ //array of strings containing the weapon names
    private:
    string attackResponse;    
    string weaponOneString = database_assign(1);
    string weaponTwoString = database_assign(2);
    string weaponThreeString = database_assign(3); //gets weapon name from DB - will make sense with inventory table 
    string weaponOneLower;
    string weaponTwoLower;
    string weaponThreeLower;
    char weaponOne[20];
    char weaponTwo[20];
    char weaponThree[20]; 
    int weaponStrength;
    char response[];
    
    public:

    int attack_response() //player chooses desired weapon  
    {
      sqlite::sqlite db( "Database.db" );
      auto cur = db.get_statement();
      
      strcpy(weaponOne, weaponOneString.c_str());   //can't make a function which returns a char array 
      strcpy(weaponTwo, weaponTwoString.c_str());   //so this is the conversion 
      strcpy(weaponThree, weaponThreeString.c_str());
      
      
        
        printw ("These are the weapons you can use:\n" );
        printw ("-    Deal damage with a %s\n", weaponOne );  
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s\n", weaponThree);
        printw ("What weapon would you like to use? \n");
        attackResponse = get_line();
      
      weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter 
      weaponTwoLower = make_lower(weaponTwoString);
      weaponThreeLower = make_lower(weaponThreeString);
      
              
        size_t weaponOptionOne = attackResponse.find(weaponOneLower);
        size_t weaponOptionTwo = attackResponse.find(weaponTwoLower);
        size_t weaponOptionThree = attackResponse.find(weaponThreeLower); //result will come out with -1 if it can't find substring 
   

        if (weaponOptionOne != string::npos) 
        {
          cur-> set_sql("SELECT Damage FROM Weapon WHERE Name = ?");
          cur-> prepare();
          cur-> bind(1, weaponOneString);
          cur-> step();
          weaponStrength = cur->get_int(0);
          return weaponStrength;
        }

        else if (weaponOptionTwo != string::npos) 
        {
          cur-> set_sql("SELECT Damage FROM Weapon WHERE Name = ?");
          cur-> prepare();
          cur-> bind(1, weaponTwoString);
          cur-> step();         
          weaponStrength = cur->get_int(0);
          return weaponStrength;

            
        }
        else if (weaponOptionThree != string::npos) 
        {
          cur-> set_sql("SELECT Damage FROM Weapon WHERE Name = ?");
          cur-> prepare();
          cur-> bind(1,weaponThreeString);
          cur-> step();
          weaponStrength = cur->get_int(0);
          return weaponStrength;
          
          
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
    string spellOneString = "decay";
    string spellTwoString = "potent slap"; //need a table for all of these 
    string spellThreeString = "loud noise";
    char spellOne[6] = "decay";
    char spellTwo[12] = "potent slap";
    char spellThree[11] = "loud noise";
    int spellStrengthOne = 10;
    int spellStrengthTwo = 20; //all hardcoded until there is a table which I can access from 
    int spellStrengthThree = 30;    
    public:  
  
    int spells_response(){
      //sqlite::sqlite db( "Database.db" );
      //auto cur = db.get_statement();
      printw ("These are the spells you can use:\n");  
      printw ("-    Cast %s\n", spellOne );  
      printw ("-    Cast %s\n", spellTwo); 
      printw ("-    Cast %s\n", spellThree); 
      printw ("What spell would you like to use?\n");

      spellResponse = get_line();
      clear();   
     
      size_t spellOptionOne = spellResponse.find(spellOneString);
      size_t spellOptionTwo = spellResponse.find(spellTwoString);
      size_t spellOptionThree = spellResponse.find(spellThreeString);
      spellOneString = upper_first(spellOneString);
      spellTwoString = upper_first(spellTwoString);
      spellThreeString = upper_first(spellThreeString);
        
      if (spellOptionOne != string::npos)
      {
        //cur->set_sql("SELECT Damage FROM Spell WHERE Name = ?");
        //cur-> bind(1, spellOne);
        //spellStrength = cur->get_int(0);
        //return spellStrength;
        return spellStrengthOne;
         
      }
                      
      else if (spellOptionTwo != string::npos)
      {
          //cur-> bind(1,spellTwo);
          //spellStrength = cur->get_int(0);
          //return spellStrength;
          return spellStrengthTwo;

      }
 
      else if (spellOptionThree != string::npos)
      {
          //cur-> bind(1,spellThree);
          //spellStrength = cur->get_int(0);
          //return spellStrength;
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
    
    public:
    
    int defence_response()
    {
        /*string sqliteFile = "<<whatever the data baseness is>>";
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select defence_stats " subject to change 
                       "from defence_table "
                       "where defence = ?");
        cur->prepare();*/
      printw ("These are the defences you can use: \n"); 
      printw ("-    Use ability %s\n", defenceOne); 
      printw ("-    Use ability %s\n", defenceTwo ); 
      printw ("-    Use ability %s\n", defenceThree);  
      printw ("What defence would you like to do? \n");
       
      defenceResponse = get_line();
      refresh();        

      size_t defenceOptionOne = defenceResponse.find(defenceOneString);
      size_t spellOptionTwo = defenceResponse.find(defenceTwoString);
      size_t spellOptionThree = defenceResponse.find(defenceThreeString);
      defenceOneString = upper_first(defenceOneString);
      defenceTwoString = upper_first(defenceTwoString);
      defenceThreeString = upper_first(defenceThreeString); //fafing around without a database 


      if (defenceOptionOne != string::npos)
      {
        //cur-> bind(1,defenceOne);
        //defenceAmount = cur->get_int(0);
        //return defenceAmount;
        return heal;   
      }      
          
      else if (spellOptionTwo != string::npos)
      {
        //cur->bind(1,defenceTwo);
        //defenceAmount = cur->get_int(0);
        //return defenceAmount;
        return syrup;

      }
     
      else if (spellOptionThree != string::npos)
      {
                //cur->bind(1,defenceThree);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return potion;
       }
      else
      {
        printw("Please enher the name of the spell\n");
        defence_response();
      }
    }
    int healing(int amount, int playerHealth){  
        playerHealth = playerHealth + amount;
        printw ("Your health is now %i \n", playerHealth);
        return playerHealth;
    }
};

class AttackTest : public Attack, public Spells, public Defence, public Dragon{
    private:
    string choice;
    string response;
    string attacksearch = "attack";
    string spellsearch = "spell";
    string defencesearch = "defence"; //can stay hardcoded or be json related 
    char attackSearch[7] = "attack"; 
    char spellSearch[6] = "spell"; 
    char defenceSearch[8] = "defence";
    string initialResponse;
    string fightingResponse;
   
    int defenceResponse;
    int point1;
    int point2;
    int point3;
    int healingPlayer;
    int weaponStrength;
    int togo;
    
    int mAttack;
    Dragon bob;
    Dragon mike;
    int Phealth;
    int monsterHealth = bob.get_health();
    int monsterAttack = bob.get_attack();
    
    
    public:
    
    int attacking_response(){
        
        printw ("What would you like to do? \n"); 
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
      
        fightingResponse = get_line();
        clear();        
            size_t nextA = fightingResponse.find(attacksearch);
            if (nextA != string::npos) 
            {  
                point1 = attack_response();
                return point1;
            }
        
            size_t nextS = fightingResponse.find(spellsearch);
            if (nextS != string::npos)
            {
                point2 = spells_response(); 
                return point2;
            }
        
            /*size_t nextD = fightingResponse.find(defencesearch);
            if (nextD != string::npos)
            {
                point3 = defence_response(); //read json file for an array selection of what they input or switch cases 
                return point3;
            }*/
        
            else{
                //initial_response_error();
                //do nothing for now
                //cout << "Still happening" << endl;
            }         
    }
    
   int battle(){
           Phealth = 100; //database
           bool startFinish = true;
           while(startFinish){
              if (Phealth > 0 && monsterHealth > 0)
              {
                  printw ("The monsters health is %i\n", monsterHealth);
                  weaponStrength = attacking_response();
                  
                  printw ("Your weapon's attack is %i\n", weaponStrength);
                  monsterHealth = monsterHealth - weaponStrength; //only an attack or spells option - no defence 
                  printw ("Monsters health after attack is %i\n", monsterHealth);
                  printw ("\nMonsters time to attack\n");
                  
                 
                  printw ("The monster did %i damage!!\n", monsterAttack);
                  Phealth = Phealth - monsterAttack; //* balance;
                  printw ("\nYour health now is... %i\n", Phealth);
                                    
                  
                  
              }
              if (Phealth <= 40 && Phealth > 0) //make this optional 
              {                   
                  printw ("You need to heal\n");
                  defenceResponse = defence_response();                  
                  Phealth = healing(defenceResponse, Phealth);                                                   
                      
              }
                                                                
              else if(Phealth <= 0)
              {
                  startFinish = false;
                  printw ("You have died\n");
                  return startFinish;
                                
              }
              else if(monsterHealth <=0){
                  startFinish = false;
                  printw ("You have killed the monster\n");
                  return startFinish;
                                
              }
          }
   }
   
   int startGame(){
      
        printw ("There is something blocking your path\n");
        printw ("What would you like to do?\n");
        printw ("-----   ");
        refresh();
        choice = get_line();
         
        togo = choice.find(attacksearch);
        //printw("%i", togo);
        if (togo != -1)
        {
          //printw ("        \nBegin\n");
          battle();
        }
        else
        {
          printw ("Move along, move along\n");
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
