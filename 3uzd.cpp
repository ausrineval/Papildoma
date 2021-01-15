#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>

#include "functions.h"

using namespace std;

int main()
{
    ifstream ifs("sausis.txt");
    string text((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    const int rows = count(text.begin(), text.end(), '\n');
    zodziusarasas(text);
    lentele();
    printnuoroda();
}