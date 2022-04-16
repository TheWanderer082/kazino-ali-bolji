#include<iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

#define pb push_back

using namespace std;

int main()
{
    srand(time(0));

    vector<int> a;
    for (int i = 1; i <= 52; i++){
        a.pb(i);
    }
    vector<int> karte;
    int counter = 1;

    for (int i = 0; i < 52; i++){
        int velicina = a.size();
        int index = rand() % velicina;
        int nabodi_bre_broj = a[index] + 1;

        auto it = a.begin() + index;

        a.erase(it);
        nabodi_bre_broj = nabodi_bre_broj % 13;
        if (nabodi_bre_broj == 0){
            nabodi_bre_broj = 13;
        }
        if (nabodi_bre_broj > 10){
            nabodi_bre_broj = 10;
        }
        karte.pb(nabodi_bre_broj);
    }

    cout << "WELCOME TO BLACKJACK\n";

    int red = 51; int zbir;
    cout << "Pocetne karte su: " << karte[red--] << " i " << karte[red--] << "\n";

    zbir = karte[51] + karte[50];
    while (1){
        cout << "Zbir je: " << zbir << "\n";
        if (zbir == 21){
            cout << "COnGrats u won\n";
            return 0;
        }
        if (zbir > 21){
            cout << "oh No u lost, better luck next time\n";
            return 0;
        }
        string sin;
        cout << "hit or stand\n";
        cin >> sin;
        if (sin == "hit"){
            zbir = zbir + karte[red--];
        }
        else if (sin == "stand"){
            int kuca = karte[red--];
            while (kuca <= 21){
                cout << "Kuca je na: "<< kuca << "\n";
                kuca = kuca + karte[red--];
                if (kuca > zbir && kuca <= 21){
                    cout << "house always wins.\n";
                    return 0;
                }
            }
            cout << "youuuuu always win\n";
            return 0;
        }
    }
}
