#include <iostream>
#include <string>
#include <cstring>


using namespace std;
class combat{
    public:
    string const attackSearch = "attack"; //melee
    string const spellSearch = "spells";
    string const defenseSearch = "defense";
    string const healSeatch = "heal"; //not implemented yet, decisions need to be made 
    string initialResponse;
    string initialResponseOne;
    string response;
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
    string initial_response(){
        cout << "What would you like to do?" << endl;
        initialResponseOne = get_line();
        initialResponse = lower_case(initialResponseOne);
    return initialResponse;
    }
    
    
};

class attack : public combat{
    public:
    string attackResponse;
    string attackResponseOne;
    string const dagger = "dagger"; //these bottom 3 can be calling from a database for the weapons which they have, more code needed to define each 
    string const bow = "bow";
    string const sword = "sword";
    
    int attack_response(){
        cout << "What weapon would you like to use?" << endl;
        attackResponseOne = get_line();
        attackResponse = lower_case(attackResponseOne);
    return 0;
    }
    int attack_choice(){ 
        size_t attackDagger = attackResponse.find(dagger);
        if (attackDagger!=string::npos){
            cout << "dagger works" << endl;
        }
        size_t attackBow = attackResponse.find(bow);
        if (attackBow!=string::npos){
            cout << "bow works" << endl;
        }
        size_t attackSword = attackResponse.find(sword);
        if (attackSword!=string::npos){
            cout << "dagger works" << endl;
        }
    return 0;
    }
};

class spells : public combat{
    public:
    string spellResponse;
    string spellResponseOne;
    string const spellOne = "spell 1";
    string const spellTwo = "spell 2";
    string const spellThree = "spell 3";
    
    int spell_response(){ 
        cout << "What spell would you like to use?" << endl;
        spellResponseOne = get_line();
        spellResponse = lower_case(spellResponseOne);
    return 0;
    }
    
    int spell_choice(){
        size_t spellAttackOne = spellResponse.find(spellOne);        
        if (spellAttackOne!=string::npos){
            cout << "spell1 works" << endl;
        }
        size_t spellAttackTwo = spellResponse.find(spellTwo);
        if (spellAttackTwo!=string::npos){
            cout << "spell2 works" << endl;
        }
        size_t spellAttackThree = spellResponse.find(spellThree);
        if (spellAttackThree!=string::npos){
            cout << "spell3 works" << endl;
        }
    return 0;
    }
    
};

class defense : public combat{
    public:
    string defenseResponse;
    string defenseResponseOne;
    string const heal = "heal";
    string const block = "block";
    
    int defense_response(){
        cout << "What defense would you like to do?" << endl;
        defenseResponseOne = get_line();
        defenseResponse = lower_case(defenseResponseOne);
    return 0;
    }
    int defense_choice(){    
    size_t defenseHeal = defenseResponse.find(heal);
        if (defenseHeal!=string::npos){
            cout << "heal works" << endl;
        }
    size_t defenseBlock = defenseResponse.find(block);
        if (defenseBlock!=string::npos){
            cout << "block works" << endl;
        }
    }
};



int main(){    
    return 0;
}
