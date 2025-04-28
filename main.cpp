#include<bits/stdc++.h>
#include <random>
using namespace std;
int hra() {
    int pocet_barev, opakovani_barev, pocet_policek, presna_pozice, moznsot_odhalit_reseni;
    cout << "Enter the number of colors you want to play with (5-8)." << '\n';
    cin >> pocet_barev;
    if(pocet_barev < 5 || pocet_barev > 8) {
        cout << "Invalid number of colors.";
        return 0;
    }
    cout << "Do you want to allow repeating colors? (1 = YES, 0 = NO)?" << '\n';
    cin >> opakovani_barev;
    if(opakovani_barev < 0 || opakovani_barev > 1) {
        cout << "Invalid repeat colors setting." << '\n';
        return 0;
    }
    cout << "How many slots do you want in a row (4-5)?" << '\n';
    cin >> pocet_policek;
    if(pocet_policek < 4 || pocet_policek > 5) {
        cout << "Invalid number of slots." << '\n';
        return 0;
    }
    cout << "Which evaluation mode do you want? (0 = exact position, 1 = any position)?" << '\n';
    cin >> presna_pozice;
    if(presna_pozice < 0 || presna_pozice > 1) {
        cout << "Invalid evaluation mode." << '\n';
        return 0;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> generator(1, pocet_barev);
    unordered_set<int> vybrana_cisla;
    int nahodne_cislo;
    vector<int> hledana_rada(pocet_policek);
    for(int i = 0; i < pocet_policek; i++) {
        nahodne_cislo = generator(gen);
        while(vybrana_cisla.find(nahodne_cislo) != vybrana_cisla.end()) {
            nahodne_cislo = generator(gen);
        }
        hledana_rada[i] = nahodne_cislo;
        if(!opakovani_barev) {
            vybrana_cisla.insert(nahodne_cislo);
        }
    }
    int pocet_pokusu = 1, p, odhaleni_reseni, pokus_index;
    vector<int> pokus(pocet_policek);
    if(pocet_policek == 4) {
        cout << "Enter your guess like this: 1 2 3 4" << '\n';
    } else {
        cout << "Enter your guess like this: 1 2 3 4 5" << '\n';
    }
    cout << "In the evaluation, 0 means the color is not present, 1 means the color is at a different position, and 2 means the color is correctly placed." << '\n';
    vector<vector<int>> vsechny_pokusy(11, vector<int>(1)), vsechny_vyhodnoceni(11, vector<int>(1));
    bool vyhra = false;
    while(pocet_pokusu < 11) {
        vector<int> vyhodnoceni_counter({0, 0, 0}), vyhodnoceni(pocet_policek), vyuziti_hledane_rady(pocet_policek), vyuziti_pokusu(pocet_policek);
        for(int i = 0; i < pocet_policek; i++) {
            vyuziti_hledane_rady[i] = 0;
            vyuziti_pokusu[i] = 0;
            vyhodnoceni[i] = 0;
        }
        cout << "Attempt number: " << pocet_pokusu << '\n';
        for(int i = 0; i < pocet_policek; i++) {
            cin >> p;
            pokus[i] = p;
        }
        vsechny_pokusy[pocet_pokusu-1] = pokus;
        for(int i = 0; i < pocet_policek; i++) {
            if(pokus[i] == hledana_rada[i]) {
                vyhodnoceni_counter[2]++;
                vyhodnoceni[i] = 2;
                vyuziti_hledane_rady[i] = 1;
                vyuziti_pokusu[i] = 1;
            }
        }
        for(int i = 0; i < pocet_policek; i++) {
            bool nasel = false;
            for(int j = 0; j < pocet_policek; j++) {
                if(pokus[j] == hledana_rada[i] && vyuziti_hledane_rady[i] == 0 && vyuziti_pokusu[j] == 0) {
                    nasel = true;
                    pokus_index = j;
                    vyuziti_hledane_rady[i] = 1;
                    vyuziti_pokusu[j] = 1;
                    break;
                }
            }
            if(nasel) {
                vyhodnoceni_counter[1]++;
                vyhodnoceni[pokus_index] = 1;
            }
        }
        if(vyhodnoceni_counter[2] == pocet_policek) {
            vyhra = true;
        }
        if(presna_pozice) {
            for(int i = 0; i < pocet_policek; i++) {
                if(vyhodnoceni_counter[2] > 0) {
                    vyhodnoceni[i] = 2;
                    vyhodnoceni_counter[2]--;
                } else if(vyhodnoceni_counter[1] > 0) {
                    vyhodnoceni[i] = 1;
                    vyhodnoceni_counter[1]--;
                } else {
                    vyhodnoceni[i] = 0;
                }
            }
        }
        vsechny_vyhodnoceni[pocet_pokusu-1] = vyhodnoceni;
        for(int i = 0; i < pocet_pokusu; i++) {
            cout << "Guess " << i+1 << ":  ";
            for(int j : vsechny_pokusy[i]) {
                cout << j << ' ';
            }
            cout << "  |  ";
            for(int j : vsechny_vyhodnoceni[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
        if(vyhra) {
            cout << "You won in " << pocet_pokusu << ". guess!" << '\n';
            return 1;
        }
        pocet_pokusu++;
    }
    cout << "You lost!" << '\n' << "The correct answer is: ";
    for(int i : hledana_rada) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}
int main() {
    int chces_hrat, pocet_vyher = 0;
    while(true) {
        cout << "If you want to play, enter 1. If you want to see your win count, enter 2." << '\n';
        cin >> chces_hrat;
        if(chces_hrat == 2) {
            cout << "Number of wins: " << pocet_vyher << '\n';
        } else if (chces_hrat == 1) {
            pocet_vyher += hra();
        } else {
            cout << "Game over!" << '\n';
            break;
        }
    }
    return 0;
}