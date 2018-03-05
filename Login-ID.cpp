//This code is the oe that records the username and password in a table and provides a unique Id number for each user.



#include <iostream>
#include <fstream>
#include <string>
#include "sqllibrary.h"
sqlite::sqlite db("Database.db");
//#include "functions2SQL.h"
using namespace std;

string UserName;

char creatCharacter(auto& username,auto& password)
    {
    auto query= db.get_statement();
    query->set_sql("INSERT INTO User(Username,Password) VALUES (?,'"+password+"'); ");
    query->prepare();
    query->bind(1,username);
    query->step();
    
    }

int showID(string username)
{
    auto query= db.get_statement();
    query->set_sql("SELECT * FROM User WHERE Username=?; ");
    query->prepare();
    query->bind(1,username);
    while(query->step())
    {
    return query->get_int(0);
    }
}

int userCheck(string username)
{
    auto query= db.get_statement();
    query->set_sql("SELECT COUNT(*) FROM User WHERE Username=?; ");
    query->prepare();
    query->bind(1,username);
    while(query->step())
    {
    return query->get_int(0);
    }
}

void registerCharater()
{
    
            
    string Username_entered, Password_entered;
    cout << "Enter Username: ";
    cin >> Username_entered;
    while(userCheck(Username_entered)==1)
    {
                
    cout<<"Sorry, you can't use that username"<<endl;
    cout<<"It has been taken by another user"<<endl;
    cout <<"Enter a more unqiue username: ";
    cin >> Username_entered;
    userCheck(Username_entered);
                
    }
    cout << "Enter Password: ";
    cin >> Password_entered;
    creatCharacter(Username_entered,Password_entered);   
    
}


char loginCharater()
    {
    string Username_entered, Password_entered;
    cout << "Enter Username: ";
    cin >> Username_entered;
    cout << "Enter Password: ";
    cin >>Password_entered;
            
    UserName=Username_entered;
            
    auto query= db.get_statement();
    query->set_sql("SELECT COUNT(*) FROM User WHERE Username=? AND Password='"+Password_entered+"'; ");
    query->prepare();
    query->bind(1,Username_entered);
    query->step();
    return query->get_int(0);
            
    }

int main()
{
    
    char Decision;
    
    cout << "1: Would you like to Register?" << endl;
    cout << "2: Would you like to Login?" << endl;
    cout << "Enter 1 or 2: ";
    cin >> Decision;
        
    
    switch(Decision)
    {
            
    case '1':        
        registerCharater();
        cout<<"Registration is complete"<<endl;
        main();
    break;
            
    
   
    case '2':
    {    
        while(loginCharater()!=1)
        {
            cout<<"Credencials do not match to the database!"<<endl;
            cout<<"Please try again"<<endl;                 
            loginCharater();        
        }
            
        cout<<"Game starting..."<<endl;
        int UserIdNum = showID(UserName);
        cout<<"Hello user number " << UserIdNum << endl;
    }
    break;
            
            
    
    default:
    cout << "Wrong Input! Please try again"<<endl;          
    main();
    break;           
            
    }
    }
