// Enrique Juan
// EDA-GDV35

/*
 * COSTE SIENDO DESORDENADOS
 *
 * El mejor coste sería ordenando los vectores de antemano: O(n * log(n) + m * log(m)). Hay otras maneras de hacerlo,
 * pero no resultan más eficientes.
 *
 *
 *
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
//Para el mergesort
#include <algorithm>

using namespace std;


struct TipoDatos {
    vector<string> A;
    vector<string> B;
};

struct TipoSolucion {
    vector<string> comunes;
    vector<string> soloA;
    vector<string> soloB;
};

//SI SON ORDEANADOS coste peor O(n+m) siendo n y m la longitud de las cadenas A y B respectivamente.
TipoSolucion resolver(TipoDatos datos) {
    TipoSolucion sol;
    int i = 0, j = 0;
    int n = datos.A.size(), m = datos.B.size();

    //Recorro las listas hasta que una de ellas se acabe
    while (i < n && j < m) {
        //Si las letras son iguales en sus respectivos punteros, se ponen en comunes
        if (datos.A[i] == datos.B[j]) {
            sol.comunes.push_back(datos.A[i]);
            i++; j++;
        }
        //Si no, se ponen en el soloX y se avanza el puntero dependiendo de cuál letra sea mayor
        else if (datos.A[i] < datos.B[j]) {
            sol.soloA.push_back(datos.A[i]);
            i++;
        }
        else {
            sol.soloB.push_back(datos.B[j]);
            j++;
        }
    }
    //Se remata las letras faltantes del puntero restante
    while (i < n) {
        sol.soloA.push_back(datos.A[i]);
        i++;
    }
    while (j < m) {
        sol.soloB.push_back(datos.B[j]);
        j++;
    }
    return sol;
}

//ESTO HACE EL COSTE O(n * log(n) + m * log(m))
void Ordenar(TipoDatos& datos) {
    std::sort(datos.A.begin(), datos.A.end());
    std::sort(datos.B.begin(), datos.B.end());
}


// Resuelve un caso de prueba
void resuelveCaso() {

    int n, m;
    cin >> n;
    TipoDatos datos;
    datos.A.resize(n);
    for (int i = 0; i < n; i++)
        cin >> datos.A[i];
    cin >> m;
    datos.B.resize(m);
    for (int i = 0; i < m; i++)
        cin >> datos.B[i];

    Ordenar(datos);

    TipoSolucion sol = resolver(datos);

    // imprimir comunes
    for (int j = 0; j < sol.comunes.size(); j++) {
        if (j > 0) cout << " ";
        cout << sol.comunes[j];
    }
    cout << "\n";

    // imprimir soloA
    for (int j = 0; j < sol.soloA.size(); j++) {
        if (j > 0) cout << " ";
        cout << sol.soloA[j];
    }
    cout << "\n";

    // imprimir soloB
    for (int j = 0; j < sol.soloB.size(); j++) {
        if (j > 0) cout << " ";
        cout << sol.soloB[j];
    }
    cout << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf());
     #endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
    #endif

    return 0;
}
