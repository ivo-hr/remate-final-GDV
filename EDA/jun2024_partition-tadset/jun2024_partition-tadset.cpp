/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

using namespace std;


// función que resuelve el problema y justificación del coste

template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:

    //Complejidad O(n), n siendo el Nº de elementos de la lista
    void partition(int pivote) {

        //El fantasma une el último y el primero; actual va a ser el siguiente al fantasma (el primero)
        Nodo* act = this->fantasma->sig;
        Nodo* next;
        //Recorremos la lista
        for (int i = 0; i < this->nelems; i++) {
            //Guardamos el siguiente nodo par aavanzar por la lista
            next = act->sig;

            if (act->elem > pivote) {
                //Desenlazamos el nodo y enlazamos el anterior y siguiente
                act->ant->sig = act->sig;
                act->sig->ant = act->ant;

                //El fantasma une el último y el primero; colocamos act antes del fantasma (al final)
                act->ant = this->fantasma->ant;
                act->sig = this->fantasma;
                //El siguiente al último nodo va a ser act
                this->fantasma->ant->sig = act;
                //El anterior al fantasma va a ser act
                this->fantasma->ant = act;
            }
            //Pasamos al siguiente nodo del recorrido
            act = next;
        }

    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int e, n, pivote;
    list_plus<int> l;

    // leer los datos de la entrada
    cin >> n >> pivote;
    if (!cin) return false;

    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.partition(pivote);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
    return true;
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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