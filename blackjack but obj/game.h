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

        vector<string> name;
        vector<int> indexplayersuvival;
        vector<int> indexbotsuvival;
        int player,bot,round;
        int cardn = 0;
        int check;
        int GiveCard();
        bool blackjack_flag = false;
        bool tryagain = true;
        bool checktwointerrupt = false;
        bool WhoSurvivalMoreover2(Player*, Bot*);
        void Start(int,int,int);
        void AddNamePlayer(string);
        void ShuffleCard();
        void PlayerShowCard(Player&);
        void PlayerShowScore(Player&);
        void BotShowCard(Bot&);
        void BotShowScore(Bot&);
        void Winner(Player*, Bot*);
        void DealerShowCard(Dealer&);
        void DealerShowScore(Dealer&);
};

void Game::Start(int numplayer,int numbot,int round){

    Player *people = new Player[numplayer];
    Bot *ai = new Bot[numbot];
    Dealer *DB = new Dealer[1];
    player = numplayer;
    bot = numbot;
     
    /////////////////////////////////////// กำหนดชื่อแต่ละคน
    cout << "::: Type your name :::\n";
    for (int i=0; i<numplayer; i++){
        string name;
        cout << "[" << 1 << "] ";
        getline(cin,name);
        AddNamePlayer(name);
    }

    for (int i=0; i<numplayer; i++){
        people[i].AssignName(name[i]);
    }
    for (int i=0; i<numbot; i++){
        ai[i].AssignNumberbot(i+1);
    }

    while(tryagain){
        system("cls");
        ShuffleCard();
        //////////////////////////////////////// แจกไพ่ก่อนเริ่มเกม

        for (int i=0; i<1; i++){
            for(int j=0; j<2; j++) DB[i].ReceiveCard(GiveCard());
        }
        for (int i=0; i<numplayer; i++){
            for(int j=0; j<2; j++) people[i].ReceiveCard(GiveCard());
        }
        for (int i=0; i<numbot; i++){
            for(int j=0; j<2; j++) ai[i].ReceiveCard(GiveCard());
        }

        ///////////////////////////////////////// GAMEPLAY

        while(WhoSurvivalMoreover2(people,ai)){

            //--------------------------------- โชว์ไพ่
            cout << "\n********* CARD & SCORE **********\n";
            for (int i=0; i<1; i++){
                DB[i].SumScore(Cardpoint);
                DealerShowCard(DB[i]);
                DealerShowScore(DB[i]);
            }

            for (int i=0; i<numplayer; i++){
                people[i].SumScore(Cardpoint);
                PlayerShowCard(people[i]);
                PlayerShowScore(people[i]);
            }
            for (int i=0; i<numbot; i++){
                ai[i].SumScore(Cardpoint);
                BotShowCard(ai[i]);
                BotShowScore(ai[i]);
            }
            cout << "\n********************************\n";
            //---------------------------------

            for (int i=0; i<numplayer; i++){
                if(people[i].blackjack){ // เช็คว่า blackjack รึเปล่าก่อนเริ่มเทิร์น
                    blackjack_flag = true;
                    break;
                }

                people[i].GamePlay(CardId, Cardpoint, cardn);

                if(people[i].blackjack){ // เช็คว่า blackjack รึเปล่าหลังจบเทิร์น
                    blackjack_flag = true;
                    break;
                }
            }
            if(numplayer==1 && numbot==1 && !people[0].survival) continue; //[Bug fix (temporary)] เมื่อเล่นคนเดียวกับบอท1ตัวแล้วแพ้ 
            if(blackjack_flag) break;
            
            for (int i=0; i<numbot; i++){
                if(ai[i].blackjack){ // เช็คว่า blackjack รึเปล่าก่อนเริ่มเกม
                    blackjack_flag = true;
                    break;
                }

                ai[i].GamePlay(CardId, Cardpoint, cardn);
                
                if(ai[i].blackjack){ // เช็คว่า blackjack รึเปล่าหลังจบเกม
                    blackjack_flag = true;
                    break;
                }
            }
            if(blackjack_flag) break;
        }

        ///////////////////////////////////////////

        Winner(people,ai);

        ///////////////////////////////////////////

        while(true){
            cout << "\nTry Again? [y/n]: ";
            string ck;
            getline(cin,ck);
            if(toupper(ck[0]) == 'Y'){
                tryagain = true;
                cardn = 0;
                for (int i=0; i<numplayer; i++) people[i].SetDefault();
                for (int i=0; i<numbot; i++) ai[i].SetDefault();
                DB[0].SetDefault();
                checktwointerrupt = false;
                blackjack_flag = false;
                indexplayersuvival.clear();
                indexbotsuvival.clear();
                break;
            }else if(toupper(ck[0]) == 'N'){
                tryagain = false;
                break;
            }else{
                cout << "Invalid Command !! Please type 'y' or 'n' only.";
                continue;
            }

        }

    }
    
    delete [] people;
    delete [] ai;
    delete DB;
}

void Game::Winner(Player *people, Bot *ai){
    //check who blackjack
    int count = 0;
    bool auth;
    bool flag_detect = false;
    for (; count<player; count++){
        if(people[count].blackjack){
            flag_detect = true;
            auth = true; //บอกว่าเป็น player
            break;
        }
    }

    if(!flag_detect){
        count = 0;
        for (; count<bot; count++){
            if(ai[count].blackjack){
                flag_detect = true;
                auth = false; //บอกว่าเป็น bot
                break;
            }
        }
    }

    //ถ้า flag_detect ยังเป็น false อยู่แสดงว่าไม่มีคนไหน blackjack
    if(flag_detect){
        string namewin;
        if(auth) namewin = people[count].ShowName();
        else namewin = ai[count].ShowName();
        cout << "\nvvvvvvvv  " << namewin << " Blackjack!!  vvvvvvvv\n";
        cout << "\n" << "@@@@@@@ The Winner This Game >> " << namewin << " << @@@@@@@\n";
    }else{
        vector<int> player_score;
        vector<int> bot_score;
        if(check==2){ // มี 2 คนที่เหลือรอด คะแนนใครมากกว่าก็ชนะ
            for(unsigned int i=0; i<indexplayersuvival.size(); i++) player_score.push_back(people[indexplayersuvival[i]].score);
            for(unsigned int i=0; i<indexbotsuvival.size(); i++)    bot_score.push_back(ai[indexbotsuvival[i]].score);

            if(player_score.size() > bot_score.size()){ //ฝั่งที่รอดเป็น player
                if(player_score[0] > player_score[1]){
                    cout << "!!!!!  " << people[indexplayersuvival[1]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << people[indexplayersuvival[0]].ShowName() << " << @@@@@@@\n";
                }else if (player_score[0] == player_score[1]){
                    cout << "\n" << "@@@@@@@       Draw!!!     @@@@@@@A2\n";
                }else{
                    cout << "!!!!!  " << people[indexplayersuvival[0]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << people[indexplayersuvival[1]].ShowName() << " << @@@@@@@\n";
                }
            }else if(player_score.size() == bot_score.size()){ //มีฝั่ง player 1 คน และ bot 1 ตัว
                if(player_score[0] > bot_score[0]){
                    cout << "!!!!!  " << ai[indexbotsuvival[0]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << people[indexplayersuvival[0]].ShowName() << " << @@@@@@A\n";
                }else if (player_score[0] == bot_score[0]){
                    cout << "\n" << "@@@@@@@       Draw!!!     @@@@@@A1\n";
                }else{
                    cout << "!!!!!  " << people[indexplayersuvival[0]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << ai[indexbotsuvival[0]].ShowName() << " << @@@@@@B\n";
                }
            }else{ //ฝั่งที่รอดเป็น bot
                if(bot_score[0] > bot_score[1]){
                    cout << "!!!!!  " << ai[indexbotsuvival[1]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << ai[indexbotsuvival[0]].ShowName() << " << @@@@@@C\n";
                }else if (bot_score[0] == bot_score[1]){
                    cout << "\n" << "@@@@@@@       Draw!!!     @@@@@@B2\n";
                }else{
                    cout << "!!!!!  " << ai[indexbotsuvival[0]].ShowName() << " lost  !!!!!\n";
                    cout << "\n" << "@@@@@@@ The Winner This Game >> " << ai[indexbotsuvival[1]].ShowName() << " << @@@@@@D\n";
                }
            }

        }else{  // มีคนเดียวที่รอด คนนั้นแหละชนะ
            if(indexplayersuvival.size() > indexbotsuvival.size()){
                cout << "\n" << "@@@@@@@ The Winner This Game >> " << people[indexplayersuvival[0]].ShowName() << " << @@@@@@E\n";
            }else{
                cout << "\n" << "@@@@@@@ The Winner This Game >> " << ai[indexbotsuvival[0]].ShowName() << " << @@@@@@F\n";
            }
        }
        /*
        
        ตัวอักษรที่อยู่ข้างหลัง เอาไว้ debug เฉยๆนะ บางที่ก็ไม่รู้ว่ามันเข้าไปในเงื่อนไขไหน 5555 ถ้าเทสทั้งหมดแล้วบัคมีน้อยจริงๆค่อยลบทิ้ง
        
        */
    }
}

void Game::AddNamePlayer(string tempname){
    name.push_back(tempname);
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
    ai.ShowScore();
}

void Game::DealerShowScore(Dealer &dealer){
    if(dealer.firstturn) dealer.ShowScore(Cardpoint);
    else dealer.ShowScore();
}

void Game::DealerShowCard(Dealer &dealer){
    dealer.ShowCard(CardId);
}

bool Game::WhoSurvivalMoreover2(Player *people, Bot *ai){ // func นี้เอาไว้เช็คว่าเหลือผู้เล่นกับบอทกี่คนแล้ว จนกว่าจะเหลือ2 (มีผลใน loop gameplay)
    int checker = 0;
    for (int i=0; i<player; i++){
        if(people[i].survival){
            indexplayersuvival.push_back(i);
            checker++;
        }
    }
    for (int i=0; i<bot; i++){
        if(ai[i].survival){
            indexbotsuvival.push_back(i);
            checker++;
        }
    }

    if(checker>2){
        indexplayersuvival.clear();
        indexbotsuvival.clear();
        return true;
    }else if(checker==2 && !checktwointerrupt){ // ถ้าเหลือ2คน แล้วจะให้แข่งอีกรอบ แต่ถ้ายังเหลือ2คนเหมือนเดิม ก็จะหลุดไปทำงานใน else
        indexplayersuvival.clear();
        indexbotsuvival.clear();
        check = checker;
        checktwointerrupt = true;
        return true;
    }else{
        check = checker;
        return false;
    }
}
