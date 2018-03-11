#include <ncurses.h>
#include <string>
#include <vector>
#include "map.h"
#include "libsqlite.hpp"

//-----------------------   MAPTILES   -----------------------------
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


//-----------------------   MAP   -----------------------------
void Map::printMap(){
  for(int y = 1; y < height; ++y){
    for(int x = 1; x < width+1; ++x){
      if(maptiles->tiles[map[y][x]].colour > 0){wattron(win,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));}
      mvwprintw(win, y, x, maptiles->tiles[map[y][x]].character.c_str());
      wattroff(win,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));
}}}
const char* Map::getName(){
  return name.c_str();
}
Map::Map(int _ID, WINDOW* _win, MapTile* _maptiles){
  ID = _ID; win = _win;
  maptiles = _maptiles;
  loadMap();
  printMap();
  wrefresh(win);
}
void Map::loadMap(){
  int yvalue, xvalue, tileno = 1;
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select x, y, tileID, dungeon.name from map, dungeon where dungeonID = ? and dungeonID = dungeon.ID order by y, x;" );
  cur->prepare();
  cur->bind( 1, ID );
  while( cur->step() ){
    xvalue = cur->get_int(0);
    yvalue = cur->get_int(1);
    tileno = cur->get_int(2);
    name = cur->get_text(3);

    map[yvalue][xvalue] = tileno;
  }
}



//------------   PEACEFUL MAP   --------------------
void PeacefulMap::fetchPlayerCoords(int ID){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select playery, playerx from dungeon where ID = ?;" );
  cur->prepare();
  cur->bind( 1, ID );
  while(cur->step()){
  playerpos[0] = cur->get_int(0);
  playerpos[1] = cur->get_int(1);}
}
void PeacefulMap::interact(int pos[2]){
  if(map[pos[0]-1][pos[1]] == 8){
      map[pos[0]-1][pos[1]] = 0;
      int temppos[] = {pos[0]-1,pos[1]};
      interact(temppos);
  }
  if(map[pos[0]][pos[1] - 1] == 8){
      map[pos[0]][pos[1] - 1] = 0;
      int temppos[] = {pos[0],pos[1]-1};
      interact(temppos);
  }
  if(map[pos[0] + 1][pos[1]] == 8){
      map[pos[0] + 1][pos[1]] = 0;
      int temppos[] = {pos[0]+1,pos[1]};
      interact(temppos);
  }
  if(map[pos[0]][pos[1] + 1] == 8){
      map[pos[0]][pos[1] + 1] = 0;
      int temppos[] = {pos[0],pos[1]+1};
      interact(temppos);
  }
}
void PeacefulMap::movement(){
  switch(toupper(wgetch(win))){
    case 'W':
        if((map[playerpos[0]-1][playerpos[1]] == 0) && (playerpos[0] - 1 > 0)){
          playerpos[0] -= 1;
        }
        break;
    case 'A':
        if((map[playerpos[0]][playerpos[1] - 1] == 0) && (playerpos[1] - 1 > 0)){
          playerpos[1] -= 1;
        }
        break;
    case 'S':
        if((map[playerpos[0]+1][playerpos[1]] == 0) && (playerpos[0] + 1 <= height - 1)){
          playerpos[0] += 1;
        }
        break;
    case 'D':
         if((map[playerpos[0]][playerpos[1] + 1] == 0) && (playerpos[1] + 1 <= width)){
           playerpos[1] += 1;
         }
         break;
    case 'E':
        interact(playerpos);
        break;
    break;
  }
  printMap();
  mvwprintw(win, playerpos[0], playerpos[1], "X");
  wrefresh(win);
}
PeacefulMap::PeacefulMap(int ID, WINDOW* _win, MapTile* maptiles) : Map(ID, _win, maptiles){
  fetchPlayerCoords(ID);
  mvwprintw(win, playerpos[0], playerpos[1], "X");
  wrefresh(win);
}




//------------   DUNGEON   --------------------
Dungeon::Dungeon(int ID, WINDOW* _win, MapTile* maptiles) : PeacefulMap(ID, _win, maptiles){

}
