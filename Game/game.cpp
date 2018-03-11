//Charlie Barry
//g++ -std=c++14 game.cpp window.cpp map.cpp -o game -lncursesw -lsqlite3
#include <locale>
#include <ncurses.h>

#include "libsqlite.hpp"

#include "window.h"
#include "map.h"

using namespace std;

class MapCreator{
private:
  MapTile* maptiles;
  WINDOW* game; WINDOW* stat; WINDOW* term;
  int map[35][105];
  void printOptions(){
    werase(stat); box(stat,0,0);
    WINDOW* currenttile = derwin(stat, 3,3, 2, 21);
    box(currenttile,0,0);
    wrefresh(currenttile);

    mvwprintw(stat,1,16,"current tile"); mvwprintw(stat, 3, 15, "O <--"); mvwprintw(stat, 3, 25, "--> P"); mvwprintw(stat, 8, 18, "q : quit"); mvwprintw(stat, 10, 18, "u : upload"); mvwprintw(stat, 12, 18, "l : load");
    mvwprintw(stat,3,22, maptiles->tiles[0].character.c_str());
    wrefresh(stat);
  }
  void refreshOptions(int tilepos){
    if(maptiles->tiles[tilepos].colour > 0){wattron(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));}
    mvwprintw(stat,3,22, maptiles->tiles[tilepos].character.c_str());
    wattroff(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));
    wrefresh(stat);
  }

  int input(){
    int coords[] = {1,1}; int tilepos = 0;
    while(true){
      switch(toupper(wgetch(stat))){
        case 'W':
          if(coords[0]-1 != 0){coords[0] -= 1;}
          break;

        case 'A':
          if(coords[1]-1 != 0){coords[1] -= 1;}
          break;

        case 'S':
          if(coords[0]+1 != 35){coords[0] += 1;}
          break;

        case 'D':
          if(coords[1]+1 != 106){coords[1] += 1;}
          break;

        case ' ':
          if(maptiles->tiles[tilepos].colour > 0){wattron(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));}
          wprintw(stat,maptiles->tiles[tilepos].character.c_str());
          map[coords[0]][coords[1]] = tilepos;
          wattroff(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));
          break;

        case 'O':
          if(tilepos-1 >= 0){tilepos -= 1;}
          break;

        case 'P':
          if(tilepos+1 < maptiles->tiles.size()){tilepos += 1;}
          break;

        case 'U':
          //uploadMap(map, info);
          break;

        case 'L':
          //loadMap(map, win);
          break;

        case 'Q':
          return 1;
          break;
      }
      wmove(stat, coords[0], coords[1]);
      refreshOptions(tilepos);
      wrefresh(stat);
    }
  }
public:
  MapCreator(WINDOW* _game, WINDOW* _stat, WINDOW* _term, MapTile* _maptiles){
    game = _game; stat = _stat; term = _term; maptiles = _maptiles;
    printOptions();
    while(true){
      if(input()){break;}
    }
  }
};

class Game{
private:
  Window* game; Window* stat; Window* term;
  MapTile* maptiles;

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

  void printDungeonName(string dungeonname, int windowWidth){
    werase(stat->getData());
    mvwprintw(stat->getData(), 1, centreTextCursorPos(dungeonname, windowWidth), dungeonname.c_str());
    wmove(stat->getData(), 2, centreTextCursorPos(dungeonname, windowWidth)- 1);
    for(int i = 0; i < (dungeonname.size() + 2); ++i){
      wprintw(stat->getData(), "¯");
    }
      box(stat->getData(), 0, 0);
    wrefresh(stat->getData());
  }

  int MainMenu(string dungeonname, int windowWidth){
    int selected = 0; int suboption = 0;
    vector<vector<string>> MenuOptions = {{"Play Game","Extra", "Options", "Exit"},{"MapCreator","Back"},{"----","Back"}};
    while(true){
      printDungeonName(dungeonname, windowWidth);

      for(int i = 0; i < MenuOptions[suboption].size(); ++i){
        if(i == selected){wattron(stat->getData(),COLOR_PAIR(2));}
        mvwprintw(stat->getData(), i+5, centreTextCursorPos(MenuOptions[suboption][i], windowWidth), MenuOptions[suboption][i].c_str());
        wattroff(stat->getData(),COLOR_PAIR(2));
      }

      wrefresh(stat->getData());
      refresh();
      switch(toupper(wgetch(stat->getData()))){
        case 'W':
          if(selected != 0){selected -= 1;}
          break;
        case 'S':
          if(selected != (MenuOptions[suboption].size())-1){selected += 1;}
          break;
        case ' ':
          switch(selected){
            case 0:
              {switch(suboption){
                case 0: return 0; break;
                case 1: {MapCreator create(game->getData(), stat->getData(), term->getData(), maptiles);} break;
                case 2: break;
              }}
              break;
            case 1:
              {switch(suboption){
                case 0: dungeonname = "Extras"; suboption += 1; selected = 0; break;
                case 1: dungeonname = "Main Menu"; suboption -= 1; selected = 0; return 2; break;
                case 2: dungeonname = "Main Menu"; suboption -= 2; selected = 0; return 2; break;
              }}
              break;
            case 2:
              {switch(suboption){
                case 0: dungeonname = "Options"; suboption += 2; selected = 0; break;
                case 1: return 2; break;
                case 2: return 2; break;
              }}
              break;
            case 3:
              return 1;
              break;
          }
          break;
      }
    }
  }

  int WorldMap(WINDOW* game, WINDOW* stat, WINDOW* term, PeacefulMap World, int windowWidth){
    int Dungeon[][2] = {{8,87},{31,85},{10,20},{30,22},{18,38}};

    printDungeonName(World.getName(), windowWidth);
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
    printDungeonName(dungeon.getName(), windowWidth);

    while(true){
      dungeon.movement();
      mvwprintw(term, 1, 1, "(%i,%i)", dungeon.playerpos[0], dungeon.playerpos[1]);
      wrefresh(term);
      werase(term);
      box(term, 0, 0);
    }
  }

  int gameSequence(){
    const int windowWidth = 45;

    Map main(1, game->getData(), maptiles);
    while(true){
    printDungeonName(main.getName(), windowWidth);
    int menuoption = MainMenu(main.getName(), windowWidth);
    if(menuoption == 1){return 1;}else if(menuoption == 0){break;}

    }

    //GET SAVE DATA FROM DATABASE HERE

    PeacefulMap World(2, game->getData(), maptiles);
    while(true){
      //PeacefulMap World(2, game.getData());
      int selecteddungeon = WorldMap(game->getData(), stat->getData(), term->getData(), World, windowWidth);
      if(selecteddungeon == 7){
        //SHOP
        Map shop(7, game->getData(), maptiles);

      }else{
        //DUNGEON
        Dungeon dungeon(selecteddungeon, game->getData(), maptiles);
        DungeonSequence(game->getData(), stat->getData(), term->getData(), dungeon, windowWidth);

      }
    }
  }
public:
  Game(Window* _game, Window* _stat, Window* _term, MapTile* _maptiles){
    game = _game; stat = _stat; term = _term; maptiles = _maptiles;
    gameSequence();
  }
};

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

    Window* main = new Window(38,159);
    Window* game = new Window(main->getData(),36,107,1,2);
    Window* stat = new Window(main->getData(),24,47,1,110);
    Window* term = new Window(main->getData(),12,47,25,110);

    MapTile* maptiles = new MapTile();
    Game startGame(game, stat, term, maptiles);
    //gameSequence(game, stat, term);

    endwin();
}
