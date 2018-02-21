#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <array>
using namespace std;

class Combat {
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

class Monster : virtual public Combat {
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

class Warrior : virtual public Playable_Character {
private:
public:
    int wAttackStr = 55;
    int wDef = 60;
    int wMagAbil = 10;
    int wMana = 20;
};

class Attack : public Dragon { //use of virtual to stop Diamond Death within classes = https://stackoverflow.com/questions/137282/how-can-i-avoid-the-diamond-of-death-when-using-multiple-inheritance
public:
    string attackResponse;
    string attackResponseOne;
    string const weaponOne = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    string const weaponTwo = "bow";
    string const weaponThree = "sword";
    int weaponStrength;
    int Phealth;
    int monsterHealth;
    
    Dragon bob;

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
        if (weaponOptionOne != string::npos) {
            cout << "Weapon 1 works" << endl;
            weaponStrength = 20;
            attacking(weaponStrength);
        }
    }
   int attacking(int weaponStrength){
        Phealth = 100;
        monsterHealth = bob.health;
            while(Phealth!=0 && monsterHealth!=0)
            {
                cout << monsterHealth << endl;
                monsterHealth = monsterHealth - weaponStrength*0.7;
                cout << monsterHealth << endl;
                break;
                //need iteration to allow multiple attacks 
                    
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
            Dragon steve;
            Dragon gerrald;
            Dragon mike;
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

        /*int initalising_attack(){
            
        int monsterSelection = rand()% 5;
        array<string,4> monsterArray = {"bob", "steve", "gerrald","mike"};
        string monsterClass = monsterArray[monsterSelection];
        cout << monsterClass << endl;
        attack_response();
        //attacking(monsterClass, playerName);
        }
    
        int attacking(string monsterClass, string playername)
        {
            Goblin a_Selection(monsterClass); // explicit call of the constructor
            int monsterHealth = a_Selection.health;
            define what class they are for their situation 
            while(Phealth!=0 && monsterHealth!=0)
            {
                attack_response(); //use this and make sure it returns some kind of stats from the weapon selection
            }
        }*/
    };    

    class AttackTest : public Attack{
        public:
        string responseError;
        string responseErrorOne;
        int nextA;
        string const attackSearch = "attack"; 
        string const spellSearch = "spells"; //string of words to use instead of just one word
        string initialResponse;
        string initialResponseOne;


        string initial_response(){//section can go into the combat class for each interation but need while loop in this section
        cout << "You can either: " << endl;
        cout << "-    Attack the monster." << endl; //could make these messages random 
        cout << "-    Use a defense ability." << endl;
        //cout << "-    Cast spells on the enemy." << endl;
        cout << "What would you like to do?" << endl;
        initialResponseOne = get_line();
        initialResponse = lower_case(initialResponseOne); 
        next_step(initialResponse);
    }
    
    int initial_response_error(){
        cout << "Please enter either, attack, defense or spells" << endl;
        responseErrorOne = get_line();
        responseError = lower_case(responseErrorOne);
        next_step(responseError);       
    }
    
    int next_step(string next){
        nextA = next.find(attackSearch);
        
        if (nextA != -1 ){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
            Attack player;
            player.attack_response();
        }

        else{
            initial_response_error();
        }
            
    }
    int startGame()
    {
        cout << "There is something blocking your path" << endl;
        cout << "What would you like to do?" << endl;
        cout << "-----";
        string choice;
        cin >> choice;
        if (choice == "attack") {
            initial_response();
        }
        else {
            cout << "Move along, move along" << endl;
        }
    }
};

    int main()
    {
        srand(time(NULL));
        User_Response initialise;
        initialise.name_selection();
        AttackTest go;
        go.startGame();
    }
