#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <cstdlib>

using namespace std;

class Player{
    private:
        string name;
        vector<int> onhand;
        bool hit = true;
    public:
        int money;
        int bet;
        int score;
    int cond;
        bool survival = true;
        bool blackjack = false;
        int GiveCard(int&);
        bool CheckScoreOver21();
        void ShowScore();
        void ShowCard(string []);
        void GamePlay(string [], int [], int&);
        void ReceiveCard(int);
        void SumScore(int []);
        void SetDefault();
        string ShowName();
        void PlayerBet();
        Player();
        
};

Player::Player(){
    money = 1000;
    cout << "::: Type your name ::: >> ";
    getline(cin,name);
}

int Player::GiveCard(int &cardn){
    ++cardn;
    return cardn;
}
void Player::SetDefault(){
    onhand.clear();
    score = 0;
    hit = true;
    survival = true;
    blackjack = false;
}

string Player::ShowName(){
    return name;
}

void Player::ShowScore(){
    cout << name <<"'s Score is " << score << "\n";
    if(score == 21) blackjack = true;
}

void Player::ShowCard(string CardId[]){
    cout << "\n" << name <<"'s Card is :: ";
    for (unsigned int i = 0; i < onhand.size(); i++){
        cout << CardId[onhand[i]] << ' ';
    }
    cout << '\n';
}

void Player::ReceiveCard(int card){
    onhand.push_back(card);
}

void Player::SumScore(int Cardpoint[]){
    int ace = 0;
    int sum = 0;
    for (unsigned int i = 0; i < onhand.size(); i++){
        if (Cardpoint[onhand[i]] == 1) ace++;
        sum += Cardpoint[onhand[i]];
    }

    for (int j = 0; j < ace; j++){
        if (21-sum >= 10) sum += 10;
    }
    score = sum;
}

bool Player::CheckScoreOver21(){
    if(score>21){
        cout << "\n!!!!!  " << name << " lost  !!!!!\n";
        survival = false;
        return true;
    }else{
        return false;
    }
}

void Player::PlayerBet(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,14);
    cout << "----888-------------------------888----\n";
    cout << "$$$ Put Your Money To Bet Your Fate $$$\n";
    cout << "----888-------------------------888----\n\n";
    cout << "you can put bet between [1-100]"<<endl;

    while(true){
    SetConsoleTextAttribute(h,14);
    cout << "Put your money (You have left ";
    SetConsoleTextAttribute(h,5);
    cout << money << "$";
    SetConsoleTextAttribute(h,14);
    cout << ") : ";

    string text;
    getline(cin,text);
    bet = stoi(text);
    if(bet > 0 && bet <= money && bet - (int) bet == 0 && bet <= 100){
        money = money-bet;
        SetConsoleTextAttribute(h,10);
        cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        cout << "You bet ";
        SetConsoleTextAttribute(h,3);
        cout << bet << "$ ";
        SetConsoleTextAttribute(h,10);
        cout << "(You have left now ";
        SetConsoleTextAttribute(h,4);
        cout << money << "$";
        SetConsoleTextAttribute(h,10);
        cout << ")\n\n";
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        SetConsoleTextAttribute(h,7);
        break;
    }
    else if(bet > 100){
        SetConsoleTextAttribute(h,4);
        cout << "\n------------------------------------\n";
        cout << "$$$ Please Bet between [1-100]!!! $$$\n";
        cout << "--------------------------------------\n\n";
    }
    else if(bet > money){
        SetConsoleTextAttribute(h,4);
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "$$$ Are you serious? You put money more than you have! Try again the poor!!! $$$\n";
        cout << "--------------------------------------------------------------------------------\n\n";
    }
    else if(bet - (int) bet != 0) {
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

void Player::GamePlay(string CardId[], int Cardpoint[], int &cardn){
    if(survival){
        cout << "\n--------   " << name << "'s turn   --------\n";
        bool check = true;
        while (true){
            if(check){
                cout << "Please Select : => ";
                cout << "[*] Hit";
                cout << " or [ ] Stand" << '\r';
                check = false;
                hit = true;
            }
            int key = _getch();
            if (key == 224){
                key = _getch();
                if(key == 75){
                    cout << "Please Select : => ";
                    cout << "[*] Hit";
                    cout << " or [ ] Stand" << '\r';
                    hit = true;
                }else if(key == 77){
                    cout << "Please Select : => [ ] Hit or ";
                    cout << "[*] Stand" << '\r';
                    hit = false;
                }
            }else if (key == 13){
                cout << '\n';
                if(hit){
                    cout << "You selected: ";
                    cout << "Hit\n";
                    onhand.push_back(GiveCard(cardn));
                    SumScore(Cardpoint);
                    ShowCard(CardId);
                    ShowScore();
                    if(CheckScoreOver21()) break;
                    else{
                        check = true;
                        continue;
                    }
                }else{
                    cout << "You selected: ";
                    cout << "Stand\n";
                    break;
                }
            }
        }
    }
}
