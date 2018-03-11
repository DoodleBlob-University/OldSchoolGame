#include <ncurses.h>
#include "window.h"

Window::Window(WINDOW* _frame, int _height, int _width, int _y, int _x){
  frame = _frame; width = _width; height = _height; x = _x; y = _y;
  winrefresh();
}
Window::Window(int _height, int _width){
  frame = NULL; width = _width; height = _height; x = 0; y = 0;
  winrefresh();
}
void Window::winrefresh(){
  refresh();
  if(frame){
    win = derwin(frame, height,width,y,x);
    box(win,0,0);
    wrefresh(frame);
  }else{
    win = newwin(height, width, 0,0);
    box(win,0,0);
  }
  wrefresh(win);
}
void Window::resize(int y, int x){
  wresize(win, y, x);
}
