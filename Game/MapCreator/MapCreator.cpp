//Charlie Barry
#include <ncurses.h>
#include <locale>
//#include <chrono>
//#include <thread>
#include "../libsqlite.hpp" //sqlite library with wrapper

using namespace std;

const int tileno = 9;

struct tile {
  string character;
  int colour;
} ;

struct tile tiles[tileno];

void uploadMap(int map[35][105], WINDOW* win){
  mvwprintw(win, 10, 3, "Please Wait!");
  for(int i = 0; i < 1; ++i){
    sqlite::sqlite db( "../gamedb.db" ); // open database
    for(int x = 1; x < 106; ++x){
      for(int y = 1; y < 35; ++y){
        auto cur = db.get_statement(); // create query
        cur->set_sql( "INSERT INTO map(dungeonID, y, x, tileID) VALUES (1,?,?,?);" );
        cur->prepare();
        cur->bind( 1, x );                // set placeholders
        cur->bind( 2, y );
        cur->bind( 3, map[y][x] );
        cur->step();
      }
    }
  }
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

void loadMap(int map[35][105], WINDOW* win){

  int yvalue, xvalue, tileno = 1;
  sqlite::sqlite db( "../gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT y, x, tileID FROM map WHERE dungeonID = 1 ORDER BY y, x;" );
  cur->prepare(); // run query
  while( cur->step() ){ // loop over results
    yvalue = cur->get_int(0);
    xvalue = cur->get_int(1);
    tileno = cur->get_int(2);

    map[yvalue][xvalue] = tileno;
    //wprintw(win, "%i,%i %i\n", yvalue, xvalue, tileno);
  }
  printMap(map, win);
}

void printOptions(WINDOW* win){
  box(win,0,0);
  WINDOW* currenttile = derwin(win, 3,3, 2, 21);
  box(currenttile,0,0);
  wrefresh(currenttile);
  sqlite::sqlite db( "../gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT * FROM maptiles;" );
  cur->prepare(); // run query
  while( cur->step() ){ // loop over results
  int selectedtile = cur->get_int(0);
  tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);}

  mvwprintw(win,1,16,"current tile"); mvwprintw(win, 3, 15, "O <--"); mvwprintw(win, 3, 25, "--> P"); mvwprintw(win, 8, 18, "q : quit"); mvwprintw(win, 10, 18, "u : upload"); mvwprintw(win, 12, 18, "l : load");
  mvwprintw(win,3,22, tiles[0].character.c_str());
  wrefresh(win);
}

void refreshOptions(WINDOW* win, int tilepos){
  if(tiles[tilepos].colour > 0){wattron(win,COLOR_PAIR(tiles[tilepos].colour));}
  mvwprintw(win,3,22, tiles[tilepos].character.c_str());
  wattroff(win,COLOR_PAIR(tiles[tilepos].colour));
  wrefresh(win);
}

int input(WINDOW* win, int map[35][105], WINDOW* info){
  int coords[] = {1,1}; int tilepos = 0;
  while(true){
    switch(wgetch(win)){
      case 'w':
        if(coords[0]-1 != 0){coords[0] -= 1;}
        break;

      case 'a':
        if(coords[1]-1 != 0){coords[1] -= 1;}
        break;

      case 's':
        if(coords[0]+1 != 35){coords[0] += 1;}
        break;

      case 'd':
        if(coords[1]+1 != 106){coords[1] += 1;}
        break;

      case ' ':
        if(tiles[tilepos].colour > 0){wattron(win,COLOR_PAIR(tiles[tilepos].colour));}
        wprintw(win,tiles[tilepos].character.c_str());
        map[coords[0]][coords[1]] = tilepos;
        wattroff(win,COLOR_PAIR(tiles[tilepos].colour));
        break;

      case 'o':
        if(tilepos-1 >= 0){tilepos -= 1;}
        break;

      case 'p':
        if(tilepos+1 < tileno){tilepos += 1;}
        break;

      case 'u':
        uploadMap(map, info);
        break;

      case 'l':
        loadMap(map, win);
        break;

      case 'q':
        return 0;
        break;
    }
    wmove(win, coords[0], coords[1]);
    refreshOptions(info, tilepos);
    wrefresh(win);
  }
}

int main(void){
  int map[35][105] = {0};
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

  WINDOW* mapwin = newwin(36,107,0,1);
  WINDOW* info = newwin(36,47,0,108);
  refresh();
  box(mapwin,0,0);
  wrefresh(mapwin);

  printOptions(info);
  wmove(mapwin, 1, 1);

  input(mapwin, map, info);

  endwin();
}
