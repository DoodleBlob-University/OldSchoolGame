#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

class TerminalFunctions{//Charles Barry
private:
  WINDOW* stat;
  WINDOW* term;
  int windowWidth;
public:
  void printTerminalText(std::string);
  std::string getUserInput();
  bool getUserYN();
  void eraseTerminal();
  TerminalFunctions(WINDOW* _stat, WINDOW* _term, int _windowWidth);
};


class Combat {//George Franklin
private:
  char response[];
  std::string nameW;
  std::string nameS;
  std::string nameD;
  int weaponAmount;
  int spellAmount;
  int healingAmount;

public:
  std::string database_assign_name_weapon(int ID);
  std::string database_assign_name_spell(int ID);
  std::string database_assign_name_defence(int ID);
  int database_assign_int_weapon(int ID);
  int database_assign_int_spell(int ID);
  int database_assign_int_healing(int ID);
  int database_remove_amount(int ID);
  std::string make_lower(std::string attach);

};

class player{
private:
  auto dbOpen();
  std::array<int, 13>playerDB;
  int pXPGain(int mEXP);
  int pXPSplit(int mEXP,int attackNum,int defenceNum);
  int levelUp();
  int healthLevelUp();
  int updateDB(int a, int b, int asLevelUpPoint);
  int statsLevelUp(int a, int b);
  TerminalFunctions* term;
public:
  int getHealthLevelUp();
  int getLevelUp();
  int getLevel();
  int getHealth();
  int getAttackStrength();
  int getMana();
  int getMagicStrength();
  int getDefence();
  int getEXP();
  int getGold();
  int getASEXP();
  int getDEXP();
  int getXPGain(int mEXP);
  int getXPSplit(int mEXP, int attackNum, int defenceNum);
  int getStatsLevelUp(int a, int b);
  int levelingSystem(int mEXP, int numOfAttacks, int numOfDefence);
  player();
  player(TerminalFunctions* _term);
};

class monster{
private:
  auto dbOpen();
  std::array<int, 9>monsterDB;

public:

  int getLevel();
  int getHealth();
  int getAttackStrength();
  int getMana();
  int getMagicStrength();
  int getDefence();
  int getEXP();
  int getGold();
  int updateDB();
  monster();
};

class Attack : public Combat{//George Franklin
  //array of strings containing the weapon names
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string attackResponse;
  std::string weaponOneString = database_assign_name_weapon(1);
  std::string weaponTwoString = database_assign_name_weapon(2);
  std::string weaponThreeString = database_assign_name_weapon(3); //gets weapon name from DB - will make sense with inventory table
  std::string weaponOneLower;
  std::string weaponTwoLower;
  std::string weaponThreeLower;
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
  /*
    WINDOW* stat;
    WINDOW* term;
    int windowWidth;
  */
TerminalFunctions* term;

public:

  int attack_response();
  Attack(TerminalFunctions* _term);
};

class Spells : public Combat{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string spellResponse;
  std::string spellOneString = database_assign_name_spell(4);
  std::string spellTwoString = database_assign_name_spell(5);
  std::string spellThreeString = database_assign_name_spell(6);
  char spellOne[20];
  char spellTwo[20];
  char spellThree[20];
  int spellStrengthOne = database_assign_int_spell(4);
  int spellStrengthTwo = database_assign_int_spell(5);
  int spellStrengthThree = database_assign_int_spell(6);
  std::string spellOneLower;
  std::string spellTwoLower;
  std::string spellThreeLower;
  size_t spellOptionOne;
  size_t spellOptionTwo;
  size_t spellOptionThree;
  /*
    WINDOW* stat;
    WINDOW* term;
    int windowWidth;
  */
TerminalFunctions* term;
public:
  int spells_response();

  Spells(TerminalFunctions* _term);
};

class Defence : public Combat{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string defenceResponse;
  std::string defenceOneString = database_assign_name_defence(7);
  std::string defenceTwoString = database_assign_name_defence(8);
  std::string defenceThreeString = database_assign_name_defence(9);
  char defenceOne[20];
  char defenceTwo[20];
  char defenceThree[20];
  int defenceAmountOne = database_assign_int_healing(7);
  int defenceAmountTwo = database_assign_int_healing(8);
  int defenceAmountThree = database_assign_int_healing(9);
  std::string defenceOneLower;
  std::string defenceTwoLower;
  std::string defenceThreeLower;
  size_t defenceOptionOne;
  size_t defenceOptionTwo;
  size_t defenceOptionThree;
  std::vector<int> vectorOfQuantity;
  int amountHealed;
  int numLeft;
  auto get_quantity();
/*
  WINDOW* stat;
  WINDOW* term;
  int windowWidth;
*/
TerminalFunctions* term;

public:
  int defence_response();
  int healing(int amount, int playerHealth);
  Defence(TerminalFunctions* _term);
};

class AttackTest : public Attack, public Spells, public Defence, public monster, public player{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string choice;
  std::string response;
  std::string responseSearch = "engage";
  std::string attacksearch = "attack";
  std::string spellsearch = "spell";
  std::string defencesearch = "yes"; //can stay hardcoded or be json related
  char attackSearch[7] = "attack";
  char spellSearch[6] = "spell";
  char defenceSearch[8] = "defence";
  std::string initialResponse;
  std::string fightingResponse;
  int defenceResponse;
  int attackPoint;
  int spellsPoint;
  int weaponStrength;
  int togo;
  size_t nextA;
  size_t nextS;
  size_t nextD;
  int spellCounter;
  int combatAttack;
  int attackCounter = 0;
  int healingCounter = 0;
  int a;
  int b;
  bool defenceOption;
/*
  WINDOW* stat;
  WINDOW* term;
  int windowWidth;
*/
  player matt;
  //int pHealth = matt.getHealth();
  int pHealth = 50;
  int pAttackStrength = matt.getAttackStrength();
  int pMana = matt.getMana();
  int pMagicStrength = matt.getMagicStrength();
  int pDef = matt.getDefence();
  int pXP = matt.getEXP();

  monster* enemy;
  int mHealth;
  //int mHealth = 50;
  int mAttackStrength;
  int mMana;
  int mMagicStrength;
  int mDef;
  int mEXP;

  void loadMonsterStats(){
    mHealth = enemy->getHealth();
    //int mHealth = 50;
    mAttackStrength = enemy->getAttackStrength();
    mMana = enemy->getMana();
    mMagicStrength = enemy->getMagicStrength();
    mDef = enemy->getDefence();
    mEXP = enemy->getEXP();
  }

  TerminalFunctions* term;

public:
  int battle();

  AttackTest(TerminalFunctions* _term);
  AttackTest(TerminalFunctions* _term, monster* phil);
};

#endif
