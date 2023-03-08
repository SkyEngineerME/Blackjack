#include <iostream>
#include <string>
using namespace std;

void win(int p1,int p2 ,int p3,int p4){
    int score[]={p1,p2,p3,p4};
    int n = sizeof(score)/sizeof(score[0]);
    int max=p1,loc=0;
    for(int i = 0;i<n;i++){
        if(max<score[i]){
            max = score[i];
            loc = i;
        }
    }
    for(int i=0;i<n;i++){
    if(score[i]==max){
        cout << "player["<<i+1<<"] win"<<endl;
        }
    }
}

int main(){
    win(0,200,500,20);
}