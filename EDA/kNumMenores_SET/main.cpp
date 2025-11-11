// Enrique Juan
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Set.h"
using namespace std;

// Devuelve los k menores distintos de la secuencia (sin ordenar toda la serie)
// Cada elemento (n) se compara e inserta como máximo una vez en un conjunto de tamaño <= k, donde cada inserción o búsqueda cuesta O(k).
// O(n · k) en el peor caso.
Set<int> menoresDistintos(const vector<int>& nums, int k) {
    Set<int> menores;
    // Para cada elemento en el vector inicial
    for (int x : nums) {
        // Compruebo que el número no esté en la lista
        if (!menores.contains(x)) {
            // compruebo si la lista no está llena
            if (menores.size() < k) {
                menores.add(x);
            }
            // Si lo está, comparo con el mayor para ver si lo meto o no
            else if (x < menores.getMax()) {
                menores.removeMax();
                menores.add(x);
            }
        }
    }
    return menores;
}

// Resuelve un caso de prueba
bool resuelveCaso() {
    int k;
    cin >> k;
    if (!cin || k == 0) return false;

    vector<int> nums;
    int x;
    while (cin >> x && x != -1) nums.push_back(x);

    Set<int> resultado = menoresDistintos(nums, k);
    cout << resultado << '\n';
    return true;
}

int main() {
#define DOMJUDGE
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
