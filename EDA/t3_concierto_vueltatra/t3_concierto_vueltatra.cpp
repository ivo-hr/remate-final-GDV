// Enrique Juan Gamboa
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;



 // Coste O(n!): en el peor caso (no se llega a aplicar la poda) se generan todas las permutaciones posibles de n artistas, 
 // en cada nivel se prueba cada artista no usado.
void backtracking(int k,
    int n,
    const vector<vector<int>>& beneficios,
    const vector<vector<bool>>& consentimientos,
    const vector<int>& maxBeneficioPos,
    vector<int>& sol,
    vector<bool>& usado,
    int donacionActual,
    int estimacionRestante,
    int& mejorDonacion) {

    // PODA POR ESTIMACIÓN
    if (donacionActual + estimacionRestante <= mejorDonacion)
        return;

    if (k == n) {
        if (donacionActual > mejorDonacion)
            mejorDonacion = donacionActual;
    }
    else {
        for (int artista = 0; artista < n; ++artista) {
            if (!usado[artista]) {

                if (k == 0 || consentimientos[artista][sol[k - 1]]) {

                    sol[k] = artista;
                    usado[artista] = true;

                    backtracking(k + 1, n,
                        beneficios, consentimientos,
                        maxBeneficioPos,
                        sol, usado,
                        donacionActual + beneficios[artista][k],
                        estimacionRestante - maxBeneficioPos[k],
                        mejorDonacion);

                    usado[artista] = false;
                }
            }
        }
    }
}


void resolver(int n,
    const vector<vector<int>>& beneficios,
    const vector<vector<bool>>& consentimientos) {

    vector<int> sol(n);
    vector<bool> usado(n, false);
    int mejorDonacion = -1;

    // Precalcular estimación optimista por posición
    vector<int> maxBeneficioPos(n, 0);
    for (int j = 0; j < n; ++j)
        for (int i = 0; i < n; ++i)
            maxBeneficioPos[j] = max(maxBeneficioPos[j], beneficios[i][j]);

    int estimacionInicial = 0;
    for (int j = 0; j < n; ++j)
        estimacionInicial += maxBeneficioPos[j];


    backtracking(0, n, beneficios, consentimientos,
        maxBeneficioPos,
        sol, usado,
        0, estimacionInicial,
        mejorDonacion);

    if (mejorDonacion == -1)
        cout << "NEGOCIA CON LOS ARTISTAS\n";
    else
        cout << mejorDonacion << "\n";
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n;
    cin >> n;

    vector<vector<int>> beneficios(n, vector<int>(n));
    vector<vector<bool>> consentimientos(n, vector<bool>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> beneficios[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int b;
            cin >> b;
            consentimientos[i][j] = b;
        }

    resolver(n, beneficios, consentimientos);
}


#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
