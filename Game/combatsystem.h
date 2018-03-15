//Charles Barry
#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

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

class player{//Matthew Fretwell
private:
  std::array<int, 13>playerDB;
  int pXPGain(int mEXP);
  int pXPSplit(int mEXP,int attackNum,int defenceNum);
  int levelUp();
  int healthLevelUp();
  int updateDB(int a, int b, int asLevelUpPoint);
  void statsLevelUp(int a, int b);
  TerminalFunctions* term;
  int playerid;
public:
  void dbOpen(TerminalFunctions* _term, int _playerid);
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
};

class monster{//Matthew Fretwell
private:
  std::array<int, 9>monsterDB;
public:
  void dbOpen();
  int getLevel();
  int getHealth();
  int getAttackStrength();
  int getMana();
  int getMagicStrength();
  int getDefence();
  int getEXP();
  int getGold();
  int updateDB();
};

class Attack : public Combat{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string attackResponse;
  std::string weaponOneString = database_assign_name_weapon(1);
  std::string weaponTwoString = database_assign_name_weapon(2);
  std::string weaponThreeString = database_assign_name_weapon(3);
  std::string weaponOneLower;
  std::string weaponTwoLower;
  std::string weaponThreeLower;
  int weaponStrength;
  int weaponStrengthOne = database_assign_int_weapon(1);
  int weaponStrengthTwo = database_assign_int_weapon(2);
  int weaponStrengthThree = database_assign_int_weapon(3);
  size_t weaponOptionOne;
  size_t weaponOptionTwo;
  size_t weaponOptionThree;
  size_t weaponOptionOneNo;
  size_t weaponOptionTwoNo;
  size_t weaponOptionThreeNo;
  TerminalFunctions* term;

public:

  int attack_response();

  Attack(TerminalFunctions* _term);//Charles Barry
};

class Spells : public Combat{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string spellResponse;
  std::string spellOneString = database_assign_name_spell(4);
  std::string spellTwoString = database_assign_name_spell(5);
  std::string spellThreeString = database_assign_name_spell(6);
  int spellStrengthOne = database_assign_int_spell(4);
  int spellStrengthTwo = database_assign_int_spell(5);
  int spellStrengthThree = database_assign_int_spell(6);
  std::string spellOneLower;
  std::string spellTwoLower;
  std::string spellThreeLower;
  size_t spellOptionOne;
  size_t spellOptionTwo;
  size_t spellOptionThree;
  size_t spellOptionOneNo;
  size_t spellOptionTwoNo;
  size_t spellOptionThreeNo;
  TerminalFunctions* term;
public:
  int spells_response();

  Spells(TerminalFunctions* _term);//Charles Barry
};

class Defence : public Combat{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string defenceResponse;
  std::string defenceOneString = database_assign_name_defence(7);
  std::string defenceTwoString = database_assign_name_defence(8);
  std::string defenceThreeString = database_assign_name_defence(9);
  int defenceAmountOne = database_assign_int_healing(7);
  int defenceAmountTwo = database_assign_int_healing(8);
  int defenceAmountThree = database_assign_int_healing(9);
  std::string defenceOneLower;
  std::string defenceTwoLower;
  std::string defenceThreeLower;
  size_t defenceOptionOne;
  size_t defenceOptionTwo;
  size_t defenceOptionThree;
  size_t defenceOptionOneNo;
  size_t defenceOptionTwoNo;
  size_t defenceOptionThreeNo;
  std::vector<int> vectorOfQuantity;
  int amountHealed;
  int numLeft;
  auto get_quantity();
  TerminalFunctions* term;

public:
  int defence_response();
  int healing(int amount, int playerHealth);

  Defence(TerminalFunctions* _term);//Charles Barry
};

class AttackTest : public Attack, public Spells, public Defence, public monster, public player{//George Franklin
private:
  void printTerminalText(std::string);
  std::string getUserInput();
  std::string choice;
  std::string response;
  std::string attacksearch = "attack";
  std::string spellsearch = "spell";
  std::string fightingResponse;
  int defenceResponse;
  size_t nextA;
  size_t nextS;
  size_t nextANo;
  size_t nextSNo;
  int combatAttack;
  int attackCounter = 0;
  int healingCounter = 0;
  int a = 3;
  int b = 9;
  bool defenceOption;

  player* matt;//Matt Fretwell
  int pHealth;
  int pAttackStrength;
  int pMana;
  int pMagicStrength;
  int pDef;
  int pXP;

  void loadPlayerStats(){
    pHealth = matt->getHealth();
    pAttackStrength = matt->getAttackStrength();
    pMana = matt->getMana();
    pMagicStrength = matt->getMagicStrength();
    pDef = matt->getDefence();
    pXP = matt->getEXP();
  }

  WINDOW* substat;

  monster* enemy;//Matt Fretwell
  int mHealth;
  int mAttackStrength;
  int mMana;
  int mMagicStrength;
  int mDef;
  int mEXP;

  void loadMonsterStats(){//Matt Fretwell
    mHealth = enemy->getHealth();
    //int mHealth = 50;
    mAttackStrength = enemy->getAttackStrength();
    mMana = enemy->getMana();
    mMagicStrength = enemy->getMagicStrength();
    mDef = enemy->getDefence();
    mEXP = enemy->getEXP();
  }

  TerminalFunctions* term;
  player* please;

public:
  int battle();

  AttackTest(TerminalFunctions* _term, int playerid);//Charles Barry
  AttackTest(TerminalFunctions* _term, int playerid, monster* phil);//Charles Barry
};

#endif
