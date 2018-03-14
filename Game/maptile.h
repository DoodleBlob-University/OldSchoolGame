#ifndef MAPTILE_H
#define MAPTILE_H

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

#endif
