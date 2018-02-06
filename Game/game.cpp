#include <locale>
#include <ncurses.h>
//#include <chrono>
//#include <thread>
#include <string.h>
#include <signal.h>
//#include <sys/ioctl.h>

using namespace std;

int MAX_HEIGHT = 40;
int MAX_WIDTH = 160;
WINDOW *mainwin;// = newwin(MAX_HEIGHT,MAX_WIDTH,0,0);

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
void drawDisplay(){
  mainwin = newwin(LINES-2,COLS-1,0,0);
  box(mainwin,0,0);
  mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
  wrefresh(mainwin);
}

void resizeHandler(int sig){
    endwin();
    refresh();//re-initialise ncurses with new terminal dimensions
    if(LINES > MAX_HEIGHT){LINES = MAX_HEIGHT;}
    if(COLS > MAX_WIDTH){COLS = MAX_WIDTH;}
    //mainwin = newwin(LINES-2,COLS-1,0,0);
    clear();
    //box(mainwin,0,0);
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d          %d", COLS, LINES, sig);
    //wrefresh(mainwin);
    drawDisplay();
}

int main(){

    initscr();
    noecho();

    struct sigaction resizeSignal;
    sigemptyset(&resizeSignal.sa_mask);
    resizeSignal.sa_flags = SA_RESTART;//Restart functions if interupted by handler
    resizeSignal.sa_handler = resizeHandler;
    sigaction(SIGWINCH, &resizeSignal, NULL);

    resizeHandler(28);

    while(true) {
      int count;
      if(wgetch(mainwin)=='1'){endwin(); return 0;}
      mvwprintw(mainwin,5,5,"%d",count);
      wrefresh(mainwin);
      count += 1;
    }

    endwin();
    return 0;
}
