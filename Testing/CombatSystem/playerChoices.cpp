#include <iostream>
#include <string>
#include <cstring>


using namespace std;
int main(){
    //display options to the user for each situation, ncurses helps with the interface but this is the simple logic 

    string const attackSearch = "attack";
    string response;
      
    
    cout << "What would you like to do?" << endl;
    getline(cin, response);
    cout << response << endl;
    
    if (cin.fail()){
    const int len = strlen(response.c_str());
    }

    for (size_t i = 0; response.size() > i; ++i){
      if ((response[i] >= 'A') && (response[i] <= 'Z')) response[i] = response[i] - 'A' + 'a';
    }
    cout << response << endl;

    //response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
    //cout << response << endl; - not needed anymore thanks to the getline(), removes spaces
    size_t pos;
    pos = response.find(attackSearch);
    
    if (pos != string::npos){ //string::npos = reference to the strings input http://www.cplusplus.com/reference/string/string/npos/ 
        cout << "It works" << endl;
    }
    else {
        cout << "Not included" << endl;
    }
    return 0;
}
