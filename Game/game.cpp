//Charlie Barry
//g++ -std=c++14 game.cpp window.cpp map.cpp -o game -lncursesw -lsqlite3
#include <locale>
#include <ncurses.h>

#include "libsqlite.hpp"

#include "window.h"
#include "map.h"

using namespace std;

template<typename T, size_t N>
int getArraySize(T (&array)[N]){
  return sizeof(array)/sizeof(*array);
}

int centreTextCursorPos(string text, int width){
  return (width - text.size())/2;
}

template<typename T, size_t N, size_t Nn>
bool ifIdenticalArray(T (&array1)[N], T (&array2)[Nn]){
  //I assume the data types for the array are identical - if this isnt the case an error will occur upon compiling
    if(N != Nn){return false;}else{
      for(int i = 0; i < N; ++i){
        if(array1[i] != array2[i]){
          return false;
        }
      }
      return true;
    }
}

void printDungeonName(WINDOW* stat, string dungeonname, int windowWidth){
  werase(stat);
  mvwprintw(stat, 1, centreTextCursorPos(dungeonname, windowWidth), dungeonname.c_str());
  wmove(stat, 2, centreTextCursorPos(dungeonname, windowWidth)- 1);
  for(int i = 0; i < (dungeonname.size() + 2); ++i){
    wprintw(stat, "¯");
  }
    box(stat, 0, 0);
  wrefresh(stat);
}

template<size_t N>
void printMenuOptions(string (&MenuOptions)[N], int selected, int windowWidth, WINDOW* stat){
  for(int i = 0; i < (getArraySize(MenuOptions)); ++i){
    if(i == selected){wattron(stat,COLOR_PAIR(2));}
    mvwprintw(stat, i+5, centreTextCursorPos(MenuOptions[i], windowWidth), MenuOptions[i].c_str());
    wattroff(stat,COLOR_PAIR(2));
  }
}

int MainMenu(WINDOW* stat, string dungeonname, int windowWidth){
  //can I do this function better?!
  printDungeonName(stat, dungeonname, windowWidth);
  string MenuOptions[] = {"Play Game", "Extra", "Options", "Exit"};
  int selected = 0;
  while(true){
    printMenuOptions(MenuOptions, selected, windowWidth, stat);

    switch(toupper(wgetch(stat))){
      case 'W':
        if(selected != 0){selected -= 1;}
        break;
      case 'S':
        if(selected != (getArraySize(MenuOptions))-1){selected += 1;}
        break;
      case ' ':
        switch(selected){
          case 0://play game
            return 0;
            break;
          case 1://extras
          {
            selected = 0;
            printDungeonName(stat, "Extras", windowWidth);
            string TempOptions[] = {"MapCreator", "Back"};
            while(true){
              printMenuOptions(TempOptions, selected, windowWidth, stat);
              switch(toupper(wgetch(stat))){
                case 'W':
                  if(selected != 0){selected -= 1;}
                  break;
                case 'S':
                  if(selected != (getArraySize(TempOptions))-1){selected += 1;}
                  break;
                case ' ':
                  switch(selected){
                    case 0:
                      break;
                    case 1:
                      return 2;
                      break;
                  }
                  break;
              }
            }
            break;
          }
          case 2://options
          {
            selected = 0;
            printDungeonName(stat, "Options", windowWidth);
            string TempOptions[] = {"---", "Back"};
            while(true){
              printMenuOptions(TempOptions, selected, windowWidth, stat);
              switch(toupper(wgetch(stat))){
                case 'W':
                  if(selected != 0){selected -= 1;}
                  break;
                case 'S':
                  if(selected != (getArraySize(TempOptions))-1){selected += 1;}
                  break;
                case ' ':
                  switch(selected){
                    case 0:
                      break;
                    case 1:
                      return 2;
                      break;
                  }
                  break;
              }
            }
            break;
          }
          case 3://exit
            return 1;
            break;
        }
        break;
    }
  }
}

int WorldMap(WINDOW* game, WINDOW* stat, WINDOW* term, PeacefulMap World, int windowWidth){
  int Dungeon[][2] = {{8,87},{31,85},{10,20},{30,22},{18,38}};

  printDungeonName(stat, World.getName(), windowWidth);
  while(true){
    World.movement();

    for(int dungeonno = 0; dungeonno < 5; ++dungeonno){
      bool enteringdungeon = false;
      switch(dungeonno){
        case 0:
          for(int i = 0; i < 2; ++i){
            int tempdungeon[] = {Dungeon[dungeonno][0],Dungeon[dungeonno][1]+i};
            if(ifIdenticalArray(tempdungeon, World.playerpos)){
              enteringdungeon = true;
          }}
          break;
        case 2: case 3:
          for(int i = 0; i < 3; ++i){
            int tempdungeon[] = {Dungeon[dungeonno][0],Dungeon[dungeonno][1]+i};
            if(ifIdenticalArray(tempdungeon, World.playerpos)){
              enteringdungeon = true;
          }}
          break;
        default:
          enteringdungeon = ifIdenticalArray(Dungeon[dungeonno], World.playerpos);
        break;
      }
      if(enteringdungeon){
        return dungeonno + 3;
      }}

  }
}

int DungeonSequence(WINDOW* game, WINDOW* stat, WINDOW* term, Dungeon dungeon, int windowWidth){
  printDungeonName(stat, dungeon.getName(), windowWidth);

  while(true){
    dungeon.movement();
    mvwprintw(term, 1, 1, "(%i,%i)", dungeon.playerpos[0], dungeon.playerpos[1]);
    wrefresh(term);
    werase(term);
    box(term, 0, 0);
  }
}

int gameSequence(Window game, Window stat, Window term){
  const int windowWidth = 45;
  MapTile *maptiles = new MapTile;

  while(true){

  Map main(1, game.getData(), maptiles);
  int menuoption = MainMenu(stat.getData(), main.getName(), windowWidth);
  if(menuoption == 1){return 1;}else if(menuoption == 0){break;}
  }

  //GET SAVE DATA FROM DATABASE HERE

  PeacefulMap World(2, game.getData(), maptiles);
  while(true){
    //PeacefulMap World(2, game.getData());
    int selecteddungeon = WorldMap(game.getData(), stat.getData(), term.getData(), World, windowWidth);
    if(selecteddungeon == 7){
      //SHOP
      Map shop(1, game.getData(), maptiles);

    }else{
      //DUNGEON
      Dungeon dungeon(selecteddungeon, game.getData(), maptiles);
      DungeonSequence(game.getData(), stat.getData(), term.getData(), dungeon, windowWidth);

    }
  }
}

int main(){
    setlocale(LC_ALL, "");
    initscr();

    start_color();
    init_pair(1, COLOR_BLACK, 0);
    init_pair(2, COLOR_RED, 0);
    init_pair(3, COLOR_GREEN, 0);
    init_pair(4, COLOR_YELLOW, 0);
    init_pair(5, COLOR_BLUE, 0);
    init_pair(6, COLOR_MAGENTA, 0);

    noecho();
    keypad(stdscr, true);//dosent work for me? try in an actual bash terminal (not windows)?
    try{
      curs_set(0);
    }catch(...) {}

    Window main(38,159);
    Window game(main.getData(),36,107,1,2);
    Window stat(main.getData(),24,47,1,110);
    Window term(main.getData(),12,47,25,110);

    gameSequence(game, stat, term);

    endwin();
}
