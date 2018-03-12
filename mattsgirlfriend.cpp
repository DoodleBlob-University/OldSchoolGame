#include <ncurses.h>

using namespace std;

class Girlfriend{
private:
  bool emotionaltrauma;
public:
  void showAffection(){
    printw("youre kinda nice i guess\n");
  }
  Girlfriend(){
    printw("hey matt\n");
  }
  void giveEmotionalTrauma(){
    printw("how dare you!\n");
    emotionaltrauma = true;
  }
};

int main(void){
  initscr();
  noecho();

  Girlfriend* beatrice = new Girlfriend;

  beatrice->showAffection();

  getch();

  beatrice->giveEmotionalTrauma();

  getch();

  endwin();
}
