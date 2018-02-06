#include <locale>
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std;

int MAX_HEIGHT = 40;
int MAX_WIDTH = 160;

void threadtest(){
  for(int i = 0; i < 10000000; ++i){
  printw("REE");
  this_thread::sleep_for(chrono::milliseconds(500));
  refresh();
  }
}
/*
class Boxes{

private:
  int pX, pY, pHeight, pWidth;

public:
  Boxes(){

  }

};
*/

void terminalResize(WINDOW* game){
  while(true){
  int x, y;
  int oldx, oldy = 0;
  getmaxyx(stdscr, y, x);
  if(oldx != x || oldy != y){
  if(y > MAX_HEIGHT && x > MAX_WIDTH){
    y = MAX_HEIGHT; x = MAX_WIDTH;
  }
  wresize(game,y-1,x-2);
  clear();
  box(game,0,0);
  wrefresh(game);
  refresh();
  oldx = x; oldy = y;
}}
}


int main(){
  setlocale(LC_ALL, "");

  initscr();
  noecho();
  cbreak();

  WINDOW * game = newwin(MAX_HEIGHT,MAX_WIDTH,0,0);
  refresh();
  box(game,0,0);
  wrefresh(game);




  thread t(&terminalResize, game);
  t.detach();

  while(true){

  }

  endwin();
}

/*
WINDOW * game = newwin(MAX_HEIGHT,MAX_WIDTH,0,0);
refresh();
void terminalResize(WINDOW* game);
//terminalResize(game);
box(game,0,0);
wrefresh(game);


//int x, y;
//getmaxyx(stdscr, y, x);
//wresize(main,y-1,x-2);
//refresh();
*/
