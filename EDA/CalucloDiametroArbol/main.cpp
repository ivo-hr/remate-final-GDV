// Enrique Juan Gamboa
// EDA-GDV35

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Info {
    int altura;   // altura del subárbol
    int diametro; // diámetro del subárbol
};

//      1. Si el árbol está vacío → altura = 0, diámetro = 0.
//      2. Calcula recursivamente altura y diámetro de los hijos.
//      3. En cada nodo:
//             altura = 1 + max(altura_izq, altura_der)
//             diametro = max(diametro_izq, diametro_der, altura_izq + altura_der + 1)
//      4. Devuelve el diámetro global del árbol.
//
//  Coste: O(n) tiempo, recorriendo cada nodo una vez.
//          O(h) espacio adicional (profundidad de recursión).
/*
template <class T>
Info diametro(bintree<T> const& tree) {
    if (tree.empty()) return {0, 0};

    Info izq = diametro(tree.left());
    Info der = diametro(tree.right());

    int altura = 1 + max(izq.altura, der.altura);
    int diam = max(max(izq.diametro, der.diametro), izq.altura + der.altura + 1);

    return {altura, diam};
}

bintree<char> leerArbolChar() {
    char c;
    cin >> c;
    if (c == '.')
        return{};
    else { // c == '*'
        auto iz = leerArbolChar();
        auto dr = leerArbolChar();
        return {iz, c, dr};
    }
}
*/

// Prueba a ver si se puede hacer las dos cosas a la vez ,para optimizar tiempo y coste (sólo se leería el arbol una vez)
Info leerYCalcular() {
    char c;
    cin >> c;
    if (c == '.') return {0, 0};
    else { // c == '*'
        Info izq = leerYCalcular();
        Info der = leerYCalcular();

        int altura = 1 + max(izq.altura, der.altura);
        int diametro = max(max(izq.diametro, der.diametro), izq.altura + der.altura + 1);

        return {altura, diametro};
    }
}

// Resuelve un caso de prueba
void resuelveCaso() {
    //bintree<char> tree = leerArbolChar();
    cout << leerYCalcular().diametro << '\n';
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
