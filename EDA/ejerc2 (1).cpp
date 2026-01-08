/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no: 

Preguntas:

Indica y explica el formato de la tupla solución:

¿Cuándo se da el caso peor? 

Indica cuántas llamadas (en función de n) genera el algoritmo en dicho caso.

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema y justificación del coste


void resuelveCaso() {
    int n = 0, M;
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v)
        cin >> e;

    // llamada a función que resuelve el problema

    // salida de datos
    
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
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