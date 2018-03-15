//Charles Barry
#ifndef MAPTILE_H
#define MAPTILE_H

class MapTile{//Charles Barry
private:
  struct tile {
    std::string character;
    int colour;
  } ;
  int getMapTileNo();//William Smith
  void loadMapTiles();//William Smith
public:
  std::vector<tile> tiles;
  MapTile();
};

#endif
