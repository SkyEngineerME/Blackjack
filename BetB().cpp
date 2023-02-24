#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

void BetB(int moneyb[], int betb[], int Nbot = 1){

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));
    SetConsoleTextAttribute(h,13);
    cout << "------------------------------------\n";
    for(int i = 0; i < Nbot; i++){
        betb[i] = (moneyb[i]/10)*(rand()%9 + 1);
        moneyb[i] = moneyb[i] - betb[i];
        SetConsoleTextAttribute(h,13);
        cout << "Bot No." << i+1 << " bets ";
        SetConsoleTextAttribute(h,3);
        cout << betb[i] << "$ ";
        SetConsoleTextAttribute(h,13);
        cout << "(left ";
        SetConsoleTextAttribute(h,4);
        cout << moneyb[i] <<"$";
        SetConsoleTextAttribute(h,13);
        cout << ")\n";

    }
    cout << "------------------------------------\n";
    SetConsoleTextAttribute(h,7);
}


int main(){
    int moneyb[3] = {10000,1870,2500};
    int betb[3] = {0,0,0};
    int Nbot = 3;
    BetB(moneyb,betb,Nbot);
    BetB(moneyb,betb,2);
    BetB(moneyb,betb,1);
    return 0;
}