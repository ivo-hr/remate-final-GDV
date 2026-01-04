
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;



// Método que resuelve el problema
pair<bool, int> caucasico(const vector<int>& sec, int ini, int fin) {
    int lon = fin - ini;

    //Caso base: longitud 1
    if (lon <= 1) {
        bool esPar = sec[ini] % 2 == 0;
        return {true, esPar};
    }

    //Caso base: si la longitud no es par
    if (lon % 2 != 0)
        return {false, 0};

    //Cálculo!
    int med = ini + lon/2;

    pair<bool, int> izq = caucasico(sec, ini, med);
    pair<bool, int> der = caucasico(sec, med, fin);


    if (!izq.first || !der.first)
        return {false, 0};

    if (abs(izq.second - der.second) > 2)
        return {false, 0};

    return{true, izq.second + der.second};

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (caucasico(sec, 0, n).first ? "SI" : "NO") << endl;
    return true;
}
#define DOMJUDGE // Para restablecer entrada. Comentar para acepta el reto
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;



#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}