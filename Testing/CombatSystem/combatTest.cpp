#include <iostream>
#include <string>
#include <time.h>
#include <locale>
#include <algorithm>

using namespace std;
//#include "libsqlite.hpp"

class Combat { 
    private:
    string response;
    public:    
    string get_line()
    {
        getline(cin, response);
        transform(response.begin(), 
                  response.end(), 
                  response.begin(), 
                  ::tolower);
        return response;
    }
};

class Dragon : public Combat {
private:
    int health = rand() % (200 - 150 + 1) + 150;
    int attackStr = rand() % (50 - 10 + 1) + 10;
    int magAbil = rand() % (200 - 20 + 1) + 20;
    int mana = 70;
    int def = rand() % (400 - 100 + 1) + 100;
public:
    int get_health(){
        return health;
    }
    int get_attack(){
        return attackStr;        
    }
};

class Playable_Character {
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
};

class Attack : virtual public Dragon {
    private:
    string attackResponse;
    string attackResponseOne;
    string const weaponOne = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    string const weaponTwo = "bow";
    string const weaponThree = "sword"; //secion might need to be in the attack response function to then change it up if it has a different name
    int weaponStrengthOne = 20;
    int weaponStrengthTwo = 30;
    int weaponStrengthThree = 40; //also from database 
    //int weaponStrength;
    
    public:
    Attack()
    {
    }

    int attack_response() //try and catch errors for wrong input and ppossible sql failures 
    {
        /*string sqliteFile = "<<whatever the data baseness is>>";
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select weaponstats " subject to change 
                       "from weapon_table "
                       "where weapon = ?");
        cur->prepare();*/
        
        
        cout << "These are the weapons you can use: " << endl
        << "-    Deal damage with a " << weaponOne << endl 
        << "-    Destroy enemy whilst weilding a " << weaponTwo << endl
        << "-    Put them 6 feet under with your " << weaponThree << endl
        << "What weapon would you like to use?" << endl;
        attackResponse = get_line();
                

        size_t weaponOptionOne = attackResponse.find(weaponOne);
        if (weaponOptionOne != string::npos) 
        {
            //cur-> bind(1,weaponOne);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthOne; //can have a bind database call
        }
        size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        if (weaponOptionTwo != string::npos) 
        {
            //cur->bind(1,weaponTwo);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthTwo;
        }
        size_t weaponOptionThree = attackResponse.find(weaponThree);
        if (weaponOptionThree != string::npos) 
        {
            //cur->bind(1,weaponThree);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthThree;
        }
        return 0;
    }                            
};

class Spells : virtual public Dragon{
    private:
    string spellResponse;
    string spellResponseOne;
    string const spellOne = "decay";
    string const spellTwo = "potent slap";
    string const spellThree = "loud noise";
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
        cout << "These are the spells you can use: " << endl;  
        cout << "-    Cast " << spellOne << endl;  
        cout << "-    Cast " << spellTwo << endl; 
        cout << "-    Cast " << spellThree << endl; 
        cout << "What spell would you like to use?" << endl;
        spellResponse = get_line();
        
 
        size_t spellAttackOne = spellResponse.find(spellOne);        
        if (spellAttackOne!=string::npos){
            //cur-> bind(1,spellOne);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthOne;
         
        }
        size_t spellAttackTwo = spellResponse.find(spellTwo);
        if (spellAttackTwo!=string::npos){
            //cur-> bind(1,spellTwo);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthTwo;

        }
        size_t spellAttackThree = spellResponse.find(spellThree);
        if (spellAttackThree!=string::npos){
            //cur-> bind(1,spellThree);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthThree;

        }
    }
    
};

class Defence : virtual public Dragon{
    private:
    string defenceResponse;
    string defenceResponseOne;
    string const defenceOne = "heal"; 
    string const defenceTwo = "syrup";
    string const defenceThree = "potion";
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
            cout << "These are the defences you can use: " << endl; 
            cout << "-    Use ability " << defenceOne << endl; 
            cout << "-    Use ability " << defenceTwo << endl; 
            cout << "-    Use ability " << defenceThree << endl;  
            cout << "What defence would you like to do?" << endl;
            defenceResponse = get_line();
            
    
            size_t defenceOptionOne = defenceResponse.find(defenceOne);
                if (defenceOptionOne != string::npos){
                    //cur-> bind(1,defenceOne);
                    //defenceAmount = cur->get_int(0);
                    //return defenceAmount;
                    return heal;
    
                }
            size_t defenceOptionTwo = defenceResponse.find(defenceTwo);
                if (defenceOptionTwo!=string::npos){
                    //cur->bind(1,defenceTwo);
                    //defenceAmount = cur->get_int(0);
                    //return defenceAmount;
                    return syrup;

                }
            size_t defenceOptionThree = defenceResponse.find(defenceThree);
                if (defenceOptionThree!=string::npos){
                    //cur->bind(1,defenceThree);
                    //defenceAmount = cur->get_int(0);
                    //return defenceAmount;
                    return potion;
                }
        return 0;
    }
};

class User_Response : public Warrior, public Combat { //includes classes for character selection
        //needs a function to pick which character they are and can then call it all from there, class has to be chosen first
        public:
        string characterChoice;
        string characterChoiceOne;
        string nameChoice;
        string const warriorSearch = "warrior";

        User_Response()
        {
        }

        int name_selection()
        {
            cout << "Please name your character... " << endl; //save to db
            cout << "--- ";
            nameChoice = get_line();
            Dragon bob; //section to create all of the monster within the game - limited amount
            character_selection(nameChoice);
        }

        int character_selection(string playerName)
        {
            cout << "Choose a class for " << nameChoice << endl;
            cout << "-  Warrior." << endl;
            characterChoiceOne = get_line();
            characterChoice = lower_case(characterChoiceOne);
            //save this to database possibly - can find the attributes given what comes out

            int classChoiceW = characterChoice.find(warriorSearch);

            if (classChoiceW != -1) {
                Warrior player;
                player.name = playerName;
                cout << player.name << endl;
            }
            else {
                character_selection(playerName);
            }
        }
    };   

class AttackTest : public Attack, public Spells, public Defence{
    private:
    string choice;
    string response;
    int nextA;
    int nextD;
    int nextS;
    string const attackSearch = "attack"; 
    string const spellSearch = "spell"; //string of words to use instead of just one word
    string const defenceSearch = "defence";
    string initialResponse;
    string fightingResponse;
    string battleResponse;
    int defenceResponse;
    int point1;
    int point2;
    int point3;
    int healingPlayer;
    int weaponStrength;
    double balance;
    Dragon bob;
    Dragon mike;
    int Phealth;
    int monsterHealth = bob.get_health();
    int monsterAttack = bob.get_attack();    
    
    public:
    
    int healing(int amount, int playerHealth){  
        playerHealth = playerHealth + amount;
        return playerHealth;
    }
    
    string attacking_response(){
        cout << "What would you like to do? " << endl; 
        cout << "-    Use an attack" << endl;
        //cout << "-    Defend yourself somehow" << endl; 
        cout << "-    Cast a spell" << endl;
        fightingResponse = get_line();
        return fightingResponse;
    }
    
    
    int next_step(string next){
        nextA = next.find(attackSearch);
        nextS = next.find(spellSearch);
        nextD = next.find(defenceSearch);
        
            if (nextA != -1 ){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
                point1 = attack_response();
                return point1;
            }
        
            if (nextD != -1){
                point2 = defence_response(); // either make an instance or make it inherit everything from these classes, both work 
                return point2;
            }
        
            if (nextS != -1){
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
                  cout << "The monsters health is "<< monsterHealth << endl;
                  battleResponse = attacking_response();
                  weaponStrength = next_step(battleResponse);
                  cout << "Your weapon's attack is " << weaponStrength << endl;
                  monsterHealth = monsterHealth - weaponStrength; //only an attack or spells option - no defence 
                  cout << "Monsters health after attack is "<< monsterHealth << endl;
                  cout << "Monsters Attack" << endl;
                  
                  balance = (double)rand() / RAND_MAX;
                  cout << balance << endl;
                  cout << "The monster did this much " << monsterAttack * balance << " damage!!" << endl;
                  Phealth = Phealth - monsterAttack * balance;
                  cout << "Your health now is... " << Phealth << endl;
                  
                  
                  
              }
              if (Phealth <= 40 && Phealth > 0)
              { 
                  
                  cout << "You need to heal" << endl;
                  defenceResponse = defence_response();                  
                  Phealth = healing(defenceResponse, Phealth);
                  //Phealth = Phealth + healingPlayer; 
                      
              }
                                                                
              else if(Phealth <= 0)
              {
                  startFinish = false;
                  cout << "You have died" << endl;
                  return startFinish;
              }
              else if(monsterHealth <=0){
                  startFinish = false;
                  cout << "You have killed the monster" << endl;
                  return startFinish;
              }
          }
   }
   
   int startGame(){
      
        cout << "There is something blocking your path" << endl;
        cout << "What would you like to do?" << endl;
        cout << "-----  ";
        choice = get_line();
        if (choice == "attack") { //json list needed so bad 
            battle();
        }
        else {
            cout << "Move along, move along" << endl;
        }
   }
};

int main()
{
   srand(time(NULL));
   //User_Response initialise;
   //initialise.name_selection();
   AttackTest go;
   go.startGame();
}
