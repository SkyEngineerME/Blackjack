#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string CardId[52] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K",
                     "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

void shuffle(string cardID[], int n)
{
    srand(time(0));
    for (int i=0; i<52 ;i++){
        int r = i + (rand() % (52 -i));
        swap(cardID[i], cardID[r]);
    }
}
string Givecard(string CardID[],int &cardn)
{
    ++cardn;
    return CardID[cardn-1];
}

int main()
{
    int cardn = 0;
    shuffle(CardId, 52);
    cout << Givecard(CardId,cardn) << endl;
    cout << Givecard(CardId,cardn) << endl;
  
  
    return 0;
}


// Reference:https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/