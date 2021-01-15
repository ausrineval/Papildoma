#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>

using namespace std;

vector<string> nuoroda; 
map<string, int> zodziai;
typedef map<string, int> Map;
multimap<string, int> lines;

void zodziusarasas(string& text);
void lentele();
bool isnuoroda(string zodis);
void printnuoroda();
void simboliai(string& zodis);

void zodziusarasas(string& text) //sudaro visu zodziu sarasa
{
    int eil = 1;
    string zodis, sentence;
    istringstream a(text);
    ofstream ofs("sarasas.txt");
    vector<string> list;
    do { //zodziu rusiavimas i list
        cout << eil << endl;
        getline(a, sentence);
        istringstream b(sentence);
        while (b) {
            b >> zodis;
            cout << "Eilute: " << eil << " | " << " Zodis: " << zodis << endl;
            if (!isnuoroda(zodis)) {
                simboliai(zodis);
                if (zodis.length() > 1) {
                    list.push_back(zodis);
                    lines.insert({ zodis, eil });
                }
            }
            if (b.eof()) break;
        }
        eil++;
    } while (a);

    map<string, int>::iterator it;
    const string tableline(50, '-');

    for (string zodis : list) {
        it = zodziai.find(zodis);
        if (it != zodziai.end()) {
            zodziai[zodis]++;
        }
        else {
            zodziai.insert({ zodis, 1 });
        }
    }
    ofs << left << setw(15) << "Pasikartojo:" << "Zodis:" << endl << tableline << endl;
    for (it = zodziai.begin(); it != zodziai.end(); ++it) {
        if (it->second > 1) {
            ofs << left << setw(15) << to_string(it->second) << it->first << endl;
        }
    }
}

void lentele() //cross-reference table
{
    ofstream ofs("lentele.txt");

    const string tableline(100, '-');

    ofs << left << setfill(' ') << setw(25) << "Zodis";
    ofs << left << setfill(' ') << setw(25) << "Pasikartojimu sk.";
    ofs << left << "Eilutes" << endl << tableline << endl;

    for (auto x = zodziai.begin(); x != zodziai.end(); x++) {
        if (x->second > 1) {
            ofs << left << setfill(' ') << setw(25) << x->first;
            ofs << left << setfill(' ') << setw(25) << x->second;
            for (auto x2 = lines.begin(); x2 != lines.end(); x2++) {
                if (x->first == x2->first) {
                    ofs << x2->second << " ";
                }
            }
            ofs << endl;
        }
    }
}

bool isnuoroda(string zodis) //suranda nuoroda ir iraso i nuorodu vektoriu
{
    if (zodis.rfind("http", 0) == 0 || zodis.rfind("www", 0) == 0) {
        nuoroda.push_back(zodis);
        return true;
    }
    else
        return false;
}

void printnuoroda() //spausdina visus zodzius, kurie yra nuorodos
{
    ofstream ofs("nuorodos.txt");
    if (nuoroda.size() == 0) {
        ofs << "Puslapiu nerasta" << endl;
    }
    else {
        for (auto x : nuoroda) {
            ofs << x << endl;
        }
    }
}

void simboliai(string& zodis) //simboliu panaikinimas
{
    const char simboliai[] = ",.:;\"!?�_`~&^%$#\n\t*()[]@#=+-–��1234567890";
    for (int i = 0; i < sizeof(simboliai); i++) {
        zodis.erase(remove(zodis.begin(), zodis.end(), simboliai[i]), zodis.end());
    }
}