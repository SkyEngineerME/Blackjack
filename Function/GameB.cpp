#include <iostream>
#include <cstdlib>
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

void GameP(bool &flag){
    system("cls");

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    bool flag_hit = true;
    SetConsoleTextAttribute(console,3);
    cout << "---------- * THIS IS YOUR TURN * -----------" << '\n';
    cout << "|                                          |" << '\n';
    cout << "|";
    SetConsoleTextAttribute(console,14);
    cout << "   ?? USE [<-] [->] button to select !!   ";
    SetConsoleTextAttribute(console,3);
    cout << "|" << '\n';
    cout << "|                                          |" << '\n';
    cout << "--------------------------------------------" << '\n';
    SetConsoleTextAttribute(console,7);
    cout << "Please Select : => ";
    SetConsoleTextAttribute(console,4);
    cout << "[*] Hit";
    SetConsoleTextAttribute(console,7);
    cout << " or [ ] Stand" << '\r';
    while (true)
    {
        int key = _getch();
        if (key == 224){
            key = _getch();
            if(key == 75){
                SetConsoleTextAttribute(console,7);
                cout << "Please Select : => ";
                SetConsoleTextAttribute(console,4);
                cout << "[*] Hit";
                SetConsoleTextAttribute(console,7);
                cout << " or [ ] Stand" << '\r';
                flag_hit = true;
            }else if(key == 77){
                SetConsoleTextAttribute(console,7);
                cout << "Please Select : => [ ] Hit or ";
                SetConsoleTextAttribute(console,4);
                cout << "[*] Stand" << '\r';
                flag_hit = false;
            }
        }else if (key == 13){
            cout << '\n';
            if(flag_hit){
                SetConsoleTextAttribute(console,2);
                cout << "You selected: ";
                SetConsoleTextAttribute(console,4);
                cout << "Hit";
                flag = true;
            }else{
                SetConsoleTextAttribute(console,2);
                cout << "You selected: ";
                SetConsoleTextAttribute(console,4);
                cout << "Stand";
                flag = false;
            }
        }
    }
}   

void shuffle(string cardID[], int n)
{
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52 -i));
        swap(cardID[i], cardID[r]);
        swap(Cardpoint[i],Cardpoint[r]);
    }
}

int Givecard(string CardID[],int &cardn)
{
    ++cardn;
    return cardn-1;
}

class bot
    {
    private:
        vector<int> bothand;
        bool botdraw;
        int betb; // bot's bet
    public:
        bot(string [], int &);
        void Propa();
        int show(int);
        bool botact();
        ~bot();
    };

bot::bot(string Card[],int &ncard)
{
    botdraw = true;
    for (int i = 0; i < 2; i++)
    {
        bothand.push_back(Givecard(Card,ncard));
    }
    
}

bot::~bot()
{

}

void bot::Propa(){ //true = drawnewcard
    int ace = 0;
    int sum = 0;
    for (int i = 0; i < bothand.size(); i++)
    {
         if (Cardpoint[bothand[i]] == 1)
         {
             ace++;
         }
    sum += Cardpoint[bothand[i]];
    }

    for (int i1 = 0; i1 < ace; i1++)
    {
        if (21-sum >= 10)
        {
            sum += 10;
        }    
    }
    int ran = rand()%100 + 1;
    if ((21-sum)>= 10)
    {
        botdraw = true;
    }else if (((21-sum)/10.0*100)>=(ran))
    {
        botdraw = true;
    }else{
        botdraw = false;
    }
}

bool bot::botact(){
    return botdraw;
}

int bot::show(int numcard){
    return bothand[numcard];
}

int main()
{
    srand(time(0));
    int cardn = 0;
    shuffle(CardId, 52);
    vector<int> playerhand;
    vector<int> bothand;
    for (int i = 0; i < 2; i++)
    {
        playerhand.push_back(Givecard(CardId,cardn));
    }
    bot bot1(CardId,cardn);
    cout <<CardId[playerhand[0]] <<' '<<playerhand[0] <<endl;
    cout << CardId[playerhand[1]] <<' '<<playerhand[1] <<endl;
    bool Phit = true;

    do{
       if (Phit)
        {
            GameP(Phit);
        }
       if (bot1.botact())
        {
            bot1.Propa();
                if (bot1.botact())
                {
                    cout<<"Bot1 HIT";
                }
        
        }
       
    } while (Phit||bot1.botact());
    
    
    return 0;
}


