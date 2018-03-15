//Shirin Shahali
#include <iostream>
#include <fstream>
#include <string>

#include <ncurses.h>
#include "terminalfunc.h"
#include "login.h"

#include "libsqlite.hpp"

    int LoginClass::userCheck(std::string username)//Shirin Shahali
    {
    sqlite::sqlite db("gamedb.db");
    auto query= db.get_statement();
    query->set_sql("SELECT COUNT(*) FROM player WHERE Name=?; ");
    query->prepare();
    query->bind(1,username);
    while(query->step())
    {
    return query->get_int(0);
    }
    }

    char LoginClass::creatCharacter(auto& username,auto& password)//Shirin Shahali
    {
    sqlite::sqlite db("gamedb.db");
    auto query= db.get_statement();
    //query->set_sql("INSERT INTO player(Name,Password) VALUES (?,'"+password+"'); ");
    query->set_sql("INSERT INTO player(Name,Password) VALUES (?,?);");
    query->prepare();
    query->bind(1,username);
    query->bind(2,password);
    query->step();
    }

    int LoginClass::showID()//Shirin Shahali
    {
          sqlite::sqlite db("gamedb.db");
    auto query= db.get_statement();
    query->set_sql("SELECT ID FROM player WHERE Name=?; ");
    query->prepare();
    query->bind(1,UserN);
    while(query->step())
    {
        int ans = query->get_int(0);
        return ans;
    }
    }


    int LoginClass::UserDecision()//Shirin Shahali
    {

    func->printTerminalText("1: Would you like to Register?");
    func->printTerminalText("\n2: Would you like to Login?");
    func->printTerminalText("\n\nEnter 1 or 2: ");

    std::string input = func->getUserInput();
      func->eraseTerminal();
    if(input == "1"){
      return 1;
    }else if(input == "2"){
      return 2;
    }else if(input.length() > 0){//allows the user to quit the login screen -Charlie
      func->printTerminalText("\n\n\n^^^^^^^^^^^^^");
      return 3;
    }else{
      return 0;
    }
    }



    void LoginClass::registerCharater()//Shirin Shahali
    {

    func->eraseTerminal();
    std::string Username_entered, Password_entered;
    func->printTerminalText("Enter Username: ");
    Username_entered = func->getUserInput();
    while(userCheck(Username_entered)==1)
    {
          func->eraseTerminal();
    func->printTerminalText("Sorry, you can't use that username");
    func->printTerminalText("\nIt has been taken by another user");
    func->printTerminalText("\n\n\nEnter a more unqiue username: ");
    Username_entered = func->getUserInput();
    userCheck(Username_entered);

    }
        func->eraseTerminal();
    func->printTerminalText("Enter Password: ");
    Password_entered = func->getUserInput(true);
    creatCharacter(Username_entered,Password_entered);

    }



    char LoginClass::loginCharater()//Shirin Shahali
    {
    std::string Password_entered;
    func->printTerminalText("Enter Username: ");
    UserN = func->getUserInput();
    func->eraseTerminal();
    func->printTerminalText("Enter Password: ");
    Password_entered = func->getUserInput(true);
    sqlite::sqlite db("gamedb.db");
    auto query= db.get_statement();
    //query->set_sql("SELECT COUNT(*) FROM User WHERE Username=? AND Password='"+Password_entered+"'; ");  <--- DON'T DO THIS!!! - Charlie
    query->set_sql("SELECT COUNT(*) FROM player WHERE Name=? AND Password=?;");
    query->prepare();
    query->bind(1,UserN);
    query->bind(2,Password_entered);
    query->step();
    return query->get_int(0);
    }


int LoginClass::getUser(){//Shirin Shahali
    int UserIdNum = 0;
    while(UserIdNum == 0){
          func->eraseTerminal();
      int Decision =  UserDecision();
      switch(Decision)
      {
      case 0:
        return 0;
      case 1:
          registerCharater();
          func->printTerminalText("Registration is complete");
          UserIdNum = showID();
          {
            sqlite::sqlite db("gamedb.db");
            auto query= db.get_statement();
            query->set_sql("INSERT INTO PlayerStats(PlayerID) VALUES(?);");
            query->prepare();
            query->bind(1,UserIdNum);
            query->step();
          }
          break;
      break;

      case 2:
      {
          while(loginCharater()!=1)
          {
            func->eraseTerminal();
            func->printTerminalText("\nCredencials do not match to the database!");
            func->printTerminalText("\n\nPlease try again");
            //loginCharater();
          }

          func->printTerminalText("Game starting...");
          UserIdNum = showID();
        //func->printTerminalText("\nHello user number " + std::to_string(UserIdNum));
          func->printTerminalText("\nWelcome back, " + UserN + "!");
      }
      break;

      default:
          func->printTerminalText("Wrong Input! Please try again");
          break;
      break;

      }
    }
  return UserIdNum;
}


/*

int main()
    {
    LoginClass Login;
    char Decision =  Login.UserDecision();



    switch(Decision)
    {

    case '1':
        Login.registerCharater();
        cout<<"Registration is complete"<<endl;
        main();
    break;


    case '2':
    {
        while(Login.loginCharater()!=1)
        {
            cout<<"Credencials do not match to the database!"<<endl;
            cout<<"Please try again"<<endl;
            Login.loginCharater();
        }

        cout<<"Game starting..."<<endl;
        string UserN = Login.UserN;
        int UserIdNum;
        UserIdNum = Login.showID(UserN);
        cout<<"Hello user number " << UserIdNum << endl;
    }
    break;



    default:
        cout << "Wrong Input! Please try again"<<endl;
        main();
    break;

    }
} */
