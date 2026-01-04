// enjuga


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct soluc {
    int x1;
    int x2;
    bool cruza;
     
};

// función que resuelve el problema
// Coste O(log N) siendo n el número de puntos, debido a hacer divide y vencerás. 
soluc resolver(vector<int>& A, vector<int>& B, int ini, int fin) {

    //Caso base: llegamos al último caso
    if (fin - ini == 0) {
        //comprobamos si las y son iguales
        if (A[ini] == B[ini])
            return {ini, A[ini], true};

        //si no, miramos dónde se encontraría
        //Estamos en el extremo izq, o sólo son vectores de 1 de long.
        if (ini == 0) {
            //si es solo de 1 de long, hay que comprobar si estaría delante o detrás. se cumple igual si estamos en el extremo
            if (A[ini] < B[ini]) return {ini, ini + 1, false};
            else return {-1, 0,false};
        }
        //Estamos en el extremo dcho
        else if (ini == (int)A.size() - 1) {
            return {ini, ini + 1, false};
        }
        
        int diff = A[ini] - B[ini];
        int diffAnt = A[ini-1] - B[ini-1];

        if (diff >= 0 && diffAnt <= 0) {
            return {ini-1, ini, false};
        }
        else return {ini, ini+1, false};
    }

    int mit = ini + (fin-ini)/2;

    int diff = A[mit] - B[mit];
    //Caso base comprobamos si las y son iguales
    if (diff == 0)
        return { mit, A[mit], true };

    //Si abajo es mayor que arriba, miramos para la dcha y viceversa
    else if (diff < 0)
        return resolver(A, B, mit+1, fin);
    else return resolver(A, B, ini, mit);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n = 0, dato;
    cin >> n;
    if (n == 0)
        return false;

    vector<int> lineA(n);

    for (int i = 0; i < n; i++) {
        cin >> dato;
        lineA[i] = dato;
    }
    vector<int> lineB(n);

    for (int i = 0; i < n; i++) {
        cin >> dato;
        lineB[i] = dato;
    }


    soluc sol = resolver(lineA, lineB, 0, n - 1);

    // escribir sol
    if (sol.cruza) {
        cout << "SI " << sol.x1 << endl;
    }
    else {
        cout << "NO " << sol.x1 << " " << sol.x2 << endl;
    }

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
    system("PAUSE");
#endif

    return 0;
}
