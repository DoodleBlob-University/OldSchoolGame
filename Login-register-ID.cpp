// This is what I managed to do so far. However, I struggled with creating a database table.
// This program helps the user register, provides an ID number for them, 
// and lets them login when the correct username and password are provided.



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    bool Loop = true, Check = false;
    string Username_entered, Password_entered , Username[100], Password[100];
    int ID[100], Decision, ID_counter = 0, Counter = 0, Check_counter;
   
    while(Loop == true)
    {
        cout << "1: Would you like to Register?" << endl;
        cout << "2: Would you like to Login?" << endl;
        cout << "Enter 1 or 2: ";
        cin >> Decision;
        if(Decision == 1)
        {
            cout << "Enter Username: ";
            cin >> Username_entered;
            cout << "Enter Password: ";
            cin >> Password_entered;
           
            Username[Counter] = Username_entered;
            Password[Counter] = Password_entered;
            ID[Counter] = ID_counter;
            Counter += 1;
            ID_counter += 1;
            Check_counter = Counter;
            cout << "Welcome " << Username_entered << " your Id number is " << ID_counter <<endl;
            cout << "\n";
            
        }
        else if(Decision == 2)
        {
            cout << "Enter Username: ";
            cin >> Username_entered;
            cout << "Enter Password: ";
            cin >> Password_entered;
            
            while(Check == false)
            {
                if((Username[Check_counter] == Username_entered) && (Password[Check_counter] == Password_entered))
                      {
                    cout << "User number " << ID_counter << " ,you've been logged in!"<<endl;
                    Check = true;
                    Loop = false;
                }
                else if (Check_counter == 0 && Check == false)
                {
                    cout << "Wrong Username or password!"<<endl;
                    cout<< "Please try again"<<endl;
                    Check = true;
                }
                else
                {
                    Check_counter -= 1;
                }
            }
        }
        else
        {
            cout << "Enter 1 or 2"<<endl;
        }
    }
}
