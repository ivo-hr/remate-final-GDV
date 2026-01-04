//enjuga
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool resolver(const vector<int>& v, int ini, int fin) {
    //Miraremos si el elemento de enmedio está bien situado o no;
    //Después si el número actual es mayor o menor a su índice posicional
    //Y subir o bajar por el vector acordemente

    //Caso base: último número
    if (fin - ini <= 1)
        //Si el vector está vacío
        if (v.size() < 1)
            return false;
        else 
            return v[ini] == ini;

        

    int mit = ini + ( fin - ini ) / 2;
    
    //Comprobación: si lo encontramos, ole!
    if (v[mit] == mit)
        return true;
    //Pa la derecha
    if (v[mit] < mit)
        return resolver(v, mit+1, fin);
    //Pa la izquierda (podría ser un else, pero por legibilidad lo dejo en un if)
    if (v[mit] > mit)
        return resolver(v, ini, mit);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (resolver(sec, 0, n) ? "SI" : "NO") << endl;
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
