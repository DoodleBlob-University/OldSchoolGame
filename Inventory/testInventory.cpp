#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <array>
#include "libsqlite.hpp"

using namespace std;

class Item {
    private:
        int itemID;
        int cost;
        string name;
        int itemType;
    public:
        int getID(){return itemID;}
        string getName(){return name;}
        int getCost(){return cost;}
        int getType(){return itemType;}
        Item(int _itemID, string _name, int _cost, int _itemType){
            itemID = _itemID; name = _name; cost = _cost; itemType = _itemType;
        }
};

class Weapon : public Item {
    private:
        int damage;

    public:
        Weapon(int ID, string name, int _damage, int cost) : Item(ID, name, cost, 0){
            damage = _damage;
        }
        int getDamage(){
            return damage;
        }
    };

class Armour : public Item {
    private:
        int armour;
    public:
        Armour(int ID, string name, int _armour, int cost) : Item(ID, name, cost, 1){
            armour = _armour;
        }
        int getArmour(){
            return armour;
        }
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
        Potion(int ID, string name, int _health, int _mana, int cost) : Item(ID, name, cost, 2){
            health = _health; mana = _mana;
        }
};

class PlayerInventory{
    private:
        struct Inventory
            Weapon *Weapon;
            Armour *Armour;
            Potion *Potion;
        };
        void getWeapon() {
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, weapon.name, weapon.damage, weapon.cost FROM weapon, item WHERE item.WeaponID = weapon.ID;");
            cur->prepare();
            while(cur->step()){
                int id = cur->get_int(0);
                Weapon* wea = new Weapon(id, cur->get_text(1), cur->get_int(2), cur->get_int(3));
                items[id].Weapon = wea;
            }
        }
        void getArmour() {
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, armour.name, armour.Armour, armour.cost FROM armour, item WHERE item.ArmourID = armour.iD;");
            cur->prepare();
            while(cur->step()){
                int id = cur->get_int(0);
                Armour* arm = new Armour(id, cur->get_text(1), cur->get_int(2), cur->get_int(3));
                items[id].Armour = arm;
            }
        }
        void getPotion() {
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, potion.name, potion.health, potion.mana, potion.cost FROM potion, item where item.PotionID = potion.ID;");
            cur->prepare();
            while(cur->step()){
                int id = cur->get_int(0);
                Potion* pot = new Potion(id, cur->get_text(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5));
                items[id].Potion = pot;
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
    public:
        vector<Inventory> items;
        vector<Inventory> playerInventory;
        vector<Inventory> playerEquipped;

        PlayerInventory(){
            items.resize(getItemCount());
            getWeapon();
            getArmour();
            getPotion();
        }
        void addItem(int id){
          int emptypos;
          for(int i = 1; i < playerInventory.size(); ++i){
            if(playerInventory[i].Weapon = NULL && playerInventory[i].Armour = NULL && playerInventory[i].Potion = NULL){
              emptypos = i;
              break;
            }
          }
          if(!emptypos){
            //no adding here
          }else{
            playerInventory[emptypos] = items[id];
          }
        }
        void removeItem(int id){

        }
};


int main() {
    PlayerInventory* inv = new PlayerInventory();
    //inv->addItem(2);
    inv->addItem(2);

    initscr();
    printw("%s", inv->playerInventory[1].Weapon->getName().c_str());
    getch();
    endwin();


}
