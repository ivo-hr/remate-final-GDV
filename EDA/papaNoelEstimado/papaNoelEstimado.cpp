//enjuga
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;


void resolver(int pos, int n, int m,
    const vector<vector<int>>& satisf,
    vector<int>& soluc, vector<bool>& usado,
    int satisfAct, int& mejorSol,
    const vector<int>& estimacion) {

    // Caso base: todos los niños asignados
    if (pos == n) {
        if (satisfAct > mejorSol)
            mejorSol = satisfAct;
        return;
    }

    // Poda por estimación
    if (satisfAct + estimacion[pos] <= mejorSol)
        return;

    // Probar cada juguete
    for (int j = 0; j < m; j++) {

        // Restricción: juguete no usado
        if (usado[j]) continue;

        // Elegimos
        soluc[pos] = j;
        usado[j] = true;

        resolver(pos + 1, n, m, satisf,
            soluc, usado,
            satisfAct + satisf[pos][j],
            mejorSol, estimacion);

        // Deshacer
        usado[j] = false;
    }
}


// Resuelve un caso de prueba
bool resuelveCaso() {
    int m, n;
    cin >> m >> n;
    if (!cin) return false;

    vector<vector<int>> satisf(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> satisf[i][j];

    vector<int> soluc(n);           // tupla solución
    vector<bool> usado(m, false);
    int mejorSol = INT_MAX * -1;

    // Cálculo de la estimación optimista
    vector<int> estimacion(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int mejor = satisf[i][0];
        for (int j = 1; j < m; j++)
            mejor = max(mejor, satisf[i][j]);
        estimacion[i] = estimacion[i + 1] + mejor;
    }

    resolver(0, n, m, satisf,
        soluc, usado,
        0, mejorSol, estimacion);

    // Salida
    cout << mejorSol << endl;
    return true;
}


//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
