/*

enjuga

Tupla solución: vols[n], donde n es el número de voluntarios. 
en cada posición del vector i (voluntario) se guarda el área asignado a él. 
-1 indica que no se le ha asignado área.


Ejemplo de aplicación de poda por estimación:
Implementada ya, se calcula si al recoger la mayor cantidad de lodo posible de cada voluntario se supera la mejor 
cantidad hallada. si es así, se prosigue por esta opción. si no, se omite.


*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, vector<T> const& v) {
    for (auto& e : v) out << e << " ";
    return out;
}


// función que resuelve el problema
// K es la capa, N el número de voluntarios, M numero de áreas, L mínimo de areas impolutas
// Coste en el peor caso: O(((m+1)^n)*m) -> se puede elegir entre m zonas o no coger ninguna (m + 1) por el recorrido del árbol
//                                          de n capas. La última multiplicación es el recorrido final en el caso base para ver
//                                          si se cumple la condición
void resolver(vector<int>& soluc, int k, int n, int m, int l, vector<int>& kilosPorArea, vector<vector<int>> const& kilosPorVoluntario,
              int lodoCogido, int& mejorLodo, vector<int>& mejorSoluc, vector<int> maxXVoluntario) {
    
    // Caso base
    if (k == n) {
        // Contamos áreas limpias
        int impolutas = 0;

        for(int i = 0; i < m; i++) 
            if (kilosPorArea[i] == 0) 
                impolutas++;

        // Si se cumple la restricción y es mejor que la solucion actual
        if (impolutas >= l && lodoCogido > mejorLodo) {
            mejorLodo = lodoCogido,
            mejorSoluc = soluc;
        }

        // Acabamos esta rama
        return;
    }

    //PODA x ESTIMACION VA AQUí
    int optimismo = lodoCogido;
    //Desde la capa en la que estamos, miramos lo mejor que puede coher cada voluntario. 
    //si no pasa de la mejor solución actual, pasamos
    for (int i = k; i < n; i++) 
        optimismo += maxXVoluntario[i];

    if (optimismo <= mejorLodo)
        return;

    // Probar sin asignar el voluntario
    soluc[k] = -1;
    resolver(soluc, k+1, n, m, l, kilosPorArea, kilosPorVoluntario,
             lodoCogido, mejorLodo, mejorSoluc, maxXVoluntario);

    // Probar asignar al voluntario a cada una de las áreas
    for (int i = 0; i < m; i++) {
        soluc[k] = i;

        int limpiado = kilosPorVoluntario[k][i];

        kilosPorArea[i] -= limpiado;
        if (kilosPorArea[i] < 0) {
            limpiado += kilosPorArea[i];
            kilosPorArea[i] = 0;
        }

        resolver(soluc, k+1, n, m, l, kilosPorArea, kilosPorVoluntario, 
                 lodoCogido + limpiado, mejorLodo, mejorSoluc, maxXVoluntario);
        // Backtrack
        kilosPorArea[i] += limpiado;

    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> kilosPorArea(m);
    for (int i = 0; i < m; ++i) {
        cin >> kilosPorArea[i];
    }
    vector<vector<int>> kilosPorVoluntario(n, vector<int>(m));
    vector<int> maxXVoluntario(n, -1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            cin >> kilosPorVoluntario[i][j];
            //Para la poda por estimación optimista guardamos el máximo de recogida posible x voluntario
            if (kilosPorVoluntario[i][j] > maxXVoluntario[i])
                maxXVoluntario[i] = kilosPorVoluntario[i][j];
            }
    
    vector<int> soluc(n, -1);
    vector<int> mejorSoluc(n, -1);

    int mejorLodo = -1;
    int k = 0;
    resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario, 0, mejorLodo, mejorSoluc, maxXVoluntario);
    if (mejorLodo < 0) cout << "IMPOSIBLE" << endl;
    else cout << mejorLodo << endl;
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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
