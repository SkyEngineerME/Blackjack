#include<iostream>
using namespace std;

void ShowCard(string *s,string name){
    cout << name << "Hand: "; 
    int i = 0;
    while(s[i] != "") {
       cout << s[i] << " ";
       i++;
    }
}

void ShowCardEx(int *s,string name){
    cout << name << "Hand: "; 
    int i = 0;
    while(*(s+i) != 0) {
       cout << s[i] << " ";
       i++;
    }
}

int main() {
    const int N = 10;
    string Hand[N] = {"A","10","K"};
    string *s = Hand;
    ShowCard(s,"Karn");
    return 0;
}