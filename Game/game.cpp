//Charlie Barry
#include <locale>
#include <ncurses.h>

#include "libsqlite.hpp"

#include "window.h"

using namespace std;

const int width = 105; const int height = 35;//height of displayed map is 34 to avoid weird database errors

struct tile {
  string character;
  int colour;
} ;

int getMapTileNo(){
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "SELECT COUNT(*) FROM maptiles;" );
  cur->prepare();
  while( cur->step() ){
  return cur->get_int(0);}
}

vector<tile> tiles(getMapTileNo());

void printMap(int map[height][width], WINDOW* win){
  for(int y = 1; y < height; ++y){
    for(int x = 1; x < width+1; ++x){
      if(tiles[map[y][x]].colour > 0){wattron(win,COLOR_PAIR(tiles[map[y][x]].colour));}
      mvwprintw(win, y, x, tiles[map[y][x]].character.c_str());
      wattroff(win,COLOR_PAIR(tiles[map[y][x]].colour));
    }
  }
}

const char* loadMap(int map[height][width], WINDOW* win, int dungeonID, int playerpos[1], int bosspos[1]){
  int yvalue, xvalue, tileno = 1;
  string dungeonname = " ";
  sqlite::sqlite db( "gamedb.db" );
  auto cur = db.get_statement();
  cur->set_sql( "select x, y, tileID, dungeon.name, dungeon.playery, dungeon.playerx, dungeon.bossy, dungeon.bossx from map, dungeon where dungeonID = ? and dungeonID = dungeon.ID order by y, x;" );
  cur->prepare();
  cur->bind( 1, dungeonID );
  while( cur->step() ){
    xvalue = cur->get_int(0);
    yvalue = cur->get_int(1);
    tileno = cur->get_int(2);
    dungeonname = cur->get_text(3);
    playerpos[0] = cur->get_int(4);
    playerpos[1] = cur->get_int(5);
    bosspos[0] = cur->get_int(6);
    bosspos[1] = cur->get_int(7);

    map[yvalue][xvalue] = tileno;
  }
  printMap(map, win);
  if(playerpos[0]){mvwprintw(win, playerpos[0], playerpos[1], "X");}
  wrefresh(win);
  return dungeonname.c_str();
}

void printDungeonName(WINDOW* stat, string dungeonname, int windowWidth){
  werase(stat);
  mvwprintw(stat, 1, (windowWidth - dungeonname.size())/2, dungeonname.c_str());
  wmove(stat, 2, ((windowWidth - dungeonname.size())/2) - 1);
  for(int i = 0; i < (dungeonname.size() + 2); ++i){
    wprintw(stat, "¯");
  }
    box(stat, 0, 0);
  wrefresh(stat);
}

template<size_t N>
void printMenuOptions(string (&MenuOptions)[N], int selected, int windowWidth, WINDOW* stat){
  for(int i = 0; i < (sizeof(MenuOptions)/sizeof(*MenuOptions)); ++i){
    if(i == selected){wattron(stat,COLOR_PAIR(2));}
    mvwprintw(stat, i+5, (windowWidth - MenuOptions[i].size())/2, MenuOptions[i].c_str());
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
        if(selected != (sizeof(MenuOptions)/sizeof(*MenuOptions))-1){selected += 1;}
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
                  if(selected != (sizeof(TempOptions)/sizeof(*TempOptions))-1){selected += 1;}
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
                  if(selected != (sizeof(TempOptions)/sizeof(*TempOptions))-1){selected += 1;}
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

void interact(int map[height][width], int playerpos[1], WINDOW* term){
//doors and chests here
if(map[playerpos[0]-1][playerpos[1]] == 8){
    map[playerpos[0]-1][playerpos[1]] = 0;
    int temppos[] = {playerpos[0]-1,playerpos[1]};
    interact(map, temppos, term);
  }
if(map[playerpos[0]][playerpos[1] - 1] == 8){
    map[playerpos[0]][playerpos[1] - 1] = 0;
    int temppos[] = {playerpos[0],playerpos[1]-1};
    interact(map, temppos, term);
  }
if(map[playerpos[0] + 1][playerpos[1]] == 8){
    map[playerpos[0] + 1][playerpos[1]] = 0;
    int temppos[] = {playerpos[0]+1,playerpos[1]};
    interact(map, temppos, term);
  }
if(map[playerpos[0]][playerpos[1] + 1] == 8){
    map[playerpos[0]][playerpos[1] + 1] = 0;
    int temppos[] = {playerpos[0],playerpos[1]+1};
    interact(map, temppos, term);
  }
}

void movement(int playerpos[1], int map[height][width], int bosspos[1], WINDOW* game, WINDOW* stat, WINDOW* term){
  switch(toupper(wgetch(game))){
    case 'W':
        if((map[playerpos[0]-1][playerpos[1]] == 0) && (playerpos[0] - 1 > 0)){
          playerpos[0] -= 1;
        }
        break;
    case 'A':
        if((map[playerpos[0]][playerpos[1] - 1] == 0) && (playerpos[1] - 1 > 0)){
          playerpos[1] -= 1;
        }
        break;
    case 'S':
        if((map[playerpos[0]+1][playerpos[1]] == 0) && (playerpos[0] + 1 <= height - 1)){
          playerpos[0] += 1;
        }
        break;
    case 'D':
         if((map[playerpos[0]][playerpos[1] + 1] == 0) && (playerpos[1] + 1 <= width)){
           playerpos[1] += 1;
         }
         break;

    case 'E':
        interact(map, playerpos, term);
        break;

    break;
  }
  printMap(map, game);
  mvwprintw(game, playerpos[0],playerpos[1], "X");
  wrefresh(game);
}

template<size_t N, size_t Nn>
bool ifIdenticalArray(int (&array1)[N], int (&array2)[Nn]){
  if(N != Nn){return false;}else{
    for(int i = 0; i < N; ++i){
      if(array1[i] != array2[i]){
        return false;
      }
    }
    return true;
  }
}

int WorldMap(int map[height][width], WINDOW* game, WINDOW* stat, WINDOW* term, string dungeonname, int windowWidth, int playerpos[1]){
  int temp[] = {0,0};
  int Dungeon[][2] = {{31,85},{8,87},{10,20},{30,22},{18,38}};
  printDungeonName(stat, dungeonname, windowWidth);
  while(true){

    movement(playerpos, map, temp, game, stat, term);
    int newplayerpos[] = {playerpos[0], playerpos[1]};//for some reason `ifIdenticalArray` dosent accept playerpos but does accept this?!
    for(int dungeonno = 0; dungeonno < 5; ++dungeonno){
      bool enteringdungeon = false;
      switch(dungeonno){
        case 1:
          for(int i = 0; i < 2; ++i){
            int tempdungeon[] = {Dungeon[dungeonno][0],Dungeon[dungeonno][1]+i};
            if(ifIdenticalArray(tempdungeon, newplayerpos)){
              enteringdungeon = true;
          }}
          break;
        case 2: case 3:
          for(int i = 0; i < 3; ++i){
            int tempdungeon[] = {Dungeon[dungeonno][0],Dungeon[dungeonno][1]+i};
            if(ifIdenticalArray(tempdungeon, newplayerpos)){
              enteringdungeon = true;
          }}
          break;
        default:
          enteringdungeon = ifIdenticalArray(Dungeon[dungeonno], newplayerpos);
        break;
      }
      if(enteringdungeon){
        return dungeonno + 3;
      }
    }
  }

}

int gameSequence(int map[height][width], WINDOW* game, WINDOW* stat, WINDOW* term){
  const int windowWidth = 45;
  int playerpos[] = {1, 1};
  int bosspos[1];
  while(true){
  int menuoption = MainMenu(stat, loadMap(map, game, 1, playerpos, bosspos), windowWidth);
  if(menuoption == 1){return 1;}else if(menuoption == 0){break;}

  }
  //GET SAVE DATA FROM DATABASE HERE

  while(true){
  /*returns dungeonID*/WorldMap(map, game, stat, term, loadMap(map, game, 2, playerpos, bosspos), windowWidth, playerpos);


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

    int map[height][width] = {0};

    sqlite::sqlite db( "gamedb.db" );
    auto cur = db.get_statement();
    cur->set_sql( "SELECT * FROM maptiles;" );
    cur->prepare();
    while( cur->step() ){
    int selectedtile = cur->get_int(0);
    tiles[selectedtile].character = cur->get_text(1).c_str(); tiles[selectedtile].colour = cur->get_int(2);}

    gameSequence(map, game.getData(), stat.getData(), term.getData());

    endwin();
}
