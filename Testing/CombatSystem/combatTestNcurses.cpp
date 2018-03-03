#include <iostream>
#include <string.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <curses.h>
//#include <json/value.h>
#include <fstream>
//gcc combatTest.cpp -g -lncursesw - for testing purposes 
//#include "libsqlite.hpp"
//http://en.cppreference.com/w/cpp/language/data_members

class Combat { 
    private:
    //string response;
    
    public:    
    /*string get_line()
    {
        getline(cin, response);
        transform(response.begin(), 
                  response.end(), 
                  response.begin(), 
                  ::tolower);
        return response;
    }*/
    bool string_find(char* choiceResponse, const char* wordSearch){
        for(int i; i<strlen(choiceResponse)-strlen(wordSearch); i++){
            bool found = true;
            for(int b=0; found && b<strlen(choiceResponse); b++){
                if (choiceResponse[i+b] != wordSearch[b]){
                    found = false;
                }
            }
            if (found){
                return true;
            }            
        }
        return false;
    }
};

class Dragon{
private:
    int health = 223; //rand() % (200 - 150 + 1) + 150;
    int attackStr = 20; //rand() % (50 - 10 + 1) + 10;
    //int magAbil = rand() % (200 - 20 + 1) + 20;
   // int mana = 70;
    //int def = rand() % (400 - 100 + 1) + 100;
public:
    int get_health(){
        return health;
    }
    int get_attack(){
        return attackStr;        
    }
};

/*class Playable_Character {
private:
public:
    string name;
    int PlayerHealth = 20; //functions to get, let matt do it 
    int XP = 0;
};

class Warrior : public Playable_Character {
private:
public:
    int wAttackStr = 55; //same with this one
    int wDef = 60;
    int wMagAbil = 10;
    int wMana = 20; 
};*/

class Attack : virtual public Combat{
    private:
    char* attackResponse;
    char* attackResponseOne;
    
    const char* weaponOne = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    const char* weaponTwo = "bow";
    const char* weaponThree = "sword" ; //secion might need to be in the attack response function to then change it up if it has a different name
    int weaponStrengthOne = 20;
    int weaponStrengthTwo = 30;
    int weaponStrengthThree = 40; //also from database 
    //int *weaponStrength = new int;
    //unique_ptr<int> pointer( new int(10));
    
    
    
    public:
    Attack()
    {
    }

    int attack_response() //try and catch errors for wrong input and ppossible sql failures 
    {
        /*string sqliteFile = "Database.db"; //basic database 
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select weaponstats " subject to change 
                       "from weapon_table "
                       "where weapon = ?");
        cur->prepare();*/
        
        
        printw ("These are the weapons you can use: \n" );
        printw ("-    Deal damage with a %s\n", weaponOne ); 
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s/n", weaponThree);
        printw ("What weapon would you like to use? \n");
        //attackResponse = get_line();
        getnstr( attackResponse, sizeof( attackResponse ) -1);
        
        //detection1 = string_find(attackResponse, weaponOne);
        //detection2 = string_find(attackResponse, weaponTwo);
        //detection3 = string_find(attackResponse, weaponThree);
                

        //size_t weaponOptionOne = attackResponse.find(weaponOne);
        //if (weaponOptionOne != string::npos)
        if (string_find(attackResponse, weaponOne)) 
        {
            //cur-> bind(1,weaponOne);
            //or for smart pointer usage 
            //*weaponStrength = cur->get_int(0); - deletion already happens 
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthOne;
            //delete weaponStrength;
        }
        //size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        //if (weaponOptionTwo != string::npos)
        if (string_find(attackResponse, weaponTwo))
        {
            //cur->bind(1,weaponTwo);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthTwo;
            //delete weaponStrength;
        }
        //size_t weaponOptionThree = attackResponse.find(weaponThree);
        //if (weaponOptionThree != string::npos)
        if (string_find(attackResponse, weaponThree)) 
        {
            //cur->bind(1,weaponThree);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthThree;
            //delete weaponStrength
        }
        else{ //make this a catch for a no input section - makes it look better 
            printw ("Please enter the name of your weapon \n");
            attack_response();
        }
    }                            
};

class Spells : virtual public Combat{
    private:
    char* spellResponse;
    char* spellResponseOne;
    const char* spellOne = "decay";
    const char* spellTwo = "potent slap";
    const char* spellThree = "loud noise";
    int spellStrengthOne = 10;
    int spellStrengthTwo = 20;
    int spellStrengthThree = 30;
    //int spellStrength;
    
    public:  
    Spells(){ //supposedly to initialise the use of the class         
    }
    
    int spells_response(){
        /*string sqliteFile = "<<whatever the data baseness is>>";
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select spellStats " subject to change 
                       "from spells_table "
                       "where spell = ?");
        cur->prepare();*/
        printw ("These are the spells you can use: \n");  
        printw ("-    Cast %s\n", spellOne );  
        printw ("-    Cast %s\n", spellTwo); 
        printw ("-    Cast &s\n", spellThree); 
        printw ("What spell would you like to use? \n");
        //spellResponse = get_line();
        getnstr( spellResponse, sizeof( spellResponse) -1);
        
        //detection1 = string_find(spellResponse, spellOne);
        //detection2 = string_find(spellResponse, spellTwo);
        //detection3 = string_find(spellResponse, spellThree);
 
        //size_t spellAttackOne = spellResponse.find(spellOne);        
        //if (spellAttackOne!=string::npos)
        if (string_find(spellResponse, spellOne))
        {
            //cur-> bind(1,spellOne);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthOne;
         
        }
        //size_t spellAttackTwo = spellResponse.find(spellTwo);
        //if (spellAttackTwo!=string::npos)
        if (string_find(spellResponse, spellTwo))
        {
            //cur-> bind(1,spellTwo);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthTwo;

        }
        //size_t spellAttackThree = spellResponse.find(spellThree);
        //if (spellAttackThree!=string::npos)
        if (string_find(spellResponse, spellThree))
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
    char* defenceResponse;
    char* defenceResponseOne;
    const char* defenceOne = "heal"; 
    const char* defenceTwo = "syrup";
    const char* defenceThree = "potion";
    int heal = 5;
    int syrup = 10;
    int potion = 15;
    //int defenceAmount;
    
    public:
    
    Defence(){
        
    }
    
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
        //defenceResponse = get_line();
        getnstr( defenceResponse, sizeof( defenceResponse ) -1 );
        
        //detection1 = string_find(defenceResponse, defenceOne);
        //detection2 = string_find(defenceResponse, defenceTwo);
        //detection3 = string_find(defenceResponse, defenceThree);
            
    
        //size_t defenceOptionOne = defenceResponse.find(defenceOne);
            //if (defenceOptionOne != string::npos)
            if (string_find(defenceResponse, defenceOne))
            {
                //cur-> bind(1,defenceOne);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return heal;
    
            }
        //size_t defenceOptionTwo = defenceResponse.find(defenceTwo);
            //if (defenceOptionTwo!=string::npos)
            if (string_find(defenceResponse, defenceTwo))
            {
                //cur->bind(1,defenceTwo);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return syrup;

            }
        //size_t defenceOptionThree = defenceResponse.find(defenceThree);
            //if (defenceOptionThree!=string::npos)
        if (string_find(defenceResponse, defenceThree))    
        {
                //cur->bind(1,defenceThree);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return potion;
            }
    return 0;
    }
    int healing(int amount, int playerHealth){  
        playerHealth = playerHealth + amount;
        return playerHealth;
    }
};

/*class User_Response : public Warrior, public Combat { //includes classes for character selection
        
        public:
        char* characterChoice;
        string nameChoice;
        string const warriorSearch = "warrior";
    

        User_Response()
        {
        }

        int name_selection()
        {
            string sqliteFile = "<<whatever the data baseness is>>";
            sqlite::sqlite db( sqliteFile );
            auto cur = db.get_statement();
            cur -> set_sql(CREATE TABLE Character(),
                           name VARCHAR2(30) NOT NULL,
                           class VARCHAR2(15) NOT NULL FOREIGN KEY REFERENCE Class_table(?), - for whatever class 
                           weaponSlot1 VARCHAR2(50) FOREIGN KEY REFERENCE Weapon_table(weapon) - this command needs work
                           weaponSlot2 VARCHAR2(50) FOREIGN KEY REFERENCE Weapon_table(weapon)
            cout << "Please name your character... " << endl; //save to db
            cout << "--- ";
            getline(cin, nameChoice);
            cur-> set_sql(INSERT INTO Character name,
                            VALUES ?)
            cur-> bind(1,nameChoice) - just guessing with whatever it needs to make 
           
            cout << "Choose a class for " << nameChoice << endl;
            cout << "-  Warrior." << endl;
            characterChoice = get_line();
            

            int classChoiceW = characterChoice.find(warriorSearch);

            if (classChoiceW != -1) {
                Warrior player;
                player.name = nameChoice;
                cout << player.name << endl;
            }
            else {
                name_selection();
            }
            return 0;
        }
};*/  

class AttackTest : public Attack, public Spells, public Defence, public Dragon{
    private:
    char* choice;
    char* response;
    //bool nextA;
    //bool nextD;
    //bool nextS;
    const char* attackSearch = "attack"; 
    const char* spellSearch = "spell"; //string of words to use instead of just one word
    const char* defenceSearch = "defence";
    char* initialResponse;
    char* fightingResponse;
    char* battleResponse;
    int defenceResponse;
    int point1;
    int point2;
    int point3;
    int healingPlayer;
    int weaponStrength;
    //double balance;
    int mAttack;
    Dragon bob;
    Dragon mike;
    int Phealth;
    int monsterHealth = bob.get_health();
    int monsterAttack = bob.get_attack();    
    
    public:
    
    char* attacking_response(){
        printw ("What would you like to do? \n"); 
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
        //fightingResponse = get_line();
        getnstr( fightingResponse, sizeof( fightingResponse) -1 );
        return fightingResponse;
    }
    
    
    int next_step(char* next){
        //nextA = string_find(next, attackSearch);
        //nextS = string_find(next, spellSearch);
        //nextD = string_find(next, defenceSearch);
        
            if (string_find(next, attackSearch)){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
                point1 = attack_response();
                return point1;
            }
        
            if (string_find(next, spellSearch)){
                point2 = defence_response(); // either make an instance or make it inherit everything from these classes, both work 
                return point2;
            }
        
            if (string_find(next, defenceSearch)){
                point3 = spells_response(); //read json file for an array selection of what they input or switch cases 
                return point3;
            }
        
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
                  battleResponse = attacking_response();
                  weaponStrength = next_step(battleResponse);
                  printw ("Your weapon's attack is %i\n", weaponStrength);
                  monsterHealth = monsterHealth - weaponStrength; //only an attack or spells option - no defence 
                  printw ("Monsters health after attack is %i\n", monsterHealth);
                  printw ("Monsters Attack \n");
                  
                  //balance = (double)rand() / RAND_MAX; //random double to multiply the monster attack by 
                  //Mattack = monsterAttack * balance;
                  printw ("The monster did this much %i damage!!", monsterAttack);
                  Phealth = Phealth - monsterAttack; //* balance;
                  printw ("Your health now is... %i \n", Phealth);
                  
                  
                  
              }
              if (Phealth <= 40 && Phealth > 0) //make this optional 
              { 
                  
                  printw ("You need to heal \n");
                  defenceResponse = defence_response();                  
                  Phealth = healing(defenceResponse, Phealth);
                   
                      
              }
                                                                
              else if(Phealth <= 0)
              {
                  startFinish = false;
                  printw ("You have died \n");
                  return startFinish;
              }
              else if(monsterHealth <=0){
                  startFinish = false;
                  printw ("You have killed the monster \n");
                  return startFinish;
              }
          }
   }
   
   int startGame(){
      
        printw ("There is something blocking your path \n");
        printw ("What would you like to do? \n");
        printw ("-----   ");
        //choice = get_line();
        getnstr(choice, sizeof(choice)-1);
        //ifstream response_file("response.json", ifstream::binary);
        //response_file >> choice;
        if (choice == "attack") { //json list needed so bad 
            battle();
        }
        else {
            printw ("Move along, move along \n");
        }
   }
};

int main()
{
   srand(time(NULL));
   //User_Response initialise;
   //initialise.name_selection(); - for the name selection make it part of laod screen to check if name is in db
   AttackTest go;
   go.startGame();
}
