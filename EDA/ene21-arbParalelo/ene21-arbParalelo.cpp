
#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta

//Función de entrada al algoritmo: coge la raíz ppal del árbol, hace el caso base de vacío y empieza a comprobar a sus hijos
// con la función de dos argumentos (su hijo izq y der)
//El coste es de O(n), n siendo el número de hojas del árbol, ya que lo recorre entero una vez.
template <class T>
bool esSimetrico(const bintree<T>& arb) {
    // Caso base: el arbol es vacio
    if (arb.empty()) return true;

    //Llamada a la función de dos argumentos
    return esSimetrico(arb.left(), arb.right());
 }

template <class T>
bool esSimetrico(const bintree<T>& arbL, const bintree<T>& arbR) {
    // Caso base: ambos vacíos
    if (arbL.empty() && arbR.empty()) return true;

    //Caso base: uno vacío y el otro no (al pasar el primer if no hace falta hacer xor)
    if (arbL.empty() || arbR.empty()) return false;

    //Misma comprobación para los hijos de cada:
    // Hijo izq del arb izq, hijo der del arb der // hijo der del arb izq, hijo izq del arb der
    return esSimetrico(arbL.left(), arbR.right()) && esSimetrico(arbL.right(), arbR.left());
}


void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');
    
    cout << (esSimetrico(tree) ? "SI" : "NO") << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
