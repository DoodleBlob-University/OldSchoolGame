#include <iostream>
#include <string>
#include <cstring>


using namespace std;
int main(){
    //display options to the user for each situation, ncurses helps with the interface but this is the simple logic 

    string const attackSearch = "attack";
    string const defenseSearch = "defense";
    string const bagSearch = "bag";
    string response;
      
    
    cout << "What would you like to do?" << endl;
    getline(cin, response);
    //cout << response << endl;

    for (size_t i = 0; response.size() > i; ++i){
      if ((response[i] >= 'A') && (response[i] <= 'Z')){
          response[i] = response[i] - 'A' + 'a';
      }
    }
    //cout << response << endl;
    
    size_t findAttack = response.find(attackSearch);
    if (findAttack!=string::npos){
        //cout << "attack works" << endl;
        string attackResponse;
        string const dagger = "dagger"; //these options could use a DB call for what kind of options, can only have 3 options to limit code and options, same for all 'string const' - s
        string const bow = "bow";
        string const sword = "sword";
        cout << "What attack would you like to do?" << endl;
        getline(cin, attackResponse);
        for (size_t i = 0; response.size() > i; ++i){
              if ((attackResponse[i] >= 'A') && (attackResponse[i] <= 'Z')){
                  attackResponse[i] = attackResponse[i] - 'A' + 'a'; //duplication of code
              }
        }
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
    }
    
    size_t findDefense = response.find(defenseSearch);
    if (findDefense!=string::npos){
        //cout << "defense works" << endl;
        string defenseResponse;
        string const heal = "heal";
        string const block = "block";
        cout << "What defense would you like to do?" << endl;
        getline(cin, defenseResponse);
        for (size_t i = 0; response.size() > i; ++i){
              if ((response[i] >= 'A') && (response[i] <= 'Z')){
                  response[i] = response[i] - 'A' + 'a';//duplication of code 
              }
        }
        size_t defenseHeal = defenseResponse.find(heal);
        if (defenseHeal!=string::npos){
            cout << "heal works" << endl;
        }
        size_t defenseBlock = defenseResponse.find(block);
        if (defenseBlock!=string::npos){
            cout << "block works" << endl;
        }
    }    
    return 0;
}
