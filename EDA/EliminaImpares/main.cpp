// Enrique Juan Gamboa
// EDA-GDV35


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>



// función que resuelve el problema
// Coste de O(n), ya que no se elimina elementos del vector, sino que se va llevando los pares a las
// posiciones en los que había impares:
/*                          BORRAR B
 *      a b c d  |  a b c d  |  a c c d  |  a c d d  |  a c d
 *      î        |    î      |    ^ i    |      ^ i  |
 *
 *
 *
 *
 */
void resolver(std::vector<int>& datos) {

    int puntero = 0;

    for (int i = 0; i < datos.size(); i++) {
        if (datos[i] % 2 == 0) {
            datos[puntero] = datos[i];
            puntero++;
        }
    }
    datos.resize(puntero);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numElem = 0;
    std::cin >> numElem;

    std::vector<int> datos(numElem);
    for (int i = 0; i < numElem; i++) {
        std::cin >> datos[i];
    }



    resolver(datos);
    // escribir sol
    for (int i = 0; i < datos.size(); i++) {
        std::cout << datos[i] << " ";
    }
    std::cout << std::endl;

}

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
    system("PAUSE");
#endif

    return 0;
}