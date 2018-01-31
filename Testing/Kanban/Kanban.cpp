//Charlie Barry
#include <ncurses.h>
#include <array>
//#include <sqlite3.h>
#include <string>

//#include "libsqlite.hpp"

using namespace std;

int main(){
  array<string,27> todoList, doingList, doneList;

  while(true){
    initscr();
    noecho();

    int height, width;
    height = width = 30;

    WINDOW * todo = newwin(30,30,2,5);
    WINDOW * doing = newwin(30,30,2,35);
    WINDOW * done = newwin(30,30,2,65);
    refresh();

    void createboxes(WINDOW*, WINDOW*, WINDOW*);
    void refreshwindows(WINDOW*, WINDOW*, WINDOW*);
    createboxes(todo, doing, done);
    refreshwindows(todo, doing, done);

    switch(getch()){
      case '1':
        int movetask(array<string,27>,array<string,27>,array<string,27>);
        movetask(todoList, doingList, doneList);
        break;
      case '2':
        int addtask(array<string,27>,array<string,27>,array<string,27>);
        addtask(todoList, doingList, doneList);
        break;
      case '3':
        int removetask(array<string,27>,array<string,27>,array<string,27>);
        removetask(todoList, doingList, doneList);
        break;
      case '9':
        endwin();
        return 1;
        break;
    }
    clear();
  }
}

void clearline(int num){
  move(num, 0);
  clrtoeol();
}

int movetask(array<string,27> todo, array<string,27> doing, array<string,27> done){
  clearline(33);
  mvprintw(33,14,"MOVE)       1: TODO         2: DOING       3: DONE           9: BACK");
  switch(getch()){
    case '1':
      //
      break;
    case '2':
      //
      break;
    case '3':
      //
      break;
    case '9':
      return 0;
      break;
  }
}

int addtask(array<string,27> todo, array<string,27> doing, array<string,27> done){
  clearline(33);
  mvprintw(33,14,"ADD)        1: TODO         2: DOING       3: DONE           9: BACK");
  switch(getch()){
    case '1':
      //
      break;
    case '2':
      //
      break;
    case '3':
      //
      break;
    case '9':
      return 0;
      break;
  }
}

int removetask(array<string,27> todo, array<string,27> doing, array<string,27> done){
  clearline(33);
  mvprintw(33,14,"REMOVE)     1: TODO         2: DOING       3: DONE           9: BACK");
  switch(getch()){
    case '1':
      //
      break;
    case '2':
      //
      break;
    case '3':
      //
      break;
    case '9':
      return 0;
      break;
  }
}

void refreshwindows(WINDOW* todo, WINDOW* doing, WINDOW* done){
  wnoutrefresh(todo);
  wnoutrefresh(doing);
  wnoutrefresh(done);
  doupdate();
}

void createboxes(WINDOW* todo, WINDOW* doing, WINDOW* done){
  start_color();

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);

  for(int i = 3; i < 31; i++){
    mvprintw(i,2,"%i",i-2);
  }

  wattron(todo,COLOR_PAIR(1));
  mvprintw(1,17,"To Do");
  box(todo,0,0);
  wattroff(todo,COLOR_PAIR(1));

  wattron(doing,COLOR_PAIR(3));
  mvprintw(1,47,"Doing");
  box(doing,0,0);
  wattroff(doing,COLOR_PAIR(3));

  wattron(done,COLOR_PAIR(2));
  mvprintw(1,77,"Done");
  box(done,0,0);
  wattroff(done,COLOR_PAIR(2));

  mvprintw(33,14,"OPTIONS)    1: MOVE TASK    2: ADD TASK    3: REMOVE TASK    9: EXIT");
  use_default_colors();
}
/*
void getTable(){
  sqlite3 *db;
  sqlite3_stmt *stmt;
  if (sqlite3_open("kanban.db", &db) == SQLITE_OK){

    sqlite3_prepare( db, "SELECT task from task;", 0, &stmt, NULL );
    while( sqlite3_column_text( stmt, 0 ) ){
      for( int i = 0; i < 4; i++ )
        printw((char *)sqlite3_column_text( stmt, i ));
        printw("\n");
        sqlite3_step( stmt );
    }

  }else{
    printw("Failed to open db");
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);

}
*/
