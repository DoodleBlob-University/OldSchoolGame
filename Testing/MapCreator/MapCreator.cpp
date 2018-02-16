//Charlie Barry
#include <ncurses.h>
#include <locale>
#include "libsqlite.hpp" //sqlite library with wrapper

using namespace std;

const int tileno = 3;

struct tile {
  string character;
  int colour;
} ;

struct tile tiles[tileno];

void printOptions(WINDOW* win){
  box(win,0,0);
  WINDOW* currenttile = derwin(win, 3,3, 2, 21);
  box(currenttile,0,0);
  wrefresh(currenttile);
  sqlite::sqlite db( "gamedb.db" ); // open database
  auto cur = db.get_statement(); // create query
  cur->set_sql( "SELECT * FROM maptiles;" );
  cur->prepare(); // run query
  while( cur->step() ){ // loop over results
  int selectedtile = cur->get_int(0);
  tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);}

  mvwprintw(win,1,16,"current tile"); mvwprintw(win, 3, 15, "O <--"); mvwprintw(win, 3, 25, "--> P");
  mvwprintw(win,3,22, tiles[0].character.c_str());
  wrefresh(win);
}

void refreshOptions(WINDOW* win, int tilepos){
  if(tiles[tilepos].colour > 0){wattron(win,COLOR_PAIR(tiles[tilepos].colour));}
  mvwprintw(win,3,22, tiles[tilepos].character.c_str());
  wattroff(win,COLOR_PAIR(tiles[tilepos].colour));
  wrefresh(win);
}

int input(WINDOW* win, int map[34][105], WINDOW* info){
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
  int map[34][105] = {0};
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, 0);
  init_pair(2, COLOR_RED, 0);
  init_pair(3, COLOR_GREEN, 0);
  init_pair(4, COLOR_YELLOW, 0);
  init_pair(5, COLOR_BLUE, 0);
  init_pair(6, COLOR_MAGENTA, 0);
  init_pair(7, COLOR_WHITE, 0);
  //keypad(stdscr, TRUE);
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
