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
        bool WhoSurvival(Player*, Bot*);
        void Start(int,int);
        void AddNamePlayer(string);
        void ShuffleCard();
        void PlayerShowCard(Player*);
        void PlayerShowScore(Player*);
        void BotShowCard(Bot&);
        void BotShowScore(Bot&);
        void Winner(Player*, Bot*, Dealer*);
        void DealerShowCard(Dealer*);
        void DealerShowScore(Dealer*);
};

void Game::Start(int numbot,int round){

    int r = 0;
    Player *people = new Player;
    Bot *ai = new Bot[numbot];
    Dealer *dealer = new Dealer;
    bot = numbot;
    
    string name;
    cout << "::: Type your name ::: >> ";
    getline(cin,name);
    people->AssignName(name);

    for (int i=0; i<numbot; i++){
        ai[i].AssignNumberbot(i+1);
    }

    while(tryagain){
        system("cls");
        ShuffleCard();
        cout << "\n--------Turn "<< r+1 << "--------";
       
        for(int j=0; j<2; j++) people->ReceiveCard(GiveCard());

        for (int i=0; i<numbot; i++){
            for(int j=0; j<2; j++) ai[i].ReceiveCard(GiveCard());
        }

        for(int j=0; j<2; j++) dealer->ReceiveCard(GiveCard());

        //--------------------------------- โชว์ไพ่
        cout << "\n********* CARD & SCORE **********\n";
        people->SumScore(Cardpoint);
        PlayerShowCard(people);
        PlayerShowScore(people);

        for (int i=0; i<numbot; i++){
            ai[i].SumScore(Cardpoint);
            BotShowCard(ai[i]);
            BotShowScore(ai[i]);
        }

        dealer->SumScore(Cardpoint);
        DealerShowCard(dealer);
        DealerShowScore(dealer);

    
        cout << "\n********************************\n\n";
        
        // Blackjack Zone
        if(people->score == 21){
            cout << ">>>>>>>>>>>>>> "<< people->ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
            blackjack_flag = true;
        }else if(dealer->score == 21){
            cout << ">>>>>>>>>>>>>> "<< dealer->ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
            blackjack_flag = true;
        }else{
            for (int i=0; i<numbot; i++){
                if(ai[i].score == 21){
                    cout << ">>>>>>>>>>>>>> "<< ai[i].ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
                    blackjack_flag = true;
                }
            }
        }    
        //---------------------------------
        if(!blackjack_flag){
            people->GamePlay(CardId, Cardpoint, cardn);
            
            for (int i=0; i<numbot; i++){
                ai[i].GamePlay(CardId, Cardpoint, cardn);
            }

            dealer->GamePlay(CardId, Cardpoint, cardn);
        }

        Winner(people,ai,dealer);

        r++;
        while(true){
            if(r < round){
                cardn = 0;
                people->SetDefault();
                dealer->SetDefault();
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
                    cout << "Pressed [Y] to continue : ";
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
    delete people;
    delete dealer;
}

void Game::Winner(Player *people, Bot *ai, Dealer *dealer){
    cout << "\n------ SCREEN -------\n";
    
    if(blackjack_flag){
        if(people->score == 21){
            cout << "* " << people->ShowName() << " WIN\n";
        }else{
            cout << "* " << people->ShowName() << " LOST\n";
        }

        for (int count = 0; count<bot; count++){
            if(ai[count].score == 21){
                cout << "* " << ai[count].ShowName() << " WIN\n";
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
            }
        
        }
    }
    
    if(dealer->survival && !blackjack_flag){
        // ถ้า dealer ไม่แพ้
        if (people->survival)
        {
            if(people->score > dealer->score){
                cout << "* " << people->ShowName() << " WIN\n";
            }else if(people->score == dealer->score){
                cout << "* " << people->ShowName() << " DRAW\n";
            }else{
                cout << "* " << people->ShowName() << " LOST\n";
            }
        }else{
            cout << "* " << people->ShowName() << " LOST\n";
        }
        
        
        for (int count = 0; count<bot; count++){
            if(ai[count].survival){
                if(ai[count].score > dealer->score){
                    cout << "* " << ai[count].ShowName() << " WIN\n";
                }else if(ai[count].score == dealer->score){
                    cout << "* " << ai[count].ShowName() << " DRAW\n";
                }else{
                    cout << "* " << ai[count].ShowName() << " LOST\n";
                }
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
            }
        }
    }else if (!dealer->survival && !blackjack_flag){
        // ถ้า dealer แพ้
        // แล้วคะแนนผู้เล่นทุกคนน้อยกว่า 21 คือชนะไปเลย
        if (people->survival)
        {
            if(people->score <= 21){
                cout << "* " << people->ShowName() << " WIN\n";
            }else{
                cout << "* " << people->ShowName() << " LOST\n";
            }
        }else{
            cout << "* " << people->ShowName() << " LOST\n";
        }
        
        
        for (int count = 0; count<bot; count++){
            if(ai[count].survival){
                if(ai[count].score <= 21){
                    cout << "* " << ai[count].ShowName() << " WIN\n";
                }else{
                    cout << "* " << ai[count].ShowName() << " LOST\n";
                }
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
            }
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

void Game::PlayerShowCard(Player *people){
    if(people->survival) people->ShowCard(CardId);
}

void Game::PlayerShowScore(Player *people){
    if(people->survival) people->ShowScore();
}

void Game::BotShowCard(Bot &ai){
    if(ai.survival) ai.ShowCard(CardId);
}

void Game::BotShowScore(Bot &ai){
    if(ai.survival) ai.ShowScore();
}

void Game::DealerShowCard(Dealer *dealer){
    dealer->ShowCard(CardId);
}

void Game::DealerShowScore(Dealer *dealer){
    if(dealer->firstturn) dealer->ShowScore(Cardpoint);
    else dealer->ShowScore();
}
