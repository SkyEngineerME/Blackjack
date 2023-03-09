#include <iostream>
#include <string>
using namespace std;

void CheckScore(int Ds,int Ps,int B1s,int B2s,int B3s,int &conditionPs,int &conditionB1s,int &conditionB2s,int &conditionB3s){
 int conditionDs = 3,conditionPs = 3,conditionB1s = 3,conditionB2s = 3,conditionB3s = 3;
 if(Ds>21){
    if(Ps<Ds){
        conditionPs=0;
        cout << "Player : win"<<endl;
    }else if(Ps>21){
        conditionPs=1;
        cout << "Player : draw"<<endl;
    }
    if(B1s<Ds && B1s != 0){
        conditionB1s=0;
        cout << "Bot1 : win"<<endl;
    }else if(B1s>21){
        conditionB1s=1;
        cout << "Bot1 : draw"<<endl;
    }
    if(B2s<Ds && B2s != 0){
        conditionB2s=0;
        cout << "Bot2 : win"<<endl;
    }else if(B2s>21){
        conditionB2s=1;
        cout << "Bot2 : draw"<<endl;
    }
    if(B3s<Ds && B3s != 0){
        conditionB3s=0;
        cout << "Bot3 : win"<<endl;
    }else if(B3s>21){
        conditionB3s=1;
        cout << "Bot3 : draw"<<endl;
    }
 }else{
    if(Ps>Ds && Ps <= 21){
        conditionPs=0;
        cout << "Player : win"<<endl;
    }else if(Ps==Ds){
        conditionPs=1;
        cout << "Player : draw"<<endl;
    }else if(Ps<Ds){
        conditionPs=2;
        cout << "Player : lose"<<endl;
    }else{
        conditionPs=2;
        cout << "Player : lose"<<endl;
    }
    if(B1s>Ds && B1s <= 21){
        conditionB1s=0;
        cout << "Bot1 : win"<<endl;
    }else if(B1s==Ds){
        conditionB1s=1;
        cout << "Bot1 : draw"<<endl;
    }else if(B1s<Ds){
        conditionB1s=2;
        cout << "Bot1 : lose"<<endl;
    }else{
        conditionB1s=2;
        cout << "Bot1 : lose"<<endl;
    }
    if(B2s>Ds && B2s <= 21){
        conditionB2s=0;
        cout << "Bot2 : win"<<endl;
    }else if(B2s==Ds){
        conditionB2s=1;
        cout << "Bot2 : draw"<<endl;
    }else if(B2s<Ds){
        conditionB2s=2;
        cout << "Bot2 : lose"<<endl;
    }else{
        conditionB2s=2;
        cout << "Bot2 : lose"<<endl;
    }
    if(B3s>Ds && B3s <= 21){
        conditionB3s=0;
        cout << "Bot3 : win"<<endl;
    }else if(B3s==Ds){
        conditionB3s=1;
        cout << "Bot3 : draw"<<endl;
    }else if(B3s<Ds){
        conditionB3s=2;
        cout << "Bot3 : lose"<<endl;
    }else{
        conditionB3s=2;
        cout << "Bot3 : lose"<<endl;
    }
 }
}