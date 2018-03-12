//Charlie Barry
//g++ -std=c++14 game.cpp window.cpp map.cpp -o game -lncursesw -lsqlite3
#include <locale>
#include <ncurses.h>
#include <signal.h>
#include <cstring>

#include "libsqlite.hpp"

#include "window.h"
#include "map.h"

using namespace std;

class MapCreator{
private:
  MapTile* maptiles;
  WINDOW* game; WINDOW* stat; WINDOW* term;
  int coords[2]; int tilepos = 0;
  int map[35][106];
  /*
  void uploadMap(int map[35][105], WINDOW* win){
    mvwprintw(win, 10, 3, "Please Wait!");

      sqlite::sqlite db( "gamedb.db" ); // open database
      for(int x = 1; x < 106; ++x){
        for(int y = 1; y < 35; ++y){
          auto cur = db.get_statement(); // create query
          cur->set_sql( "INSERT INTO map(dungeonID, y, x, tileID) VALUES (7,?,?,?);" );
          cur->prepare();
          cur->bind( 1, y );                // set placeholders
          cur->bind( 2, x );
          cur->bind( 3, map[y][x] );
          cur->step();

      }
    }
  }
  */
  void printMap(){
    for(int y = 1; y < 35; ++y){
      for(int x = 1; x < 106; ++x){
        if(maptiles->tiles[map[y][x]].colour > 0){wattron(game,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));}
        mvwprintw(game, y, x, maptiles->tiles[map[y][x]].character.c_str());
        wattroff(game,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));
      }
    }
  }

  void loadMap(int ID){
    int yvalue, xvalue, tileno = 1;
    sqlite::sqlite db( "gamedb.db" ); // open database
    auto cur = db.get_statement(); // create query
    cur->set_sql( "SELECT y, x, tileID FROM map WHERE dungeonID = ? ORDER BY y, x;" );
    cur->prepare(); // run query
    cur->bind( 1, ID );
    while( cur->step() ){ // loop over results
      yvalue = cur->get_int(0);
      xvalue = cur->get_int(1);
      tileno = cur->get_int(2);
      map[yvalue][xvalue] = tileno;
    }
    printMap();
  }

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
      switch(toupper(wgetch(game))){
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
          if(maptiles->tiles[tilepos].colour > 0){wattron(game,COLOR_PAIR(maptiles->tiles[tilepos].colour));}
          wprintw(game,maptiles->tiles[tilepos].character.c_str());
          map[coords[0]][coords[1]] = tilepos;
          wattroff(game,COLOR_PAIR(maptiles->tiles[tilepos].colour));
          break;

        case 'O':
          if(tilepos-1 >= 0){tilepos -= 1;}
          break;

        case 'P':
          if(tilepos+1 < maptiles->tiles.size()){tilepos += 1;}
          break;

        case 'U':
          //overwrite/create new map

          //uploadMap(map, info);
          break;

        case 'L':
          //select map to load

          loadMap(7);
          break;

        case 'Q':
          return 1;
          break;
      }
    return 0;
  }
public:
  MapCreator(WINDOW* _game, WINDOW* _stat, WINDOW* _term, MapTile* _maptiles){
    game = _game; stat = _stat; term = _term; maptiles = _maptiles;
    printOptions();
    curs_set(1);
    werase(game); box(game, 0, 0); coords[0] = 1; coords[1] = 1;
    while(true){
      wmove(game, coords[0], coords[1]);
      wrefresh(game);
      if(input()){break;}
      refreshOptions(tilepos);
      wrefresh(stat);
    }
    try{
      curs_set(0);
    }catch(...) {}
  }
};

class Game{
private:
  Window* game; Window* stat; Window* term;
  MapTile* maptiles;

  int centreTextCursorPos(string text, int width){
    return (width - text.size())/2;
  }

  template<typename T, unsigned int N, unsigned int Nn>
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

  int MainMenu(Map main, int windowWidth){
    string dungeonname = main.getName();
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
                case 1: {MapCreator creator(game->getData(), stat->getData(), term->getData(), maptiles);} return 2; break;
                case 2: break;
              }}
              break;
            case 1:
              {switch(suboption){
                case 0: dungeonname = "Extras"; suboption += 1; selected = 0; break;
                case 1: dungeonname = main.getName(); suboption -= 1; selected = 0; return 2; break;
                case 2: dungeonname = main.getName(); suboption -= 2; selected = 0; return 2; break;
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

  int WorldMap(WINDOW* game, WINDOW* stat, WINDOW* term, PeacefulMap World, int windowWidth, int temppos[2]){
    int Dungeon[][2] = {{8,87},{31,85},{10,20},{30,22},{18,38}};

    printDungeonName(World.getName(), windowWidth);
    World.printMap();
    if(temppos[0] != 0){World.playerpos[0] = temppos[0]; World.playerpos[1] = temppos[1];}
    mvwprintw(game, World.playerpos[0], World.playerpos[1], "X");
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
          temppos[0] = World.playerpos[0] + 1; temppos[1] = World.playerpos[1];
          return dungeonno + 3;
        }}

    }
  }

  int DungeonSequence(WINDOW* game, WINDOW* stat, WINDOW* term, Dungeon dungeon, int windowWidth){
    printDungeonName(dungeon.getName(), windowWidth);

    while(true){
      if(dungeon.movement()){return 0;}
      mvwprintw(term, 1, 1, "(%i,%i)", dungeon.playerpos[0], dungeon.playerpos[1]);
      wrefresh(term);
      werase(term);
      box(term, 0, 0);
    }
  }

  int gameSequence(){
    const int windowWidth = 45;

    while(true){
      Map main(1, game->getData(), maptiles);

      printDungeonName(main.getName(), windowWidth);
      int menuoption = MainMenu(main, windowWidth);
      if(menuoption == 1){return 1;}else if(menuoption == 0){break;}
    }

    //GET SAVE DATA FROM DATABASE HERE

    int temppos[2];
    PeacefulMap World(2, game->getData(), maptiles);
    while(true){
      //PeacefulMap World(2, game.getData());
      int selecteddungeon = WorldMap(game->getData(), stat->getData(), term->getData(), World, windowWidth,temppos);
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

/*
Window* mainwin; Window* gamewin; Window* statwin; Window* termwin;
void resize(int sig){
  wait();
  endwin();
  refresh();//re-initialise ncurses with new terminal dimensions
  if(LINES > mainwin->getHeight()){LINES = mainwin->getHeight();}
  if(COLS > mainwin->getWidth()){COLS = mainwin->getWidth();}
  clear();

  mainwin->resize(LINES, COLS);
  mainwin->winrefresh(); gamewin->winrefresh(); statwin->winrefresh(); termwin->winrefresh();
  refresh();
  try{
    curs_set(0);//some terminals dont support this feature, hence `try` and `catch`
  }catch(...) {}
  fflush(0);
}*/

int main(){
    setlocale(LC_ALL, "");//setting locale in order to allow unicode characters
    initscr();

    start_color();//initialise all colour pairs
    init_pair(1, COLOR_BLACK, 0);
    init_pair(2, COLOR_RED, 0);
    init_pair(3, COLOR_GREEN, 0);
    init_pair(4, COLOR_YELLOW, 0);
    init_pair(5, COLOR_BLUE, 0);
    init_pair(6, COLOR_MAGENTA, 0);

    noecho();
    keypad(stdscr, true);//dosent work for me? try in an actual bash terminal (not windows)?
    try{
      curs_set(0);//some terminals dont support this feature, hence `try` and `catch`
    }catch(...) {}

    Window* main = new Window(38,159);//create main window
    //mainwin = main;
    Window* game = new Window(main->getData(),36,107,1,2);//game subwindow
    //gamewin = game;
    Window* stat = new Window(main->getData(),24,47,1,110);//statistics subwindow
    //statwin = stat;
    Window* term = new Window(main->getData(),12,47,25,110);//user terminal subwindow
    //termwin = term;
    /*
    struct sigaction resizeSignal;
    sigemptyset(&resizeSignal.sa_mask);
    memset(&resizeSignal, 0, sizeof(resizeSignal));//reset all members of resizeSignal to 0
    resizeSignal.sa_flags = SA_RESTART;//restart functions if interupted by handler
    resizeSignal.sa_handler = resize;//cannot give arguments to a function when called by handler
    sigaction(SIGWINCH, &resizeSignal, NULL);//signal occurs upon terminal resizing*/

    MapTile* maptiles = new MapTile();//load all maptiles from database and store in class

    Game startGame(game, stat, term, maptiles);//start game

    endwin();
}
