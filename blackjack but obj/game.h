#include <string>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cctype>
#include <fstream>
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

        int bot,round;
        int cardn = 0;
        int GiveCard();
        bool blackjack_flag = false;
        bool tryagain = true;
        bool checktwointerrupt = false;
        void Start(int,int);
        void ShuffleCard();
        void PlayerShowCard(Player*);
        void PlayerShowScore(Player*);
        void BotShowCard(Bot&);
        void BotShowScore(Bot&);
        void Winner(Player*, Bot*, Dealer*);
        void DealerShowCard(Dealer*);
        void DealerShowScore(Dealer*);
        void ResultGame(Player*, Bot*);
        void WriteScoreboard(Player*);
        void Checkmoney(int &,int &,int);
};

void Game::Start(int numbot,int round){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int counter = 0;
    Player *people = new Player;
    Bot *ai = new Bot[numbot];
    Dealer *dealer = new Dealer;

    for (int i=0; i<numbot; i++){
        ai[i].AssignNumberbot(i+1);
    }

    while(tryagain){
        system("cls");
        srand(time(0));
        bot = numbot;

        people->PlayerBet();
        SetConsoleTextAttribute(h,13);
        cout << "------------------------------------\n";
        for (int i=0; i<numbot; i++) ai[i].BotBet();
        cout << "------------------------------------\n";
        SetConsoleTextAttribute(h,7);

        cout << "\nPressed [Y] to continue .. " << '\r';
            int key = _getch();
            if(key == 121 || key == 89){
                system("cls");
            }
            else{
                while(true){
                    cout << "Invalid Command !! Please Pressed [Y] to continue .. " << '\r';
                    int key = _getch();
                    if(key == 121 || key == 89){
                        system("cls");
                        break;
                    }
                }
            }

        ShuffleCard();
        cout << "\n----------------------";
        cout << "\n|       Turn "<< counter+1 << "       |";
        cout << "\n----------------------\n";
       
        //--------------------------------- ????????????????????????
        for(int j=0; j<2; j++) people->ReceiveCard(GiveCard());
        for (int i=0; i<numbot; i++) for(int j=0; j<2; j++) ai[i].ReceiveCard(GiveCard());
        for(int j=0; j<2; j++) dealer->ReceiveCard(GiveCard());

        //--------------------------------- ?????????????????????
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

    
        cout << "\n********************************\n";
        
        //--------------------------------- ????????????????????????????????? blackjack ?????????????????????????????????????????????
        if(people->score == 21){
            cout << "\n>>>>>>>>>>>>>> "<< people->ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
            blackjack_flag = true;
        }
        if(dealer->score == 21){
            cout << "\n>>>>>>>>>>>>>> "<< dealer->ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
            blackjack_flag = true;
        }
        for (int i=0; i<numbot; i++){
            if(ai[i].score == 21){
                cout << "\n>>>>>>>>>>>>>> "<< ai[i].ShowName() <<" Blackjack!! <<<<<<<<<<<<<\n";
                blackjack_flag = true;
            }
        }
            
        //--------------------------------- GAMEPLAY
        if(!blackjack_flag){
            people->GamePlay(CardId, Cardpoint, cardn);
            
            for (int i=0; i<numbot; i++){
                ai[i].GamePlay(CardId, Cardpoint, cardn);
            }

            dealer->GamePlay(CardId, Cardpoint, cardn);
        }

        //--------------------------------- ????????????????????????????????????
        Winner(people,ai,dealer);
        //---------------------------------
        
        counter++;
        if(counter >= round){
            ResultGame(people,ai);
            WriteScoreboard(people);
            cout << "\nGo to HOMEPAGE [Y] .. " << '\r';
            int key = _getch();
            if(key == 121 || key == 89){
                tryagain = false;
            }
            else{
                while(true){
                    cout << "Invalid Command !! Please Pressed [Y] to continue .. " << '\r';
                    int key = _getch();
                    if(key == 121 || key == 89){
                        tryagain = false;
                        break;
                    }
                }
            }
        }else{
            cardn = 0;
            people->SetDefault();
            dealer->SetDefault();
            for (int i=0; i<numbot; i++) ai[i].SetDefault();
            blackjack_flag = false;

            cout << "\nPressed [Y] to continue .. " << '\r';
            int key = _getch();
            if(key == 121 || key == 89){
                tryagain = true;
            }
            else{
                while(true){
                    cout << "Invalid Command !! Please Pressed [Y] to continue .. " << '\r';
                    int key = _getch();
                    if(key == 121 || key == 89){
                        tryagain = true;
                        break;
                    }
                }
            }
        }
    }
    delete [] ai;
    delete people;
    delete dealer;
}
    void Game::Checkmoney(int &moneyPlayer,int &Betplayer,int condition){
    if(condition == 0){
        cout << "Got" << endl;
        moneyPlayer += Betplayer*2;
    }else if(condition == 1){
        cout << "Draw" << endl;
        moneyPlayer += Betplayer;
    }
    else{
        cout << "Lose" << endl;
    }

    }
void Game::Winner(Player *people, Bot *ai, Dealer *dealer){
    cout << "\n------ SCREEN -------\n";
    
    if(blackjack_flag){
        // ???????????????????????? blackjack ????????????????????? ???????????????????????????
        // ???????????????????????? ????????????????????????????????????????????? dealer ????????????????????????????????????
        if(people->score == 21){
            cout << "* " << people->ShowName() << " WIN\n";
        }else if(people->score > dealer->score){
            cout << "* " << people->ShowName() << " WIN\n";
        }else if(people->score == dealer->score){
            cout << "* " << people->ShowName() << " DRAW\n";
        }else{
            cout << "* " << people->ShowName() << " LOST\n";
        }
        Checkmoney(people->bet,people->bet,people->cond);



        for (int count = 0; count<bot; count++){
            if(ai[count].score == 21){
                cout << "* " << ai[count].ShowName() << " WIN\n";
            }else if(ai[count].score > dealer->score){
                cout << "* " << ai[count].ShowName() << " WIN\n";
            }else if(ai[count].score == dealer->score){
                cout << "* " << ai[count].ShowName() << " DRAW\n";
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
            }
        }
    }
    
    if(dealer->survival && !blackjack_flag){
        // ????????????????????? dealer ????????? lost
        people->cond = 3;
        if (people->survival)
        {
            if(people->score > dealer->score){
                cout << "* " << people->ShowName() << " WIN\n";
                people->cond = 0;
            }else if(people->score == dealer->score){
                cout << "* " << people->ShowName() << " DRAW\n";
                people->cond = 1;
            }else{
                cout << "* " << people->ShowName() << " LOST\n";
                people->cond = 2;
            }
        }else{
            cout << "* " << people->ShowName() << " LOST\n";
            people->cond = 2;
        }
        Checkmoney(people->money,people->bet,people->cond);
        
        
        for (int count = 0; count<bot; count++){
            if(ai[count].survival){
                if(ai[count].score > dealer->score){
                    cout << "* " << ai[count].ShowName() << " WIN\n";
                    ai[count].cond = 0;
                }else if(ai[count].score == dealer->score){
                    cout << "* " << ai[count].ShowName() << " DRAW\n";
                    ai[count].cond = 1;
                }else{
                    cout << "* " << ai[count].ShowName() << " LOST\n";
                    ai[count].cond = 2;
                }
            }else{
                cout << "* " << ai[count].ShowName() << " LOST\n";
                ai[count].cond = 2;
            }
            Checkmoney(ai[count].money,ai[count].bet,ai[count].cond);
        }
    }else if (!dealer->survival && !blackjack_flag){
        // ????????? dealer lost
        // ??????????????????????????????????????????????????????????????????????????????????????? 21 ?????????????????????????????????
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
    dealer->ShowScore();
}

void Game::ResultGame(Player* p, Bot* b){ // ??????????????????????????????????????? TT
    cout << "\n&&&&&&&&& RESULT THIS GAME &&&&&&&&&\n\n";
    string name;
    vector<int> score;
    score.push_back(p->money);
    for(int k=0; k<bot; k++){
        score.push_back(b[k].money);
    }

    int max=score[0],loc=0;
    for(unsigned int i=0; i<score.size(); i++){
        if(max<score[i]){
            max = score[i];
            loc = i;
        }
    }
    for(unsigned int i=0; i<score.size(); i++){
        if(score[i]==max){
            if(i == 0) name = p->ShowName();
            else name = b[i].ShowName();
            cout << "            " << name << " WIN!!!" << endl;
            cout << "            " << "MONEY : " << max << endl;
        }
    }

    cout << "\n\n      My Current Money = " << p->money;
    cout << "\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
}

void Game::WriteScoreboard(Player *p){
    ofstream output("scoreboard.txt", ios::app);
    output << '\n' << p->ShowName() << ',' << p->money; 
    output.close();  
}
