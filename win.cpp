#include <iostream>
#include <string>
using namespace std;

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

int main(){
    Win(22,22,22,34);
}