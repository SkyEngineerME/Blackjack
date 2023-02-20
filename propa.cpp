#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string CardId[52] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

int Cardpoint[52] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10,
                     1,2,3,4,5,6,7,8,9,10,10,10,10};

void shuffle(string cardID[], int n)
{
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52 -i));
        swap(cardID[i], cardID[r]);
        swap(Cardpoint[i],Cardpoint[r]);
    }
}

int Givecard(string CardID[],int &cardn)
{
    ++cardn;
    return cardn-1;
}

bool Propa(int handbot[]){ //true = drawnewcard
    int ace = 0;
    int sum = 0;
    for (int i = 0; i < 2; i++)
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

int main()
{
    srand(time(0));
    int cardn = 0;
    shuffle(CardId, 52);
    int playerhand[10] = {Givecard(CardId,cardn),Givecard(CardId,cardn)};
    int bothand[10] = {Givecard(CardId,cardn),Givecard(CardId,cardn)};
    cout <<'\n' <<CardId[playerhand[0]] <<' '<<playerhand[0] <<endl;
    cout << CardId[playerhand[1]] <<' '<<playerhand[1] <<endl;
    return 0;

}


// Reference:https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/