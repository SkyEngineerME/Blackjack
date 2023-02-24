#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;


string CardId[52] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

int Cardpoint[52] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10};

void GameP(vector<int> &, bool &, int &, int &);
void GameP_ShowCard(vector<int>);
void GameB(vector<int> &, bool &, int &, int &);
void GameB_ShowCard(vector<int>, bool);
void shuffle(string [],int [],int);
int  Givecard(string [],int&);
void Propa (vector<int>,bool &, int &);
void CheckScore(int, bool &);
void CheckScore(int, int);
void ShowScore(int &, bool);
void ShowScore(int &, bool, vector<int>, bool firstturn = false);
void SumScore(vector<int>, int &);
void BotThinking();

int main(){
    srand(time(0));
    int cardn = 0;
    shuffle(CardId, Cardpoint, 52);
    vector<int> playerhand;
    vector<int> bothand;

    for (int i = 0; i < 2; i++)
    {
        playerhand.push_back(Givecard(CardId,cardn));
        bothand.push_back(Givecard(CardId,cardn));
    }

    bool PlayerHit = true ,BotHit = true, bypassend = true;
    int ScoreB = 0, ScoreP = 0;

    // สกอร์ครั้งแรกของแต่ละคนเป็นเท่าใด ถ้าได้ 21 ก็แบล๊คแจ๊คเลย
    SumScore(playerhand,ScoreP);
    SumScore(bothand,ScoreB);
    GameB_ShowCard(bothand,true);
    ShowScore(ScoreB,true,bothand,true);
    if(ScoreP >= 21) bypassend = false;
    if(ScoreB >= 21) {
        GameB_ShowCard(bothand,false);
        ShowScore(ScoreB,true,bothand);
        bypassend = false;
    }

    while(PlayerHit && bypassend){
        GameP_ShowCard(playerhand);
        GameP(playerhand,PlayerHit,cardn,ScoreP);
        CheckScore(ScoreP,bypassend);
        if (!bypassend) ShowScore(ScoreP,false);
    }
    while(BotHit && bypassend){
        GameB(bothand,BotHit,cardn,ScoreB);
        CheckScore(ScoreB,bypassend);
        if (!bypassend) ShowScore(ScoreB,true);
    }

    cout << '\n';
    CheckScore(ScoreB,ScoreP);
    
    
    return 0;
}

void CheckScore(int scoreb, int scorep){
    if(scoreb > 21) cout << "Player Win\n";
    else if(scorep > 21) cout << "Bot Win\n";
    else if(scoreb == 21) cout << "Bot Blackjact\n";  
    else if(scorep == 21) cout << "Player Blackjact\n";
    else if(scorep > scoreb) cout << "Player Win\n";
    else if(scorep == scoreb) cout << "Draw\n";
    else cout << "Bot Win\n";
}

void CheckScore(int score, bool &bypassend){
    if(score >= 21){
        bypassend = false;
    }
}

void GameP_ShowCard(vector<int> playerhand){
    cout << "Your Card is => ";
    for (unsigned int i = 0; i < playerhand.size(); i++){
        cout << CardId[playerhand[i]] << ' ';
    }
    cout << '\n';
}

void GameB_ShowCard(vector<int> bothand,bool firstturn){
    cout << "Bot's card is => ";
    for (unsigned int i = 0; i < bothand.size(); i++){
        if(firstturn){
            if (bothand.size()-1 == i) cout << CardId[bothand[i]] << ' ';
            else cout << "* "; 
        }else{
            cout << CardId[bothand[i]] << ' ';
        }
    }
    cout << '\n';
}

void ShowScore(int &score, bool authbot, vector<int> bothand, bool firstturn){
    if(authbot) cout << "Current Bot Score => ";
    else cout << "Your Score => ";
    if(firstturn) {
        int botscore = score - Cardpoint[bothand[0]];
        cout << botscore << '\n';
    }else{
        cout << score << '\n';
    }
}

void ShowScore(int &score, bool authbot){
    if(authbot) cout << "Bot Score => ";
    else cout << "Your Score => ";
    cout << score << '\n';
}

void SumScore(vector<int> card, int &score){
    
    int ace = 0;
    int sum = 0;
    for (int i = 0; i < card.size(); i++){
        if (Cardpoint[card[i]] == 1) ace++;
        sum += Cardpoint[card[i]];
    }

    for (int j = 0; j < ace; j++){
        if (21-sum >= 10) sum += 10;
    }
    score = sum;
    
}

void GameP(vector<int> &playerhand, bool &flag_gamep_hit, int &cardn, int &score){
    // system("cls");

    // HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    bool flag = false;
    bool flag_hit = true;
    // SetConsoleTextAttribute(console,3);
    // cout << "---------- * THIS IS YOUR TURN * -----------" << '\n';
    // cout << "|                                          |" << '\n';
    // cout << "|";
    // SetConsoleTextAttribute(console,14);
    // cout << "   ?? USE [<-] [->] button to select !!   ";
    // SetConsoleTextAttribute(console,3);
    // cout << "|" << '\n';
    // cout << "|                                          |" << '\n';
    // cout << "--------------------------------------------" << '\n';
    ShowScore(score,false);
    cout << "Please Select : => ";
    cout << "[*] Hit";
    cout << " or [ ] Stand" << '\r';
    while (true)
    {
        int key = _getch();
        if (key == 224){
            key = _getch();
            if(key == 75){
                cout << "Please Select : => ";
                cout << "[*] Hit";
                cout << " or [ ] Stand" << '\r';
                flag_hit = true;
            }else if(key == 77){
                cout << "Please Select : => [ ] Hit or ";
                cout << "[*] Stand" << '\r';
                flag_hit = false;
            }
        }else if (key == 13){
            cout << '\n';
            if(flag_hit){
                cout << "You selected: ";
                cout << "Hit\n";
                playerhand.push_back(Givecard(CardId,cardn));
                SumScore(playerhand,score);
                flag_gamep_hit = true;
                break;
            }else{
                cout << "You selected: ";
                cout << "Stand\n";
                flag_gamep_hit = false;
                break;
            }
        }
    }
}   

void GameB(vector<int> &bothand, bool &flag_gameb_hit, int &cardn, int &score){
    GameB_ShowCard(bothand,false);
    Propa(bothand,flag_gameb_hit,score);
    BotThinking();
    if(flag_gameb_hit){
        cout << "\nBot Selected >> Hit\n";
        bothand.push_back(Givecard(CardId,cardn));
        SumScore(bothand,score);
        // ShowScore(score,true);
    }else{
        cout << "\nBot Selected >> Stand\n";
    }
}

void shuffle(string cardID[],int cardpoint[], int n)
{
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52 -i));
        swap(cardID[i], cardID[r]);
        swap(cardpoint[i],cardpoint[r]);
    }
}

int Givecard(string CardID[],int &cardn)
{
    ++cardn;
    return cardn-1;
}

void Propa(vector<int> handbot,bool &Blag, int &score){
    int ace = 0;
    int sum = 0;
    for (int i = 0; i < handbot.size(); i++)
    {
         if (Cardpoint[handbot[i]] == 1)
         {
             ace++;
         }
    sum += Cardpoint[handbot[i]];
    }

    for (int i1 = 0; i1 < ace; i1++)
    {
        if (21-sum >= 10)
        {
            sum += 10;
        }    
    }
    
    cout << "Current Bot Score => " << sum << '\n';
    score = sum;

    int ran = rand()%100 + 1;
    if ((21-sum)>= 10)
    {
        Blag = true;
    }else if (((21-sum)/10.0*100)>=(ran))
    {
        Blag = true;
    }else{
        Blag = false;
    }
}

void BotThinking(){
    string dot=". ";
    int temp = rand()%7+3;
    cout << '\n';
    for (int i=0; i<temp; i++){
        dot += ". ";
        cout << "Bot Thinking" << dot << "\r";
        Sleep(200);
    }
}