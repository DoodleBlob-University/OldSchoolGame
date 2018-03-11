#ifndef MAP_H
#define MAP_H

class MapTile{
private:
  struct tile {
    std::string character;
    int colour;
  } ;
  int getMapTileNo();
  void loadMapTiles();
public:
  std::vector<tile> tiles;
  MapTile();
};

class Map{
private:
  int ID;
  std::string name;
  MapTile *maptiles;
  void loadMap();
protected:
  const int width = 105; const int height = 35;//height of displayed map is 34 to avoid weird database errors
  int map[35][106];
  WINDOW* win;
public:
  void printMap();
  const char* getName();
  Map(int _ID, WINDOW* _win, MapTile* _maptiles);
};

class PeacefulMap : public Map{
private:
  void fetchPlayerCoords(int ID);
  void interact(int pos[2]);
protected:
public:
  int playerpos[2];
  void movement();
  PeacefulMap(int ID, WINDOW* _win, MapTile* maptiles);
};

class Dungeon : public PeacefulMap{
private:
  void fetchBossCoords(int ID){}
  void fetchExitCoords(int ID){}
protected:
public:
  int bosspos[2];
  Dungeon(int ID, WINDOW* _win, MapTile* maptiles);
};

#endif
