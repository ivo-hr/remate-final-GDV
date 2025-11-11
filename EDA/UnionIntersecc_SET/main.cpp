// Enrique Juan
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
using namespace std;

// Función que lee un conjunto desde la entrada
Set<int> leerSet() {
    int n;
    cin >> n;
    Set<int> s;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        s.add(x);
    }
    return s;
}

// Resuelve un caso de prueba
bool resuelveCaso() {
    if (!cin) return false;

    // Leer primer conjunto
    Set<int> set1 = leerSet();
    if (!cin) return false;

    // Leer segundo conjunto
    Set<int> set2 = leerSet();
    if (!cin) return false;

    // Mostrar resultados
    cout << (set1 || set2) << endl;
    cout << (set1 && set2) << endl;

    return true;
}

int main() {
    // Para la entrada por fichero (comentar para enviar al juez)
#define DOMJUDGE
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf()); // redirige cin a datos.txt
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
