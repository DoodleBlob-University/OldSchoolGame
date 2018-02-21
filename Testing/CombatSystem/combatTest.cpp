#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Combat { //could have the general while loop with if statements which could help?
public:
    string response;
    
    Combat()
    {
    }
    string lower_case(string input)
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
};

class Monster : public Combat {
public:
    int monster_battlecry(string cry)
    {
        cout << cry << endl;
    }
};

class Dragon : public Monster {
public:
    int health = rand() % (200 - 150 + 1) + 150;
    int attackStr = rand() % (500 - 10 + 1) + 10;
    int magAbil = rand() % (200 - 20 + 1) + 20;
    int mana = 70;
    int def = rand() % (400 - 100 + 1) + 100;
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

class Attack : public Dragon {
public:
    Dragon bob;
    Dragon mike;
    string attackResponse;
    string attackResponseOne;
    string const weaponOne = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    string const weaponTwo = "bow";
    string const weaponThree = "sword";
    int weaponStrength;
    int Phealth;
    int monsterHealth = bob.health;
    


    Attack()
    {
    }

    int attack_response()
    {
        cout << "These are the weapons you can use: " << endl;
        cout << "-    Deal damage with a " << weaponOne << endl; //could make each option selection random
        cout << "-    Destroy enemy whilst weilding a " << weaponTwo << endl;
        cout << "-    Put them 6 feet under with your " << weaponThree << endl;
        cout << "What weapon would you like to use?" << endl;
        getline(cin, attackResponseOne);
        attackResponse = lower_case(attackResponseOne);
        attack_choice();
    }
    string attack_choice()
    {
        size_t weaponOptionOne = attackResponse.find(weaponOne);
        if (weaponOptionOne != string::npos) 
        {
            cout << "Weapon 1 works" << endl;
            weaponStrength = 20;
            attacking(weaponStrength);
        }
        size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        if (weaponOptionTwo != string::npos) 
        {
            cout << "Weapon 2 works" << endl;
            weaponStrength = 30;
            attacking(weaponStrength);
        }
        size_t weaponOptionThree = attackResponse.find(weaponThree);
        if (weaponOptionThree != string::npos) 
        {
            cout << "Weapon 3 works" << endl;
            weaponStrength = 40;
            attacking(weaponStrength);
        }
    }
   int attacking(int weaponStrength){
        Phealth = 100;
            while(Phealth > 0 && monsterHealth > 0) //need to have a true or false section so the combat will stop when the health is at 0 or below
            {
                cout << monsterHealth << endl;
                monsterHealth = monsterHealth - weaponStrength*0.7;
                cout << monsterHealth << endl;
                
                attack_response();
                break;
                
                //need iteration to allow multiple attacks 
                //need to heal during attacks so this deffo needs to be in the combat 
            }
   }
};

class Spells : public Dragon{
    public:
    string spellResponse;
    string spellResponseOne;
    string const spellOne = "decay";//database reference
    string const spellTwo = "potent slap";
    string const spellThree = "loud noise";
    
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
        spell_choice(spellResponse);
    }
    
     int spell_choice(string spellResponse){
        size_t spellAttackOne = spellResponse.find(spellOne);        
        if (spellAttackOne!=string::npos){
            cout << "Spell one works" << endl;

        }
        size_t spellAttackTwo = spellResponse.find(spellTwo);
        if (spellAttackTwo!=string::npos){
            cout << "Spell two works" << endl;

        }
        size_t spellAttackThree = spellResponse.find(spellThree);
        if (spellAttackThree!=string::npos){
            cout << "Spell three works" << endl;

        }
    }
    
};

class Defense : public Dragon{
     public:
    string defenseResponse;
    string defenseResponseOne;
    string const defenseOne = "heal";//database reference for each 
    string const defenseTwo = "block";
    string const defenseThree = "potion";
    
    Defense(){
        
    }
    
    int defense_response(){
        cout << "These are the defenses you can use: " << endl; 
        cout << "-    Use ability " << defenseOne << endl; //possible code duplication
        cout << "-    Use ability " << defenseTwo << endl; 
        cout << "-    Use ability " << defenseThree << endl;  
        cout << "What defense would you like to do?" << endl;
        defenseResponseOne = get_line();
        defenseResponse = lower_case(defenseResponseOne);
        defense_choice(defenseResponse);
    }
    int defense_choice(string defenseResponse){    
    size_t defenseOptionOne = defenseResponse.find(defenseOne);
        if (defenseOptionOne != string::npos){
            cout << "Option 1  " << endl;

        }
    size_t defenseOptionTwo = defenseResponse.find(defenseTwo);
        if (defenseOptionTwo!=string::npos){
            cout << "Option 2 works" << endl;

        }
    size_t defenseOptionThree = defenseResponse.find(defenseThree);
        if (defenseOptionThree!=string::npos){
            cout << "Option 3 works" << endl;
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

    class AttackTest : public Attack{
        public:
        string responseError;
        string responseErrorOne;
        string choice;
        int nextA;
        int nextD;
        int nextS;
        string const attackSearch = "attack"; 
        string const spellSearch = "spells"; //string of words to use instead of just one word
        string const defenseSearch = "defense";
        string initialResponse;
        string initialResponseOne;


    int initial_response(){//section can go into the combat class for each interation but need while loop in this section
        cout << "You can either: " << endl;
        cout << "-    Attack the monster." << endl; //could make these messages random 
        cout << "-    Use a defense ability." << endl;
        cout << "-    Cast spells on the enemy." << endl;
        cout << "What would you like to do?" << endl;
        getline(cin, initialResponseOne);
        initialResponse = lower_case(initialResponseOne); 
        next_step(initialResponse);
        return 0;
    }
    
    int initial_response_error(){
        cout << "Please enter either, attack, defense or spells" << endl;
        getline(cin, responseErrorOne);
        responseError = lower_case(responseErrorOne);
        next_step(responseError);
        return 0;
    }
    
    int next_step(string next){
        nextA = next.find(attackSearch);
        nextS = next.find(spellSearch);
        nextD = next.find(defenseSearch);
        
        if (nextA != -1 ){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
            Attack player;
            player.attack_response();
        }
        
        else if (nextD != -1){
            Defense player;
            player.defense_response(); // either make an instance or make it inherit everything from these classes, both work 
        }
        
        else if (nextS != -1){
            Spells player;
            player.spells_response();
        }

        else{
            //initial_response_error();
            //do nothing for now;
            //cout << "Still happening" << endl;
        }
        
        return 0;
            
    }
    int startGame()
    {
        cout << "There is something blocking your path" << endl;
        cout << "What would you like to do?" << endl;
        cout << "-----  ";
        getline(cin, choice);
        if (choice == "attack") {
            initial_response();
        }
        else {
            cout << "Move along, move along" << endl;
        }
        return 0;
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
