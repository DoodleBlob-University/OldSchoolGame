//Charles Barry
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>
#include <vector>
#include <unistd.h>
#include "libsqlite.hpp"
#include "terminalfunc.h"
#include "combatsystem.h"

// ------------------------------  COMBAT  ----------------------------------------

    //all calls below get the name and stats for each of the spells, weapons and defence abilities
    std::string Combat::database_assign_name_weapon(int ID) //George Franklin
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
  std::string Combat::database_assign_name_spell(int ID)  //George Franklin
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
  std::string Combat::database_assign_name_defence(int ID)  //George Franklin
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

  int Combat::database_assign_int_weapon(int ID)  //George Franklin
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
  int Combat::database_assign_int_spell(int ID)  //George Franklin
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
  int Combat::database_assign_int_healing(int ID)  //George Franklin
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
  //this updates the database when the consumable is used
  int Combat::database_remove_amount(int ID)  //George Franklin
  {
    sqlite::sqlite db( "gamedb.db");
    auto cur = db.get_statement();
    cur->set_sql("UPDATE Inventory SET Quantity = Quantity - 1 WHERE ID = ?");
          cur->prepare();
          cur->bind(1, ID);
          cur->step();
  }

  std::string Combat::make_lower(std::string attach){ //allows user input to match the name of the weapon or spell  //George Franklin
    for(int length = 0; length < attach.length(); ++length){
      attach[length] = tolower(attach[length]);
    }
    return attach;
  }

// ------------------------  PLAYER  ------------------------------------

     void player::dbOpen(TerminalFunctions* _term, int _playerid){//Matthew Fretwell and Charles Barry
       term = _term; playerid = _playerid;
       //assigns playerid the actual playerid and gives term a pointer to an instance of terminalfunctions
        sqlite::sqlite db( "gamedb.db" );
        auto cur = db.get_statement();
        cur->set_sql( "SELECT * FROM PlayerStats WHERE PlayerID = ?");
        cur->prepare();//query gets all data about the player with said id
        cur->bind(1, playerid);
        cur->step();
        int num = 1;
        while(num<14){//all stats about player are put into an array
            playerDB[num-1] = cur->get_int(num-1);
            num = num +1;
        }

    }



    int player::pXPGain(int mEXP){//Matthew Fretwell
           int xpGain = playerDB[7] + mEXP;
            playerDB[7] = xpGain;
            sqlite::sqlite db( "gamedb.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE PlayerStats SET EXP = ? WHERE PlayerID = ?;");
            cur->prepare();

            cur->bind( 1, xpGain );
            cur->bind( 2, playerid);

            cur->step();
            term->printTerminalText("\n\n\n\n\nXP: " + std::to_string(getEXP()));
            return playerDB[7];
}
    int player::pXPSplit(int mEXP,int attackNum,int defenceNum){//Matthew Fretwell
            int totalNum = attackNum + defenceNum;
            int equalSplit = mEXP/totalNum;
            int attackXP = equalSplit * attackNum;
            int defenceXP = equalSplit * defenceNum;
            int attackXPGain = playerDB[9] + attackXP;
            int defenceXPGain = playerDB[12] + defenceXP;
            sqlite::sqlite db( "gamedb.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE PlayerStats SET ASEXP = ?, MEXP = ?, MSEXP = ?, DEXP = ? WHERE PlayerID = ?;");
            cur->prepare();

            cur->bind( 1, attackXPGain );
            cur->bind( 2, 0);
            cur->bind( 3, 0);
            cur->bind( 4, defenceXPGain);
            cur->bind( 5, playerid);
            cur->step();
            term->printTerminalText("\n\n\nAttack XP: " + std::to_string(getASEXP()));
            term->printTerminalText("\n\n\n\nDefence XP: " + std::to_string(getDEXP()));

        }
    int player::levelUp(){//Matthew Fretwell
       int level = getLevel();
       int EXP = getEXP();
       int levelUpPoint = 40 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[1] = playerDB[1]+1;
            term->printTerminalText("\n\n\n\n\n\nYou have leveled up!");
            term->printTerminalText("\n\n\n\n\n\n\nYou are level " + std::to_string(playerDB[1]));


            sqlite::sqlite db( "gamedb.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE PlayerStats SET Level = ? WHERE PlayerID = ?;");
            cur->prepare();

            cur->bind( 1, playerDB[1] );
            cur->bind( 2, playerid);

            cur->step();
           }

            }
      int player::health(int playerHealth){//Matthew Fretwell
       int level = playerDB[2];
       int EXP = playerDB[7];
       float levelUpPoint = 20 *(level *1.2);
        if (EXP >= levelUpPoint){
            playerDB[2] = playerDB[2]+1;
            term->printTerminalText("\n\n\n\n\n\n\n\nYour health has leveled up!");
            term->printTerminalText("\n\n\n\n\n\n\n\n\nYou now have " + std::to_string(playerDB[2]) + " health.");//*/
            sqlite::sqlite db( "gamedb.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE PlayerStats SET Health = ? WHERE PlayerID = ?;");
            cur->prepare();

            cur->bind( 1, playerDB[2] );
            cur->bind( 2, playerid);

            cur->step();


            /*sqlite::sqlite db( "gamedb.db" );
            auto cur = db.get_statement();
            cur->set_sql("UPDATE PlayerStats SET Health = ? WHERE PlayerID = ?;");
            cur->prepare();

            cur->bind( 1, playerHealth );
            cur->bind( 2, playerid);

            cur->step();
            playerDB[2] = playerHealth;
           }//*/
        }
      }
        

int player::updateDB(int a, int b, int asLevelUpPoint){//Matthew Fretwell
    std::string upgrade;
    int playerid;
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
            sleep(2);
            term->eraseTerminal();
            term->printTerminalText ("Your stats have increased!\n");
            term->printTerminalText ("\nYou are " + upgrade + " level " + std::to_string(playerDB[a]));
            term->printTerminalText ("\n\nYou have " + std::to_string(playerDB[b]) + " EXP in " + upgrade);
            term->printTerminalText ("\n\n\nNext level at EXP. " + std::to_string(asLevelUpPoint));
    }

    void player::statsLevelUp(int a, int b){//Matthew Fretwell

            int asLevel = playerDB[a];
            int asEXP = playerDB[b];
            int asLevelUpPoint = 20*(asLevel*1.2);
            if(a==3 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "gamedb.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE PlayerStats SET AttackStrength = ? WHERE PlayerID = ?;");
                updateDB(3, 9, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->bind( 2, playerid);
                cur->step();
            }
            if(a==4 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "gamedb.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE PlayerStats SET Mana = ? WHERE PlayerID = ?;");
                updateDB(4, 10, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->bind( 2, playerid);
                cur->step();
            }
            if(a==5 && asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "gamedb.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE PlayerStats SET MagicStrength = ? WHERE PlayerID = ?;");
                updateDB(5, 11, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->bind( 2, playerid);
                cur->step();
            }
            if(a==6&& asEXP >= asLevelUpPoint){
                sqlite::sqlite db( "gamedb.db" );
                auto cur = db.get_statement();
                cur->set_sql("UPDATE PlayerStats SET Defence = ? WHERE PlayerID = ?;");
                updateDB(6, 12, asLevelUpPoint);
                cur->prepare();
                cur->bind( 1, playerDB[a] );
                cur->bind( 2, playerid);
                cur->step();
            }
    }

    /*int player::getLevelUp(){//Matthew Fretwell
        return levelUp();
    }*/

    int player::getLevel(){//Matthew Fretwell
        return playerDB[1];
    }
    int player::getHealth(){//Matthew Fretwell
        return playerDB[2];
    }
    int player::getAttackStrength(){//Matthew Fretwell
        return playerDB[3];
    }
    int player::getMana(){//Matthew Fretwell
        return playerDB[4];
    }
    int player::getMagicStrength(){//Matthew Fretwell
        return playerDB[5];
    }
    int player::getDefence(){//Matthew Fretwell
        return playerDB[6];
    }
    int player::getEXP(){//Matthew Fretwell
        return playerDB[7];
    }
    int player::getGold(){//Matthew Fretwell
        return playerDB[8];
    }
    int player::getASEXP(){//Matthew Fretwell
        return playerDB[9];
    }
    int player::getDEXP(){//Matthew Fretwell
        return playerDB[12];
    }
    int player::getPlayerID(){
      return playerid;
    }

       /* int player::getXPGain(int mEXP){//Matthew Fretwell
            return pXPGain(mEXP);
        }
        int player::getXPSplit(int mEXP, int attackNum, int defenceNum){//Matthew Fretwell
            return pXPSplit(mEXP, attackNum, defenceNum);
        }

        int player::getStatsLevelUp(int a, int b){//Matthew Fretwell
            statsLevelUp(a, b);
        }
        int player::getHealthLevelUp(){//Matthew Fretwell
            return healthLevelUp();
        }*/




// -----------------------  MONSTER -----------------------------

void monster::dbOpen(int _monsterid){//Matthew Fretwell and Charles Barry
    monsterid = _monsterid;
    //assigns monsterid the actual monster id
    sqlite::sqlite db( "gamedb.db" );
    auto cur = db.get_statement();
    cur->set_sql( "SELECT MonsterName, Level, Health, AttackStrength, Mana, MagicStrength, Defence, EXP, Gold FROM Monster WHERE ID = ?");
    cur->prepare();//query gets all data from the monster with said id
    cur->bind(1, monsterid);
    cur->step();
    int num = 1;
    monstername = cur->get_text(0);
    while(num<8){//all stats about monster are put into an array
        monsterDB[num-1] = cur->get_int(num);
        num = num +1;
    }
}

    std::string monster::getName(){//Charles Barry
      return monstername;
    }
    int monster::getLevel(){//Matthew Fretwell
        return monsterDB[0];
    }
    int monster::getHealth(){//Matthew Fretwell
        return monsterDB[1];
    }
    int monster::getAttackStrength(){//Matthew Fretwell
        return monsterDB[2];
    }
    int monster::getMana(){//Matthew Fretwell
        return monsterDB[3];
    }
    int monster::getMagicStrength(){//Matthew Fretwell
        return monsterDB[4];
    }
    int monster::getDefence(){//Matthew Fretwell
        return monsterDB[5];
    }
    int monster::getEXP(){//Matthew Fretwell
        return monsterDB[6];
    }
    int monster::getGold(){//Matthew Fretwell
        return monsterDB[7];
    }
    void monster::updateDB(){//Matthew Fretwell
        dbOpen(monsterid);
    }



// -------------------------- ATTACK -----------------------------

int Attack::attack_response() //player chooses desired weapon  //George Franklin
{
  term->printTerminalText("These are damage stats " + std::to_string(weaponStrengthOne) +", " + std::to_string(weaponStrengthTwo) +", " + std::to_string(weaponStrengthThree));
  term->printTerminalText ("\nThese are the weapons you can use:");
  term->printTerminalText ("\n\n-1    Deal damage with a " + weaponOneString);
  term->printTerminalText ("\n\n\n-2    Destroy enemy with " +  weaponTwoString);
  term->printTerminalText ("\n\n\n\n-3    Slice them with " + weaponThreeString);
  term->printTerminalText ("\n\n\n\n\nWhat weapon would you like to use?");
  attackResponse = term->getUserInput();
  term->eraseTerminal();
  weaponOneLower = make_lower(weaponOneString); //made lower so user can't misplace and uppercase letter
  weaponTwoLower = make_lower(weaponTwoString);
  weaponThreeLower = make_lower(weaponThreeString);


  weaponOptionOne = attackResponse.find("1");
  weaponOptionTwo = attackResponse.find("2");
  weaponOptionThree = attackResponse.find("3");
  weaponOptionOneNo = attackResponse.find(weaponOneLower);
  weaponOptionTwoNo = attackResponse.find(weaponTwoLower);
  weaponOptionThreeNo = attackResponse.find(weaponThreeLower);

  if (weaponOptionOne != std::string::npos || weaponOptionOneNo != std::string::npos)//within standard documentation
    {
      return weaponStrengthOne;
    }
    else if (weaponOptionTwo != std::string::npos || weaponOptionTwoNo != std::string::npos)
    {
      return weaponStrengthTwo;
    }
    else if (weaponOptionThree != std::string::npos || weaponOptionThreeNo != std::string::npos)
    {
      return weaponStrengthThree;
    }
    else{
        term->printTerminalText ("\n\n\n\n\n\nEnter number slot or name of weapon");
        attack_response();
    }
}

Attack::Attack(TerminalFunctions* _term){//Charles Barry
  term = _term;
}


// ----------------------- SPELLS ------------------------------------

int Spells::spells_response()  //George Franklin
{
  term->printTerminalText("These are damage stats " + std::to_string(spellStrengthOne) +", " + std::to_string(spellStrengthTwo) +", " + std::to_string(spellStrengthThree));
  term->printTerminalText ("\nThese are the spells you can use:");
  term->printTerminalText ("\n\n-1    Cast " + spellOneString);
  term->printTerminalText ("\n\n\n-2    Cast " + spellTwoString);
  term-> printTerminalText ("\n\n\n\n-3    Cast " + spellThreeString);
  term->printTerminalText ("\n\n\n\n\nWhat spell would you like to use?");
  spellResponse = term->getUserInput();
  term->eraseTerminal();

  spellOneLower = make_lower(spellOneString); //made lower so user can't misplace and uppercase letter
  spellTwoLower = make_lower(spellTwoString); //either be in function or in the prirate section

  spellThreeLower = make_lower(spellThreeString);

  spellOptionOneNo = spellResponse.find("1");
  spellOptionTwoNo = spellResponse.find("2");
  spellOptionThreeNo = spellResponse.find("3");
  spellOptionOne = spellResponse.find(spellOneLower);
  spellOptionTwo = spellResponse.find(spellTwoLower);
  spellOptionThree = spellResponse.find(spellThreeLower);

  if (spellOptionOne != std::string::npos || spellOptionOneNo != std::string::npos)
  {
    return spellStrengthOne;
  }
  else if (spellOptionTwo != std::string::npos || spellOptionTwoNo != std::string::npos)
  {
    return spellStrengthTwo;
  }
  else if (spellOptionThree != std::string::npos || spellOptionThreeNo != std::string::npos)
  {
    return spellStrengthThree;
  }
  else{
    term->printTerminalText ("\n\n\n\n\n\nEnter number slot or name of spell");
    spells_response();
  }
}
Spells::Spells(TerminalFunctions* _term){//Charles Barry
  term = _term;
}


//-------------------------- DEFENCE  ----------------------------------
    //updates and gets the number of consumables left in your inventory
    auto Defence::get_quantity(){  //George Franklin
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

int Defence::defence_response()  //George Franklin
{
  vectorOfQuantity = get_quantity();
  term->eraseTerminal();
  term->printTerminalText("These are healing stats " + std::to_string(defenceAmountOne) +", " + std::to_string(defenceAmountTwo) +", " + std::to_string(defenceAmountThree));
  term->printTerminalText ("\nThese are the defences you can use:");
  term->printTerminalText ("\n\n-1    Use " + defenceOneString + " which has " + std::to_string(vectorOfQuantity[0]) + " uses left");
  term->printTerminalText ("\n\n\n-2    Use " +defenceTwoString + " which has " + std::to_string(vectorOfQuantity[1]) + " uses left");
  term->printTerminalText ("\n\n\n\n-3    Use " + defenceThreeString + " which has " + std::to_string(vectorOfQuantity[2]) + " uses left");
  term->printTerminalText ("\n\n\n\n\n What defence would you like to do?");

  defenceResponse = term->getUserInput();
  term->eraseTerminal();

  defenceOneLower = make_lower(defenceOneString); //made lower so user can't misplace and uppercase letter
  defenceTwoLower = make_lower(defenceTwoString);
  defenceThreeLower = make_lower(defenceThreeString);
  defenceOptionOneNo = defenceResponse.find("1"); //find function to check if the substr is in the main
  defenceOptionTwoNo = defenceResponse.find("2");
  defenceOptionThreeNo = defenceResponse.find("3");
  defenceOptionOne = defenceResponse.find(defenceOneLower); //find function to check if the substr is in the main
  defenceOptionTwo = defenceResponse.find(defenceTwoLower);
  defenceOptionThree = defenceResponse.find(defenceThreeLower);

  if (defenceOptionOne != std::string::npos || defenceOptionOneNo != std::string::npos)
  {

    if(vectorOfQuantity[0]!=0){
      database_remove_amount(7);
      return defenceAmountOne;
    }

    else{
      term->printTerminalText("\n\n\n\n\n\nNot enough of these in your inventory.");
      defence_response();
    }
  }

  else if (defenceOptionTwo != std::string::npos || defenceOptionTwoNo != std::string::npos) //get amount of them that you have left in inventory
  {
    if(vectorOfQuantity[1]!=0)
    {
      database_remove_amount(8);
      return defenceAmountTwo;
    }
    else
    {
      term->printTerminalText("\n\n\n\n\n\nNot enough of these in your inventory.");
      defence_response();
    }
  }

  else if (defenceOptionThree != std::string::npos || defenceOptionThreeNo != std::string::npos)
  {
    if(vectorOfQuantity[2]!=0)
    {
      database_remove_amount(9);
      return defenceAmountThree;
    }
    else
    {
      term->printTerminalText("\n\n\n\n\n\nNot enough of these in your inventory.");
      defence_response();
    }
   }
  else
  {
    term->printTerminalText("\n\n\n\n\n\nEnter number slot or name of consumable");
    defence_response();
  }
}

Defence::Defence(TerminalFunctions* _term){//Charles Barry
    term = _term;
}


// ------------------------  ATTACKTEST ---------------------------
int AttackTest::battle(){  //George Franklin
  while(true)
  {
    substat = derwin(term->getStat(), 9,43,3,1);
    term->changeWindowWidth(windowWidth);
    term->eraseTerminal();
    term->printTerminalText ("What would you like to do?");
    term-> printTerminalText ("\n-1    Cast a spell");
    term-> printTerminalText ("\n\n-2    Use an attack");
    term->printTerminalText ("\n\n\n----- ");
    wclear(substat);

    wattron(substat,COLOR_PAIR(2));
    mvwprintw(substat, 1, term->centreTextCursorPos(enemy->getName()), enemy->getName().c_str());
    mvwprintw(substat, 2, term->centreTextCursorPos(std::string(enemy->getName().length()+2, '.')), std::string(enemy->getName().length()+2, '~').c_str());
    wattroff(substat,COLOR_PAIR(2));

    mvwprintw(substat, 4, term->centreTextCursorPos("Your health is " + std::to_string(pHealth)), "Your health is %i", pHealth);
    mvwprintw(substat, 5, term->centreTextCursorPos("Monster's Health: " + std::to_string(mHealth)), "Monster's Health: %i", mHealth);
    wrefresh(substat);
    fightingResponse = term->getUserInput();
    term->eraseTerminal();

    nextA = fightingResponse.find(attacksearch);
    nextS = fightingResponse.find(spellsearch);
    nextSNo = fightingResponse.find("1");
    nextANo = fightingResponse.find("2");


      if (nextSNo != std::string::npos || nextS != std::string::npos)
      {
        attackCounter = attackCounter + 1;
        combatAttack = spells_response();
      }

     else if (nextANo != std::string::npos || nextA != std::string::npos)
     {
       attackCounter = attackCounter + 1;
       combatAttack = attack_response();
     }
     else
     {
       term->eraseTerminal();
       term->printTerminalText("\n\n\n\n\nType exactly what you want to do");
       battle();
     }

    term->printTerminalText ("Your attack = " + std::to_string(combatAttack));
    mHealth = mHealth - combatAttack;
    wclear(substat);
    wattron(substat,COLOR_PAIR(2));
    mvwprintw(substat, 1, term->centreTextCursorPos(enemy->getName()), enemy->getName().c_str());
    mvwprintw(substat, 2, term->centreTextCursorPos(std::string(enemy->getName().length()+2, '.')), std::string(enemy->getName().length()+2, '~').c_str());
    wattroff(substat,COLOR_PAIR(2));

    mvwprintw(substat, 4, term->centreTextCursorPos("Your health is " + std::to_string(pHealth)), "Your health is %i", pHealth);
    mvwprintw(substat, 5, term->centreTextCursorPos("Monster's Health: " + std::to_string(mHealth)), "Monster's Health: %i", mHealth);
    wrefresh(substat);
    wclear(substat);
    wrefresh(substat);
    
    sleep(1);

      if(mHealth <=0)
      {
          term->eraseTerminal();
          term->printTerminalText ("You have killed the monster");
          term->printTerminalText("\nYou have been awarded with " + std::to_string(mEXP)+ " XP!");
          matt-> pXPGain(mEXP);// Matthew Fretwell
          matt-> pXPSplit(mEXP, attackCounter, healingCounter);
          matt-> levelUp();
          matt-> health(pHealth);
          sleep(2);
          wclear(substat);
          wrefresh(substat);

          while(a<=6)
          {
            matt-> statsLevelUp(a, b);
            a=a+1;
            b=b+1;
          }
          sleep(2);
        term->eraseTerminal();
        break;
      }
      term->eraseTerminal();//George Franklin
      term->printTerminalText ("Monsters time to attack");
      sleep(1);
      term->printTerminalText ("\n\n\nThe monster did " + std::to_string(mAttackStrength) + " damage!");
      pHealth = pHealth - mAttackStrength;
      wclear(substat);
      wattron(substat,COLOR_PAIR(2));
      mvwprintw(substat, 1, term->centreTextCursorPos(enemy->getName()), enemy->getName().c_str());
      mvwprintw(substat, 2, term->centreTextCursorPos(std::string(enemy->getName().length()+2, '.')), std::string(enemy->getName().length()+2, '~').c_str());
      wattroff(substat,COLOR_PAIR(2));

      mvwprintw(substat, 4, term->centreTextCursorPos("Your health is " + std::to_string(pHealth)), "Your health is %i", pHealth);
      mvwprintw(substat, 5, term->centreTextCursorPos("Monster's Health: " + std::to_string(mHealth)), "Monster's Health: %i", mHealth);
      wrefresh(substat);
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
       term->eraseTerminal();
       //term->printTerminalText("Your health now is... " + std::to_string(pHealth));
       term->printTerminalText("Would you like to use a defence item?");
       term->printTerminalText("\nType yes if you would like to heal...");
       defenceOption = term->getUserYN();
      if (defenceOption == true)
      {
        defenceResponse = defence_response();
        term->eraseTerminal();
        pHealth = pHealth + defenceResponse;
        //term->printTerminalText("Your health is now... " + std::to_string(pHealth));
        wclear(substat);
        wattron(substat,COLOR_PAIR(2));
        mvwprintw(substat, 1, term->centreTextCursorPos(enemy->getName()), enemy->getName().c_str());
        mvwprintw(substat, 2, term->centreTextCursorPos(std::string(enemy->getName().length()+2, '.')), std::string(enemy->getName().length()+2, '~').c_str());
        wattroff(substat,COLOR_PAIR(2));

        mvwprintw(substat, 4, term->centreTextCursorPos("Your health is " + std::to_string(pHealth)), "Your health is %i", pHealth);
        mvwprintw(substat, 5, term->centreTextCursorPos("Monster's Health: " + std::to_string(mHealth)), "Monster's Health: %i", mHealth);
        wrefresh(substat);
        sleep(1);
        term->eraseTerminal();
        healingCounter = healingCounter + 1;
      }
       else{
         term->eraseTerminal();
       }
    }
  }
  term->eraseTerminal();
  term->changeWindowWidth(45);
}

AttackTest::AttackTest(TerminalFunctions* _term, int _playerid) : Attack(_term), Spells(_term), Defence(_term){//Charles Barry
  //if no monster is specified, a monster with the ID of one will always load
  term = _term;
  enemy = new monster();//create new instances of monster and player and assign them
  matt = new player();

  matt->dbOpen(_term, _playerid);//get data from database about player
  enemy->dbOpen(1);//get data from database about monster, where ID is 1

  loadMonsterStats();
  loadPlayerStats();
  battle();//commence battle
}

AttackTest::AttackTest(TerminalFunctions* _term, int _playerid, int monsterid) : Attack(_term), Spells(_term), Defence(_term){//Charles Barry
  //if monsterid is specified, a monster will spawn with the specified id
  term = _term;
  enemy = new monster();//create new instances of monster and player and assign them
  matt = new player();

  matt->dbOpen(_term, _playerid);//get data from database about player
  enemy->dbOpen(monsterid);//get data from database about monster, where ID is equal to monsterid

  loadMonsterStats();
  loadPlayerStats();
  battle();//commence battle
}
