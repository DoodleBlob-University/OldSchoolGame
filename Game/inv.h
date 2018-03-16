//Charles Barry
#ifndef INV_H
#define INV_H

class Item {// Kai Arnold - Creates a class of Item, the purpose of this class is to create an Item.
    private:
        int cost;
        std::string name;           // Creating private variables cost of type int, name of type string and itemType of type int.
        int itemType;
    protected:
      void setItemValues(std::string _name, int _cost, int _itemType);  // Creates a Function to allow access to private variables. 
    public:
        std::string getName(){return name;}  // Creates a function called getName, that simply returns name.
        int getCost(){return cost;}
        int getType(){return itemType;}
        Item(){} // Creates an instace of Item which is empty. 
};

class Weapon : public Item {// Kai Arnold - Creates a class of Weapon which inherits attributes from the Item Class.
    private:
        int damage;  // Declaring a private variable damage of type int.
    public:
        void setValues(std::string name, int _damage, int cost);    // Creates a function to allow access to private variables. 
        int getDamage(){return damage;}
        Weapon() : Item(){} // Creates an intstance of Weapon which is empty.
    };

class Armour : public Item {// Kai Arnold - Creates a class of Armour which inherits attributes from the Item Class. 
    private:
        int armour; // Declaring a private variable armour of type int.
    public:
        void setValues(std::string name, int _armour, int cost); // Creates a function to allow access to private variables. 
        int getArmour(){return armour;}
        Armour() : Item(){} // Creates an intstance of Weapon which is empty.
};

class Potion : public Item {//Kai Arnold - Creates a class of Potion which inherits attributes from the Item Class. 
    private:
        int health; // Declaring a private variable armour of type int.
        int mana;
    public:
        int getHealth(){return health;}
        int getMana(){return mana;}
        void setValues(std::string name, int _health, int _mana, int cost); //Declaring a private variable armour of type int.
        Potion() : Item(){} // Creates an intstance of Weapon which is empty.
};

class PlayerInventory{//Kai Arnold and Charles Barry
    private:
        Weapon* wempty = new Weapon(); // Pointer to the Weapon Class which creates a empty instance of Weapon
        Armour* aempty = new Armour();
        Potion* pempty = new Potion();
        struct Inventory{
            Weapon* w = new Weapon(); //Pointer to the Weapon Class inside a structure which creates a empty instance of Weapon
            Armour* a = new Armour();
            Potion* p = new Potion();
        };
        void getWeapon();
        void getArmour();
        void getPotion();
        int getItemCount();
        int itemno = 0;
    public:
        std::vector<Inventory> items; //Creates a vector of type Inventory called Items with no size.
        std::vector<Inventory> playerInv;
        std::vector<Inventory> playerEquip;
        PlayerInventory();
        void addItem(int id);
        void removeItem(int pos);
        void equipItem(int invpos, int equipslot);
};

#endif
