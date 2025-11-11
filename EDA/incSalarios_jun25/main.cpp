/*
Enrique Juan Gamboa
EDA-GDV35
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad: O(log n), al ser una función recusiva de búsqueda binaria, descartando mitades enteras
// al buscar el resultado correcto, de manera:
/*
 *  1000 1001 1003 1008 1015 | 1023 1040 1080 1130 1190
 *               busco aquí, descarto la derecha
 *
 *  1000 1001 | 1003 1008 1015
 *  busco aquí, descarto la izquierda
 *
 *   1003 | 1008 1015
 *  busco aquí, descarto la izquierda
 *
 * etc...
 */
int buscarSalario(const vector<int>& sec, int inc, int ini, int fin) {
    if (inc == 0) return 0; // caso especial

    if (ini > fin) return -1; // rango vacío

    int mid = ini + (fin - ini) / 2;

    int diff = sec[mid] - sec[mid - 1]; // incremento en año mid

    if (diff == inc) {
        // Buscamos si hay otro igual más a la izquierda (primer año)
        int left = buscarSalario(sec, inc, ini, mid - 1);
        if (left != -1)
            return left;
        return mid;
    }
    else if (diff > inc) {
        return buscarSalario(sec, inc, ini, mid - 1);
    }
    else {
        return buscarSalario(sec, inc, mid + 1, fin);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, inc;
    cin >> inc >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    // Llamada a función y escritura de la salida
    cout << buscarSalario(sec, inc, 0, n -1) << endl;

}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
