#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    
    srand (time(NULL)); //initialise random seed
    string arrayFirstMessage[4] = {"What to do", "How to do it", "When to do it", "Time to do it"};
    int RandIndex1 = rand() % 4; //generates a random number between 0 and 3
    string FirstMessage = arrayFirstMessage[RandIndex1];
    
    string arraySecondMessage[4] = {"Slap", "Dribble", "Shotgun", "GG"};
    int RandIndex2 = rand() % 4;
    string SecondMessage = arraySecondMessage[RandIndex2];
    
    string arrayFinalMessage[4] = {"Death", "Time to die", "RIP", "Addios Amigo"};
    int RandIndex3 = rand() % 4; 
    string FinalMessage = arrayFinalMessage[RandIndex3];
    
    cout << RandIndex1 << RandIndex2 << RandIndex3; //just to show which numbers are generated
    cout << FirstMessage << " " << SecondMessage << " " << FinalMessage << endl;
    //to make it relevent to the encouter this cout message would require a DB reference to then put in the monster, weapon, could display stats
   
    return 0;
}
