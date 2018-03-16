//Charles Barry
#ifndef LOGIN_H
#define LOGIN_H

class LoginClass//Shirin Shahali
{
    private:
    int userCheck(std::string username);
    char creatCharacter(auto& username,auto& password);
    int showID();
    int UserDecision();
    void registerCharater();
    char loginCharater();
    std::string UserN;

    TerminalFunctions* func;
  public:
    int getUser();

    LoginClass(TerminalFunctions* _func){//Charles Barry
      func = _func;
    }
};

#endif

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
}
*/
