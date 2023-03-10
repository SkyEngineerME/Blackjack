#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void BetB(int&,int&);
void BetP(int&,int&);
void Checkmoney(int&,int&,bool,bool&);

int main(){
    srand(time(0));
    int moneyP =100,moneyB = 100,i =0;
    bool swP = false;
    bool swB = false;
    bool survive = true;
    int betp,betb;
    while(survive == true){
    //BetP(moneyP,betp);
    BetB(moneyB,betb);
    i = rand()%3;
    Checkmoney(moneyB,betb,i,survive);
    }

return 0;

}

void Checkmoney(int &moneyPlayer,int &Betplayer,int condition,bool &survive){

    if(condition == 0){
        cout << "Got" << endl;
        moneyPlayer += Betplayer*2;
    }else if(condition == 1){
        cout << "Draw" << endl;
        moneyPlayer += Betplayer;
    }
    else if(condition == 2{
        cout << "Lose" << endl;
    }else;
    if(moneyPlayer <= 0){
        cout << "Lose Game bye" << endl;
        survive = false;
    }

}

void BetB(int &moneyb, int &betb){

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,13);
    cout << "------------------------------------\n";

        cout << "[ ";
        SetConsoleTextAttribute(h,3);
        cout << moneyb ;
        SetConsoleTextAttribute(h,13);
        cout << " ] ";
        while(betb > moneyb){
        betb = (rand()%9 + 1);
        }
        moneyb -= betb;
        SetConsoleTextAttribute(h,13);
        cout << "Bot No." << " bets ";
        SetConsoleTextAttribute(h,3);
        cout << betb<< "$ ";
        SetConsoleTextAttribute(h,13);
        cout << "(left ";
        SetConsoleTextAttribute(h,4);
        cout << moneyb <<"$";
        SetConsoleTextAttribute(h,13);
        cout << ")\n";
    cout << "------------------------------------\n";
    SetConsoleTextAttribute(h,7);
}

void BetP(int &moneyp,int &betp){
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
    betp = atof(text.c_str());
    if(betp > 0 && betp <= moneyp && betp - (int) betp == 0 && betp <= 10){
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
    else if(betp > 10){
        SetConsoleTextAttribute(h,4);
        cout << "\n------------------------------------\n";
        cout << "$$$ Please Bet between [1-10]!!! $$$\n";
        cout << "--------------------------------------\n\n";
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
