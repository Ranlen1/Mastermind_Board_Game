#include<bits/stdc++.h>
#include <random>
using namespace std;
int hra() {
    //nastaveni hry
    int pocet_barev, opakovani_barev, pocet_policek, presna_pozice, moznsot_odhalit_reseni;
    cout << "Zadej pocet barev, se kterymi ches hrat(5-8)." << '\n';
    cin >> pocet_barev;
    if(pocet_barev < 5 || pocet_barev > 8) {
        cout << "Neplatny pocet barev.";
        return 0;
    }
    cout << "Chces hrat s opakovanim barev(1=ANO, 0=NE)?" << '\n';
    cin >> opakovani_barev;
    if(opakovani_barev < 0 || opakovani_barev > 1) {
        cout << "Neplatne nastaveni opakovani barev." << '\n';
        return 0;
    }
    cout << "Kolik chces mit policek v jedne rade(4-5)?" << '\n';
    cin >> pocet_policek;
    if(pocet_policek < 4 || pocet_policek > 5) {
        cout << "Neplatny pocet policek." << '\n';
        return 0;
    }
    cout << "Jaky zpusob hodnoceni chces mit(0 = presna pozice, 1 = nepresna pozice)?" << '\n';
    cin >> presna_pozice;
    if(presna_pozice < 0 || presna_pozice > 1) {
        cout << "Neplatne nastaveni zpusobu hodnoceni." << '\n';
        return 0;
    }
    cout << "Chces mit moznost odhalit reseni(1 = ANO)?" << '\n';
    cin >> moznsot_odhalit_reseni;
    random_device rd;    //seed pro generator nahodnych cisel
    mt19937 gen(rd());
    uniform_int_distribution<> generator(1, pocet_barev);
    unordered_set<int> vybrana_cisla;     //set krery trackuje ktra cisla uz jsem vygeneroval aby se neopakovala pri zvolenem typu hry
    int nahodne_cislo;
    vector<int> hledana_rada(pocet_policek);
    for(int i = 0; i < pocet_policek; i++) {
        nahodne_cislo = generator(gen);
        while(vybrana_cisla.find(nahodne_cislo) != vybrana_cisla.end()) {
            nahodne_cislo = generator(gen);
        }
        hledana_rada[i] = nahodne_cislo;
        if(!opakovani_barev) {     //tento if statement se triggerne pokud je povoleno opakovani barev
            vybrana_cisla.insert(nahodne_cislo);
        }
    }
    int pocet_pokusu = 1, p, odhaleni_reseni, pokus_index;
    vector<int> pokus(pocet_policek);
    if(pocet_policek == 4) {
        cout << "Tvuj pokus zadej nasledovne: 1 2 3 4" << '\n';
    } else {
        cout << "Tvuj pokus zadej nasledovne: 1 2 3 4 5" << '\n';
    }
    cout << "Ve vyhodnoceni 0 znamena, ze dana barva neni, 1 znamena, ze dana barva je na jinem miste a 2 ze jsi barvu uhodl." << '\n';
    //vectory ktere trackuji vsechny predesle pokusy a vyhodnoceni danych pokusu
    vector<vector<int>> vsechny_pokusy(11, vector<int>(1)), vsechny_vyhodnoceni(11, vector<int>(1));
    while(pocet_pokusu < 11) {     //while loop ktery skonci pote, co pocet pokusu presahne 10
        vector<int> vyhodnoceni_counter({0, 0, 0}), vyhodnoceni(pocet_policek), vyuziti_hledane_rady(pocet_policek), vyuziti_pokusu(pocet_policek);
        for(int i = 0; i < pocet_policek; i++) {
            vyuziti_hledane_rady[i] = 0;
            vyuziti_pokusu[i] = 0;
            vyhodnoceni[i] = 0;
        }
        if(moznsot_odhalit_reseni == 1) {       //monzost odhaleni reseni se zobrazi, pokus v nastaveni hry umoznime odhaleni reseni
            cout << "Pokud chces odhalit reseni, zadej 1." << '\n';
            cin >> odhaleni_reseni;
            if(odhaleni_reseni == 1) {
                cout << "Reseni: ";
                for(int i : hledana_rada) {
                    cout << i << ' ';
                }
                cout << '\n';
            }
        }
        cout << "Pokus cislo: " << pocet_pokusu << '\n';
        for(int i = 0; i < pocet_policek; i++) {
            cin >> p;
            pokus[i] = p;
        }
        /*
        nejdrive odhalime vsechny spravne kolicky, aby se nam nestalo ze priradime bily kolicek ke stejne barve,
        ktery by ale nasledne dostal cerny kolicek. Tatko koplikovane jsem to rozdelil z duvodu, ze existuje pravdilo
        ze kazdy kolicek ktery je skryty muze poskitnout maximalne jeden kolicek z odopovdi napr pokud by jsem
        meli skryty jeden modry kolicek a mi by jsem do naseho guessu dali 2 modre kolicky, a netrefil by se ani jeden
        meli by jsme vydat pouze 1 bily kolicek a ne 2, stejne tak to je i kdyz se jeden trefi, tak dame pouze 1 cerny
        kolicek a nikoliv cerny a bily. Proto si musime vytvorit par extra arrayi, ktere trackuji pro ktere schovane
        kolikcy jsme uz vypsali odpoved, aby jsem neporousili jiz zminene pravdilo.
        */
        vsechny_pokusy[pocet_pokusu-1] = pokus;
        for(int i = 0; i < pocet_policek; i++) {
            if(pokus[i] == hledana_rada[i]) {
                vyhodnoceni_counter[2]++;
                vyhodnoceni[i] = 2;
                vyuziti_hledane_rady[i] = 1;
                vyuziti_pokusu[i] = 1;
            }
        }
        for(int i = 0; i < pocet_policek; i++) {   //tato cast hleda bile kolicky
            bool nasel = false;
            for(int j = 0; j < pocet_policek; j++) {
                //if statement checkuje pokud maji kolicky stejnou barvu a ani jeden z nich jeste nebyl pouzit
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
        if(presna_pozice) {    //meni vyhodnoceni, pokus se hrac rozhodl pro 2 format hry
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
            cout << "Pokus " << i+1 << ":  ";
            for(int j : vsechny_pokusy[i]) {
                cout << j << ' ';
            }
            cout << "  |  ";
            for(int j : vsechny_vyhodnoceni[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
        if(vyhodnoceni_counter[2] == pocet_policek) {
            cout << "Vyhral jsi v " << pocet_pokusu << ". kole!" << '\n';
            return 1;
        }
        pocet_pokusu++;
    }
    cout << "Prohral jsi." << '\n';
    return 0;
}
int main() {
    int chces_hrat, pocet_vyher = 0;
    while(true) {
        cout << "Pokud chces hrat, zadej 1. Pokud chces zobrazit pocet vyher, zadej 2" << '\n';
        cin >> chces_hrat;
        if(chces_hrat == 2) {
            cout << "Pocet vyher je: "<< pocet_vyher << '\n';
        } else if (chces_hrat == 1) {
            pocet_vyher += hra();
        } else {
            cout << "Konce hry!" << '\n';
            break;
        }
    }
    return 0;
}