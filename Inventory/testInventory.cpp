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
    public:
        int getID(){return itemID;}
        string getName(){return name;} 
        int getCost(){return cost;}  
        Item(int _itemID, string _name, int _cost){
            itemID = _itemID; name = _name; cost = _cost;
        }
        Item(){
        }
};

class Weapon : public Item {
    private:
        int damage;

    public:
        Weapon(int ID, string name, int _damage, int cost) : Item(ID, name, cost){
            damage = _damage;
        }
        int getDamage(){
            return damage;
        }

        
    };

class Armour : public Item {
    private:
        int armour;
        int durability;
    public:
        Armour(int ID, string name, int _armour, int cost) : Item(ID, name, cost){
            armour = _armour;
        }      
        int getArmour(){
            return armour;
        }
};

class Potion : public Item {

    private: 
        int health;
        int stamina;
        int mana;
    public:
        Potion(int ID, string name, int _health, int _stamina, int _mana, int cost) : Item(ID, name, cost){
            health = _health; stamina = _stamina; mana = _mana;
        }
        int getHealth(){
            return health;
        }
        int getStamina(){
            return stamina;
        }
        int getMana(){
            return mana;
        }
};

class PlayerInventory{
    private:
        struct Inventory{
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
                Weapon* ree = new Weapon(id, cur->get_text(1), cur->get_int(2), cur->get_int(3));
                items[id].Weapon = ree;
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
                Armour* reh = new Armour(id, cur->get_text(1), cur->get_int(2), cur->get_int(3));
                items[id].Armour = reh;
            } 
        }
        void getPotion() {
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, potion.name, potion.health, potion.mana, potion.stamina, potion.cost FROM potion, item where item.PotionID = potion.ID;");
            cur->prepare();
            while(cur->step()){
                int id = cur->get_int(0);
                Potion* reeeeee = new Potion(id, cur->get_text(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5));
                items[id].Potion = reeeeee;
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
        array<Inventory, 10> playerInventory;
        array<Inventory, 10> playerEquipped;

        PlayerInventory(){
            items.resize(getItemCount());
            getWeapon();
            getArmour();
            getPotion();
        }
        void addItem(int id){
            int slot;
            for(int i = 1; i < playerInventory.size(); ++i) {
                slot = i;
            }
            if(slot > 0){
                playerInventory[slot] = items[id];
            }
        }
        //void removeItem(int id){

       // }
       // int equipItem(int id){

      //  }
};


int main() {
    PlayerInventory* inv = new PlayerInventory();
    //inv->addItem(2);
    inv->playerInventory[1] = inv->items[1];

    initscr();
    printw("%s", inv->playerInventory[1].Weapon->getName().c_str());
    getch();
    endwin();
    

}
