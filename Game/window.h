#ifndef WINDOW_H
#define WINDOW_H

class Window{
private:
  int _width, _height, _x, _y;
  WINDOW* win;
  WINDOW* _frame;
  void winrefresh();
public:
  Window(WINDOW* frame, int height, int width, int y, int x);
  Window(int height, int width);

  WINDOW* getData(){return win;}
};

#endif
