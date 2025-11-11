// Enrique Juan Gamboa
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Info {
    int numSingulares; // número de nodos singulares en el subárbol
    int sumaSubarbol;  // suma de valores del subárbol
};

//      1. Si el árbol está vacío → {0, 0}.
//      2. Calcula recursivamente info de los hijos con la suma
//         de antepasados actualizada.
//      3. sumaDescendientes = suma izquierda + suma derecha.
//      4. Es singular si sumaAntepasados == sumaDescendientes.
//      5. Devuelve el número de singulares y la suma total.
//
//  Coste: O(n) tiempo (visita cada nodo una sola vez)

Info contarSingulares(bintree<int> const& tree, int sumaAntepasados) {
    if (tree.empty()) return {0, 0};

    int valor = tree.root();

    Info izq = contarSingulares(tree.left(), sumaAntepasados + valor);
    Info der = contarSingulares(tree.right(), sumaAntepasados + valor);

    int sumaDesc = izq.sumaSubarbol + der.sumaSubarbol;
    int num = izq.numSingulares + der.numSingulares;

    if (sumaAntepasados == sumaDesc) ++num;

    int sumaSubarbol = valor + sumaDesc;
    return {num, sumaSubarbol};
}

// Resuelve un caso de prueba
void resuelveCaso() {
    bintree<int> tree = leerArbol(-1);
    Info res = contarSingulares(tree, 0);
    cout << res.numSingulares << '\n';
}

int main() {
#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

