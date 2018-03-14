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
void PeacefulMap::fetchPlayerCoords(){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select playery, playerx from dungeon where ID = ?;" );
  cur->prepare();
  cur->bind( 1, this->ID );
  while(cur->step()){
  playerpos[0] = cur->get_int(0);
  playerpos[1] = cur->get_int(1);}
}

int PeacefulMap::interact(int pos[2]){ // Opens doors checking case ID 
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
  if(map[pos[0] - 1][pos[1]] == 9){
    map[pos[0]-1][pos[1]] = 0;
    return 1;
  }
  if(map[pos[0]][pos[1] - 1] == 9){
    map[pos[0]][pos[1] - 1] = 0;
    return 1;
  }
  if(map[pos[0] + 1][pos[1]] == 9){
    map[pos[0] + 1][pos[1]] = 0;
    return 1;
  }
  if(map[pos[0]][pos[1] + 1] == 9){
    map[pos[0]][pos[1] + 1] = 0;
    return 1;
  }
  return 0;
}

template<typename T, unsigned int N, unsigned int Nn>
bool PeacefulMap::ifIdenticalArray(T (&array1)[N], T (&array2)[Nn]){
  //I assume the data types for the array are identical - if this isnt the case an error will occur upon compiling
    if(N != Nn){return false;}else{
      for(int i = 0; i < N; ++i){
        if(array1[i] != array2[i]){
          return false;
        }
      }
      return true;
    }
}

bool PeacefulMap::checkPlayerExit(){
  for(int i = 0; i < exitcoords.size(); ++i){
    int temparray[] = {exitcoords[i][0], exitcoords[i][1]};
    if(ifIdenticalArray(playerpos, temparray)){
      return true;
    }
  }
  return false;
}

void PeacefulMap::fetchExitCoords(){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select y, x from exitcoord where DungeonID = ?;" );
  cur->prepare();
  cur->bind( 1, this->ID );
  while(cur->step()){
    std::vector<int> temp = {cur->get_int(0),  cur->get_int(1)};
    exitcoords.push_back(temp);
  }
}

int PeacefulMap::movement(){
  if(checkPlayerExit()){return 1;}
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
        if(interact(playerpos)){return 2;};
        break;
    break;
  }
  printMap();
  mvwprintw(win, playerpos[0], playerpos[1], "X");
  wrefresh(win);
}

PeacefulMap::PeacefulMap(int _ID, WINDOW* _win, MapTile* maptiles) : Map(_ID, _win, maptiles){
  fetchPlayerCoords();
  fetchExitCoords();
  mvwprintw(win, playerpos[0], playerpos[1], "X");
  wrefresh(win);
}



//------------   DUNGEON   --------------------
Dungeon::Dungeon(int _ID, WINDOW* _win, MapTile* maptiles) : PeacefulMap(_ID, _win, maptiles){

}
