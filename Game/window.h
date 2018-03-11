#ifndef WINDOW_H
#define WINDOW_H

class Window{
private:
  int width, height, x, y;
  WINDOW* win;
  WINDOW* frame;
public:
  void winrefresh();
  Window(WINDOW* _frame, int _height, int _width, int _y, int _x);
  Window(int height, int width);
  WINDOW* getData(){return win;}
  int getWidth(){return width;}
  int getHeight(){return height;}
  int getY(){return y;}
  int getX(){return x;}
  void resize(int y, int x);
};

#endif
