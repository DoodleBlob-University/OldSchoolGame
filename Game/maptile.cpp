//Charles Barry
#include <ncurses.h>
#include <string>
#include <vector>
#include "libsqlite.hpp"
#include "maptile.h"

int MapTile::getMapTileNo(){//William Smith 
  sqlite::sqlite db( "gamedb.db" ); //Function finds how many map tiles there are, using that to size the dungeon up
  auto cur = db.get_statement();
  cur->set_sql( "SELECT COUNT(*) FROM maptiles;" ); //SQL query
  cur->prepare();
  cur->step(); //Runs Query
  return cur->get_int(0);}//Get amount of map tiles and return it
}

void MapTile::loadMapTiles(){//William Smith
  sqlite::sqlite db( "gamedb.db" ); //Function select everything from map tiles; ID, Character, Colour.
  auto cur = db.get_statement();
  cur->set_sql( "SELECT * FROM maptiles;" ); //SQL query
  cur->prepare();
  while( cur->step() ){ //Runs Query
  int selectedtile = cur->get_int(0); //Assigns selected tiles to variable
  tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);} //Puts that information into the vector
}

MapTile::MapTile(){//Charles Barry
  tiles.resize(getMapTileNo());
  loadMapTiles();
}
