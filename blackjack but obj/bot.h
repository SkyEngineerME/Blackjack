#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Bot{
    private:
        int number;
        vector<int> onhand;
    public:
        int score; // ตอนแรกเอาไว้ใน private แต่คิดว่าคงไม่จำเป็น เพราะเกมเราคงไม่มีใครมาแฮก555 แล้ว "game.h" จะมา access ค่าง่ายขึ้นด้วย
        bool survival = true;
        int money;
        int bet;
    int cond;
        
        int GiveCard(int&);
        bool Probability();
        bool CheckScoreOver21();
        void AssignNumberbot(int);
        void ShowScore();
        void ShowScore(int []);
        void ShowCard(string []);
        void GamePlay(string [], int [], int&);
        void ReceiveCard(int);
        void SumScore(int []);
        void BotThinking();
        void SetDefault();
        void BotBet();        
        string ShowName();
        Bot();
};

Bot::Bot(){
    money = 1000;
}

int Bot::GiveCard(int &cardn){
    ++cardn;
    return cardn;
}

void Bot::SetDefault(){
    onhand.clear();
    score = 0;
    survival = true;
}

string Bot::ShowName(){
    return "Bot" + to_string(number);
}

void Bot::AssignNumberbot(int num){
    number = num;
}

void Bot::ShowScore(){
    cout << "Bot" << number << "'s Score is " << score << "\n";
}

void Bot::ShowCard(string CardId[]){
    cout << "\nBot" << number << "'s Card is => ";
    for (unsigned int i = 0; i < onhand.size(); i++){
        cout << CardId[onhand[i]] << ' ';
    }
    cout << '\n';
}

void Bot::ReceiveCard(int card){
    onhand.push_back(card);
}

void Bot::SumScore(int Cardpoint[]){
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

bool Bot::Probability(){
    int ran = rand()%100 + 1;
    if ((21-score)>= 10) return true;
    else if (((21-score)/10.0*100)>=(ran)) return true;
    else return false;
}

void Bot::BotThinking(){
    string dot=". ";
    for (int i=0; i<6; i++){
        dot += ". ";
        cout << "Bot Thinking" << dot << "\r";
        Sleep(200);
    }
}

bool Bot::CheckScoreOver21(){
    if(score>21){
        cout << "\n!!!!!  Bot" << number << " lost  !!!!!\n";
        survival = false;
        return true;
    }else{
        return false;
    }
}

void Bot::GamePlay(string CardId[], int Cardpoint[], int &cardn){
    if(survival){
        cout << "\n--------   Bot" << number << "'s turn   --------";
        ShowCard(CardId);
        ShowScore();
        while (true){
            BotThinking();
            if(Probability()){
                cout << "\nBot Selected >> Hit\n\n";
                onhand.push_back(GiveCard(cardn));
                SumScore(Cardpoint);
                ShowCard(CardId);
                ShowScore();
                if(CheckScoreOver21()) break;
                else continue;
            }else{
                cout << "\nBot Selected >> Stand\n\n";
                break;
            }
        }
    }
}

void Bot::BotBet(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,13);
    cout << "------------------------------------\n";
        cout << "[ ";
        SetConsoleTextAttribute(h,3);
        cout << money ;
        SetConsoleTextAttribute(h,13);
        cout << " ] ";
        bet = (rand()%9 + 1);
        while(bet > money){
        bet = (rand()%9 + 1);
        }
        money -= bet;
        SetConsoleTextAttribute(h,13);
        cout << "Bot No." << " bets ";
        SetConsoleTextAttribute(h,3);
        cout << bet<< "$ ";
        SetConsoleTextAttribute(h,13);
        cout << "(left ";
        SetConsoleTextAttribute(h,4);
        cout << money <<"$";
        SetConsoleTextAttribute(h,13);
        cout << ")\n";
    cout << "------------------------------------\n";
    SetConsoleTextAttribute(h,7);
}
