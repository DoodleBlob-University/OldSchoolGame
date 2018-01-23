//Charlie Barry
#include <iostream>
#include <conio.h>

using namespace std;

const int width = 20;
const int height = 12;

int playerpos[] = {10,10};

int main(){
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
    }
    return 0;
  }

void movement(int map[][width]){
  char keypress;
  keypress = toupper(getch());
  try{
    switch(keypress){
      case 'W':
          if(map[playerpos[0]-1][playerpos[1]] == 3){
            playerpos[0] -= 1;
          }
          break;
        case 'A':
          if(map[playerpos[0]][playerpos[1]-1] == 3){
            playerpos[1] -= 1;
          }
          break;
        case 'S':
          if(map[playerpos[0]+1][playerpos[1]] == 3){
            playerpos[0] += 1;
          }
          break;
        case 'D':
          if(map[playerpos[0]][playerpos[1]+1] == 3){
            playerpos[1] += 1;
          }
          break;
        default: cout << "";
          break;
        }
        if(map[playerpos[0]][playerpos[1]] == 2){
          cout << endl << "You opened a door" << endl;
        }
    }catch(...){}
  }


void printMap(int map[][width]){

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
          char terrain;
          switch(map[row][column]){
            case 0:
              terrain = '#';
              break;
            case 1:
              terrain = '|';
              break;
            case 2:
              terrain = '%';
              break;
            case 3:
              terrain = ' ';
              break;
          }
          if(playerpos[0] == row && playerpos[1] == column){
            terrain = 'X';
          }
          cout << terrain;
        }
        cout << endl;
    }
}
