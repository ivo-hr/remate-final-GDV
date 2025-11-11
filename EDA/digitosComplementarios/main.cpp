// Enrique Juan
// EDA-GDV35


#include <iostream>
#include <iomanip>
#include <fstream>



// Devuelve el número complementario
int resolver(int n, int capa = 1, int sol = 0) {
    if (n == 0) return sol;  // caso base: ya no quedan dígitos

    int last = 9 - (n % 10);           // complementario del último dígito
    sol += last * capa;           // acumular en su posición
    return resolver(n / 10, capa * 10, sol);  // procesar resto del número
}


// Invierte un entero
int invertir(int n, int inv = 0) {
    if (n == 0) return inv;
    return invertir(n / 10, inv * 10 + n % 10);
}

void resuelveCaso() {
    int n;
    std::cin >> n;
    int comp = resolver(n);
    std::cout << comp << " " << invertir(comp) << std::endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #define DOMJUDGE
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