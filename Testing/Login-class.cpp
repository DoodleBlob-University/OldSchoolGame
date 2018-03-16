// final version of my individual unit 


#include <iostream>
#include <fstream>
#include <string>
#include "sqllibrary.h"        //This is the same library that we've been told to use, just called the file a different name 
sqlite::sqlite db("UserInfo.db");

using namespace std;


class LoginClass 
{
    private:
    
    int userCheck(string username) //Checks the DB formaching username
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
    


    char creatCharacter(auto& username,auto& password) //creates a new rcord for the newly registered user 
    {
        auto query= db.get_statement();
        query->set_sql("INSERT INTO User(Username,Password) VALUES (?,'"+password+"'); ");
        query->prepare();
        query->bind(1,username);
        query->step();
    }




    public: 
    string UserN;
    int showID(string username)
    {
        auto query= db.get_statement();
        query->set_sql("SELECT ID FROM User WHERE Username=?; ");
        query->prepare();
        query->bind(1,username);
        while(query->step())
        {
            int ans = query->get_int(0);
            return ans;
        }
    }



    char UserDecision()
    {
        char Decision;

        cout << "1: Would you like to Register?" << endl;
        cout << "2: Would you like to Login?" << endl;
        cout << "Enter 1 or 2: ";
        cin >> Decision;

        return Decision;
    }



    void registerCharater()
    {
        string Username_entered, Password_entered;
        cout << "Enter Username: ";
        cin >> Username_entered;
       
        while(userCheck(Username_entered)==1) //UserCheck returns 1 when the username already exist in the DB 
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

        this->UserN=Username_entered;

        auto query= db.get_statement();
        query->set_sql("SELECT COUNT(*) FROM User WHERE Username=? AND Password='"+Password_entered+"'; ");
        query->prepare();
        query->bind(1,Username_entered);
        query->step();
        return query->get_int(0);

    }
    
};




                                
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
}
