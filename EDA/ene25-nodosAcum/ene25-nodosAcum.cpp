/*
enjuga
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

//Coste: O(n) siendo n el Nº de nodos en el árbol.
template <class T>
int acumuladores(bintree<T> const& tree, int&numAcum) {
    
    if (tree.empty()) return 0;

    int sum = 0;

    if (!tree.left().empty()) sum += acumuladores(tree.left(), numAcum);
    if (!tree.right().empty()) sum += acumuladores(tree.right(), numAcum);

    if (sum == tree.root()) numAcum++;

    return sum + tree.root();
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    int numAcum = 0;
    int finSum = acumuladores(tree, numAcum);
    cout << numAcum << endl;
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("input2.txt");
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
