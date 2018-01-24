//Charlie Barry
#include <iostream>
#include <ncurses.h>
#include <locale.h>

using namespace std;

const int width = 20;
const int height = 12;

int playerpos[] = {10,10};

int main(void){
    cout << "\u2588";
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    void printMap(int map[][width]);
    void movement(int map[][width]);

    int map[][width] = {  {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
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

    while(true){
      printMap(map);
      movement(map);
      clear();
    }
  }

void movement(int map[][width]){
  char keypress;
  keypress = getch();
  try{
    switch(keypress){
      case 'w':
          if(map[playerpos[0]-1][playerpos[1]] == 3){
            playerpos[0] -= 1;
          }
          break;
        case 'a':
          if(map[playerpos[0]][playerpos[1]-1] == 3){
            playerpos[1] -= 1;
          }
          break;
        case 's':
          if(map[playerpos[0]+1][playerpos[1]] == 3){
            playerpos[0] += 1;
          }
          break;
        case 'd':
          if(map[playerpos[0]][playerpos[1]+1] == 3){
            playerpos[1] += 1;
          }
          break;
        default: cout << "";
          break;
        }

    }catch(...){}
  }


void printMap(int map[][width]){

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
          string terrain;
          switch(map[row][column]){
            case 0:
              terrain = "#";
              break;
            case 1:
              terrain = "|";
              break;
            case 2:
              terrain = "7";
              break;
            case 3:
              terrain = " ";
              break;
          }
          if(playerpos[0] == row && playerpos[1] == column){
            terrain = "X";
          }
          printw(terrain.c_str());
        }
        printw("\n");
    }
}
