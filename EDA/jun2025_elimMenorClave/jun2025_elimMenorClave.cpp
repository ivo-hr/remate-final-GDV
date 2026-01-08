/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:

Cuestión extra: ¿Cuál sería la menor complejidad en tiempo que podría tener una función que elimine los k pares clave-valor con menor valor para cada caso (map y unordered_map)? Justifica tu respuesta.

Tendrían ambosla misma complejidad O(n * log(k)): n porque hay que recorrer todos los elementos del mapa SIEMPRE para leer el contenido de valor,
                                             y log(k) es el coste de meter la referencia al elemento del mapa ordenado según su valor en una 
                                             cola de prioridad. Con una cola de prioridad de tamaño k siempre se guardarían los k elementos de menor
                                             valor con el menor coste posible, y luego para borrarlos habría que eliminar cualquier elemento 
                                             refernciado en dicha cola.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Complejidad: O(k*log(n)), ya que viene el mapa ordenado por clave
template <class K, class V>
void eliminaKMenores(map<K, V>& map, int k) {
    //Caso base: se elimina más de lo que hay (caso mejor)
    if (map.size() <= k) {
        map.clear();
        return;
    }

    auto it = map.begin();


    for (int i = 0; i < k; i++) {
        it = map.erase(it);
    }
}

// Complejidad: O(n*log(n)), ya que hay que ordenar
template <class C, class V>
void eliminaKMenores(unordered_map<C, V>& map, int k) {
    //Caso base: se elimina más de lo que hay (caso mejor)
    if (map.size() <= k) {
        map.clear();
        return;
    }

    //Ordenamos el mapa con vector sort
    vector<string> claves;
    for (auto& cl : map) {
        claves.push_back(cl.first);
    }
    //Ordenamos el vector (coste O(n*log(n)))
    sort(claves.begin(), claves.end());

    //Borramos!
    for (int i = 0; i < k; i++) {
        map.erase(claves[i]);
    }
}



void resuelveCaso() {
    map<string, int> map1;
    unordered_map<string, int> map2;
    int n, k;

    // Lectura de datos
    cin >> n >> k;
    string clave;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> clave >> valor;
        map1.insert({ clave, valor });
        map2.insert({ clave, valor });
    }

    // Llamada a funciones
    eliminaKMenores(map1, k);
    eliminaKMenores(map2, k);

    // Escritura de la salida
        // Imprimir map1 ordenado por claves
    for (auto it = map1.begin(); it != map1.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    cout << "-\n";

    // Imprimir map2 ordenado por claves (para ello debes volcarlo a un vector, ordenarlo e imprimirlo)
    //Ordenamos el mapa con vector sort
    vector<string> claves;
    for (auto const& cl : map2) {
        claves.push_back(cl.first);
    }
    //Ordenamos el vector
    sort(claves.begin(), claves.end());

    //Imprimimos!
    for (auto const& cl : claves) {
        cout << cl << " " << map2.at(cl) << endl;
    }
    cout << "---\n";
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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