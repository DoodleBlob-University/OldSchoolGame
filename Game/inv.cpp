//Charles Barry
#include <string>
#include <vector>

#include "inv.h"
#include "libsqlite.hpp"


      void Item::setItemValues(std::string _name, int _cost, int _itemType){//Kai Arnold
        name = _name; cost = _cost; itemType = _itemType;
      }

        void Weapon::setValues(std::string name, int _damage, int cost){//Kai Arnold
          damage = _damage;
          setItemValues(name, cost, 0);
        }

        void Armour::setValues(std::string name, int _armour, int cost){//Kai Arnold
          armour = _armour;
          setItemValues(name, cost, 1);
        }


        void Potion::setValues(std::string name, int _health, int _mana, int cost){//Kai Arnold
          health = _health; mana = _mana;
          setItemValues(name, cost, 2);
        }

        void PlayerInventory::getWeapon() {//Kai Arnold
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, weapon.name, weapon.damage, weapon.cost FROM weapon, item WHERE item.WeaponID = weapon.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].w->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3));
            }
        }
        void PlayerInventory::getArmour() {//Kai Arnold
            int count = 1;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, armour.name, armour.Armour, armour.cost FROM armour, item WHERE item.ArmourID = armour.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].a->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3));
            }
        }
        void PlayerInventory::getPotion() {//Kai Arnold
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT item.id, potion.name, potion.health, potion.mana, potion.cost FROM potion, item where item.PotionID = potion.ID;");
            cur->prepare();
            while(cur->step()){
                items[cur->get_int(0)].p->setValues(cur->get_text(1), cur->get_int(2), cur->get_int(3), cur->get_int(4));
            }
        }
        int PlayerInventory::getItemCount() {//Kai Arnold
            int size;
            sqlite::sqlite db("Database.db");
            auto cur = db.get_statement();
            cur->set_sql("SELECT COUNT(*) FROM item;");
            cur->prepare();
            cur->step();
            size = cur->get_int(0);

            return size;
        }

        PlayerInventory::PlayerInventory(){//Kai Arnold and Charles Barry
            itemno = getItemCount() + 1;//itemno starts from 1 as the position in the vector equals itemid
            items.resize(itemno);//resize all vectors to their appropriate size
            playerInv.resize(10);
            playerEquip.resize(3);
            getWeapon();//get weapons from database
            getArmour();//get armour from database
            getPotion();//get potions from database
        }
        void PlayerInventory::addItem(int id){//Kai Arnold and Charles Barry
          int emptypos = -1;
          for(int i = 0; i < playerInv.size(); ++i){//check each object of every structure in the vector to see if they are empty
            if(playerInv[i].w->getName() == "" && playerInv[i].a->getName() == "" && playerInv[i].p->getName() == ""){
              emptypos = i;//get the position in the vector of the empty structure
              break;//exit the for loop
            }
          }
          if(emptypos >= 0){
            if(id <= itemno && id > 0){//check if id is valid
            playerInv[emptypos] = items[id];//the empty position in playerinv is given the reference to the item
            }
          }
        }
        void PlayerInventory::removeItem(int pos){//Kai Arnold
          playerInv[pos].w = wempty;
          playerInv[pos].a = aempty;
          playerInv[pos].p = pempty;
        }
        void PlayerInventory::equipItem(int invpos, int equipslot){//Kai Arnold
          Inventory temp = playerEquip[equipslot];
          playerEquip[equipslot] = playerInv[invpos];
          playerInv[invpos] = temp;
        }


/*
int main() {//Kai Arnold
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
*/
