
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;



void resolver(int pos, int n, int m, int consumoMax, const vector<int>& consumosPorColor,
    vector<int>& soluc, vector<int>& totCol, int consumoActual, int& combinaciones) {

    // Caso base: tira completa
    if (pos == n) {
        combinaciones++;
        return;
    }

    // Probar cada color
    for (int color = 0; color < m; color++) {

        // 1. No más de dos seguidas del mismo color
        if (pos >= 2 &&
            soluc[pos - 1] == color &&
            soluc[pos - 2] == color)
            continue;

        // 2. Consumo máximo
        if (consumoActual + consumosPorColor[color] > consumoMax)
            continue;

        // Elegimos
        soluc[pos] = color;
        totCol[color]++;

        // 3. Restricción de equilibrio de colores
        bool valido = true;
        int usadas = pos + 1;
        for (int c = 0; c < m && valido; c++) {
            if (totCol[c] > (usadas - totCol[c]) + 1)
                valido = false;
        }

        if (valido) {
            resolver(pos + 1, n, m, consumoMax,
                consumosPorColor, soluc, totCol,
                consumoActual + consumosPorColor[color],
                combinaciones);
        }

        // Deshacer
        totCol[color]--;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m, consumoMax;
    int combinaciones = 0;
    cin >> n;
    if (n == 0) return false;
    cin >> m >> consumoMax;
    vector<int> consumosPorColor(m);
    for (int& e : consumosPorColor) cin >> e;
    vector<int> soluc(n);
    int k = 0;
    vector<int> totalesPorColor(m, 0);
    resolver(0, n, m, consumoMax,
        consumosPorColor, soluc,
        totalesPorColor, 0, combinaciones);
    // Salida
    cout << combinaciones << endl;
    return true;
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}