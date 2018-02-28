//Charlie Barry
//compile with 'g++ -std=c++14 game.cpp Window.cpp -o game -lncursesw -lsqlite3'
#include <locale>
#include <ncurses.h>

#include "libsqlite.hpp"

#include "Window.h"

using namespace std;

struct tile {
  string character;
  int colour;
} ;

int getMapTileNo(){
  sqlite::sqlite db( "MapCreator/gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT COUNT(*) FROM maptiles;" );
  cur->prepare(); // run query
  while( cur->step() ){
  return cur->get_int(0);}
}

vector<tile> tiles(getMapTileNo());

void initialiseGame(){

  sqlite::sqlite db( "MapCreator/gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT * FROM maptiles;" );
  cur->prepare(); // run query
  while( cur->step() ){ // loop over results
  int selectedtile = cur->get_int(0);
  tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);}
}

void printMap(int map[35][105], WINDOW* win){
  for(int y = 1; y < 35; ++y){
    for(int x = 1; x < 106; ++x){
      if(tiles[map[y][x]].colour > 0){wattron(win,COLOR_PAIR(tiles[map[y][x]].colour));}
      mvwprintw(win, y, x, tiles[map[y][x]].character.c_str());
      wattroff(win,COLOR_PAIR(tiles[map[y][x]].colour));
    }
  }
}

const char* loadMap(int map[35][105], WINDOW* win, int dungeonID){
  int yvalue, xvalue, tileno = 1;
  string dungeonname;
  sqlite::sqlite db( "MapCreator/gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT map.y, map.x, map.tileID, dungeon.name FROM map, dungeon WHERE map.dungeonID = ? ORDER BY map.y, map.x;" );
  cur->prepare(); // run query
  cur->bind( 1, dungeonID );
  while( cur->step() ){ // loop over results
    yvalue = cur->get_int(0);
    xvalue = cur->get_int(1);
    tileno = cur->get_int(2);
    dungeonname = cur->get_text(3);

    map[yvalue][xvalue] = tileno;
  }
  printMap(map, win);
  wrefresh(win);
  return dungeonname.c_str();
}

void printDungeonName(WINDOW* stat, string dungeonname, int windowWidth){
  mvwprintw(stat, 1, (windowWidth - dungeonname.size())/2, dungeonname.c_str());
  wmove(stat, 2, ((windowWidth - dungeonname.size())/2) - 1);
  for(int i = 0; i < (dungeonname.size() + 2); ++i){
    wprintw(stat, "¯");
  }
}

int MainMenu(WINDOW* stat, string dungeonname, int windowWidth){
  printDungeonName(stat, dungeonname, windowWidth);
  string MenuOptions[] = {"Play Game", "Extra", "Options", "Exit"};
  int selected = 0;

  while(true){
    for(int i = 0; i < (sizeof(MenuOptions)/sizeof(*MenuOptions)); ++i){
      if(i == selected){wattron(stat,COLOR_PAIR(2));}
      mvwprintw(stat, i+5, (windowWidth - MenuOptions[i].size())/2, MenuOptions[i].c_str());
      wattroff(stat,COLOR_PAIR(2));
    }
    wmove(stat, 2, 2);
    switch(toupper(wgetch(stat))){
      case 'W':
        if(selected != 0){selected -= 1;}
        break;
      case 'S':
        if(selected != (sizeof(MenuOptions)/sizeof(*MenuOptions))-1){selected += 1;}
        break;
      case ' ':
        switch(selected){
          case 0://play game
            return 0;
            break;
          case 1://extra

            break;
          case 2://options

            break;
          case 3://exit
            return 1;
            break;
        }
        break;
    }
  }
}

int gameSequence(int map[35][105], WINDOW* game, WINDOW* stat, WINDOW*){
  const int windowWidth = 45;

  string dungeonname = loadMap(map, game, 1);
  if(MainMenu(stat, dungeonname, windowWidth)){return 1;};

  getch();

}

int main(){
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, 0);
    init_pair(2, COLOR_RED, 0);
    init_pair(3, COLOR_GREEN, 0);
    init_pair(4, COLOR_YELLOW, 0);
    init_pair(5, COLOR_BLUE, 0);
    init_pair(6, COLOR_MAGENTA, 0);
    noecho();

    Window main(38,159);
    Window game(main.getData(),36,107,1,2);
    Window stat(main.getData(),24,47,1,110);
    Window term(main.getData(),12,47,25,110);

    keypad(stdscr, true);

    int map[35][105] = {0};
    initialiseGame();
    gameSequence(map, game.getData(), stat.getData(), term.getData());

    endwin();
}
