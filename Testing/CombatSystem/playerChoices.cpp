#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
//George Franklin + Matt Fretwell
/*Currently is a combat option selection with the use of taking in type from the user
 * the damage and actual operation/selection will come with integreation with Matt's code
 * steps after this are to use database and make each option selection do something
 * not too sure how many of the includes are needed but we will see
 */
using namespace std;

class Combat{
    public:
    string response;
    
    Combat(){        
    }    
    string lower_case(string input){     
        for (size_t i = 0; input.size() > i; ++i){
            if ((input[i] >= 'A') && (input[i] <= 'Z')){
                input[i] = input[i] - 'A' + 'a';
            }
        }       
    return input;
    }
        
    string get_line(){ 
        getline(cin, response);
        //response2 = lower_case(response1); to reduce code usage 
    return response;
    }
};

class Monster : virtual public Combat{
    public:
    int monster_battlecry(string cry){
        cout << cry << endl;
    }
};

class Goblin : public Monster{
    public:

    int health = rand()%(8-5+1)+5;
    int attackStr = rand()%(8-5+1)+5;
    int magAbil = rand()%(3-1+1)+1;
    int mana = 10;
    int def = rand()%(6-2+1)+2;
        
};

class Wolf : public Monster{
    public:
    
    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;
    
};

class Ugandan_Knuckles : public Monster{
    public:
    

    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;    
    string const uCryOne = "We fight for da qween!";
    string const uCryTwo = "We know de wae.";
    
    int time_to_cry(){
        monster_battlecry(uCryOne);
        monster_battlecry(uCryTwo);
    }
};

class Rabbit : public Monster{
    public:
    
    int health = rand()%(30-10+1)+10;
    int attackStr = rand()%(14-1+1)+1;
    int magAbil = rand()%(10-0+1)+0;
    int mana = 10;
    int def = rand()%(10-3+1)+3;
    
};

class Dragon : public Monster{
    public:

    int health = rand()%(200-150+1)+150;
    int attackStr = rand()%(500-10+1)+10;
    int magAbil = rand()%(200-20+1)+20;
    int mana = 70;
    int def = rand()%(400-100+1)+100;
    
};

class Playable_Character{
    private:

    public:
        int PlayerHealth =20;
        int XP = 0;
    //XP adding function, can be implemented with different monsters later.
    int addXP(int pXP){
        XP= XP + pXP;
    }
    
    //Damage Taking Function, will be changed to accomodate armour and def stats. Need databse for that.
    int damageTaken(int mAttack){
        health = health - mAttack;    
    }

};

class Warrior : virtual public Playable_Character{
    private:

    public:
        int wAttackStr = 55;
        int wDef = 60;
        int wMagAbil = 10;
        int wMana = 20;

};

class Mage : virtual public Playable_Character{
    private:

    public:
        int wAttackStr = 30;
        int wDef = 40;
        int wMagAbil = 60;
        int wMana = 50;
    
};

class Archer : virtual public Playable_Character{
    private:

    public:
        int wAttackStr = 45;
        int wDef = 50;
        int wMagAbil = 35;
        int wMana = 30;
    
};

class Attack : virtual public Combat{ //use of virtual to stop Diamond Death within classes = https://stackoverflow.com/questions/137282/how-can-i-avoid-the-diamond-of-death-when-using-multiple-inheritance
    public:
    string attackResponse;
    string attackResponseOne;
    string const weaponOne = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it 
    string const weaponTwo = "bow"; 
    string const weaponThree = "sword";
    
    Attack(){        
    }
    
    int attack_response(){
        cout << "These are the weapons you can use: " << endl; 
        cout << "-    Deal damage with a " << weaponOne << endl; //could make each option selection random
        cout << "-    Destroy enemy whilst weilding a " << weaponTwo << endl;
        cout << "-    Put them 6 feet under with your " << weaponThree << endl; 
        cout << "What weapon would you like to use?" << endl;
        attackResponseOne = get_line();
        attackResponse = lower_case(attackResponseOne);
        attack_choice();
    }
    string attack_choice(){ 
        size_t weaponOptionOne = attackResponse.find(weaponOne);
        if (weaponOptionOne!=string::npos){
            cout << "Weapon 1 works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 10 << endl; //these numbers are just to test with during battle, can do damage and all that 
            myfile.close();
            attack_section();
            /*
            can make the primary key or foreign key link to the players options
            update/alter the db so it selects the choice 
            section would call the database for the specific stats of each of the weapons 
            could have a weapon durability which after use we can update the database with - this adds an element of choice to your weapon selection during a fight 
            */
        }
        size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        if (weaponOptionTwo!=string::npos){
            cout << "Weapon 2 works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 8 << endl;
            myfile.close();
        }
        size_t weaponOptionThree = attackResponse.find(weaponThree);
        if (weaponOptionThree!=string::npos){
            cout << "Weapon 3 works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 9 << endl;
            myfile.close();
        }
    }
    //function to send backwards 
};

class Spells : virtual public Combat{
    public:
    string spellResponse;
    string spellResponseOne;
    string const spellOne = "decay";//database reference
    string const spellTwo = "potent slap";
    string const spellThree = "loud noise";
    
    Spells(){ //supposedly to initialise the use of the class 
        
    }
    
    int spell_response(){
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
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 15 << endl;
            myfile.close();
        }
        size_t spellAttackTwo = spellResponse.find(spellTwo);
        if (spellAttackTwo!=string::npos){
            cout << "Spell two works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 5 << endl;
            myfile.close();
        }
        size_t spellAttackThree = spellResponse.find(spellThree);
        if (spellAttackThree!=string::npos){
            cout << "Spell three works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 11 << endl;
            myfile.close();
        }
    }
    
};

class Defense : virtual public Combat{
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
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 10 << endl;
            myfile.close();
        }
    size_t defenseOptionTwo = defenseResponse.find(defenseTwo);
        if (defenseOptionTwo!=string::npos){
            cout << "Option 2 works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 10 << endl;
            myfile.close();
        }
    size_t defenseOptionThree = defenseResponse.find(defenseThree);
        if (defenseOptionThree!=string::npos){
            cout << "Option 3 works" << endl;
            ofstream myfile;
            myfile.open("weaponChoice.txt");
            myfile << 10 << endl;
            myfile.close();
        }
    }
};

class User_Response : public Defense, public Attack, public Spells, public Warrior, public Archer, public Mage, public Goblin, public Wolf, public Rabbit, public Dragon{
    //needs a function to pick which character they are and can then call it all from there, class has to be chosen first 
    public:    
    string initialResponse;
    string initialResponseOne;
    string responseError;
    string responseErrorOne;
    string characterChoice;
    string characterChoiceOne;
    string nameChoice;
    int nextA;
    int nextD;
    int nextS;
    string const attackSearch = "attack"; 
    string const spellSearch = "spells"; //string of words to use instead of just one word
    string const defenseSearch = "defense";
    string const warriorSearch = "warrior";
    string const archerSearch = "archer";
    string const mageSearch = "mage";
    
    User_Response(){        
    }
    
    int name_selection(){
        cout << "Please name your character... " << endl;//save to db 
        cout << "--- ";
        nameChoice = get_line();        
        
        ofstream myfile;
        myfile.open ("playerResponses.txt");
        myfile << nameChoice << endl;
        myfile.close();
        
        Dragon bob;//section to create all of the monster within the game - limited amount 
        Dragon steve;
        Dragon gerrald;
        Dragon mike;
        Goblin boblin;
        Goblin stevelin;
        Goblin gerraldlin;
        Goblin mikelin;
        Wolf bobolf;
        Wolf steveolf;
        Wolf mikeolf;
        Wolf gerraldolf;
        Rabbit bobit;
        Rabbit steveit;
        Rabbit gerraldit;
        Rabbit mikeit;
        /*cout << bob.health << endl;
        cout << steve.health << endl; just to check if the random worked when creating multiple
        cout << boblin.health << endl;
        cout << mikelin.health << endl;*/
       
        character_selection(nameChoice);
    }
    
    int character_selection(string playerName){ //this function and the one above only need to be called once
        //this can be changed to be put into the login
        cout << "Choose a class for " << nameChoice << endl;
        cout <<"-  Warrior." << endl;
        cout <<"-  Archer." << endl;
        cout <<"-  Mage." << endl;
        characterChoiceOne = get_line();
        characterChoice = lower_case(characterChoiceOne);
        
        int classChoiceW = characterChoice.find(warriorSearch);
        int classChoiceM = characterChoice.find(mageSearch);
        int classChoiceA = characterChoice.find(archerSearch);
        
        if(classChoiceW != -1){
            ofstream myfile;
            myfile.open("playerResponsesClass.txt");
            myfile << "Warrior" << endl;
            myfile.close();
            Warrior playerName;
            cout << playerName.wAttackStr << endl;
        }
        else if(classChoiceM != -1){
            ofstream myfile;
            myfile.open("playerResponsesClass.txt");
            myfile << "Mage" << endl;
            myfile.close();
            Mage playerName;
        }
        else if(classChoiceA != -1){
           ofstream myfile;
           myfile.open("playerResponsesClass.txt");
           myfile << "Archer" << endl;
           myfile.close();
           Archer playerName;
        }
        
        else{
            character_selection(playerName);
        }
    }
    
    string initial_response(){ //this needs to be included within the while loop
        cout << "You can either: " << endl;
        cout << "-    Attack the monster." << endl; //could make these messages random 
        cout << "-    Use a defense ability." << endl;
        cout << "-    Cast spells on the enemy." << endl;
        cout << "What would you like to do?" << endl;
        initialResponseOne = get_line();
        initialResponse = lower_case(initialResponseOne); 
        next_step(initialResponse);
    return initialResponse;
    }
    
    int initial_response_error(){
        cout << "Please enter either, attack, defense or spells" << endl;
        responseErrorOne = get_line();
        responseError = lower_case(responseErrorOne);
        next_step(responseError);
    }
    
        int next_step(string next){
        nextA = next.find(attackSearch);
        nextD = next.find(defenseSearch);
        nextS = next.find(spellSearch); //instead of using find could do a string search algorithm
        //cout << nextA;
        //cout << nextD;
        //cout << nextS;
        
        if (nextA != -1){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
            attack_response();
        }
        else if(nextD != -1){
            defense_response();
        }
        else if(nextS != -1){
            spell_response();
        }
        else{
            initial_response_error();
        }
            
    }
    
        /*int attack_section(){
            //include everything which the user has selected and use a while loop to continue the fight until the monster or players health is 0
            while(PlayerHealth != 0){
                if (health == 0){ used to simulate a battle, can make multiple calls for each attack, starting to get a grip
                    break
                }
            }
        }*/
    
};

int main(){
    srand(time(NULL));
    User_Response testing;
    testing.name_selection();
    testing.initial_response();
    Goblin geoff;
    //run the user_response function to select the weapon stats from the db
    //combine both of these by defining their types within the main and conbine them into a function within the main
    //same with the monster but only one call 
    
    return 0;
}
