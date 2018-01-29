#include <ncurses.h>
#include <locale>

using namespace std;

int main(void){
  setlocale(LC_ALL, "");
  initscr();
  printw("█");
  getch();
  endwin();
}
