#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Combat { //could have the general while loop with if statements which could help?
    private:
    string response;
    public:
    
    string lower_case(string input)//change this or add more functions to be called 
    {
        for (size_t i = 0; input.size() > i; ++i) {
            if ((input[i] >= 'A') && (input[i] <= 'Z')) {
                input[i] = input[i] - 'A' + 'a';
            }
        }
        return input;
    }

    string get_line()
    {
        getline(cin, response);
        //response2 = lower_case(response1); to reduce code usage
        return response;
    }
    
    int monster_battlecry(string cry)
    {
        cout << cry << endl;
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
    int PlayerHealth = 20;
    int XP = 0;
};

class Warrior : public Playable_Character {
private:
public:
    int wAttackStr = 55;
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
    string const weaponThree = "sword";
    int weaponStrengthOne = 20;
    int weaponStrengthTwo = 30;
    int weaponStrengthThree = 40; //also from database 
    
    public:
    Attack()
    {
    }

    int attack_response()
    {
        cout << "These are the weapons you can use: " << endl
        << "-    Deal damage with a " << weaponOne << endl //could make each option selection random
        << "-    Destroy enemy whilst weilding a " << weaponTwo << endl
        << "-    Put them 6 feet under with your " << weaponThree << endl
        << "What weapon would you like to use?" << endl;
        getline(cin, attackResponseOne);
        attackResponse = lower_case(attackResponseOne);        

        size_t weaponOptionOne = attackResponse.find(weaponOne);
        if (weaponOptionOne != string::npos) 
        {
            //cout << "Weapon 1 works" << endl;        
            return weaponStrengthOne;
        }
        size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        if (weaponOptionTwo != string::npos) 
        {
            //cout << "Weapon 2 works" << endl;           
            return weaponStrengthTwo;
        }
        size_t weaponOptionThree = attackResponse.find(weaponThree);
        if (weaponOptionThree != string::npos) 
        {
            //cout << "Weapon 3 works" << endl;            
            return weaponStrengthThree;
        }
        return 0;
    }                            
};

class Spells : virtual public Dragon{
    private:
    string spellResponse;
    string spellResponseOne;
    string const spellOne = "decay";//database reference
    string const spellTwo = "potent slap";
    string const spellThree = "loud noise";
    int spellStrengthOne = 10;
    int spellStrengthTwo = 20;
    int spellStrengthThree = 30;
    
    public:  
    Spells(){ //supposedly to initialise the use of the class 
        
    }
    
    int spells_response(){
        cout << "These are the spells you can use: " << endl;  
        cout << "-    Cast " << spellOne << endl;  
        cout << "-    Cast " << spellTwo << endl; 
        cout << "-    Cast " << spellThree << endl; //possible code duplication
        cout << "What spell would you like to use?" << endl;
        spellResponseOne = get_line();
        spellResponse = lower_case(spellResponseOne);
 
        size_t spellAttackOne = spellResponse.find(spellOne);        
        if (spellAttackOne!=string::npos){
            //cout << "Spell one works" << endl;
            return spellStrengthOne;
         
        }
        size_t spellAttackTwo = spellResponse.find(spellTwo);
        if (spellAttackTwo!=string::npos){
            //cout << "Spell two works" << endl;
            return spellStrengthTwo;

        }
        size_t spellAttackThree = spellResponse.find(spellThree);
        if (spellAttackThree!=string::npos){
            //cout << "Spell three works" << endl;
            return spellStrengthThree;

        }
    }
    
};

class Defense : virtual public Dragon{
    private:
    int defenseResponse;
    int defenseResponseOne;
    string const defenseOne = "heal";//database reference for each 
    string const defenseTwo = "syrup";
    string const defenseThree = "potion";
    int heal = 2;
    int syrup = 5;
    int potion = 8;
    
    public:
    
    Defense(){
        
    }
    
    int defense_response()
    {
        cout << "These are the defenses you can use: " << endl
        << "-1    Use ability " << defenseOne << endl
        << "-2    Use ability " << defenseTwo << endl //for printw("%s", defenseTwo)
        << "-3    Use ability " << defenseThree << endl
        << "What defense would you like to do?" << endl;
        
        do{cin >> defenseResponse;} while(defenseResponse > 3 && defenseResponse < 1);
        {
            switch(defenseResponse){
                case 1:
                    cout << "Healing for " << heal << endl;
                    return heal;
                    break;
                
                case 2:
                    cout << "Healing for " << syrup << endl;
                    return syrup;
                    break;
                
                case 3:
                    cout << "Healing for " << potion << endl;
                    return potion;
                    break;
            }
          
        }
        
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

class AttackTest : public Attack, public Spells, public Defense{
    private:
    string choice;
    string response;
    string responseError;
    string responseErrorOne;
    int nextA;
    int nextD;
    int nextS;
    string moveForward;
    string const attackSearch = "attack"; 
    string const spellSearch = "spells"; //string of words to use instead of just one word
    string const defenseSearch = "defense";
    string initialResponse;
    string initialResponseOne;
    string fightingResponse;
    string fightingResponseOne;
    string battleResponse;
    int defenseResponse;
    int point1;
    int point2;
    int point3;
    int amount;
    int healing1;
    int andAgain;
    int weaponStrength;
    double balance;
    Dragon bob;
    Dragon mike;
    int Phealth;
    int monsterHealth = bob.get_health();
    int monsterAttack = bob.get_attack();
    int healingChance;
    
    public:
    
    int healing(int amount, int playerHealth){  
        playerHealth = playerHealth + amount;
        return playerHealth;
    }
 
    string initial_response(){//section can go into the combat class for each interation but need while loop in this section
        cout << "You can either: " << endl;
        cout << "-    Attack the monster." << endl; //could make these messages random 
        cout << "-    Use a defense ability." << endl;
        cout << "-    Cast spells on the enemy." << endl;
        cout << "What would you like to do?" << endl;
        getline(cin, initialResponseOne);
        initialResponse = lower_case(initialResponseOne);
        return initialResponse;
    }
    
    /*int initial_response_error(){
        cout << "Please enter either, attack, defense or spells" << endl;
        getline(cin, responseErrorOne);
        responseError = lower_case(responseErrorOne);
        //next_step(responseError);
        cout << responseError << endl;
        return responseError;
    }*/
    
    string attacking_response(int playerHealth){
        cout << "Your health is " << playerHealth << "." << endl;
        cout << "What would you like to do? " << endl; 
        cout << "-    Use an attack" << endl;
        //cout << "-    Defend yourself somehow" << endl; 
        cout << "-    Cast a spell" << endl;
        getline(cin, fightingResponseOne);
        fightingResponse = lower_case(fightingResponseOne);
        return fightingResponse;
    }
    
    
    int next_step(string next){
        nextA = next.find(attackSearch);
        nextS = next.find(spellSearch);
        nextD = next.find(defenseSearch);
        
            if (nextA != -1 ){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
                point1 = attack_response();
                //cout << point1 << endl;
                return point1;
            }
        
            if (nextD != -1){
                point2 = defense_response(); // either make an instance or make it inherit everything from these classes, both work 
                //cout << point2 << endl;
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
           Phealth = 39; //database
           bool startFinish = true;
           while(startFinish){
              if (Phealth > 0 && monsterHealth > 0)
              {
                  cout << "The monsters health is "<< monsterHealth << endl;
                  battleResponse = attacking_response(Phealth);
                  weaponStrength = next_step(battleResponse);
                  cout << "Your weapon's attack is " << weaponStrength << endl;
                  monsterHealth = monsterHealth - weaponStrength; //only an attack or spells option - no defense 
                  cout << "Monsters health after attack is "<< monsterHealth << endl;
                  cout << "Monsters Attack" << endl;
                  
                  balance = (double)rand() / RAND_MAX;
                  cout << balance << endl
                      << monsterAttack * balance << endl;
                  Phealth = Phealth - monsterAttack * balance;
                  
                  
                  
              }
              if (Phealth < 40 && Phealth > 0) //defense only section - doesn't work currently 
              { 
                  
                  /*cout << "You have the chance to heal - would you like to?" << endl
                      << "1- To heal" << endl
                      << "2- To not... " << endl; 
                  
                  cin >> healingChance;
                  if (healingChance == 1){
                      defenseResponse = next_step("Defense");                     
                      healing1 = healing(defenseResponse, Phealth);
                      Phealth = healing1;
                      
                  }
                  else{
                      cout << "Interesting choice" << endl;
                      
                  }                  
              }*/
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
        getline(cin, choice);
        if (choice == "attack") {
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
