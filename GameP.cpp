#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
/*

REFERENCE
--------------
? change text console colour                        ::  https://youtu.be/MvX4tVETjHk
? press LEFT,RIGHT arrow button without ENTER key   ::  https://www.geeksforgeeks.org/getch-function-in-c-with-examples/

*/
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

int main()
{
    GameP();
    return 0;
}
