//Charles Barry
//g++-5 -std=c++14 game.cpp maptile.cpp terminalfunc.cpp map.cpp window.cpp combatsystem.cpp login.cpp -o game -lncursesw -lsqlite3
#include <locale>
#include <cstring>

#include <ncurses.h>
#include "libsqlite.hpp"

#include "window.h"
#include "maptile.h"
#include "map.h"
#include "terminalfunc.h"
#include "combatsystem.h"
#include "login.h"
//#include "inv.h"

using namespace std;

class MapCreator{//Charles Barry
    private:
      MapTile* maptiles;
      WINDOW* game; WINDOW* stat; WINDOW* term;
      int coords[2]; int tilepos = 0;
      int map[35][106];
      TerminalFunctions* func;

      void uploadMap(int ID){//Charles Barry
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

      void printMap(){//Charles Barry
        for(int y = 1; y < 35; ++y){
          for(int x = 1; x < 106; ++x){
            if(maptiles->tiles[map[y][x]].colour > 0){wattron(game,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));}
            mvwprintw(game, y, x, maptiles->tiles[map[y][x]].character.c_str());
            wattroff(game,COLOR_PAIR(maptiles->tiles[map[y][x]].colour));
          }
        }
      }

      void loadMap(int ID){//Charles Barry
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

      void printOptions(){//Charles Barry
        werase(stat); box(stat,0,0);
        WINDOW* currenttile = derwin(stat, 3,3, 2, 21);
        box(currenttile,0,0);
        wrefresh(currenttile);

        mvwprintw(stat,1,16,"current tile"); mvwprintw(stat, 3, 15, "O <--"); mvwprintw(stat, 3, 25, "--> P"); mvwprintw(stat, 8, 18, "q : quit"); mvwprintw(stat, 10, 18, "u : upload"); mvwprintw(stat, 12, 18, "l : load");
        mvwprintw(stat, 16, 18, "h : help");
        mvwprintw(stat,3,22, maptiles->tiles[0].character.c_str());
        wrefresh(stat);
      }

      void refreshOptions(int tilepos){//Charles Barry
        if(maptiles->tiles[tilepos].colour > 0){wattron(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));}
        mvwprintw(stat,3,22, maptiles->tiles[tilepos].character.c_str());
        wattroff(stat,COLOR_PAIR(maptiles->tiles[tilepos].colour));
        wrefresh(stat);
      }

      int input(){//Charles Barry
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
              func->eraseTerminal();

              while(true){//get userinput less than 15 char
                func->printTerminalText("What would you like to call this map?\nMax 15 Characters!");
                mapname = func->getUserInput();

                if(mapname.length() <= 15){break;}
                func->eraseTerminal();
                func->printTerminalText("\n\nName must be less than 15 characters!");

              }

              if(mapname.length() == 0){
                func->eraseTerminal();
                func->printTerminalText("Upload cancelled");
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

              if(suggestedmapname == mapname){
                func->eraseTerminal();
                existing = true;
                func->printTerminalText("This would overwrite " + suggestedmapname + "!\nAre you sure? y/n");
                if(func->getUserYN() == false){
                  func->eraseTerminal();
                  func->printTerminalText("Upload cancelled");
                  break;
                }
              }else if(suggestedmapname.length()>0){
                func->eraseTerminal();
                func->printTerminalText("Did you mean: " + suggestedmapname + "?\ny/n");
                if(func->getUserYN() == true){
                  func->eraseTerminal();
                  func->printTerminalText("This will overwrite the current " + suggestedmapname + "\nAre you sure? y/n");
                  if(func->getUserYN() == true){
                    mapname = suggestedmapname;
                    existing = true;
                  }else{
                    func->eraseTerminal();
                    func->printTerminalText("Upload cancelled");
                    break;
                  }
                }
              }
              func->eraseTerminal();
              func->printTerminalText("Uploading " + mapname + "...\nPlease wait");
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
                    func->eraseTerminal();
                    func->printTerminalText(mapname + " uploaded");
                    refresh();
                    break;
                  }
                }
              }

              break;}

            case 'L':{//load
              string mapname; int mapnum;
              func->eraseTerminal();

              func->printTerminalText("Enter name of the map you would like to load:");
              mapname = func->getUserInput();
              func->eraseTerminal();

              if(!mapname.length()){
                func->printTerminalText("Map Loading cancelled");
              }else{
                func->printTerminalText(">"+mapname);
                {
                  sqlite::sqlite db( "gamedb.db" ); // open database
                  auto cur = db.get_statement();
                  cur->set_sql( "SELECT ID, name FROM dungeon WHERE name LIKE ? OR name = ?;" );
                  cur->prepare();
                  cur->bind(1, "%%"+mapname+"%%");
                  cur->bind(2, mapname);
                  while( cur->step() ){
                     mapnum = cur->get_int(0);
                     mapname = cur->get_text(1);
                  }
                }
                if(mapnum == 0){
                  func->printTerminalText("\nError 404: Map Not Found");
                }else{
                  func->printTerminalText("\nLoading "+mapname);
                  loadMap(mapnum);
                }
              }
              break;}

            case 'H':
              func->printTerminalText("Move the cursor using 'W', 'A', 'S' and 'D'\nDraw your selected tile by pressing SPACEBAR\nChoose your tile by pressing 'O' or 'P'");
              break;

            case 'Q':
              func->eraseTerminal();
              return 1;
              break;
          }
        return 0;
      }
    public:
      MapCreator(WINDOW* _game, WINDOW* _stat, WINDOW* _term, MapTile* _maptiles, TerminalFunctions* _func){//Charles Barry
        game = _game; stat = _stat; term = _term; maptiles = _maptiles; func = _func;
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

class Game{//Charles Barry
  private:
    Window* game; Window* stat; Window* term;
    MapTile* maptiles;
    TerminalFunctions* func;
    int playerID;

    void chests(){//William Smith
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

    void printDungeonName(string dungeonname){//Charles Barry
      werase(stat->getData());
      mvwprintw(stat->getData(), 1, func->centreTextCursorPos(dungeonname), dungeonname.c_str());
      wmove(stat->getData(), 2, func->centreTextCursorPos(dungeonname)- 1);
      for(int i = 0; i < (dungeonname.size() + 2); ++i){
        wprintw(stat->getData(), "¯");
      }
        box(stat->getData(), 0, 0);
      wrefresh(stat->getData());
    }

    int MainMenu(Map main){//Charles Barry
      string dungeonname = main.getName();
      int selected = 0; int suboption = 0;
      vector<vector<string>> MenuOptions = {{"Play Game","Extra", "Options", "Exit"},{"MapCreator","Back"},{"About","Back"}};
      while(true){
        printDungeonName(dungeonname);
        mvwprintw(stat->getData(), 20, func->centreTextCursorPos("h: Help"), "h: Help");


        for(int i = 0; i < MenuOptions[suboption].size(); ++i){
          if(i == selected){wattron(stat->getData(),COLOR_PAIR(2));}
          mvwprintw(stat->getData(), i+5, func->centreTextCursorPos(MenuOptions[suboption][i]), MenuOptions[suboption][i].c_str());
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
          case 'H':
              func->eraseTerminal();
              func->printTerminalText("Move the cursor using 'W', 'A', 'S' and 'D'\nPress SPACE or ENTER to Confirm");
              break;
          case ' ': case '\n':
            switch(selected){
              case 0:
                {switch(suboption){
                  case 0: return 0; break;
                  case 1:
                  func->eraseTerminal();
                  {MapCreator creator(game->getData(), stat->getData(), term->getData(), maptiles, func);} return 2; break;
                  case 2:
                  func->eraseTerminal();
                  func->printTerminalText("Game created by:\nCharlie Barry, Will Smith, Matt Fretwell\nGeorge Franklin, Kai Arnold, Shirin Shahali\n\nOur inspiration for the game was taken from\nZork (1980), The Hobbit (1982) and\nDungeons and Dragons.\n\n\nEnjoy 'Not a Dungeon Crawler'!!");
                  break;
                }}
                break;
              case 1:
                {switch(suboption){
                  case 0: dungeonname = "Extras"; suboption += 1; selected = 0; break;
                  case 1: dungeonname = main.getName(); suboption -= 1; selected = 0; return 2; break;
                  case 2:
                  func->eraseTerminal();
                  dungeonname = main.getName(); suboption -= 2; selected = 0; return 2; break;
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

    int WorldMap(WINDOW* game, WINDOW* stat, WINDOW* term, PeacefulMap World, int temppos[2]){//Charles Barry
      int Dungeon[][2] = {{8,87},{31,85},{10,20},{30,22},{18,38}};

      printDungeonName(World.getName());
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
                if(World.ifIdenticalArray(tempdungeon, World.playerpos)){
                  enteringdungeon = true;
              }}
              break;
            case 2: case 3:
              for(int i = 0; i < 3; ++i){
                int tempdungeon[] = {Dungeon[dungeonno][0],Dungeon[dungeonno][1]+i};
                if(World.ifIdenticalArray(tempdungeon, World.playerpos)){
                  enteringdungeon = true;
              }}
              break;
            default:
              enteringdungeon = World.ifIdenticalArray(Dungeon[dungeonno], World.playerpos);
            break;
          }
          if(enteringdungeon){
            temppos[0] = World.playerpos[0] + 1; temppos[1] = World.playerpos[1];
            return dungeonno + 3;
          }}

      }
    }

    int DungeonSequence(WINDOW* game, WINDOW* stat, WINDOW* term, Dungeon dungeon){//Charles Barry
      printDungeonName(dungeon.getName());

      while(true){
        AttackTest* go;
        int movementflag = dungeon.movement();
        switch(movementflag){
          case 1://Exit dungeon
            return 0;
            break;
          case 2:
            chests();//Open Chest
            break;
          case 3:
            //Combat with normal monsters
            int monster;
            {
              vector<int> monsterIDs;
              sqlite::sqlite db( "gamedb.db" ); // open database
              auto cur = db.get_statement();
              cur->set_sql( "SELECT ID FROM Monster WHERE Dungeon = ?;" );
              cur->prepare();
              cur->bind(1, dungeon.getID());
              while( cur->step() ){
                 monsterIDs.push_back(cur->get_int(0));
              }
              srand(time(0));
              int size = monsterIDs.size();
              if(size > 0){
                int random = rand() % size;
                monster = monsterIDs[random];
              }else{
                monster = 8;
              }
            }
            go = new AttackTest(func, playerID, monster);
            break;
          case 4:
            //Combat with bosses
            {

            }
            go = new AttackTest(func, playerID);
            break;
        }
      }
    }

    int gameSequence(){//Charles Barry
      LoginClass login(func);
      Map main(1, game->getData(), maptiles);

      while(true){//Main Menu loop
        printDungeonName(main.getName());
        int menuoption = MainMenu(main);
        if(menuoption == 1){
          return 1;
        }else if(menuoption == 0){
          playerID = login.getUser();
          if(playerID > 0){break;}}
        main.printMap();
      }

      int temppos[] = {0,0};
      PeacefulMap World(2, game->getData(), maptiles);
      while(true){//Gameplay loop
        int selecteddungeon = WorldMap(game->getData(), stat->getData(), term->getData(), World, temppos);
        if(selecteddungeon == 7){
          //SHOP
          Map shop(7, game->getData(), maptiles);

        }else{
          //DUNGEON
          Dungeon dungeon(selecteddungeon, game->getData(), maptiles);
          DungeonSequence(game->getData(), stat->getData(), term->getData(), dungeon);

        }
      }
    }
  public:
    Game(Window* _game, Window* _stat, Window* _term, MapTile* _maptiles, TerminalFunctions* _func){//Charles Barry
      game = _game; stat = _stat; term = _term; maptiles = _maptiles; func = _func;
      gameSequence();
    }
  };

  int main(){//Charles Barry
      setlocale(LC_ALL, "");//setting locale in order to allow unicode and extended ascii characters
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
      //AttackTest ree(func);

      Game startGame(game, stat, term, maptiles, func);//start game

      endwin();
}
