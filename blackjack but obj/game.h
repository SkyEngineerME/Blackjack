#include <string>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cctype>
#include "player.h"
#include "bot.h"
#include "Dealer.h"
using namespace std;

class Game{
    public:
        std::string CardId[52] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K",
                                "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                                "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                                "A","2","3","4","5","6","7","8","9","10","J","Q","K"};
        int Cardpoint[52] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
                            1,2,3,4,5,6,7,8,9,10,10,10,10,
                            1,2,3,4,5,6,7,8,9,10,10,10,10,
                            1,2,3,4,5,6,7,8,9,10,10,10,10};

        vector<int> indexplayersuvival;
        vector<int> indexbotsuvival;
        int bot,round;
        int cardn = 0;
        int check;
        int GiveCard();
        bool blackjack_flag = false;
        bool tryagain = true;
        bool checktwointerrupt = false;
        bool WhoSurvival(Player&, Bot*);
        void Start(int,int);
        void AddNamePlayer(string);
        void ShuffleCard();
        void PlayerShowCard(Player&);
        void PlayerShowScore(Player&);
        void BotShowCard(Bot&);
        void BotShowScore(Bot&);
        void Winner(Player&, Bot*, Dealer&);
        void DealerShowCard(Dealer&);
        void DealerShowScore(Dealer&);
};

void Game::Start(int numbot,int round){

    int r = 0;
    Player people;
    Bot *ai = new Bot[numbot];
    Dealer dealer;
    bot = numbot;
    
    string name;
    cout << "::: Type your name ::: >> ";
    getline(cin,name);
    people.AssignName(name);

    for (int i=0; i<numbot; i++){
        ai[i].AssignNumberbot(i+1);
    }

    while(tryagain){
        system("cls");
        ShuffleCard();
        cout << "\n--------Turn "<< r+1 << "--------";
       
        for(int j=0; j<2; j++) people.ReceiveCard(GiveCard());

        for (int i=0; i<numbot; i++){
            for(int j=0; j<2; j++) ai[i].ReceiveCard(GiveCard());
        }

        for(int j=0; j<2; j++) dealer.ReceiveCard(GiveCard());

        //--------------------------------- โชว์ไพ่
        cout << "\n********* CARD & SCORE **********\n";
        people.SumScore(Cardpoint);
        PlayerShowCard(people);
        PlayerShowScore(people);

        for (int i=0; i<numbot; i++){
            ai[i].SumScore(Cardpoint);
            BotShowCard(ai[i]);
            BotShowScore(ai[i]);
        }

        dealer.SumScore(Cardpoint);
        DealerShowCard(dealer);
        DealerShowScore(dealer);

        cout << "\n********************************\n";
        //---------------------------------

        if(people.blackjack){ // เช็คว่า blackjack รึเปล่าก่อนเริ่มเทิร์น
            blackjack_flag = true;
            break;
        }

        people.GamePlay(CardId, Cardpoint, cardn);
        if(blackjack_flag) break;
        if(numbot==1 && !people.survival) continue; //[Bug fix (temporary)] เมื่อเล่นคนเดียวกับบอท1ตัวแล้วแพ้ 
        
        for (int i=0; i<numbot; i++){
            if(ai[i].blackjack){ // เช็คว่า blackjack รึเปล่าก่อนเริ่มเกม
                blackjack_flag = true;
                break;
            }

            ai[i].GamePlay(CardId, Cardpoint, cardn);
        }
        if(blackjack_flag) break;
        
        // Dealer Open Cards
        dealer.GamePlay(CardId, Cardpoint, cardn);

        Winner(people,ai,dealer);

        r++;
        while(true){
            if(r < round){
                cardn = 0;
                people.SetDefault();
                dealer.SetDefault();
                for (int i=0; i<numbot; i++) ai[i].SetDefault();
                checktwointerrupt = false;
                blackjack_flag = false;
                indexplayersuvival.clear();
                indexbotsuvival.clear();

                string ck;
                cout << "\nNEXT ROUND [Y] : ";
                getline(cin,ck);
                while(true){
                    if(toupper(ck[0]) == 'Y'){
                        break;
                    }
                    cout << "Pressed [Y] to continue ";
                    getline(cin,ck);
                }

                tryagain = true;
                break;
            }else if(r >= round){
                string ck;
                cout << "\nGO TO HOMEPAGE [Y] : ";
                getline(cin,ck);
                while(true){
                    if(toupper(ck[0]) == 'Y'){
                        break;
                    }
                    cout << "Pressed [Y] to continue ";
                    getline(cin,ck);
                }
                tryagain = false;
                break;
            }else{
                cout << "Invalid Command !! Please type 'y' or 'n' only.";
                break;
            }
        }
        
    }
    delete [] ai;
}

void Game::Winner(Player &people, Bot *ai, Dealer &dealer){
    int count = 0;
    int auth = false;
    bool flag_detect = false;
    cout << "------ SCREEN -------\n";
    if (people.survival)
    {
        if(people.score > dealer.score){
            cout << "* " << people.ShowName() << " WIN\n";
        }else if(people.score == dealer.score){
            cout << "* " << people.ShowName() << " DRAW\n";
        }else{
            cout << "* " << people.ShowName() << " LOST\n";
        }
    }else{
        cout << "* " << people.ShowName() << " LOST\n";
    }
    
    
    for (count = 0; count<bot; count++){
        if(ai[count].survival){
            if(ai[count].score > dealer.score){
                cout << "* " << ai[count].ShowName() << " WIN\n";
            }else if(ai[count].score == dealer.score){
                cout << "* " << ai[count].ShowName() << " DRAW\n";
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
            }
        }else{
            cout << "* " << ai[count].ShowName() << " LOST\n";
        }
    }
    
}

void Game::ShuffleCard(){
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52-i));
        swap(CardId[i], CardId[r]);
        swap(Cardpoint[i], Cardpoint[r]);
    }
    cout << "########## ShuffleCard.... ###########\n";
}

int Game::GiveCard(){
    ++cardn;
    return cardn-1;
}

void Game::PlayerShowCard(Player &people){
    if(people.survival) people.ShowCard(CardId);
}

void Game::PlayerShowScore(Player &people){
    if(people.survival) people.ShowScore();
}

void Game::BotShowCard(Bot &ai){
    if(ai.survival) ai.ShowCard(CardId);
}

void Game::BotShowScore(Bot &ai){
    if(ai.survival) ai.ShowScore();
}

void Game::DealerShowCard(Dealer &dealer){
    dealer.ShowCard(CardId);
}

void Game::DealerShowScore(Dealer &dealer){
    if(dealer.firstturn) dealer.ShowScore(Cardpoint);
    else dealer.ShowScore();
}
