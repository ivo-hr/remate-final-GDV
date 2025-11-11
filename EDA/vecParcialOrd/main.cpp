// Alumno: Enrique Juan
// Código juez: EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Coste: O(n) usando divide y vencerás, cada elemento se visita una sola vez
bool parcialmenteOrdenado(const vector<int>& v, int ini, int fin, int& minVal, int& maxVal) {
    if (fin - ini == 1) { // caso base: un solo elemento
        minVal = maxVal = v[ini];
        return true;
    }

    int mid = (ini + fin) / 2;
    int minIzq, maxIzq, minDer, maxDer;

    bool izquierda = parcialmenteOrdenado(v, ini, mid, minIzq, maxIzq);
    bool derecha   = parcialmenteOrdenado(v, mid, fin, minDer, maxDer);

    minVal = min(minIzq, minDer);
    maxVal = max(maxIzq, maxDer);

    // Verificamos condición de parcialmente ordenado
    return izquierda && derecha && (maxIzq <= maxDer) && (minIzq <= minDer);
}

bool parcialmenteOrdenado(const vector<int>& v) {
    int minVal, maxVal;
    return parcialmenteOrdenado(v, 0, v.size(), minVal, maxVal);
}

bool resuelveCaso() {
    int e;
    cin >> e;
    if (e == 0) return false;

    vector<int> sec;
    while (e != 0) {
        sec.push_back(e);
        cin >> e;
    }

    cout << (parcialmenteOrdenado(sec) ? "SI" : "NO") << endl;
    return true;
}

int main() {
//#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
