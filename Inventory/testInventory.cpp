#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <array>
#include "libsqlite.hpp"

using namespace std;

class Item {
    private:
        int cost;
        string name;
        int itemType;
    protected:
      void setItemValues(string _name, int _cost, int _itemType){
        name = _name; cost = _cost; itemType = _itemType;
      }
    public:
        string getName(){return name;}
        int getCost(){return cost;}
        int getType(){return itemType;}
        Item(){}
};

class Weapon : public Item {
    private:
        int damage;

    public:
        void setValues(string name, int _damage, int cost){
          damage = _damage;
          setItemValues(name, cost, 0);
        }
        int getDamage(){
            return damage;
        }
        Weapon() : Item(){}
    };

class Armour : public Item {
    private:
        int armour;
    public:
        void setValues(string name, int _armour, int cost){
          armour = _armour;
          setItemValues(name, cost, 1);
        }
        int getArmour(){
            return armour;
        }
        Armour() : Item(){}
};

class Potion : public Item {

    private:
        int health;
        int mana;
    public:
        int getHealth(){
            return health;
        }
        int getMana(){
            return mana;
        }
        void setValues(string name, int _health, int _mana, int cost){
          health = _health; mana = _mana;
          setItemValues(name, cost, 2);
        }

        Potion() : Item(){}
};

class PlayerInventory{
    private:
        struct Inventory{
            Weapon* w = new Weapon();
            Armour* a = new Armour();
            Potion* p = new Potion();
        };
        void getWeapon() {
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, weapon.name, weapon.damage, weapon.cost FROM weapon, item WHERE item.WeaponID = weapon.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].w->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3));
            }
        }
        void getArmour() {
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, armour.name, armour.Armour, armour.cost FROM armour, item WHERE item.ArmourID = armour.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].a->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3));
            }
        }
        void getPotion() {
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, potion.name, potion.health, potion.mana, potion.cost FROM potion, item where item.PotionID = potion.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].p->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3), cur->get_int(4));
            }
        }
        int getItemCount() {
            int size;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT COUNT(*) FROM item;");
            cur->prepare();
            cur->step();
            size = cur->get_int(0);

            return size;
        }
        Weapon* wempty = new Weapon();
        Armour* aempty = new Armour();
        Potion* pempty = new Potion();
        int itemno = 0;
    public:
        vector<Inventory> items;
        vector<Inventory> playerInv;
        vector<Inventory> playerEquip;

        PlayerInventory(){
            itemno = getItemCount() + 1;
            items.resize(itemno);
            playerInv.resize(10);
            playerEquip.resize(3);
            getWeapon();
            getArmour();
            getPotion();
        }
        void addItem(int id){
          int emptypos = -1;
          for(int i = 0; i < playerInv.size(); ++i){
            if(playerInv[i].w->getName() == "" && playerInv[i].a->getName() == "" && playerInv[i].p->getName() == ""){
              emptypos = i;
              break;
            }
          }
          //playerInventory[1] = items[id];
          if(emptypos >= 0){
            if(id <= itemno){
            playerInv[emptypos] = items[id];
          }//ur a fgt
          }else{
            //is empty bois
          }
        }
        void removeItem(int pos){
          playerInv[pos].w = wempty;
          playerInv[pos].a = aempty;
          playerInv[pos].p = pempty;
        }
        void equipItem(int invpos, int equipslot){
          Inventory temp = playerEquip[equipslot];
          playerEquip[equipslot] = playerInv[invpos];
          playerInv[invpos] = temp;
        }

};


int main() {
    PlayerInventory* inv = new PlayerInventory();
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->addItem(1);
    inv->removeItem(2);
    inv->addItem(10);

    inv->equipItem(3, 1);

    initscr();
    for(int i = 0; i < 10; ++i){
      printw("-%s\n", inv->playerInv[i].w->getName().c_str());
    }
    printw("\n\n");
    for(int i = 0; i < 3; ++i){
      printw("-%s\n", inv->playerEquip[i].w->getName().c_str());
    }
    getch();
    endwin();

}
