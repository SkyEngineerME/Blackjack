#include "game.h"

bool menu();

int main(){
    bool selectplay;
    selectplay = menu();

    while(selectplay){
        srand(time(0));
        Game obj;
        string input;
        int numplayer,numbot;
        bool flagfour = false;
        system("cls");
        cout << "----------------  Game init  ----------------\n";
        while (true)
        {
            cout << "Number of Player : ";
            getline(cin,input);
            if(input.size() > 1 || isdigit(input[0]) == false){
                cout << "Invalid Input !! Please type number [1-4]\n"; 
            }else{
                numplayer = stoi(input);
                if (numplayer == 4){
                    flagfour = true;
                    break;
                } 
                else if(numplayer < 1 || numplayer > 4) cout << "Invalid Input !! Please type number [1-4]\n";
                else break;
            }
        }
        if (!flagfour) cout << "\nYou can choose up to " << (4 - numplayer) << " more bots only.\n";
        while (!flagfour)
        {
            cout << "Number of Bot : ";
            input = '\0';
            getline(cin,input);
            if(input.size() > 1 || isdigit(input[0]) == false){
                cout << input.size() << ' ' << isdigit(input[0]);
                cout << "Invalid Input !! Please type number [0-" << (4 - numplayer) << "]\n"; 
            }else{
                numbot = stoi(input);
                if(numbot < 0 || numbot > (4-numplayer)) cout << "Invalid Input !! Please type number [0-" << (4 - numplayer) << "]\n";
                else break;
            }
        }

        obj.Start(numplayer,numbot);
        selectplay = menu();
    }


}

bool menu(){
    system("cls");
    cout << "-------------  Main Menu  ----------------\n";
    bool hit = true;
    cout << "\t[*] NewGame ";
    cout << "or";
    cout << " [ ] Exit" << '\r';
    while (true){
        int key = _getch();
        if (key == 224){
            key = _getch();
            if(key == 75){ // Left arrow key
                cout << "\t[*] NewGame ";
                cout << "or";
                cout << " [ ] Exit" << '\r';
                hit = true;
            }else if(key == 77){ // Right arrow key
                cout << "\t[ ] NewGame ";
                cout << "or";
                cout << " [*] Exit" << '\r';
                hit = false;
            }
        }else if (key == 13){ // Enter Key
            if(hit){
                return true;
            }else{
                return false;
            }
        }
    }
}
