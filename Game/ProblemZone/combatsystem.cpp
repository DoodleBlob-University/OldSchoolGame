#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>
#include <vector>
#include "libsqlite.hpp"
#include "combatsystem.h"

// -------------------------------

void TerminalFunctions::printTerminalText(std::string text){{
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


/*void AttackTest::printTerminalText(std::string text){
  int y = 1;
  wmove(term, y, 1);
  for(int i = 0; i < text.length(); ++i){
    char cha = text[i];
    if(cha == '\n'){y += 1; wmove(term, y, 1);}else{
      wprintw(term, "%c", cha);
    }
  }
  wrefresh(term);
}*/



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

  int Combat::database_assign_int_weapon(std::string weaponItem)
  {
    sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur-> set_sql("SELECT Weapons.damage FROM Inventory "
                      "INNER JOIN Weapons ON Inventory.weapon_name = weapons.ID " 
                      "WHERE weapon_name = ?");
        cur-> prepare();
        cur-> bind(1, weaponItem);
        cur-> step();
        weaponAmount = cur->get_int(0);
        return weaponAmount;
  }
  int Combat::database_assign_int_spell(std::string spellItem)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur-> set_sql("SELECT Spells.damage FROM Inventory "
                  "INNER JOIN Spells ON Inventory.spell_name = Spells.ID "
                  "WHERE spell_name = ?");
    cur->prepare();
    cur->bind(1, spellItem);
    cur->step();
    spellAmount = cur->get_int(0);
    return spellAmount;
  }
  int Combat::database_assign_int_healing(std::string healingItem)
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("SELECT Defence.healing_amount FROM Inventory "
                 "INNER JOIN Defence ON Inventory.defence_name = Defence.ID "
                 "WHERE defence_name = ?");
    cur->prepare();
    cur->bind(1, healingItem);
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
            printTerminalText ("XP: " + std::to_string(getEXP()).c_str() + "\n");
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
            term->printTerminalText ("Attack XP: " + std::to_string(getASEXP()).c_str() "\n");
            term->printTerminalText ("Defence XP: " + std::to_string(getDEXP()).c_str() "\n");

        }
    int player::levelUp(){
       int level = getLevel();
       int EXP = getEXP();
       int levelUpPoint = 40 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[1] = playerDB[1]+1;
            term->printTerminalText ("\nYou have leveled up!\n");
            term->printTerminalText ("You are level " + std::to_string(playerDB[1]).c_str() + "\n");


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
            term->printTerminalText ("\nYour health has leveled up!\n");
            term->printTerminalText ("You now have " + std::to_string(playerDB[2]).c_str() + " health.\n");


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
            strcpy(upgradeChar, upgrade.c_str());
            term->printTerminalText ("\nYour stats have increased!\n");
            term->printTerminalText ("You are " + upgradeChar + " level " + std::to_string(playerDB[a]).c_str() + "\n");
            term->printTerminalText ("You have " + std::to_string(playerDB[b]).c_str() + " EXP in " + upgradeChar + "\n");
            term->printTerminalText ("Next level at EXP. " + std::to_string(asLevelUpPoint).c_str() + "\n");
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

        int player::levelingSystem(int mEXP, int numOfAttacks, int numOfDefence){
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

    player::player(){
        playerDB = dbOpen();
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
  clear();

  strcpy(weaponOne, weaponOneString.c_str());   //can't make a function which returns a char array
  strcpy(weaponTwo, weaponTwoString.c_str());   //so this is the conversion
  strcpy(weaponThree, weaponThreeString.c_str());


    //printTerminalText ("These are the weapon stats %i, %i, %i \n", weaponStrengthOne, weaponStrengthTwo, weaponStrengthThree);
    term->printTerminalText ("These are the weapons you can use:\n" );
    term->printTerminalText ("-    Deal damage with a " + weaponOne + "\n");
    term->printTerminalText ("-    Destroy enemy whilst weilding a " +  weaponTwo + "\n");
    term->printTerminalText ("-    Put them 6 feet under with your " + weaponThree + "\n");
    term->printTerminalText ("What weapon would you like to use? \n");
    term->printTerminalText ("----- ");
    //attackResponse = getUserInput;
    attackResponse = weaponOneString();
    getch();

    weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter
    weaponTwoLower = make_lower(weaponTwoString);
    weaponThreeLower = make_lower(weaponThreeString);
    refresh();


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
        term->printTerminalText ("Please enter the name of your weapon \n");
        refresh();
        attack_response();
    }
}


// ----------------------- SPELLS ------------------------------------

int Spells::spells_response(){

  strcpy(spellOne, spellOneString.c_str());   //can't make a function which returns a char array
  strcpy(spellTwo, spellTwoString.c_str());   //so this is the conversion
  strcpy(spellThree, spellThreeString.c_str());

  clear();
  //printTerminalText ("These are the spell stats %i, %i, %i \n", spellStrengthOne, spellStrengthTwo, spellStrengthThree);
  term->printTerminalText ("These are the spells you can use:\n");
  term->printTerminalText ("-    Cast " + spellOne + "\n", spellOne );
  term->printTerminalText ("-    Cast " + spellTwo + "\n");
 term-> printTerminalText ("-    Cast " + spellThree + "\n");
  term->printTerminalText ("What spell would you like to use?\n");
  term->printTerminalText ("----- ");

  //spellResponse = getUserInput();
  spellResponse = spellOneString;
  getch();
  refresh();
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
  strcpy(defenceOne, defenceOneString.c_str());   //can't make a function which returns a char array
  strcpy(defenceTwo, defenceTwoString.c_str());   //so this is the conversion
  strcpy(defenceThree, defenceThreeString.c_str());
  vectorOfQuantity = get_quantity();

  //printTerminalText ("These are the healing stats %i, %i, %i\n", defenceAmountOne, defenceAmountTwo, defenceAmountThree);
  term->printTerminalText ("These are the defences you can use: \n");
  term->printTerminalText ("-    Use ability " + defenceOne + " which has " + std::to_string(vectorOfQuantity[0]).c_str() + " uses left\n");
  term->printTerminalText ("-    Use ability " + defenceTwo + " which has " + std::to_string(vectorOfQuantity[1]).c_str() + " uses left\n");
  term->printTerminalText ("-    Use ability " + defenceThree + " which has " + std::to_string(vectorOfQuantity[2]).c_str() + " uses left\n");
  term->printTerminalText ("What defence would you like to do? \n");
  term->printTerminalText ("----- ");

  //defenceResponse = getUserInput();
  defenceResponse = defenceOneString;
  getch();
  refresh();

  defenceOneLower = make_lower(defenceOneString); //made lower so user can't misplace and uppercase letter
  defenceTwoLower = make_lower(defenceTwoString);
  defenceThreeLower = make_lower(defenceThreeString);

  defenceOptionOne = defenceResponse.find(defenceOneLower);
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
      refresh();
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
      refresh();
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
      refresh();
      defence_response();
    }
   }
  else
  {
    term->printTerminalText("Please enter the name of the spell\n");
    refresh();
    defence_response();
  }
}
int Defence::healing(int amount, int playerHealth)
{
    playerHealth = playerHealth + amount;
    term->printTerminalText ("Your health is now " + std::to_string(playerHealth).c_str()+ "\n");
    refresh();
    return playerHealth;
}



// ------------------------  ATTACKTEST ---------------------------
int AttackTest::battle(){
  while(true)
  {
      term->printTerminalText ("What would you like to do? \n");
     term-> printTerminalText ("-    Use an attack \n");
     term-> printTerminalText ("-    Cast a spell \n");
      term->printTerminalText ("----- ");

      //fightingResponse = getUserInput();
      fightingResponse = attacksearch;
      getch();
      refresh();
      nextA = fightingResponse.find(attacksearch);
      nextS = fightingResponse.find(spellsearch);
      if (nextA != std::string::npos)
      {
        attackCounter = attackCounter + 1;
        combatAttack = attack_response();
        //mHealth = mHealth - combatAttack;
        //pHealth = pHealth - mAttackStrength;


      }

      if (nextS != std::string::npos)
      {
        combatAttack = spells_response();
        //mHealth = mHealth - combatAttack;
        //pHealth = pHealth - mAttackStrength;


      }
      if(nextA == std::string::npos && nextS == std::string::npos)
      {
        clear();
        term->printTerminalText("Type exactly what you want to do\n");
        refresh();
        battle();
      }

      term->printTerminalText("Player Health = " + std::to_string(pHealth).c_str() + "\n");
      term->printTerminalText ("Your weapon's attack is " + std::to_string(combatAttack).c_str()+ "\n");
      mHealth = mHealth - combatAttack;
      term->printTerminalText ("Monsters health after attack is " + std::to_string(mHealth).c_str() + "\n", );

      if(mHealth <= 0)
        {
          //startFinish = false;
          term->printTerminalText ("You have killed the monster\n");
          term->printTerminalText("You have been awarded with " + std::to_string(mEXP).c_str() xp! + "\n");
          matt.levelingSystem(mEXP, attackCounter, healingCounter);
          refresh();
          //return startFinish;
          break;
        }
      else
      {
          term->printTerminalText ("\nMonsters time to attack\n");
          term->printTerminalText ("The monster did " + std::to_string(mAttackStrength).c_str() + " damage!\n");
          pHealth = pHealth - mAttackStrength;
      }

      if(pHealth <= 0)
      {
        startFinish = false;
        term->printTerminalText ("You have died\n");
        refresh();
        return startFinish;
        //break;
      }
     else
     {
      term->printTerminalText ("\nYour health now is... " + std::to_string(pHealth).c_str() + "\n");
      term->printTerminalText("Would you like to use a defence item? \n");
      term->printTerminalText("Type yes if you would like to heal ---- ");
      //defenceOption = getUserInput();
      defenceOption = defenceSearch;
      nextD = defenceOption.find(defencesearch);
      refresh();

      if (nextD != std::string::npos)
      {
        term->printTerminalText ("You need to heal\n");
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
  term->printTerminalText("It has ended\n");
  refresh();
  //sleep(5);
  //endwin();
}

