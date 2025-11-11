// Enrique Juan Gamboa
// EDA-GDV35


#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "bintree_eda.h"
using namespace std;
struct Info {
    bool esBST;
    int minVal;
    int maxVal;
};

//      1. Si el árbol está vacío → es BST (sin min ni max).
//      2. Si es hoja → es BST y min=max=raíz.
//      3. Calcula recursivamente info del hijo izq. y der.
//      4. El árbol es BST si: izq y der son BST,
//         max(izq) < raíz < min(der).
//      5. Devuelve si es BST y el min/max de todo el subárbol.
//
//  Coste: O(n) tiempo, visitando cada nodo una vez.
//          O(h) espacio adicional (por la recursión).
template <class T>
Info esBST(bintree<T> const& tree) {
    if (tree.empty()) {
        // Árbol vacío: es BST, pero no tiene min ni max reales
        return {true, INT_MAX, INT_MIN};
    }

    if (tree.left().empty() && tree.right().empty()) {
        // Nodo hoja: es BST y su min/max son su valor
        return {true, tree.root(), tree.root()};
    }

    Info izq = esBST(tree.left());
    Info der = esBST(tree.right());

    bool ok = izq.esBST && der.esBST &&
              (izq.maxVal < tree.root()) &&
              (tree.root() < der.minVal);

    int minVal = min(tree.root(), min(izq.minVal, der.minVal));
    int maxVal = max(tree.root(), max(izq.maxVal, der.maxVal));

    return {ok, minVal, maxVal};
}

// Resuelve un caso de prueba
void resuelveCaso() {
    bintree<int> tree;
    tree = leerArbol(-1);
    if (esBST(tree).esBST)
        cout << "SI\n";
    else
        cout << "NO\n";
}

int main() {
#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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