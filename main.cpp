#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    int chaves[20000];

    string line;
    ifstream keys;
    keys.open("chaves.txt");

    int i = 0;
    while (!keys.eof()){
        getline(keys, line);
        stringstream aux(line);
        int nAux;
        aux >> nAux;
        chaves[i] = nAux;
        i++;
    }
    keys.close();

    for (int i = 0; i < 10; i++){
        cout << chaves[i] << endl;
    }
    return 0;
}