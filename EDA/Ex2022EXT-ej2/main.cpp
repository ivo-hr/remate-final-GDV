// Enrique Juan Gamboa
// EDA-GDV35
#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    // Coste: O(n)
    // recorre la lista para ubicar nodos; enlaces = O(1)
    //
    // Ej:
    // Lista: A - B - C - D - E - F - G - H
    // Segmento: [C D E], pos=2, lon=3, k=2
    //
    // Paso 1: localizar el bloque
    // A - B - [C D E] - F - G - H
    //
    // Paso 2: romper conexiones
    // B->sig salta a F
    // F->ant salta a B
    //
    // Paso 3: moverse k=2 nodos hacia atrás desde B
    // destino = A
    //
    // Paso 4: insertar el bloque después de A
    // A->sig = C
    // C->ant = A
    // E->sig = B
    // B->ant = E
    //
    // Resultado final:
    // A - [C D E] - B - F - G - H
    void adelantar(int pos, int lon, int k) {
        int n = this->size();

        // Ajustar longitud si se pasa del final
        if (pos + lon > n)
            lon = n - pos;

        //Comprobamos si todos los datos son válidos, si no, cest fini
        if (n <= 0 || lon <= 0 || k <= 0 || pos >= n || pos - k < 0)
            return;

        // 1. Localizar el inicio del segmento
        Nodo* ini = this->fantasma->sig;
        for (int i = 0; i < pos; ++i)
            ini = ini->sig;

        // 2. Localizar el final del segmento
        Nodo* fin = ini;
        for (int i = 1; i < lon; ++i)
            fin = fin->sig;

        // 3. Guardar los nodos antes y después del segmento
        Nodo* bef = ini->ant;
        Nodo* aft = fin->sig;

        // 4. Desconectar el segmento
        bef->sig = aft;
        aft->ant = bef;

        // 5. Buscar nuevo lugar de inserción (k posiciones antes)
        Nodo* dest = bef;
        for (int i = 0; i < k; ++i) dest = dest->ant;

        // 6. Insertar el segmento después de dest
        Nodo* destSig = dest->sig;
        dest->sig = ini;
        ini->ant = dest;
        fin->sig = destSig;
        destSig->ant = fin;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, length, dif);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i){
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()){
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#define DOMJUDGE
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
