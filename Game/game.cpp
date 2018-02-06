#include <locale>
#include <ncurses.h>
//#include <chrono>
//#include <thread>
#include <string.h>
#include <signal.h>
//#include <sys/ioctl.h>

using namespace std;

int const MAX_HEIGHT = 40;
int const MAX_WIDTH = 160;
WINDOW *mainwin;// = newwin(MAX_HEIGHT,MAX_WIDTH,0,0);
WINDOW *gamewin;

int map[][MAX_WIDTH - 2] =  {   {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0},
                                {0,0,0,0,0,1,1,1,1,2,2,1,1,1,1,0,0,0,0,0}};

int playerpos[] = {10,10};

int readkey(){//replacement for getch()
  while(true){
    int key = wgetch(mainwin);
    if(key != KEY_RESIZE){
      return key;
    }
  }
}

/*
void threadtest(){
  for(int i = 0; i < 10000000; ++i){
  printw("REE");
  this_thread::sleep_for(chrono::milliseconds(500));
  refresh();
  }
}*/

/*
class Boxes{

private:
  int pX, pY, pHeight, pWidth;

public:
  Boxes(){

  }

};
*/

void resizeHandler(int sig){
    endwin();
    refresh();//re-initialise ncurses with new terminal dimensions
    if(LINES > MAX_HEIGHT){LINES = MAX_HEIGHT;}
    if(COLS > MAX_WIDTH){COLS = MAX_WIDTH;}
    //mainwin = newwin(LINES-2,COLS-1,0,0);
    //box(mainwin,0,0);
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d          %d", COLS, LINES, sig);
    //wrefresh(mainwin);
    clear();
    mainwin = newwin(LINES-2,COLS-1,0,0);
    gamewin = derwin(mainwin, 20,20,10,10);
    box(mainwin,0,0);
    box(gamewin,0,0);
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
    wrefresh(mainwin);
    wrefresh(gamewin);
}

void printMap(){
  wmove(mainwin,1,1);
  for (int row = 0; row < 12; ++row){
      for (int column = 0; column < 20; ++column){
        //wprintw(mainwin,"X");
        string terrain;
        switch(map[row][column]){
          case 0:
            terrain = "░";
            break;
          case 1:
            terrain = "\u2588";
            break;
          case 2:
            terrain = "~";
            break;
          case 3:
            terrain = " ";
            break;
        }
        if(playerpos[0] == row && playerpos[1] == column){
          terrain = "X";
        }
        wprintw(mainwin,terrain.c_str());
      }
      wmove(mainwin,row+2,1);
  }
  wrefresh(mainwin);
}

int game(){
  while(true){
    printMap();
    readkey();
  }
}

int main(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    //resizeterm(MAX_WIDTH,MAX_HEIGHT);

    struct sigaction resizeSignal;
    sigemptyset(&resizeSignal.sa_mask);
    resizeSignal.sa_flags = SA_RESTART;//restart functions if interupted by handler
    resizeSignal.sa_handler = resizeHandler;//cannot give arguments to a function when called by handler
    sigaction(SIGWINCH, &resizeSignal, NULL);

    resizeHandler(28);//resize to terminals current size

    game();

    endwin();
}
