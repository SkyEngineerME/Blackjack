#include "game.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>

bool menu();
void ShowScoreBoard();

bool compare(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

int main(){
    bool selectplay;
    selectplay = menu();

    while(selectplay){
        srand(time(0));
        Game obj;
        string input;
        int numbot;//numplayer
        int round;
        bool flagfour = false;
        system("cls");
        cout << "----------------  Game init  ----------------\n";
        cout << "Choose bot between [1-3]" << " Unit.\n";
        while (!flagfour)
        {
            cout << "Number of Bot : ";
            input = '\0';
            getline(cin,input);
            if(input.size() > 1 || isdigit(input[0]) == false){
                cout << input.size() << ' ' << isdigit(input[0]);
                cout << "Invalid Input !! Please type number [1-" << (4 - 1) << "]\n"; 
            }else{
                numbot = stoi(input);
                if(numbot < 1 || numbot > (4-1)) cout << "Invalid Input !! Please type number [1-" << (4 - 1) << "]\n";
                else break;
            }
        }
        cout << "::: How many round you want to play between [1-50] :::\n";
        cout <<"Round: ";
        cin >> round; // เจอ bug นะ ใส่อะไรที่ไม่ใช่เลขแล้วมันค้าง
        while(round < 1 || round > 50){
            cout << "!!! Please choose between [1-50] !!!\n";
            cout <<"Round: ";
            cin >> round;
        }

        cin.ignore();
        obj.Start(numbot,round);
        selectplay = menu();
    }


}

bool menu(){
    system("cls");
    cout << "-------------  BLACKJACK  ---------------\n";
    cout << "|                                       |\n";
    cout << "|             [N] NewGame               |\n";
    cout << "|             [E] Exit                  |\n";
    cout << "|                                       |\n";
    cout << "-----------------------------------------\n";
    ShowScoreBoard();
    while (true){
        int key = _getch();
        if (key == 110 || key == 78){
            return true;
        }else if (key == 211 || key == 174 || key == 101 || key == 69){
            return false;
        }else{
            cout << "Invalid Command !! Please Pressed [Y] or [E] to continue .. " << '\r';
        }
    }
}

void ShowScoreBoard(){ // concept support by ChatGPT
    ifstream input("scoreboard.txt");
    string textline;
    vector<int> money;
    vector<string> name;
    while (getline(input,textline)){
        int cash;
        char temp[100];
        char format[] = "%[^,],%d";
        sscanf(textline.c_str(), format, temp, &cash);
        name.push_back(temp);
        money.push_back(cash);
    }
    input.close();
    vector<pair<int, string>> sorteddata(name.size());    

    for(unsigned int i=0; i<money.size(); i++){
        sorteddata[i] = make_pair(money[i], name[i]);
    }

    sort(sorteddata.begin(), sorteddata.end(), compare);
    
    for(unsigned int i=0; i<money.size(); i++){
        money[i] = sorteddata[i].first;
        name[i] = sorteddata[i].second;
    }

    cout << "********  SCOREBOARD  ********\n";
    cout << "NAME" << "\t\t\t" << "MONEY" << '\n'; 
    for(unsigned int i=0; i<money.size(); i++){
        cout << "[" << i+1 << "] " << name[i] << setw(24-name[i].length()) << money[i] << "$\n"; 
    }
    cout << "******************************\n";

}
