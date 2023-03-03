#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

void GameP();
void shuffle(string);
void GiveCard(vector<string> ,vector<int> ,int& );
void Dealer();
void Stat(int,string,bool);
void Stat();
void BetB(int[],int[],int);
void BetP(int&);
void GameB(vector<int> &, bool &, int &, int &);
void GameP();
bool Propa(vector<int> );
void ShowCard(string *,string );
void Win(int p1,int p2,int p3,int p4);


string CardId[52] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

int Cardpoint[52] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10};

vector<int> Dealerpoint;
vector<string> Dealercard;
int n = 0;//นับการ์ดที่จั่วไป


int main()
{


    return 0;
}












































void Win(int p1,int p2,int p3,int p4){
    int score[]={p1,p2,p3,p4};
    int n = sizeof(score)/sizeof(score[0]);
    int win[4];
    int min = abs(score[0]-21);
    int loc[]={0,0,0,0};
    int p=0;
    for(int a  = 0;a<n;a++){
        win[a] = abs(score[a]-21);
        if(min>win[a]){
            min = win[a];
            p = a;  
            }
    }
    for(int i = 0;i<n;i++){
        if(min<win[i]){
            loc[p] = 1;
        }
        if(min == win[i]){
            loc[i]=1;
        }
    }
    for(int k = 0;k<n;k++){
        if(loc[k]==1){
            cout << "p" << k+1 << " win ";
            }
        }
}

void ShowCard(string *s,string name){
    cout << name << "Hand: "; 
    int i = 0;
    while(s[i] != "") {
       cout << s[i] << " ";
       i++;
    }
}

bool Propa(vector<int> handbot){ //true = drawnewcard
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
    int ran = rand()%100 + 1;
    cout <<ace <<' '<<sum<<' ';
    if ((21-sum)>= 10)
    {
        return true;
    }else if (((21-sum)/10.0*100)>=(ran))
    {
        return true;
    }else{
        return false;
    }
}

void GameP(){
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
                break;
            }else{
                SetConsoleTextAttribute(console,2);
                cout << "You selected: ";
                SetConsoleTextAttribute(console,4);
                cout << "Stand";
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

void BetP(int &moneyp){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,14);
    cout << "----888-------------------------888----\n";
    cout << "$$$ Put Your Money To Bet Your Fate $$$\n";
    cout << "----888-------------------------888----\n\n";

    while(true){
    SetConsoleTextAttribute(h,14);
    cout << "Put your money (You have left ";
    SetConsoleTextAttribute(h,5);
    cout << moneyp << "$";
    SetConsoleTextAttribute(h,14);
    cout << ") : ";

    string text;
    getline(cin,text);
    double betp = atof(text.c_str());
    if(betp > 0 && betp <= moneyp && betp - (int) betp == 0) {
        moneyp = moneyp-betp;
        SetConsoleTextAttribute(h,10);
        cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        cout << "You bet ";
        SetConsoleTextAttribute(h,3);
        cout << betp << "$ ";
        SetConsoleTextAttribute(h,10);
        cout << "(You have left now ";
        SetConsoleTextAttribute(h,4);
        cout << moneyp << "$";
        SetConsoleTextAttribute(h,10);
        cout << ")\n\n";
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
        SetConsoleTextAttribute(h,7);
        break;
    }
    else if(betp > moneyp){
        SetConsoleTextAttribute(h,4);
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "$$$ Are you serious? You put money more than you have! Try again the poor!!! $$$\n";
        cout << "--------------------------------------------------------------------------------\n\n";
    }
    else if(betp - (int) betp != 0) {
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

void BetB(int moneyb[], int betb[], int Nbot = 1)
{

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));
    SetConsoleTextAttribute(h,13);
    cout << "------------------------------------\n";
    for(int i = 0; i < Nbot; i++){
        betb[i] = (moneyb[i]/10)*(rand()%9 + 1);
        moneyb[i] = moneyb[i] - betb[i];
        SetConsoleTextAttribute(h,13);
        cout << "Bot No." << i+1 << " bets ";
        SetConsoleTextAttribute(h,3);
        cout << betb[i] << "$ ";
        SetConsoleTextAttribute(h,13);
        cout << "(left ";
        SetConsoleTextAttribute(h,4);
        cout << moneyb[i] <<"$";
        SetConsoleTextAttribute(h,13);
        cout << ")\n";

    }
    cout << "------------------------------------\n";
    SetConsoleTextAttribute(h,7);
}

void Stat(int point,string name,bool condition )
{
    int a ,n=0;
    string filedata ,conditionstring ;
    
    if(condition == true) conditionstring = "W"; 
    else conditionstring = "L";

    ifstream infile("StatBlackjack.txt");
    ofstream oufile("StatBlackjack.txt",ios::app);

    while (getline(infile,filedata)){
        a = atoi(filedata.c_str());
    }
    if(a == 6422260) a = -1;
    n = a+1;
    oufile << n <<" | "<< name << " | "<< point << " | "<< conditionstring << endl;

    oufile.close();
    infile.close();

}

void Stat()
{

    string filedata;
    ifstream infile("StatBlackjack.txt");
    ofstream oufile("StatBlackjack.txt",ios::app);
    cout << "LeaderBoard" << endl;
    cout << "N  |"<< "  Name  |" << "  Score  |" << "  Condition  |"<< endl;
    cout << "-------------------------------------"<<endl;
    while (getline(infile,filedata)){
        cout << filedata << endl;
    }
    oufile.close();
    infile.close();

}

void shuffle(string cardID[])
{
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52 -i));
        swap(cardID[i], cardID[r]);
        swap(Cardpoint[i],Cardpoint[r]);
    }
}

void GiveCard(vector<string> &ID,vector<int> &Point,int &cardn){
    ID.push_back(CardId[n]);
    Point.push_back(Cardpoint[n]);
    ++cardn;
}

void Dealer()
{
   // int i = 0; //รอฟังก์ชั่นความน่าจะเป็น
    while(true){
      GiveCard(Dealercard,Dealerpoint,n);
    }   
}

void GameP()
{
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
                break;
            }else{
                SetConsoleTextAttribute(console,2);
                cout << "You selected: ";
                SetConsoleTextAttribute(console,4);
                cout << "Stand";
                break;
            }
        }
    }
}