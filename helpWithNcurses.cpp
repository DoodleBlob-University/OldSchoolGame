#include <iostream>
#include <string.h>
#include <string>
#include <ncurses.h>
#include <locale>
#include <algorithm>


using namespace std;
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

class Attack : virtual public Combat{
    private:
    string attackResponse;    
    string weaponone = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    string weapontwo = "bow";
    string weaponthree = "sword"; //secion might need to be in the attack response function to then change it up if it has a different name
    char weaponOne[7] = "dagger";
    char weaponTwo[4] = "bow";
    char weaponThree[6] = "sword";
    int weaponStrengthOne = 20;
    int weaponStrengthTwo = 30;
    int weaponStrengthThree = 40; //also from database 
    
    
    
    public:

    int attack_response() //try and catch errors for wrong input and ppossible sql failures 
    {
        /*string sqliteFile = "Database.db"; //basic database 
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select weaponstats " subject to change 
                       "from weapon_table "
                       "where weapon = ?");
        cur->prepare(); for the names of the weapons*/
        
        
        printw ("These are the weapons you can use:\n" );
        printw ("-    Deal damage with a %s\n", weaponOne ); //convert from string to char array 
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s\n", weaponThree);
        printw ("What weapon would you like to use? \n");

        //getstr(attackResponse);
        attackResponse = get_line();
        refresh();
                

        size_t weaponOptionOne = attackResponse.find(weaponone);
        if (weaponOptionOne != string::npos) 
        //if(strstr(attackResponse, weaponOne))
        {
            //cur-> set_sql("SELECT Damage FROM Weapons WHERE ID = 1");
            //cur-> bind(1,weaponOne);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthOne;
        }

        size_t weaponOptionTwo = attackResponse.find(weapontwo);
        if (weaponOptionTwo != string::npos) 
        //if(strstr(attackResponse, weaponTwo))
        {
            //cur->bind(1,weaponTwo);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthTwo;
            //delete weaponStrength;
        }

        size_t weaponOptionThree = attackResponse.find(weaponthree);
        if (weaponOptionOne != string::npos) 
        //if(strstr(attackResponse, weaponThree))
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
    string spellResponse;
    string spellone = "decay";
    string spelltwo = "potent slap";
    string spellthree = "loud noise";
    char spellOne[10] = "decay";
    char spellTwo[15] = "potent slap";
    char spellThree[20] = "loud noise";
    int spellStrengthOne = 10;
    int spellStrengthTwo = 20;
    int spellStrengthThree = 30;    
    public:  
  
    int spells_response(){

        printw ("These are the spells you can use:\n");  
        printw ("-    Cast %s\n", spellOne );  
        printw ("-    Cast %s\n", spellTwo); 
        printw ("-    Cast %s\n", spellThree); 
        printw ("What spell would you like to use?\n");

        spellResponse = get_line();
        //getstr(spellResponse);
        refresh();   
     
        //if(strstr (spellResponse, spellOne))
        size_t spellOptionOne = spellResponse.find(spellone);
        if (spellOptionOne != string::npos)
        {
            //cur-> bind(1,spellOne);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthOne;
         
        }
      
        
        //if(strstr (spellResponse, spellTwo))
        size_t spellOptionTwo = spellResponse.find(spelltwo);
        if (spellOptionTwo != string::npos)
        {
            //cur-> bind(1,spellTwo);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthTwo;

        }
      
        //if(strstr (spellResponse, spellThree))
        size_t spellOptionThree = spellResponse.find(spellthree);
        if (spellOptionThree != string::npos)
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
    string defenceone = "heal";
    string defencetwo = "syrup";
    string defencethree = "potion";
    char defenceOne[10] = "heal"; 
    char defenceTwo[10] = "syrup";
    char defenceThree[10] = "potion";
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
        //getstr(defenceResponse);
        refresh();        

            //if(strstr(defenceResponse, defenceOne))
            size_t defenceOptionOne = defenceResponse.find(defenceone);
            if (defenceOptionOne != string::npos)
            {
                //cur-> bind(1,defenceOne);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return heal;
    
            }
       
            //if(strstr(defenceResponse, defenceTwo))
            size_t spellOptionTwo = defenceResponse.find(defencetwo);
            if (spellOptionTwo != string::npos)
            {
                //cur->bind(1,defenceTwo);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return syrup;

            }
     
        //if(strstr(defenceResponse, defenceThree))
        size_t spellOptionThree = defenceResponse.find(defencethree);
        if (spellOptionThree != string::npos)
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
    string defencesearch = "defence";
    char attackSearch[10] = "attack"; 
    char spellSearch[10] = "spell"; //string of words to use instead of just one word
    char defenceSearch[10] = "defence";
    string initialResponse;
    string fightingResponse;
   
    int defenceResponse;
    int point1;
    int point2;
    int point3;
    int healingPlayer;
    int weaponStrength;
    
    int mAttack;
    Dragon bob;
    Dragon mike;
    int Phealth;
    int monsterHealth = bob.get_health();
    int monsterAttack = bob.get_attack();
    
    
    public:
    
    int attacking_response(int monsterHealth){
        printw ("The monsters health is %i \n", monsterHealth);
        printw ("\nWhat would you like to do? \n"); 
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
      
        fightingResponse = get_line();
        //getstr(fightingResponse);
        refresh();        
            //if(strstr(fightingResponse, attackSearch))
            size_t nextA = fightingResponse.find(attacksearch);
            if (nextA != string::npos) 
            {  
                point1 = attack_response();
                return point1;
            }
        
            //if(strstr(fightingResponse, spellSearch))
            size_t nextS = fightingResponse.find(spellsearch);
            if (nextS != string::npos)
            {
                point2 = spells_response(); 
                return point2;
            }
        
            //if(strstr(fightingResponse, defenceSearch))
            size_t nextD = fightingResponse.find(defencesearch);
            if (nextD != string::npos)
            {
                point3 = defence_response(); //read json file for an array selection of what they input or switch cases 
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
                  //printw ("The monsters health is %i\n", monsterHealth);
                  weaponStrength = attacking_response(monsterHealth);
                  //weaponStrength = next_step(battleResponse);
                  printw ("Your weapon's attack is %i\n", weaponStrength);
                  monsterHealth = monsterHealth - weaponStrength; //only an attack or spells option - no defence 
                  printw ("Monsters health after attack is %i\n", monsterHealth);
                  printw ("\n\nMonsters time to attack\n");
                  
                 
                  printw ("\nThe monster did %i damage!!\n", monsterAttack);
                  Phealth = Phealth - monsterAttack; //* balance;
                  printw ("\nYour health now is... %i\n", Phealth);
                  refresh();                  
                  
                  
              }
              if (Phealth <= 40 && Phealth > 0) //make this optional 
              { 
                  
                  printw ("You need to heal\n");
                  defenceResponse = defence_response();                  
                  Phealth = healing(defenceResponse, Phealth);
                  refresh();                
                   
                      
              }
                                                                
              else if(Phealth <= 0)
              {
                  startFinish = false;
                  printw ("You have died\n");
                  return startFinish;
                  refresh();              
              }
              else if(monsterHealth <=0){
                  startFinish = false;
                  printw ("You have killed the monster\n");
                  return startFinish;
                  refresh();              
              }
          }
   }
   
   int startGame(){
      
        printw ("There is something blocking your path\n");
        printw ("What would you like to do?\n");
        printw ("-----   ");
         
        choice = get_line();
        //getstr(choice);
        refresh();
       
        //if(strstr(choice, attackSearch))
        size_t initial = choice.find(attacksearch);
        if (initial != string::npos)
        {
          printw ("Begin\n");
            battle();
        }
        else {
            printw ("Move along, move along\n");
        }
   }
};

int main()
{
    initscr();
    //addstr("Help");
    srand(time(NULL));
    //User_Response initialise;
    //initialise.name_selection(); - for the name selection make it part of laod screen to check if name is in db
    AttackTest go;
    go.startGame();
    return 0;
}
