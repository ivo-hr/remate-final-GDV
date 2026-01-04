//enjuga
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int minimo(const vector<int>& sec, int ini, int fin) {
    //Sabiendo que despues de bajar solo puede subir, vamos a ver hasta donde empieza a subir.

    //Caso base: solo queda un elemento
    if (fin-ini == 1)
        return sec[ini];


    //Cálculo
    int mit = ini + (fin-ini)/2;

    //Caso base: estamos en la última posición
    if (mit >= sec.size()-1)
        return min(sec[mit], sec[mit-1]);

    if (sec[mit] < sec[mit + 1]) {
        if (sec[mit-1] > sec[mit])
            return sec[mit];
        else return minimo(sec, ini, mit);
    }
    else return minimo(sec, mit+1, fin); 
        
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (!cin) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << minimo(sec, 0, n) << endl;
    return true;
}

#define DOMJUDGE

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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