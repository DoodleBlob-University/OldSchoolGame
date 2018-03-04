#include <iostream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

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
    /*bool string_find(char choiceResponse[], char wordSearch[]){
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
    }*/
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
    char attackResponse[256];
    //char attackResponseOne;
    
    char weaponOne[10] = "dagger"; //database reference just for the name and when they choose the weapon we can call for the rest of the information about it
    char weaponTwo[10] = "bow";
    char weaponThree[10] = "sword"; //secion might need to be in the attack response function to then change it up if it has a different name
    int weaponStrengthOne = 20;
    int weaponStrengthTwo = 30;
    int weaponStrengthThree = 40; //also from database 
    //int *weaponStrength = new int;
    //unique_ptr<int> pointer( new int(10));
    
    
    
    public:
    //Attack(){}

    int attack_response() //try and catch errors for wrong input and ppossible sql failures 
    {
        /*string sqliteFile = "Database.db"; //basic database 
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select weaponstats " subject to change 
                       "from weapon_table "
                       "where weapon = ?");
        cur->prepare();*/
        
        
        printw ("These are the weapons you can use:\n" );
        printw ("-    Deal damage with a %s\n", weaponOne ); 
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s\n", weaponThree);
        printw ("What weapon would you like to use? \n");

        getstr( attackResponse);
        clear();

                

        if (strstr(attackResponse, weaponOne)){
            //cur-> bind(1,weaponOne);
            //or for smart pointer usage 
            //*weaponStrength = cur->get_int(0); - deletion already happens 
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthOne;
            //delete weaponStrength;
        }

        if(strstr(attackResponse, weaponTwo))
        {
            //cur->bind(1,weaponTwo);
            //weaponStrength = cur->get_int(0);
            //return weaponStrength;
            return weaponStrengthTwo;
            //delete weaponStrength;
        }
)
        if(strstr (attackResponse, weaponThree))
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
    char spellResponse[];
    char spellResponseOne[];
    char spellOne[10] = "decay";
    char spellTwo[15] = "potent slap";
    char spellThree[20] = "loud noise";
    int spellStrengthOne = 10;
    int spellStrengthTwo = 20;
    int spellStrengthThree = 30;
    //int spellStrength;
    
    public:  
   // Spells(){ //supposedly to initialise the use of the class         
    //}
    
    int spells_response(){
        /*string sqliteFile = "<<whatever the data baseness is>>";
        sqlite::sqlite db( sqliteFile );
        auto cur = db.get_statement();
        cur -> set_sql("select spellStats " subject to change 
                       "from spells_table "
                       "where spell = ?");
        cur->prepare();*/
        printw ("These are the spells you can use:\n");  
        printw ("-    Cast %s\n", spellOne );  
        printw ("-    Cast %s\n", spellTwo); 
        printw ("-    Cast %s\n", spellThree); 
        printw ("What spell would you like to use?\n");

        getstr(spellResponse);
        clear();
   
     
        if(strstr (spellResponse, spellOne) )
        {
            //cur-> bind(1,spellOne);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthOne;
         
        }
      
        if(strstr (spellResponse, spellTwo) )
        {
            //cur-> bind(1,spellTwo);
            //spellStrength = cur->get_int(0);
            //return spellStrength;
            return spellStrengthTwo;

        }
      
        if(strstr (spellResponse, spellThree) )
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
    char defenceResponse[];
    //char defenceResponseOne;
    char defenceOne[10] = "heal"; 
    char defenceTwo[10] = "syrup";
    char defenceThree[10] = "potion";
    int heal = 5;
    int syrup = 10;
    int potion = 15;
    //int defenceAmount;
    
    public:
    
    //Defence(){
        
    //}
    
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
       
        getstr(defenceResponse);
        clear();
        

            if(strstr(defenceResponse, defenceOne))
            {
                //cur-> bind(1,defenceOne);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return heal;
    
            }
       
            if(strstr(defenceResponse, defenceTwo))
            {
                //cur->bind(1,defenceTwo);
                //defenceAmount = cur->get_int(0);
                //return defenceAmount;
                return syrup;

            }
     
        if(strstr(defenceResponse, defenceTwo))   
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
        printw ("Your health is now %i", playerHealth);
        return playerHealth;
    }
};

class AttackTest : public Attack, public Spells, public Defence, public Dragon{
    private:
    char choice[];
    char response[];
    char attackSearch[10] = "attack"; 
    char spellSearch[10] = "spell"; //string of words to use instead of just one word
    char defenceSearch[10] = "defence";
    char initialResponse[256];
    char fightingResponse[256];
   
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
        printw("The monsters health is %i \n", monsterHealth);
        printw ("\nWhat would you like to do? \n"); 
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
      
        getstr( fightingResponse);
        clear();
        
            if (strstr(fightingResponse, attackSearch)){ //says the index no. if the word is found but if not then it produces a -1 - test file proves this 
                point1 = attack_response();
                return point1;
            }
        
            if (strstr(fightingResponse, spellSearch)){
                point2 = spells_response(); // either make an instance or make it inherit everything from these classes, both work 
                return point2;
            }
        
            if (strstr(fightingResponse, defenceSearch)){
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
                  //clear();
                  
                  
                  
              }
              if (Phealth <= 40 && Phealth > 0) //make this optional 
              { 
                  
                  printw ("You need to heal\n");
                  defenceResponse = defence_response();                  
                  Phealth = healing(defenceResponse, Phealth);
                  //clear();
                   
                      
              }
                                                                
              else if(Phealth <= 0)
              {
                  startFinish = false;
                  printw ("You have died\n");
                  return startFinish;
                  clear();
              }
              else if(monsterHealth <=0){
                  startFinish = false;
                  printw ("You have killed the monster\n");
                  return startFinish;
                  clear();
              }
          }
   }
   
   int startGame(){
      
        printw ("There is something blocking your path\n");
        printw ("What would you like to do?\n");
        printw ("-----   ");
     
        getstr(choice);
        clear();
       
        if (strstr(choice, attackSearch)) { //json list needed so bad
            
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
   srand(time(NULL));
   //User_Response initialise;
   //initialise.name_selection(); - for the name selection make it part of laod screen to check if name is in db
   AttackTest go;
   go.startGame();
}
