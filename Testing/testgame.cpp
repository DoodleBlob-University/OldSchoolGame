#include <locale>
#include <ncurses.h>
//#include <chrono>
//#include <thread>
#include <string.h>
#include <signal.h>
//#include <sys/ioctl.h>

using namespace std;

class Window{
private:
  int _width, _height, _x, _y;
  WINDOW* win;
  WINDOW* _frame;
public:
  Window(WINDOW* frame, int height, int width, int y, int x){
    _frame = frame; _width = width; _height = height; _x = x; _y = y;
    winrefresh();
  }
  Window(int height, int width){
    _frame = NULL; _width = width; _height = height; _x = 0; _y = 0;
    winrefresh();
  }
  void winrefresh(){
    refresh();
    if(_frame){
      win = derwin(_frame, _height,_width,_y,_x);
      box(win,0,0);
      wrefresh(_frame);
    }else{
      win = newwin(_height, _width, 0,0);
      box(win,0,0);
    }
    wrefresh(win);
  }
  WINDOW* getData(){
    return win;
  }
  void changeDimensions(int nheight, int nwidth, int posy, int posx){
    _y = posy; _x = posx; _height = nheight; _width = nwidth;
    winrefresh();
  }
};

void resizeHandler(Window main, Window game, Window stat, Window term){
    endwin();
    refresh();//re-initialise ncurses with new terminal dimensions
    if(LINES > MAX_HEIGHT){LINES = MAX_HEIGHT;}
    if(COLS > MAX_WIDTH){COLS = MAX_WIDTH;}
    //mainwin = newwin(LINES-2,COLS-1,0,0);
    //box(mainwin,0,0);
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d          %d", COLS, LINES, sig);
    //wrefresh(mainwin);
    clear();
    main.changeDimensions(LINES,COLS,0,0);
    main.winrefresh();
    mvwprintw(main.getData(), 1, 2, "Please enlarge the Terminal");
    game.winrefresh();
    stat.winrefresh();
    term.winrefresh();
    //mvwprintw(mainwin, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
}

void printMap(){
  /*
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
  wrefresh(gamewin); */
}

void gamesequence(WINDOW* gamewin, WINDOW* statwin, WINDOW* termwin){
  int playerpos[] = {10,10};
  getch();
}

int main(){
    int const MAX_HEIGHT = 38;
    int const MAX_WIDTH = 159;
    setlocale(LC_ALL, "");
    initscr();
    noecho();

    Window main(MAX_HEIGHT,MAX_WIDTH);
    Window game(main.getData(),MAX_HEIGHT-2,107,1,2);
    Window stat(main.getData(),MAX_HEIGHT-14,47,1,110);
    Window term(main.getData(),12,47,MAX_HEIGHT-13,110);

    //resizeHandler(main, game, stat, term);//resize to terminals current size

    gamesequence(game.getData(),stat.getData(),term.getData());

    endwin();

}
