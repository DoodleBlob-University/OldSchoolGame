#include <iostream>
#include <string>
#include <cstring>
//George Franklin
/*Currently is a combat option selection with the use of taking in type from the user
 * the damage and actual operation/selection will come with integreation with Matt's code
 * steps after this are to use database and make each option selection do something
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
    return response;
    }
    


};

class Attack : virtual public Combat{ //use of virtual to stop Diamond Death within classes = https://stackoverflow.com/questions/137282/how-can-i-avoid-the-diamond-of-death-when-using-multiple-inheritance
    public:
    string attackResponse;
    string attackResponseOne;
    string const weaponOne = "dagger"; //database reference for each 
    string const weaponTwo = "bow"; //these will not have to be hardcoded because of this 
    string const weaponThree = "sword";
    
    Attack(){
        
    }
    
    int attack_response(){
        cout << "These are the weapons you can use: " << endl; 
        cout << "-    Deal damage with a " << weaponOne << endl;
        cout << "-    Destroy enemy whilst weilding a " << weaponTwo << endl;
        cout << "-    Put them 6 feet under with your " << weaponThree << endl; //possible code duplication 
        cout << "What weapon would you like to use?" << endl;
        attackResponseOne = get_line();
        attackResponse = lower_case(attackResponseOne);
        attack_choice();
    }
    int attack_choice(){ 
        size_t weaponOptionOne = attackResponse.find(weaponOne);
        if (weaponOptionOne!=string::npos){
            cout << "Weapon 1 works" << endl;
        }
        size_t weaponOptionTwo = attackResponse.find(weaponTwo);
        if (weaponOptionTwo!=string::npos){
            cout << "Weapon 2 works" << endl;
        }
        size_t weaponOptionThree = attackResponse.find(weaponThree);
        if (weaponOptionThree!=string::npos){
            cout << "dagger works" << endl;
        }
    }
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
            cout << "Option 1 works" << endl;
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
class User_Response : public Defense, public Attack, public Spells{
    public:    
    string initialResponse;
    string initialResponseOne;
    int nextA;
    int nextD;
    int nextS;
    string const attackSearch = "attack"; 
    string const spellSearch = "spells";
    string const defenseSearch = "defense";
    
    User_Response(){
        
    }
    
    string initial_response(){
        cout << "You can either: " << endl;
        cout << "-    Attack the monster." << endl;
        cout << "-    Use a defense ability." << endl;
        cout << "-    Cast spells on the enemy." << endl;
        cout << "What would you like to do?" << endl;
        initialResponseOne = get_line();
        initialResponse = lower_case(initialResponseOne); 
        next_step(initialResponse);
    return initialResponse;
    }
    
        int next_step(string next){
        nextA = next.find(attackSearch);
        nextD = next.find(defenseSearch);
        nextS = next.find(spellSearch); //instead of using find could do a string search algorithm
        //cout << nextA;
        //cout << nextD;
        //cout << nextS;
        
        if (nextA != -1){ //-1 comes out if the word is found within the input 
            Attack NextStep; //"Test file proves this 
            NextStep.attack_response();
        }
        else if(nextD != -1){
            Defense NextStep;
            NextStep.defense_response();
        }
        else if(nextS != -1){
            Spells NextStep;
            NextStep.spell_response();
        }
        else{
            initial_response();
        }
    }
    
};


int main(){
    User_Response testing;
    testing.initial_response();
    return 0;
}
