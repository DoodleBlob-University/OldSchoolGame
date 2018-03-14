//Charlie Barry
//g++ -std=c++14 game.cpp window.cpp map.cpp -o game -lncursesw -lsqlite3
#include <locale>
#include <ncurses.h>
#include <signal.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

#include "libsqlite.hpp"

#include "window.h"
#include "map.h"
#include "combatsystem.h"

using namespace std;

class MapCreator{
private:
  MapTile* maptiles;
  WINDOW* game; WINDOW* stat; WINDOW* term;
  int coords[2]; int tilepos = 0;
  int map[35][106];

  void uploadMap(int ID){
      sqlite::sqlite db( "gamedb.db" ); // open database
      for(int x = 1; x < 106; ++x){
        for(int y = 1; y < 35; ++y){
          auto cur = db.get_statement(); // create query
          cur->set_sql( "INSERT INTO map(dungeonID, y, x, tileID) VALUES (?,?,?,?);" );
          cur->prepare();
          cur->bind( 1, ID );
          cur->bind( 2, y );                // set placeholders
          cur->bind( 3, x );
          cur->bind( 4, map[y][x] );
          cur->step();

      }
    }
  }

  void printTerminalText(string text){
    int y = 1;
    wmove(term, y, 1);
    for(int i = 0; i < text.length(); ++i){
      char cha = text[i];
      if(cha == '\n'){y += 1; wmove(term, y, 1);}else{
        wprintw(term, "%c", cha);
      }
    }
    wrefresh(term);
  }

string getUserInput(){
  wmove(term, 10, 1);
  wprintw(term, ">");
  string userinput;
  for(int i = 1; i < 45; ++i){
    int input = wgetch(term);
    switch(input){
      case 127:
        if(userinput.length() > 0){userinput = userinput.substr(0,userinput.length()-1); mvwprintw(term, 10, i, " "); i -= 1; wmove(term, 10, i+1);}
        i -= 1;
        break;
      case '\n':
        return userinput;
        break;
      default:
        userinput = userinput.append(1u, input);
        wprintw(term, "%c", input);
        break;
    }
  }
}

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
    mvwprintw(stat, 16, 18, "h : help");
    mvwprintw(stat,3,22, maptiles->tiles[0].character.c_str());
    wrefresh(stat);
  }

  void refreshOptions(int tilepos){
    if(maptiles->tiles[tilepos].colour > 0){wattron(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));}
    mvwprintw(stat,3,22, maptiles->tiles[tilepos].character.c_str());
    wattroff(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));
    wrefresh(stat);
  }
  void eraseTerminal(){
    werase(term);
    box(term, 0, 0);
    wrefresh(term);
  }

  bool getUserYN(){
    while(true){
      string input = getUserInput();
      if(input == "y" || input == "yes" || input == "Y" || input == "YES"){
        return true;
      }else if(input == "n" || input == "no" || input == "N" || input == "NO"){
        return false;
      }else{
        printTerminalText("\n\nSorry, I didn't understand that");
      }
    }
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

        case 'U':{//upload
          string mapname; string suggestedmapname; int mapnum; bool existing = false;
          existing = false;
          eraseTerminal();

          while(true){//get userinput less than 15 char
            printTerminalText("What would you like to call this map?\nMax 15 Characters!");
            mapname = getUserInput();

            if(mapname.length() <= 15){break;}
            eraseTerminal();
            printTerminalText("\n\nName must be less than 15 characters!");

          }

          if(mapname.length() == 0){
            eraseTerminal();
            printTerminalText("Upload cancelled");
            break;
          }

          {
            sqlite::sqlite db( "gamedb.db" ); // open database
            auto cur = db.get_statement();
            cur->set_sql( "SELECT ID, name FROM dungeon WHERE name LIKE ? OR name = ?;" );
            cur->prepare();
            cur->bind(1, "%%"+mapname+"%%");
            cur->bind(2, mapname);
            while( cur->step() ){
               mapnum = cur->get_int(0);
               suggestedmapname = cur->get_text(1);
            }
          }
          //eraseTerminal();
          //printTerminalText(suggestedmapname + "\n" + mapname);
          //break;
          if(suggestedmapname == mapname){
            eraseTerminal();
            existing = true;
            printTerminalText("This would overwrite " + suggestedmapname + "!\nAre you sure? y/n");
            if(getUserYN() == false){
              eraseTerminal();
              printTerminalText("Upload cancelled");
              break;
            }
          }else if(suggestedmapname.length()>0){
            eraseTerminal();
            printTerminalText("Did you mean: " + suggestedmapname + "?\ny/n");
            if(getUserYN() == true){
              eraseTerminal();
              printTerminalText("This will overwrite the current " + suggestedmapname + "\nAre you sure? y/n");
              if(getUserYN() == true){
                mapname = suggestedmapname;
                existing = true;
              }else{
                eraseTerminal();
                printTerminalText("Upload cancelled");
                break;
              }
            }
          }
          eraseTerminal();
          printTerminalText("Uploading " + mapname + "...\nPlease wait");
          if(existing == true){
            {//delete previous map
              {//get dungeon ID
                sqlite::sqlite db( "gamedb.db" );
                auto cur = db.get_statement();
                cur->set_sql( "SELECT ID FROM dungeon WHERE name = ?;" );
                cur->prepare();
                cur->bind(1, mapname);
                while( cur->step() ){
                   mapnum = cur->get_int(0);
                }
              }
              sqlite::sqlite db( "gamedb.db" );
              for(int x = 1; x < 106; ++x){
                for(int y = 1; y < 35; ++y){
                  auto cur = db.get_statement();
                  cur->set_sql( "DELETE FROM map WHERE dungeonID = ?" );
                  cur->prepare();
                  cur->bind( 1, mapnum );
                  cur->step();
                }
              }
            }
          }else{
            {//create a new dungeon
              sqlite::sqlite db( "gamedb.db" );
                  auto cur = db.get_statement();
                  cur->set_sql( "INSERT INTO dungeon(name) VALUES (?);" );
                  cur->prepare();
                  cur->bind( 1, mapname );
                  cur->step();
            }
            {//get dungeon ID
              sqlite::sqlite db( "gamedb.db" );
              auto cur = db.get_statement();
              cur->set_sql( "SELECT ID FROM dungeon WHERE name = ?;" );
              cur->prepare();
              cur->bind(1, mapname);
              while( cur->step() ){
                 mapnum = cur->get_int(0);
              }
            }
          }

          while(true){
            uploadMap(mapnum);
            {//get dungeon ID
              int tileno;
              sqlite::sqlite db( "gamedb.db" );
              auto cur = db.get_statement();
              cur->set_sql( "SELECT COUNT(*) FROM map WHERE DungeonID = ?;" );
              cur->prepare();
              cur->bind(1, mapnum);
              while( cur->step() ){
                 tileno = cur->get_int(0);
              }
              if(tileno == 3570){
                eraseTerminal();
                printTerminalText(mapname + " uploaded");
                refresh();
                break;
              }
            }
          }

          break;}

        case 'L':{//load
          string mapname; int mapnum;
          eraseTerminal();

          printTerminalText("Enter name of the map you would like to load:");
          mapname = getUserInput();
          eraseTerminal();

          if(!mapname.length()){
            printTerminalText("Map Loading cancelled");
          }else{
            printTerminalText(">"+mapname);
            {
              sqlite::sqlite db( "gamedb.db" ); // open database
              auto cur = db.get_statement();
              cur->set_sql( "SELECT ID, name FROM dungeon WHERE name LIKE ?;" );
              cur->prepare();
              cur->bind(1, "%%"+mapname+"%%");
              while( cur->step() ){
                 mapnum = cur->get_int(0);
                 mapname = cur->get_text(1);
              }
            }
            if(mapnum == 0){
              printTerminalText("\nError 404: Map Not Found");
            }else{
              printTerminalText("\nLoading "+mapname);
              loadMap(mapnum);
            }
          }
          break;}

        case 'H':
          printTerminalText("Move the cursor using 'W', 'A', 'S' and 'D'\nDraw your selected tile by pressing SPACEBAR\nChoose your tile by pressing 'O' or 'P'");
          break;

        case 'Q':
          eraseTerminal();
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

    for(int y = 1; y < 35; ++y){
      for(int x = 1; x < 106; ++x){
        map[y][x] = 0;
      }
    }

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

  void chests(){
    int getRanNum;
    int textRan;
    srand(time(0));
    string textArray[] = {"The chest swings open!", "The chest creaks open!", "The chest slowly creaks open!", "The chest thuds open!"};
    textRan = rand() % 4;
    mvwprintw(term->getData(), 2, 1, "%s", textArray[textRan].c_str());
    wrefresh(term->getData());
    getRanNum = rand() % 20 + 1;
    if(getRanNum < 15){
    int getRanGold;
    getRanGold = rand() % 30 + 5;
    mvwprintw(term->getData(), 3, 1, "You have received %i Gold!", getRanGold);
    wrefresh(term->getData());
    }else if(getRanNum == 20){
    mvwprintw(term->getData(), 3, 1, "You have received an item and gold!");
    wrefresh(term->getData());
    }else{
    mvwprintw(term->getData(), 3, 1, "You have received an Item");
    wrefresh(term->getData());
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
      int movementflag = dungeon.movement();
      if(movementflag==1){return 0;}else if(movementflag == 2){chests();}
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
    Window* game = new Window(main->getData(),36,107,1,2);//game subwindow
    Window* stat = new Window(main->getData(),24,47,1,110);//statistics subwindow
    Window* term = new Window(main->getData(),12,47,25,110);//user terminal subwindow

    MapTile* maptiles = new MapTile();//load all maptiles from database and store in class

    TerminalFunctions* func = new TerminalFunctions(stat->getData(),term->getData(),45);
    AttackTest ree(func);
    getch();

    Game startGame(game, stat, term, maptiles);//start game

    endwin();
}
