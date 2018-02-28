#include <ncurses.h>
#include "Window.h"

Window::Window(WINDOW* frame, int height, int width, int y, int x){
  _frame = frame; _width = width; _height = height; _x = x; _y = y;
  winrefresh();
}
Window::Window(int height, int width){
  _frame = NULL; _width = width; _height = height; _x = 0; _y = 0;
  winrefresh();
}
void Window::winrefresh(){
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
