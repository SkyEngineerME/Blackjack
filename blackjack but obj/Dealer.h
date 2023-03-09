#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Dealer{
    private:
        vector<int> onhand;
    public:
        int score;
        int money;
        int bet;
        bool firstturn = true;
        bool survival = true;
        
        int GiveCard(int&);
        bool Probability();
        bool CheckScoreOver21();
        void ShowScore();
        void ShowScore(int []);
        void ShowCard(string []);
        void GamePlay(string [], int [], int&);
        void ReceiveCard(int);
        void SumScore(int []);
        void DealerThinking();
        void SetDefault();
        void DealerBet();
        string ShowName();
        Dealer();
};

Dealer::Dealer(){
    money = 2000;
}

int Dealer::GiveCard(int &cardn){
    ++cardn;
    return cardn;
}

void Dealer::SetDefault(){
    onhand.clear();
    score = 0;
    firstturn = true;
    survival = true;
}

string Dealer::ShowName(){
    return "Dealer";
}

void Dealer::ShowScore(){
    cout << "Dealer's Score is " << score << "\n\n";
}

void Dealer::ShowScore(int Cardpoint[]){ // Overload Func First turn
    cout << "Dealer's Score is " << score - Cardpoint[onhand[0]] << '\n';
    firstturn = false;
}

void Dealer::ShowCard(string CardId[]){
    cout << "\nDealer's Card is => ";
    for (unsigned int i = 0; i < onhand.size(); i++){
        if(firstturn){
            if (onhand.size()-1 == i) cout << CardId[onhand[i]] << ' ';
            else cout << "* "; 
        }else{
            cout << CardId[onhand[i]] << ' ';
        }
    }
    cout << '\n';
}

void Dealer::ReceiveCard(int card){
    onhand.push_back(card);
}

void Dealer::SumScore(int Cardpoint[]){
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

bool Dealer::Probability(){
    int ran = rand()%100 + 1;
    if ((21-score)>= 10) return true;
    else if (((21-score)/10.0*100)>=(ran)) return true;
    else return false;
}

void Dealer::DealerThinking(){
    string dot=". ";
    for (int i=0; i<6; i++){
        dot += ". ";
        cout << "Dealer Thinking" << dot << "\r";
        Sleep(200);
    }
}

bool Dealer::CheckScoreOver21(){
    if(score>21){
        cout << "\n!!!!!  Dealer's lost  !!!!!\n";
        survival = false;
        return true;
    }else{
        return false;
    }
}

void Dealer::GamePlay(string CardId[], int Cardpoint[], int &cardn){
    cout << "\n--------   Dealer's turn   --------";
    ShowCard(CardId);
    ShowScore();
    while(true){
        DealerThinking();
        if(Probability()){
            cout << "\nDealer Selected >> Hit\n\n";
            onhand.push_back(GiveCard(cardn));
            SumScore(Cardpoint);
            ShowCard(CardId);
            ShowScore();
            if(CheckScoreOver21()) break;
            else continue;
        }else{
            cout << "\nDealer Selected >> Stand\n\n";
            firstturn = true;
            break;
        }
    }
    
}

void Dealer::DealerBet(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));
    SetConsoleTextAttribute(h,1);
    cout << "------------------------------------\n";
    bet = (money/10)*(rand()%9 + 1);
    money = money - bet;
    SetConsoleTextAttribute(h,2);
    cout << "Dealer bets ";
    SetConsoleTextAttribute(h,13);
    cout << bet << "$ ";
    SetConsoleTextAttribute(h,2);
    cout << "(left ";
    SetConsoleTextAttribute(h,4);
    cout << money <<"$";
    SetConsoleTextAttribute(h,2);
    cout << ")\n";
    SetConsoleTextAttribute(h,1);
    cout << "------------------------------------";
    SetConsoleTextAttribute(h,7);
}