//Charles Barry
#ifndef INV_H
#define INV_H

class Item {//Kai Arnold
    private:
        int cost;
        std::string name;
        int itemType;
    protected:
      void setItemValues(std::string _name, int _cost, int _itemType);
    public:
        std::string getName(){return name;}
        int getCost(){return cost;}
        int getType(){return itemType;}
        Item(){}
};

class Weapon : public Item {//Kai Arnold
    private:
        int damage;
    public:
        void setValues(std::string name, int _damage, int cost);
        int getDamage(){return damage;}
        Weapon() : Item(){}
    };

class Armour : public Item {//Kai Arnold
    private:
        int armour;
    public:
        void setValues(std::string name, int _armour, int cost);
        int getArmour(){return armour;}
        Armour() : Item(){}
};

class Potion : public Item {//Kai Arnold
    private:
        int health;
        int mana;
    public:
        int getHealth(){return health;}
        int getMana(){return mana;}
        void setValues(std::string name, int _health, int _mana, int cost);
        Potion() : Item(){}
};

class PlayerInventory{//Kai Arnold and Charles Barry
    private:
        Weapon* wempty = new Weapon();
        Armour* aempty = new Armour();
        Potion* pempty = new Potion();
        struct Inventory{
            Weapon* w = new Weapon();
            Armour* a = new Armour();
            Potion* p = new Potion();
        };
        void getWeapon();
        void getArmour();
        void getPotion();
        int getItemCount();
        int itemno = 0;
    public:
        std::vector<Inventory> items;
        std::vector<Inventory> playerInv;
        std::vector<Inventory> playerEquip;
        PlayerInventory();
        void addItem(int id);
        void removeItem(int pos);
        void equipItem(int invpos, int equipslot);
};

#endif
