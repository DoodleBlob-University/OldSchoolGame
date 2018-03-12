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

class PeacefulMap : public Map{
private:
  void fetchPlayerCoords();
  void interact(int pos[2]);
  template<typename T, unsigned int N, unsigned int Nn>
  bool ifIdenticalArray(T (&array1)[N], T (&array2)[Nn]);
  bool checkPlayerExit();
  std::vector<std::vector<int> > exitcoords;
protected:
  void fetchExitCoords();
public:
  int playerpos[2];
  bool movement();
  PeacefulMap(int _ID, WINDOW* _win, MapTile* maptiles);
};

class Dungeon : public PeacefulMap{
private:
protected:
public:
  int bosspos[2];
  Dungeon(int _ID, WINDOW* _win, MapTile* maptiles);
};

#endif
