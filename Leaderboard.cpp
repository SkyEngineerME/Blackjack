#include <iostream>
#include <fstream>
using namespace std;

void Leaderboard(){
    ifstream infile("Leaderboard.txt");
    ofstream oufile("Leaderboard.txt");
    cout << "LeaderBoard" << endl;
    cout << "N "<< "Name " << "Score" << endl;
    string name;
    int money = 70;
    while (getline(infile,name)){
        cout << name << endl;
    }
    getline(cin,name);
    oufile << name << endl;
    while (getline(infile,name)){
        cout << name << endl;
    }

    oufile.close();
    infile.close();

}
int main()
{
    /*ifstream infile("Leaderboard.txt");
    ofstream oufile("Leaderboard.txt");
    oufile << "Leaderboardbggh" << endl;
    string textline;
    while 
    getline(infile, textline);
    cout << textline;

    infile.close();
    oufile.close();*/

    Leaderboard();

    return 0;
}