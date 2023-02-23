#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
using namespace std;

/* color ref. https://www.youtube.com/watch?v=MvX4tVETjHk&t=19s&ab_channel=CodeLeader */
/* can solve when put invalid input (like alphabet a,b,cat,y2000k,a4.5b or more two data like 100 200, 1.5 2.5 3.5,...)*/
/* cannot solve in only this case (ex. 123abc, 100cat, ...)*/

void BetP(int &moneyp){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,14);
    cout << "----888-------------------------888----\n";
    cout << "$$$ Put Your Money To Bet Your Fate $$$\n";
    cout << "----888-------------------------888----\n\n";

    while(true){
    SetConsoleTextAttribute(h,14);
    cout << "Put your money (You have left ";
    SetConsoleTextAttribute(h,5);
    cout << moneyp << "$";
    SetConsoleTextAttribute(h,14);
    cout << ") : ";

    string text;
    getline(cin,text);
    double betp = atof(text.c_str());
    if(betp > 0 && betp <= moneyp && betp - (int) betp == 0) {
        moneyp = moneyp-betp;
        SetConsoleTextAttribute(h,10);
        cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        cout << "You bet ";
        SetConsoleTextAttribute(h,3);
        cout << betp << "$ ";
        SetConsoleTextAttribute(h,10);
        cout << "(You have left now ";
        SetConsoleTextAttribute(h,4);
        cout << moneyp << "$";
        SetConsoleTextAttribute(h,10);
        cout << ")\n\n";
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        SetConsoleTextAttribute(h,7);
        break;
    }
    else if(betp > moneyp){
        SetConsoleTextAttribute(h,4);
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "$$$ Are you serious? You put money more than you have! Try again the poor!!! $$$\n";
        cout << "--------------------------------------------------------------------------------\n\n";
    }
    else if(betp - (int) betp != 0) {
        SetConsoleTextAttribute(h,4);
        cout << "\n---------------------------------------------------------------------------------\n";
        cout << "$$$ I don't want some kind of pocket change...Try again with integer numbers. $$$\n";
        cout << "---------------------------------------------------------------------------------\n\n";
    }
    else{
        SetConsoleTextAttribute(h,4);
        cout << "\n-----------------------------------------------------------------------\n";
        cout << "$$$ Invalid input Man! Give me your money! Try again and quickly!!! $$$\n";
        cout << "-----------------------------------------------------------------------\n\n";
        cin.clear(); /*use to solve alphabet wrong input*/
    }
    }
}

int main(){
    int money = 1000;
    BetP(money);
    return 0;
}
