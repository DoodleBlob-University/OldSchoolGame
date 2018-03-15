//Charles Barry
#include <ncurses.h>
#include <string>
#include <vector>

#include "maptile.h"
#include "map.h"
#include "libsqlite.hpp"

//-----------------------   MAP   -----------------------------
void Map::printMap(){//Charles Barry
  for(int y = 1; y < height; ++y){
    for(int x = 1; x < width+1; ++x){
      if(maptiles->tiles[map[y][x]].colour > 0){wattron(win,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));}
      mvwprintw(win, y, x, maptiles->tiles[map[y][x]].character.c_str());
      wattroff(win,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));
    }}
    wrefresh(win);
}

const char* Map::getName(){//Charles Barry
  return name.c_str();
}

Map::Map(int _ID, WINDOW* _win, MapTile* _maptiles){//Charles Barry
  ID = _ID; win = _win;
  maptiles = _maptiles;
  loadMap();
  printMap();
  wrefresh(win);
}

void Map::loadMap(){//Charles Barry
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
void PeacefulMap::fetchPlayerCoords(){//Charles Barry
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select playery, playerx from dungeon where ID = ?;" );
  cur->prepare();
  cur->bind( 1, this->ID );
  while(cur->step()){
  playerpos[0] = cur->get_int(0);
  playerpos[1] = cur->get_int(1);}
}

int PeacefulMap::interact(int pos[2]){//William Smith
  // Opens doors checking case ID
  if(map[pos[0]-1][pos[1]] == 8){
      map[pos[0]-1][pos[1]] = 0;
      int temppos[] = {pos[0]-1,pos[1]}; //Temporarily moves pos allowing double doors to be open
      interact(temppos); //Recursion call to rerun code to open doors
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
  if(map[pos[0] - 1][pos[1]] == 9){ //Checks if space is a chest (Case ID = 9)
    map[pos[0]-1][pos[1]] = 0; //If so change TileID to 0 removing the chest
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
bool PeacefulMap::ifIdenticalArray(T (&array1)[N], T (&array2)[Nn]){//Charles Barry
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

bool PeacefulMap::checkPlayerExit(){//Charles Barry
  for(int i = 0; i < exitcoords.size(); ++i){
    int temparray[] = {exitcoords[i][0], exitcoords[i][1]};
    if(ifIdenticalArray(playerpos, temparray)){
      return true;
    }
  }
  return false;
}
void PeacefulMap::fetchExitCoords(){//Charles Barry
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

int PeacefulMap::movement(){//William Smith & Charles Barry
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

PeacefulMap::PeacefulMap(int _ID, WINDOW* _win, MapTile* maptiles) : Map(_ID, _win, maptiles){//Charles Barry
  fetchPlayerCoords();
  fetchExitCoords();
  mvwprintw(win, playerpos[0], playerpos[1], "X");
  wrefresh(win);
}



//------------   DUNGEON   --------------------
Dungeon::Dungeon(int _ID, WINDOW* _win, MapTile* maptiles) : PeacefulMap(_ID, _win, maptiles){//Charles Barry
    int numberOfMonsters = 20;
    {//Spawn monsters randomly across map //Matthew Fretwell
      sqlite::sqlite db( "gamedb.db" );
      auto cur = db.get_statement();
      cur->set_sql("SELECT map.y, map.x FROM map WHERE map.tileID = 0 AND dungeonID = ? ORDER BY RANDOM() LIMIT ?;");
      cur->prepare();
      cur->bind(1, ID);
      cur->bind(2, numberOfMonsters);
      int num = 0;
        while(cur->step()){
        map[cur->get_int(0)][cur->get_int(1)] = 13;
        num = num+1;
      }
    }
    printMap();//reprints map with monsters displaying
    mvwprintw(_win, playerpos[0], playerpos[1],"X");//draws player onto screen
    wrefresh(_win);

}

int Dungeon::movement(){//Charles Barry
  int movementflag = checkForMonsters();
  if(movementflag){return movementflag;}//check before player moves

  movementflag = PeacefulMap::movement();
  if(movementflag){return movementflag;}

  movementflag = checkForMonsters();
  if(movementflag){return movementflag;}//check after player moves
}

int Dungeon::checkForMonsters(){//Charles Barry
  //not very nice looking :(
  if((map[playerpos[0]-1][playerpos[1]] == 13) || (map[playerpos[0]-1][playerpos[1]] == 14) && (playerpos[0] - 1 > 0)){//UP
    int movementflag = map[playerpos[0]-1][playerpos[1]] - 10;//takes away 10 to make values either 3 or 4
    map[playerpos[0]-1][playerpos[1]] = 0;//remove the monster on the map
    mvwprintw(win, playerpos[0]-1, playerpos[1], " ");//remove the monster visually
    return movementflag;
  }else if((map[playerpos[0]][playerpos[1] - 1] == 13) || (map[playerpos[0]][playerpos[1] - 1] == 14) && (playerpos[1] - 1 > 0)){//LEFT
    int movementflag = map[playerpos[0]][playerpos[1]-1] - 10;
    map[playerpos[0]][playerpos[1]-1] = 0;
    mvwprintw(win, playerpos[0], playerpos[1]-1, " ");
    return movementflag;
  }else if((map[playerpos[0]+1][playerpos[1]] == 13) || (map[playerpos[0]+1][playerpos[1]] == 14) && (playerpos[0] + 1 <= height - 1)){//DOWN
    int movementflag = map[playerpos[0]+1][playerpos[1]] - 10;
    map[playerpos[0]+1][playerpos[1]] = 0;
    mvwprintw(win, playerpos[0]+1, playerpos[1], " ");
    return movementflag;
  }else if((map[playerpos[0]][playerpos[1] + 1] == 13) || (map[playerpos[0]][playerpos[1] + 1] == 14) && (playerpos[1] + 1 <= width)){//RIGHT
    int movementflag = map[playerpos[0]][playerpos[1] + 1] - 10;
    map[playerpos[0]][playerpos[1] + 1] = 0;
    mvwprintw(win, playerpos[0], playerpos[1]+1 , " ");
    return movementflag;
  }
  return 0;
}
