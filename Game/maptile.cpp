#include <ncurses.h>
#include <string>
#include <vector>
#include "libsqlite.hpp"
#include "maptile.h"

int MapTile::getMapTileNo(){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "SELECT COUNT(*) FROM maptiles;" );
  cur->prepare();
  while( cur->step() ){
  return cur->get_int(0);}
}

void MapTile::loadMapTiles(){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "SELECT * FROM maptiles;" );
  cur->prepare();
  while( cur->step() ){
  int selectedtile = cur->get_int(0);
  tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);}
}

MapTile::MapTile(){
  tiles.resize(getMapTileNo());
  loadMapTiles();
}
