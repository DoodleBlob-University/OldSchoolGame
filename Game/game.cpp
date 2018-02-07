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
WINDOW *statwin;
WINDOW *termwin;

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
    gamewin = derwin(mainwin, MAX_HEIGHT - 4,107,1,2);
    statwin = derwin(mainwin, MAX_HEIGHT - 16,47,1,110);
    termwin = derwin(mainwin, 12,47,MAX_HEIGHT - 15,110);
    box(mainwin,0,0);
    mvwprintw(mainwin, 1, 2, "Please enlarge the Terminal");
    box(gamewin,0,0);
    box(statwin,0,0);
    box(termwin,0,0);
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
    wrefresh(mainwin);
    wrefresh(gamewin);
}

void printMap(){
  wmove(gamewin,1,1);
  for (int row = 0; row < 12; ++row){
      for (int column = 0; column < 20; ++column){
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
        wprintw(gamewin,terrain.c_str());
      }
      wmove(gamewin,row+2,1);
  }
  wrefresh(gamewin);
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
    //resize_term(MAX_WIDTH,MAX_HEIGHT);

    struct sigaction resizeSignal;
    sigemptyset(&resizeSignal.sa_mask);
    resizeSignal.sa_flags = SA_RESTART;//restart functions if interupted by handler
    resizeSignal.sa_handler = resizeHandler;//cannot give arguments to a function when called by handler
    sigaction(SIGWINCH, &resizeSignal, NULL);//signal occurs upon terminal resizing

    resizeHandler(28);//resize to terminals current size

    game();

    endwin();
}
