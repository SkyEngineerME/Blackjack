#include "game.h"

bool menu();

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
       /* while (true)
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
        }*/
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
        cin >> round;
        while(round < 1 || round > 50){
            cout << "!!! Please choose between [1-50] !!!\n";
            cout <<"Round: ";
            cin >> round;
        }

        cin.ignore();
        obj.Start(1,numbot,round);
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
