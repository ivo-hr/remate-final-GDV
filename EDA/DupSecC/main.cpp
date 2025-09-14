// Enrique JG
// EDA-GDV35


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>



// función que resuelve el problema
std::vector<int> resolver(int datos) {
	std::vector<int> secuencias(datos);
	//Leer secuencias
    
	for (int i = 0; i < datos; ++i) {
		std::cin >> secuencias[i];
		secuencias[i] *= 2;
	}

    return secuencias;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    if (! std::cin)
        return false;

    int numSeq;
    std::cin >> numSeq;
    std::vector<int> sol = resolver(numSeq);
    // escribir sol
	for (int num : sol)
        std::cout << num << " ";
	std::cout << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinaabuf);
    //system("PAUSE");
#endif

    return 0;
}