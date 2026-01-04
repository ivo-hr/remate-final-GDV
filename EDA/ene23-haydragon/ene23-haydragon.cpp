//enjuga

#include <iostream>
#include <fstream>
#include <limits>
#include "bintree_eda.h"
using namespace std;



void mejorCamino(bintree<int> arb, int& mejorHoja, int dracoEnRuta, int& minDracos) {
    if (arb.empty())
        return;

    int hoja = arb.root();

    //si el valor es mayor que 2, es una entrada
    if (hoja > 2) {
        // Al empezar siempre la exploración por la izquierda (más adelante), prevalece en caso de empate la primera hoja que salió
        if (dracoEnRuta < minDracos) {
            minDracos = dracoEnRuta;
            mejorHoja = hoja;
        }

        //Se acaba el ciclo
        return;
    }

    //Si hay dragón, se aumenta el valor
    if (hoja == 1)
        dracoEnRuta++;

    //Empezamosexplorando por la izq. para darle prioridad
    mejorCamino(arb.left(), mejorHoja, dracoEnRuta, minDracos);
    mejorCamino(arb.right(), mejorHoja, dracoEnRuta, minDracos);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
int resuelveCaso() {
    bintree<int> arb;
    arb = leerArbol(-1); // -1 es la repr. de arbol vacio
    
    int minDragones = INT_MAX;
    int entrada = -1;

    mejorCamino(arb, entrada, 0, minDragones);

    cout << entrada << endl;

    return 0;
}

#define DOMJUDGE
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

