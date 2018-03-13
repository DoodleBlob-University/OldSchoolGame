#include <iostream>
#include <cstring>
#include <ncurses.h>
#include <algorithm>
#include <array>
#include <vector>
#include "libsqlite.hpp"


using namespace std;
class Combat {
    private:
    char response[];
    string nameW;
    string nameS;
    string nameD;
    int weaponAmount;
    int spellAmount;
  int healingAmount;
    public:

    string get_line() //take input from the user and put it in lowercase so that doesn't affect it
    {
        getstr(response);
        string again(response);
        transform(again.begin(),
                  again.end(),
                  again.begin(),
                  ::tolower);
        return again;
    }

    string upper_first(string call){ //makes the first letter uppercase (hardcoded purposes)
      call[0] = toupper(call[0]);
      return call;
    }

    string database_assign_name_weapon(int ID) //gets the name of the weapons and spells used
      {
        sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT weapon_name FROM Inventory WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        nameW = cur->get_text(0);
        return nameW;
      }
  string database_assign_name_spell(int ID) //gets the name of the weapons and spells used
      {
        sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT spell_name FROM Inventory WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        nameS = cur->get_text(0);
        return nameS;
      }
  string database_assign_name_defence(int ID) //gets the name of the weapons and spells used
      {
        sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT defence_name FROM Inventory WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        nameD = cur->get_text(0);
        return nameD;
      }

  int database_assign_int_weapon(int ID)
  {
    sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Weapons.damage FROM Inventory "
                      "INNER JOIN Weapons ON Inventory.weapon_name = weapons.Weapon_name " //change it to item name not just weapon
                      "WHERE ID = ?");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        weaponAmount = cur->get_int(0);
        return weaponAmount;
  }
  int database_assign_int_spell(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur-> set_sql("SELECT Spells.damage FROM Inventory "
                  "INNER JOIN Spells ON Inventory.spell_name = Spells.spell_name "
                  "WHERE ID = ?");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    spellAmount = cur->get_int(0);
    return spellAmount;
  }
  int database_assign_int_healing(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("SELECT Defence.healing_amount FROM Inventory "
                 "INNER JOIN Defence ON Inventory.defence_name = Defence.defence_name "
                 "WHERE ID = ?");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    healingAmount = cur->get_int(0);
    return healingAmount;
  }

  int database_remove_amount(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("UPDATE Inventory SET Quantity = Quantity - 1 WHERE ID = ?");
          cur->prepare();
          cur->bind(1, ID);
          cur->step();
  }

  string make_lower(string attach){ //allows user input to match the name of the weapon or spell
    for(int length = 0; length < attach.length(); ++length){
      attach[length] = tolower(attach[length]);
    }
    return attach;
  }
};

class player{
    private:

    auto dbOpen(){
        sqlite::sqlite db( "../Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Player WHERE PlayerName = 'Test'");
        cur->prepare();
        cur->step();
        int num = 1;
        array<int, 13>arrayOfStatsP;
        while(num<14){
            arrayOfStatsP[num-1] = cur->get_int(num-1);;
            num = num +1;
        }
     return arrayOfStatsP;

    }
    array<int, 13>playerDB;
       int pXPGain(int mEXP){
           int xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET EXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, xpGain );

            cur->step();
            printw ("XP: %i \n", getEXP());
            return playerDB[7];
}
    int pXPSplit(int mEXP,int attackNum,int defenceNum){
            int totalNum = attackNum + defenceNum;
            int equalSplit = mEXP/totalNum;
            int attackXP = equalSplit * attackNum;
            int defenceXP = equalSplit * defenceNum;
            int attackXPGain = playerDB[9] + attackXP;
            int defenceXPGain = playerDB[12] + defenceXP;
            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET ASEXP = ?, MEXP = ?, MSEXP = ?, DEXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, attackXPGain );
            cur->bind( 2, 0);
            cur->bind( 3, 0);
            cur->bind( 4, defenceXPGain);

            cur->step();
            printw ("Attack XP: %i \n", getASEXP());
            printw ("Defence XP: %i \n", getDEXP());

        }
    int levelUp(){
       int level = getLevel();
       int EXP = getEXP();
       int levelUpPoint = 40 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[1] = playerDB[1]+1;
            printw ("\nYou have leveled up!\n");
            printw ("You are level %i \n", playerDB[1]);


            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Level = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[1] );

            cur->step();
           }

            }
      int healthLevelUp(){
       int level = getHealth();
       int EXP = getEXP();
       int levelUpPoint = 30 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[2] = playerDB[2]+1;
            printw ("\nYour health has leveled up!\n");
            printw ("You now have %i health.\n", playerDB[2]);


            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Health = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[2] );

            cur->step();
           }

       }

int updateDB(int a, int b, int asLevelUpPoint){
    string upgrade;
    char upgradeChar[60];
    playerDB[a] = playerDB[a]+1;
    if(a==3){
        upgrade = "Attack Strength";
    }
    if(a==4){
        upgrade = "Mana";
    }
    if(a==5){
        upgrade = "Magic Strength";
    }
    if(a==6){
        upgrade = "Defence";
    };
            strcpy(upgradeChar, upgrade.c_str());
            printw ("\nYour stats have increased!\n");
            printw ("You are %s level %i\n", upgradeChar, playerDB[a]);
            printw ("You have  %i EXP in %s\n", playerDB[b], upgradeChar);
            printw ("Next level at EXP.\n", asLevelUpPoint);
    }

    int statsLevelUp(int a, int b){

            int asLevel = playerDB[a];
            int asEXP = playerDB[b];
            int asLevelUpPoint = 20*(asLevel*1.2);
            if(a==3 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "../Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET AttackStrength = ? WHERE PlayerName = 'Test';");
                updateDB(3, 9, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==4 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "../Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET Mana = ? WHERE PlayerName = 'Test';");
                updateDB(4, 10, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==5 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "../Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET MagicStrength = ? WHERE PlayerName = 'Test';");
                updateDB(5, 11, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
            if(a==6&& asEXP >= asLevelUpPoint){
               sqlite::sqlite db( "../Database.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE Player SET Defence = ? WHERE PlayerName = 'Test';");
                updateDB(6, 12, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->step();
            }
    else{
        return 0;
    }

    }
    public:

        int getLevel(){
            return playerDB[1];
        }
        int getHealth(){
            return playerDB[2];
        }
        int getAttackStrength(){
            return playerDB[3];
        }
        int getMana(){
            return playerDB[4];
        }
        int getMagicStrength(){
            return playerDB[5];
        }
        int getDefence(){
            return playerDB[6];
        }
        int getEXP(){
            return playerDB[7];
        }
        int getGold(){
            return playerDB[8];
        }
        int getASEXP(){
            return playerDB[9];
        }
        int getDEXP(){
            return playerDB[12];
        }
        int getXPGain(int mEXP){
            return pXPGain(mEXP);
        }
        int getXPSplit(int mEXP, int attackNum, int defenceNum){
            return pXPSplit(mEXP, attackNum, defenceNum);
        }
        int getLevelUp(){
            return levelUp();
        }
        int getStatsLevelUp(int a, int b){
            return statsLevelUp(a, b);
        }
        int getHealthLevelUp(){
            return healthLevelUp();
        }

        int levelingSystem(int mEXP, int numOfAttacks, int numOfDefence){
            getXPGain(mEXP);
            getXPSplit(mEXP, numOfAttacks, numOfDefence);
            getLevelUp();
            getHealthLevelUp();
        int a=3;
        int b = 9;
        while(a<=6){

            getStatsLevelUp(a, b);
            a=a+1;
            b=b+1;
        }
     }


    player(){
        playerDB = dbOpen();
    }
};

class monster{
    private:
    auto dbOpen(){
        sqlite::sqlite db( "../Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Monster WHERE MonsterName = 'Goblin'");
        cur->prepare();
        cur->step();
        int num = 1;
        array<int, 9>arrayofstats;
        while(num<10){
            arrayofstats[num-1] = cur->get_int(num-1);
            num = num +1;
        }

     return arrayofstats;
    }
    array<int, 9>monsterDB;

    public:

        int getLevel(){
            return monsterDB[1];
        }
        int getHealth(){
            return monsterDB[2];
        }
        int getAttackStrength(){
            return monsterDB[3];
        }
        int getMana(){
            return monsterDB[4];
        }
        int getMagicStrength(){
            return monsterDB[5];
        }
        int getDefence(){
            return monsterDB[6];
        }
        int getEXP(){
            return monsterDB[7];
        }
        int getGold(){
            return monsterDB[8];
        }
        int updateDB(){
            dbOpen();
            return 0;
        }

    monster(){
        monsterDB = dbOpen();
    }
};

class Attack : virtual public Combat{ //array of strings containing the weapon names
    private:
    string attackResponse;
    string weaponOneString = database_assign_name_weapon(1);
    string weaponTwoString = database_assign_name_weapon(2);
    string weaponThreeString = database_assign_name_weapon(3); //gets weapon name from DB - will make sense with inventory table
    string weaponOneLower;
    string weaponTwoLower;
    string weaponThreeLower;
    char weaponOne[20];
    char weaponTwo[20];
    char weaponThree[20];
    int weaponStrength;
    int weaponStrengthOne = database_assign_int_weapon(1);
    int weaponStrengthTwo = database_assign_int_weapon(2);
    int weaponStrengthThree = database_assign_int_weapon(3);
    size_t weaponOptionOne;
    size_t weaponOptionTwo;
    size_t weaponOptionThree;
    public:

    int attack_response() //player chooses desired weapon
    {
      clear();

      strcpy(weaponOne, weaponOneString.c_str());   //can't make a function which returns a char array
      strcpy(weaponTwo, weaponTwoString.c_str());   //so this is the conversion
      strcpy(weaponThree, weaponThreeString.c_str());


        printw ("These are the weapon stats %i, %i, %i \n", weaponStrengthOne, weaponStrengthTwo, weaponStrengthThree);
        printw ("These are the weapons you can use:\n" );
        printw ("-    Deal damage with a %s\n", weaponOne);
        printw ("-    Destroy enemy whilst weilding a %s\n", weaponTwo);
        printw ("-    Put them 6 feet under with your %s\n", weaponThree);
        printw ("What weapon would you like to use? \n");
        printw ("----- ");
        attackResponse = get_line();

        weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter
        weaponTwoLower = make_lower(weaponTwoString);
        weaponThreeLower = make_lower(weaponThreeString);
        refresh();


        weaponOptionOne = attackResponse.find(weaponOneLower);
        weaponOptionTwo = attackResponse.find(weaponTwoLower);
        weaponOptionThree = attackResponse.find(weaponThreeLower); //result will come out with -1 if it can't find substring

        if (weaponOptionOne != string::npos)
        {
          return weaponStrengthOne;
        }

        else if (weaponOptionTwo != string::npos)
        {
          return weaponStrengthTwo;
        }
        else if (weaponOptionThree != string::npos)
        {
          return weaponStrengthThree;
        }
        else{
            printw ("Please enter the name of your weapon \n");
            refresh();
            attack_response();
        }
    }


};

class Spells : virtual public Combat{
    private:
    string spellResponse;
    string spellOneString = database_assign_name_spell(4);
    string spellTwoString = database_assign_name_spell(5);
    string spellThreeString = database_assign_name_spell(6);
    char spellOne[20];
    char spellTwo[20];
    char spellThree[20];
    int spellStrengthOne = database_assign_int_spell(4);
    int spellStrengthTwo = database_assign_int_spell(5);
    int spellStrengthThree = database_assign_int_spell(6);
    string spellOneLower;
    string spellTwoLower;
    string spellThreeLower;
    size_t spellOptionOne;
    size_t spellOptionTwo;
    size_t spellOptionThree;
    public:

    int spells_response(){

      strcpy(spellOne, spellOneString.c_str());   //can't make a function which returns a char array
      strcpy(spellTwo, spellTwoString.c_str());   //so this is the conversion
      strcpy(spellThree, spellThreeString.c_str());

      clear();
      printw ("These are the spell stats %i, %i, %i \n", spellStrengthOne, spellStrengthTwo, spellStrengthThree);
      printw ("These are the spells you can use:\n");
      printw ("-    Cast %s\n", spellOne );
      printw ("-    Cast %s\n", spellTwo);
      printw ("-    Cast %s\n", spellThree);
      printw ("What spell would you like to use?\n");
      printw ("----- ");

      spellResponse = get_line();
      refresh();
      spellOneLower = make_lower(spellOneString); //made lower so user can't misplace and uppercase letter
      spellTwoLower = make_lower(spellTwoString); //either be in function or in the prirate section
      spellThreeLower = make_lower(spellThreeString);

      spellOptionOne = spellResponse.find(spellOneLower);
      spellOptionTwo = spellResponse.find(spellTwoLower);
      spellOptionThree = spellResponse.find(spellThreeLower);

      if (spellOptionOne != string::npos)
      {
        return spellStrengthOne;
      }
      else if (spellOptionTwo != string::npos)
      {
        return spellStrengthTwo;
      }
      else if (spellOptionThree != string::npos)
      {
        return spellStrengthThree;
      }
    }

};

class Defence : virtual public Combat{
    private:
    string defenceResponse;
    string defenceOneString = database_assign_name_defence(7);
    string defenceTwoString = database_assign_name_defence(8);
    string defenceThreeString = database_assign_name_defence(9);
    char defenceOne[20];
    char defenceTwo[20];
    char defenceThree[20];
    int defenceAmountOne = database_assign_int_healing(7);
    int defenceAmountTwo = database_assign_int_healing(8);
    int defenceAmountThree = database_assign_int_healing(9);
    string defenceOneLower;
    string defenceTwoLower;
    string defenceThreeLower;
    size_t defenceOptionOne;
    size_t defenceOptionTwo;
    size_t defenceOptionThree;
    vector<int> vectorOfQuantity;
    int amountHealed;
    int numLeft;

    private:

    auto get_quantity(){
      sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur -> set_sql("SELECT Quantity FROM Inventory WHERE ID >=7");
        cur->prepare();
        vector<int> vectorOfAmountLeft;
        numLeft = 0;
        while(numLeft<3)
        {
          cur->step();
          vectorOfAmountLeft.emplace_back(cur->get_int(0));
          numLeft = numLeft + 1;
        }
      return vectorOfAmountLeft;
    }
    public:
    int defence_response()
    {

      strcpy(defenceOne, defenceOneString.c_str());   //can't make a function which returns a char array
      strcpy(defenceTwo, defenceTwoString.c_str());   //so this is the conversion
      strcpy(defenceThree, defenceThreeString.c_str());
      vectorOfQuantity = get_quantity();

      //printw ("These are the healing stats %i, %i, %i\n", defenceAmountOne, defenceAmountTwo, defenceAmountThree);
      printw ("These are the defences you can use: \n");
      printw ("-    Use ability %s which has %i uses left\n", defenceOne, vectorOfQuantity[0]);
      printw ("-    Use ability %s which has %i uses left\n", defenceTwo, vectorOfQuantity[1]);
      printw ("-    Use ability %s which has %i uses left\n", defenceThree, vectorOfQuantity[2]);
      printw ("What defence would you like to do? \n");
      printw ("----- ");

      defenceResponse = get_line();
      refresh();

      defenceOneLower = make_lower(defenceOneString); //made lower so user can't misplace and uppercase letter
      defenceTwoLower = make_lower(defenceTwoString);
      defenceThreeLower = make_lower(defenceThreeString);

      defenceOptionOne = defenceResponse.find(defenceOneLower);
      defenceOptionTwo = defenceResponse.find(defenceTwoLower);
      defenceOptionThree = defenceResponse.find(defenceThreeLower);

      if (defenceOptionOne != string::npos)
      {

        if(vectorOfQuantity[0]!=0){
          database_remove_amount(7);
          return defenceAmountOne;
        }

        else{
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }
      }

      else if (defenceOptionTwo != string::npos) //get amount of them that you have left in inventory
      {
        if(vectorOfQuantity[1]!=0)
        {
          database_remove_amount(8);
          return defenceAmountTwo;
        }
        else
        {
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }
      }

      else if (defenceOptionThree != string::npos)
      {
        if(vectorOfQuantity[2]!=0)
        {
          database_remove_amount(9);
          string sqliteFile = "gamedb.db";
          return defenceAmountThree;
        }
        else
        {
          printw("You do not have enough of these in your inventory.\n");
          refresh();
          defence_response();
        }
       }
      else
      {
        printw("Please enter the name of the spell\n");
        refresh();
        defence_response();
      }
    }
    int healing(int amount, int playerHealth)
    {
        playerHealth = playerHealth + amount;
        printw ("Your health is now %i \n", playerHealth);
        refresh();
        return playerHealth;
    }
    Defence(){
        vectorOfQuantity = get_quantity();
    }
};

class AttackTest : public Attack, public Spells, public Defence, public monster, public player{
  private:
  string choice;
  string response;
  string responseSearch = "engage";
  string attacksearch = "attack";
  string spellsearch = "spell";
  string defencesearch = "yes"; //can stay hardcoded or be json related
  char attackSearch[7] = "attack";
  char spellSearch[6] = "spell";
  char defenceSearch[8] = "defence";
  string initialResponse;
  string fightingResponse;
  int defenceResponse;
  int attackPoint;
  int spellsPoint;
  int weaponStrength;
  int togo;
  size_t nextA;
  size_t nextS;
  size_t nextD;
  bool startFinish = true;
  int spellCounter;
  int combatAttack;
  int attackCounter = 0;
  int healingCounter = 0;
  string defenceOption;

  player matt;
  //int pHealth = matt.getHealth();
  int pHealth = 30;
  int pAttackStrength = matt.getAttackStrength();
  int pMana = matt.getMana();
  int pMagicStrength = matt.getMagicStrength();
  int pDef = matt.getDefence();
  int pXP = matt.getEXP();

  monster bob;
  int mHealth = bob.getHealth();
  //int mHealth = 50;
  int mAttackStrength = bob.getAttackStrength();
  int mMana = bob.getMana();
  int mMagicStrength = bob.getMagicStrength();
  int mDef = bob.getDefence();
  int mEXP = bob.getEXP();
  public:

  int battle(){
    while(true)
    {
        printw ("What would you like to do? \n");
        printw ("-    Use an attack \n");
        printw ("-    Cast a spell \n");
        printw ("----- ");

        fightingResponse = get_line();
        refresh();
        nextA = fightingResponse.find(attacksearch);
        nextS = fightingResponse.find(spellsearch);
        if (nextA != string::npos)
        {
          attackCounter = attackCounter + 1;
          combatAttack = attack_response();
          //mHealth = mHealth - combatAttack;
          //pHealth = pHealth - mAttackStrength;


        }

        if (nextS != string::npos)
        {
          combatAttack = spells_response();
          //mHealth = mHealth - combatAttack;
          //pHealth = pHealth - mAttackStrength;


        }
        if(nextA == string::npos && nextS == string::npos)
        {
          clear();
          printw("Type exactly what you want to do\n");
          refresh();
          battle();
        }

        printw("Player Health = %i \n", pHealth);
        printw ("Your weapon's attack is %i\n", combatAttack);
        mHealth = mHealth - combatAttack;
        printw ("Monsters health after attack is %i\n", mHealth);

        if(mHealth <= 0)
          {
            //startFinish = false;
            printw ("You have killed the monster\n");
            printw("You have been awarded with %i xp!\n", mEXP);
            matt.levelingSystem(mEXP, attackCounter, healingCounter);
            refresh();
            //return startFinish;
            break;
          }
        else
        {
            printw ("\nMonsters time to attack\n");
            printw ("The monster did %i damage!\n", mAttackStrength);
            pHealth = pHealth - mAttackStrength;
        }

        if(pHealth <= 0)
        {
          startFinish = false;
          printw ("You have died\n");
          refresh();
          return startFinish;
          //break;
        }
       else
       {
        printw ("\nYour health now is... %i\n", pHealth);
        printw("Would you like to use a defence item? \n");
        printw("Type yes if you would like to heal ---- ");
        defenceOption = get_line();
        nextD = defenceOption.find(defencesearch);
        refresh();

        if (nextD != string::npos)
        {
          printw ("You need to heal\n");
          defenceResponse = defence_response();
          pHealth = healing(defenceResponse, pHealth);
          healingCounter = healingCounter + 1;
          refresh();
        }
         else{
           //do noting
         }
      }
    }
    printw("It has ended\n");
    refresh();
    //sleep(5);
    //endwin();
  }

  int startGame(){
    printw ("There is something blocking your path\n");
    printw ("What would you like to do?\n");
    printw ("----- ");
    refresh();
    choice = get_line();
    togo = choice.find(responseSearch);
    refresh();
    if (togo != -1)
    {
       battle(); //starts the attacking of the monster
    }
    else
    {
      printw ("Move along, move along\n");
      refresh();
      //endwin();
    }
  }
};

int main()
{
    initscr();
    srand(time(NULL));
    AttackTest go;
    go.startGame();
    getch();
    endwin();
}
