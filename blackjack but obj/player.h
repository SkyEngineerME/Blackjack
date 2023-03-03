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
        int score;
        bool survival = true;
        bool blackjack = false;
        
        int GiveCard(int&);
        bool CheckScoreOver21();
        void AssignName(string);
        void ShowScore();
        void ShowCard(string []);
        void GamePlay(string [], int [], int&);
        void ReceiveCard(int);
        void SumScore(int []);
        void SetDefault();
        string ShowName();
        
};

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

void Player::AssignName(string inputname){
    name = inputname; 
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
    }else if(score == 21){
        blackjack = true;
        return true;
    }else{
        return false;
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
                    if(CheckScoreOver21() || blackjack) break;
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
