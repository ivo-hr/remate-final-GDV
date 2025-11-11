// Enrique Juan Gamboa
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Info {
    int equipos;   // número de equipos necesarios en el subárbol
    int sumaMax;   // máxima suma de excursionistas en una ruta desde este nodo
    bool hayGrupo; // indica si hay algún grupo en el subárbol
};

//      1. Si el árbol está vacío → {0, 0, false}.
//      2. Calcula recursivamente info de los hijos.
//      3. Si el nodo actual tiene excursionistas (>0):
//           - hayGrupo = true
//           - Si ni el hijo izq. ni der. tienen grupo, hace falta un nuevo equipo (+1).
//      4. sumaMax = valor del nodo + max(sumaMax_izq, sumaMax_der).
//      5. Devuelve la suma total de equipos y la suma máxima de excursionistas.
//
//  Coste: O(n) tiempo, recorriendo cada nodo una sola vez.
//          O(h) espacio adicional (profundidad de la recursión).

template <class T>
Info excursionistas(bintree<T> const& tree) {
    if (tree.empty()) return {0, 0, false};

    Info izq = excursionistas(tree.left());
    Info der = excursionistas(tree.right());

    int valor = tree.root();
    int equipos = izq.equipos + der.equipos;
    bool hay = izq.hayGrupo || der.hayGrupo || valor > 0;

    if (valor > 0 && !izq.hayGrupo && !der.hayGrupo) {
        equipos += 1; // grupo sin nadie debajo → necesita equipo nuevo
    }

    int sumaMax = 0;
    if (valor > 0 || izq.hayGrupo || der.hayGrupo) {
        sumaMax = valor + max(izq.sumaMax, der.sumaMax);
    }

    return {equipos, sumaMax, hay};
}

// Resuelve un caso de prueba
void resuelveCaso() {
    bintree<int> tree = leerArbol(-1);
    Info res = excursionistas(tree);
    cout << res.equipos << " " << res.sumaMax << '\n';
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
