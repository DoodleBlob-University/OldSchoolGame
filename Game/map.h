//Charles Barry
#ifndef MAP_H
#define MAP_H

class Map{//Charles Barry
private:
  std::string name;
  MapTile *maptiles;
  void loadMap();
protected:
  int ID;
  const int width = 105; const int height = 35;//height of displayed map is 34 to avoid weird database errors
  int map[35][106];
  WINDOW* win;
public:
  void printMap();
  const char* getName();
  Map(int _ID, WINDOW* _win, MapTile* _maptiles);
};

class PeacefulMap : public Map{//Charles Barry
private:
  void fetchPlayerCoords();
  int interact(int pos[2]);//William Smith
  template<typename T, unsigned int N, unsigned int Nn>
  bool ifIdenticalArray(T (&array1)[N], T (&array2)[Nn]);
  bool checkPlayerExit();
  std::vector<std::vector<int> > exitcoords;
protected:
  void fetchExitCoords();
public:
  int playerpos[2];
  virtual int movement();
  PeacefulMap(int _ID, WINDOW* _win, MapTile* maptiles);
};

class Dungeon : public PeacefulMap{//Charles Barry
private:
  int checkForMonsters();
public:
  int bosspos[2];
  int movement();
  Dungeon(int _ID, WINDOW* _win, MapTile* maptiles);
};

#endif
