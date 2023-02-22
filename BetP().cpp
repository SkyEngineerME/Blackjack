#include <iostream>
#include <windows.h>
using namespace std;

/* color ref. https://www.youtube.com/watch?v=MvX4tVETjHk&t=19s&ab_channel=CodeLeader */
/* this function doesn't work in some cases (bug when put alphabat in it, cannot put 2 data in one time)*/

void BetP(int &moneyp){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,14);
    cout << "----888-------------------------888----\n";
    cout << "$$$ Put Your Money To Bet Your Fate $$$\n";
    cout << "----888-------------------------888----\n";

    while(true){
    cout << "Put your money (You have left ";
    SetConsoleTextAttribute(h,5);
    cout << moneyp << "$";
    SetConsoleTextAttribute(h,14);
    cout << ") : ";

 double betp;
    cin >> betp;
    if(betp <= 0) {
        SetConsoleTextAttribute(h,4);
        cout << "-----------------------------------------------------------------------\n";
        cout << "$$$ Invalid input Man! Give me your money! Try again and quickly!!! $$$\n";
        cout << "-----------------------------------------------------------------------\n";
    }
    else if(betp > moneyp){
        SetConsoleTextAttribute(h,4);
        cout << "--------------------------------------------------------------------------------\n";
        cout << "$$$ Are you serious? You put money more than you have! Try again the poor!!! $$$\n";
        cout << "--------------------------------------------------------------------------------\n";
    }
    else if(betp - (int) betp != 0) {
        SetConsoleTextAttribute(h,4);
        cout << "---------------------------------------------------------------------------------\n";
        cout << "$$$ I don't want some kind of pocket change...Try again with integer numbers. $$$\n";
        cout << "---------------------------------------------------------------------------------\n";
    }
    else{
        moneyp = moneyp-betp;
        SetConsoleTextAttribute(h,10);
        cout << "You bet ";
        SetConsoleTextAttribute(h,3);
        cout << betp << "$ ";
        SetConsoleTextAttribute(h,10);
        cout << "(You have left now ";
        SetConsoleTextAttribute(h,4);
        cout << moneyp << "$";
        SetConsoleTextAttribute(h,10);
        cout << ")\n";
        break;
    }
    }
}

int main(){
    int money = 100;
    BetP(money);
    return 0;
}
