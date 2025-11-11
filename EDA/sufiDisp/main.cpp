// Alumno: Enrique Juan
// Código juez: EDA-GDV35

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Coste: O(n), cada elemento se visita una sola vez usando divide y vencerás
bool suficientementeDisperso(const vector<int>& v, int ini, int fin, int K) {
    if (fin - ini == 1) return true; // Caso base: un solo elemento

    int mid = (ini + fin) / 2;

    // Diferencia entre primer y último elemento de la sección
    if (abs(v[fin - 1] - v[ini]) < K) return false;

    // Recursivamente comprobamos ambas mitades
    return suficientementeDisperso(v, ini, mid, K) && suficientementeDisperso(v, mid, fin, K);
}

// Resuelve un caso de prueba
bool resuelveCaso() {
    int n, K;
    if (!(cin >> n >> K)) return false; // fin de la entrada

    vector<int> tiradas(n);
    for (int i = 0; i < n; ++i) cin >> tiradas[i];

    cout << (suficientementeDisperso(tiradas, 0, n, K) ? "SI" : "NO") << endl;
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
#endif

    return 0;
}
