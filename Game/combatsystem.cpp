#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>
#include <vector>
#include <unistd.h>
#include "libsqlite.hpp"
#include "combatsystem.h"

// -------------------------------

void TerminalFunctions::printTerminalText(std::string text){
  int y = 1;
  wmove(term, y, 1);
  for(int i = 0; i < text.length(); ++i){
    char cha = text[i];
    if(cha == '\n'){y += 1; wmove(term, y, 1);}else{
      wprintw(term, "%c", cha);
    }
  }
  wrefresh(term);
}

std::string TerminalFunctions::getUserInput(){
  wmove(term, 10, 1);
  wprintw(term, ">");
  std::string userinput;
  for(int i = 1; i < 45; ++i){
    int input = wgetch(term);
    switch(input){
      case 127:
        if(userinput.length() > 0){userinput = userinput.substr(0,userinput.length()-1); mvwprintw(term, 10, i, " "); i -= 1; wmove(term, 10, i+1);}
        i -= 1;
        break;
      case '\n':
        return userinput;
        break;
      default:
        userinput = userinput.append(1u, input);
        wprintw(term, "%c", input);
        break;
    }
  }
}

bool TerminalFunctions::getUserYN(){
  while(true){
    std::string input = getUserInput();
    if(input == "y" || input == "yes" || input == "Y" || input == "YES"){
      return true;
    }else if(input == "n" || input == "no" || input == "N" || input == "NO"){
      return false;
    }else{
      printTerminalText("\n\nSorry, I didn't understand that");
    }
  }
}


void TerminalFunctions::eraseTerminal(){
  werase(term);
  box(term, 0, 0);
  wrefresh(term);
}

TerminalFunctions::TerminalFunctions(WINDOW* _stat, WINDOW* _term, int _windowWidth){
  stat = _stat; term = _term; windowWidth = _windowWidth;
}


// ------------------------------  COMBAT  ----------------------------------------

    std::string Combat::database_assign_name_weapon(int ID) //gets the name of the weapons and spells used
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
  std::string Combat::database_assign_name_spell(int ID) //gets the name of the weapons and spells used
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
  std::string Combat::database_assign_name_defence(int ID) //gets the name of the weapons and spells used
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

  int Combat::database_assign_int_weapon(int ID)
  {
    sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Weapons.damage FROM Inventory, Weapons WHERE Inventory.weapon_name = weapons.Weapon_name AND Inventory.ID = ?;");
        cur-> prepare();
        cur-> bind(1, ID);
        cur-> step();
        weaponAmount = cur->get_int(0);
        return weaponAmount;
  }
  int Combat::database_assign_int_spell(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur-> set_sql("SELECT Spells.damage FROM Inventory, Spells WHERE Inventory.spell_name = Spells.spell_name AND Inventory.ID = ?;");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    spellAmount = cur->get_int(0);
    return spellAmount;
  }
  int Combat::database_assign_int_healing(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("SELECT Defence.healing_amount FROM Inventory, Defence WHERE Inventory.defence_name = Defence.defence_name AND Inventory.ID = ?;");
    cur->prepare();
    cur->bind(1, ID);
    cur->step();
    healingAmount = cur->get_int(0);
    return healingAmount;
  }

  int Combat::database_remove_amount(int ID)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("UPDATE Inventory SET Quantity = Quantity - 1 WHERE ID = ?");
          cur->prepare();
          cur->bind(1, ID);
          cur->step();
  }

  std::string Combat::make_lower(std::string attach){ //allows user input to match the name of the weapon or spell
    for(int length = 0; length < attach.length(); ++length){
      attach[length] = tolower(attach[length]);
    }
    return attach;
  }



// ------------------------  PLAYER  ------------------------------------

    auto player::dbOpen(){
        sqlite::sqlite db( "../Database.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM Player WHERE PlayerName = 'Test'");
        cur->prepare();
        cur->step();
        int num = 1;
        std::array<int, 13>arrayOfStatsP;
        while(num<14){
            arrayOfStatsP[num-1] = cur->get_int(num-1);;
            num = num +1;
        }
     return arrayOfStatsP;

    }
    std::array<int, 13>playerDB;
    int player::pXPGain(int mEXP){
           int xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET EXP = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, xpGain );

            cur->step();
            term->printTerminalText("\n\n\n\n\nXP: " + std::to_string(getEXP()));
            return playerDB[7];
}
    int player::pXPSplit(int mEXP,int attackNum,int defenceNum){
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
            term->printTerminalText("\n\n\nAttack XP: " + std::to_string(getASEXP()));
            term->printTerminalText("\n\n\n\nDefence XP: " + std::to_string(getDEXP()));

        }
    int player::levelUp(){
       int level = getLevel();
       int EXP = getEXP();
       int levelUpPoint = 40 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[1] = playerDB[1]+1;
            term->printTerminalText("\n\n\n\n\n\nYou have leveled up!");
            term->printTerminalText("\n\n\n\n\n\n\nYou are level " + std::to_string(playerDB[1]));


            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Level = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[1] );

            cur->step();
           }

            }
      int player::healthLevelUp(){
       int level = getHealth();
       int EXP = getEXP();
       int levelUpPoint = 30 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[2] = playerDB[2]+1;
            term->printTerminalText("\n\n\n\n\n\n\n\nYour health has leveled up!");
            term->printTerminalText("\n\n\n\n\n\n\n\n\nYou now have " + std::to_string(playerDB[2]) + " health.");


            sqlite::sqlite db( "../Database.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE Player SET Health = ? WHERE PlayerName = 'Test';");
            cur->prepare();

            cur->bind( 1, playerDB[2] );

            cur->step();
           }

       }

int player::updateDB(int a, int b, int asLevelUpPoint){
    std::string upgrade;
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
            sleep(1);
            term->eraseTerminal();
            term->printTerminalText ("Your stats have increased!\n");
            term->printTerminalText ("\nYou are " + upgrade + " level " + std::to_string(playerDB[a]));
            term->printTerminalText ("\n\nYou have " + std::to_string(playerDB[b]) + " EXP in " + upgrade);
            term->printTerminalText ("\n\n\nNext level at EXP. " + std::to_string(asLevelUpPoint));
    }

    int player::statsLevelUp(int a, int b){

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

    int player::getLevelUp(){
        return levelUp();
    }

    int player::getLevel(){
        return playerDB[1];
    }
    int player::getHealth(){
        return playerDB[2];
    }
    int player::getAttackStrength(){
        return playerDB[3];
    }
    int player::getMana(){
        return playerDB[4];
    }
    int player::getMagicStrength(){
        return playerDB[5];
    }
    int player::getDefence(){
        return playerDB[6];
    }
    int player::getEXP(){
        return playerDB[7];
    }
    int player::getGold(){
        return playerDB[8];
    }
    int player::getASEXP(){
        return playerDB[9];
    }
    int player::getDEXP(){
        return playerDB[12];
    }

        int player::getXPGain(int mEXP){
            return pXPGain(mEXP);
        }
        int player::getXPSplit(int mEXP, int attackNum, int defenceNum){
            return pXPSplit(mEXP, attackNum, defenceNum);
        }

        int player::getStatsLevelUp(int a, int b){
            return statsLevelUp(a, b);
        }
        int player::getHealthLevelUp(){
            return healthLevelUp();
        }

        /*int player::levelingSystem(int mEXP, int numOfAttacks, int numOfDefence){
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
     }*/

    player::player(){
        playerDB = dbOpen();
    }
    player::player(TerminalFunctions* _term){
        playerDB = dbOpen();
        term = _term;
    }



// -----------------------  MONSTER -----------------------------

auto monster::dbOpen(){
    sqlite::sqlite db( "../Database.db" );
    auto cur = db.get_statement();
    cur->set_sql( "SELECT * FROM Monster WHERE MonsterName = 'Goblin'");
    cur->prepare();
    cur->step();
    int num = 1;
    std::array<int, 9>arrayofstats;
    while(num<10){
        arrayofstats[num-1] = cur->get_int(num-1);
        num = num +1;
    }

 return arrayofstats;
}


    int monster::getLevel(){
        return monsterDB[1];
    }
    int monster::getHealth(){
        return monsterDB[2];
    }
    int monster::getAttackStrength(){
        return monsterDB[3];
    }
    int monster::getMana(){
        return monsterDB[4];
    }
    int monster::getMagicStrength(){
        return monsterDB[5];
    }
    int monster::getDefence(){
        return monsterDB[6];
    }
    int monster::getEXP(){
        return monsterDB[7];
    }
    int monster::getGold(){
        return monsterDB[8];
    }
    int monster::updateDB(){
        dbOpen();
        return 0;
    }

monster::monster(){
    monsterDB = dbOpen();
}



// -------------------------- ATTACK -----------------------------

int Attack::attack_response() //player chooses desired weapon
{
  term->printTerminalText ("These are the weapons you can use:");
  term->printTerminalText ("\n-    Deal damage with a " + weaponOneString);
  term->printTerminalText ("\n\n-    Destroy enemy with " +  weaponTwoString);
  term->printTerminalText ("\n\n\n-    Slice them with " + weaponThreeString);
  term->printTerminalText ("\n\n\n\nWhat weapon would you like to use?");
  attackResponse = term->getUserInput();
  term->eraseTerminal();

  weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter
  weaponTwoLower = make_lower(weaponTwoString);
  weaponThreeLower = make_lower(weaponThreeString);
  weaponOptionOne = attackResponse.find(weaponOneLower);
  weaponOptionTwo = attackResponse.find(weaponTwoLower);
  weaponOptionThree = attackResponse.find(weaponThreeLower); //result will come out with -1 if it can't find substring

    if (weaponOptionOne != std::string::npos)
    {
      return weaponStrengthOne;
    }
    else if (weaponOptionTwo != std::string::npos)
    {
      return weaponStrengthTwo;
    }
    else if (weaponOptionThree != std::string::npos)
    {
      return weaponStrengthThree;
    }
    else{
        term->printTerminalText ("\n\n\n\n\n\nPlease enter the name of your weapon");        
        attack_response();
    }
}

Attack::Attack(TerminalFunctions* _term){
  term = _term;
}


// ----------------------- SPELLS ------------------------------------

int Spells::spells_response()
{
  term->printTerminalText ("These are the spells you can use:");
  term->printTerminalText ("\n-    Cast " + spellOneString);
  term->printTerminalText ("\n\n-    Cast " + spellTwoString);
  term-> printTerminalText ("\n\n\n-    Cast " + spellThreeString);
  term->printTerminalText ("\n\n\n\nWhat spell would you like to use?");
  spellResponse = term->getUserInput();
  term->eraseTerminal();

  spellOneLower = make_lower(spellOneString); //made lower so user can't misplace and uppercase letter
  spellTwoLower = make_lower(spellTwoString); //either be in function or in the prirate section
  spellThreeLower = make_lower(spellThreeString);
  spellOptionOne = spellResponse.find(spellOneLower);
  spellOptionTwo = spellResponse.find(spellTwoLower);
  spellOptionThree = spellResponse.find(spellThreeLower);

  if (spellOptionOne != std::string::npos)
  {
    return spellStrengthOne;
  }
  else if (spellOptionTwo != std::string::npos)
  {
    return spellStrengthTwo;
  }
  else if (spellOptionThree != std::string::npos)
  {
    return spellStrengthThree;
  }
  else{
    term->printTerminalText ("\n\n\n\n\n\nPlease enter the name of your spell");        
    spells_response();
  }
}
Spells::Spells(TerminalFunctions* _term){
  term = _term;
}


//-------------------------- DEFENCE  ----------------------------------
auto Defence::get_quantity(){
  sqlite::sqlite db( "gamedb.db" );
    auto cur = db.get_statement();
    cur -> set_sql("SELECT Quantity FROM Inventory WHERE ID >=7");
    cur->prepare();
    std::vector<int> vectorOfAmountLeft;
    numLeft = 0;
    while(numLeft<3)
    {
      cur->step();
      vectorOfAmountLeft.emplace_back(cur->get_int(0));
      numLeft = numLeft + 1;
    }
  return vectorOfAmountLeft;
}

int Defence::defence_response()
{
  vectorOfQuantity = get_quantity();
  term->printTerminalText ("These are the defences you can use:");
  term->printTerminalText ("\n-    Use " + defenceOneString + " which has " + std::to_string(vectorOfQuantity[0]) + " uses left");
  term->printTerminalText ("\n\n-    Use " +defenceTwoString + " which has " + std::to_string(vectorOfQuantity[1]) + " uses left");
  term->printTerminalText ("\n\n\n-    Use " + defenceThreeString + " which has " + std::to_string(vectorOfQuantity[2]) + " uses left");
  term->printTerminalText ("\n\n\n\n What defence would you like to do?");

  defenceResponse = term->getUserInput();
  term->eraseTerminal();
  defenceOneLower = make_lower(defenceOneString); //made lower so user can't misplace and uppercase letter
  defenceTwoLower = make_lower(defenceTwoString);
  defenceThreeLower = make_lower(defenceThreeString);
  defenceOptionOne = defenceResponse.find(defenceOneLower); //find function to check if the substr is in the main
  defenceOptionTwo = defenceResponse.find(defenceTwoLower);
  defenceOptionThree = defenceResponse.find(defenceThreeLower);

  if (defenceOptionOne != std::string::npos)
  {

    if(vectorOfQuantity[0]!=0){
      database_remove_amount(7);
      return defenceAmountOne;
    }

    else{
      term->printTerminalText("You do not have enough of these in your inventory.\n");
      defence_response();
    }
  }

  else if (defenceOptionTwo != std::string::npos) //get amount of them that you have left in inventory
  {
    if(vectorOfQuantity[1]!=0)
    {
      database_remove_amount(8);
      return defenceAmountTwo;
    }
    else
    {
      term->printTerminalText("You do not have enough of these in your inventory.\n");
      defence_response();
    }
  }

  else if (defenceOptionThree != std::string::npos)
  {
    if(vectorOfQuantity[2]!=0)
    {
      database_remove_amount(9);
      return defenceAmountThree;
    }
    else
    {
      term->printTerminalText("You do not have enough of these in your inventory.\n");
      defence_response();
    }
   }
  else
  {
    term->printTerminalText("Please enter the name of the spell\n");
    defence_response();
  }
}
int Defence::healing(int amount, int playerHealth)
{
    playerHealth = playerHealth + amount;
    term->printTerminalText ("Your health is now " + std::to_string(playerHealth)+ "\n");
    return playerHealth;
}


Defence::Defence(TerminalFunctions* _term){
    term = _term;
}


// ------------------------  ATTACKTEST ---------------------------
int AttackTest::battle(){
  while(true)
  {
    term->printTerminalText ("The monster's health is... " + std::to_string(mHealth));
    term->printTerminalText ("\nWhat would you like to do?");
    term-> printTerminalText ("\n\n-    Use an attack");
    term-> printTerminalText ("\n\n\n-    Cast a spell");
    term->printTerminalText ("\n\n\n\n----- ");

      fightingResponse = term->getUserInput();
      term->eraseTerminal();

      nextA = fightingResponse.find(attacksearch);
      nextS = fightingResponse.find(spellsearch);
      if (nextA != std::string::npos)
      {
        attackCounter = attackCounter + 1;
        combatAttack = attack_response();         
      }

     else if (nextS != std::string::npos)
     {
       combatAttack = spells_response();    
     }
     else
     {
       term->eraseTerminal();
       term->printTerminalText("\n\n\n\n\nType exactly what you want to do");
       battle();
     }
      
    term->printTerminalText("Player Health = " + std::to_string(pHealth));
    term->printTerminalText ("\nYour weapon's attack is " + std::to_string(combatAttack));
    mHealth = mHealth - combatAttack;
    term->printTerminalText ("\n\nMonsters health after attack is " + std::to_string(mHealth));
    sleep(2);
  
      if(mHealth <= 0)
      {
          term->eraseTerminal();
          term->printTerminalText ("You have killed the monster");
          term->printTerminalText("\nYou have been awarded with " + std::to_string(mEXP)+ " XP!");
          getXPGain(mEXP);
          getXPSplit(mEXP, attackCounter, healingCounter);
          /*getLevelUp();
          getHealthLevelUp();
          a = 3;
          b = 9;
          while(a<=6){
            getStatsLevelUp(a, b);
            a=a+1;
            b=b+1;
        }*/
          getch();
          break;
      }
      term->eraseTerminal();
      term->printTerminalText ("Monsters time to attack");
      term->printTerminalText ("\nThe monster did " + std::to_string(mAttackStrength) + " damage!");
      pHealth = pHealth - mAttackStrength;
      sleep(1);
     
      

      if(pHealth <= 0)
      {
          term->eraseTerminal();
          term->printTerminalText ("You have died");
          getch();
          break;
      }
     else
     {
       term->printTerminalText("Your health now is... " + std::to_string(pHealth));
       term->printTerminalText("\nWould you like to use a defence item?");
       term->printTerminalText("\n\nType yes if you would like to heal ---- ");
       defenceOption = term->getUserYN();
       term->eraseTerminal();
      if (defenceOption == true)
      {
        defenceResponse = defence_response();
        pHealth = healing(defenceResponse, pHealth);
        healingCounter = healingCounter + 1;
      }
       else{
         //do noting
       }
    }
  }
  term->eraseTerminal();
  term->printTerminalText("It has ended");
  //sleep(5);
  //endwin();
}

AttackTest::AttackTest(TerminalFunctions* _term) : Attack(_term), Spells(_term), Defence(_term), player(_term){
  term = _term;
  monster* bob = new monster;
  enemy = bob;
  loadMonsterStats();
  //term->printTerminalText("test");
  battle();
}

AttackTest::AttackTest(TerminalFunctions* _term, monster* phil) : Attack(_term), Spells(_term), Defence(_term), player(_term){
  term = _term;
  enemy = phil;
  loadMonsterStats();
}
