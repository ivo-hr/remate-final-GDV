/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:

*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    // Complejidad: O(n), siendo n el tamaño de la cola. Se recorre la cola y se meten sus elementos en dos pseudo-colas, se invierte la cola de 
    // negativos y luego se juntan de nuevo.
    void reordena() {
        // Para acceder a los atributos de queue hay que escribir this->...
        //Caso base: cola vacía/un solo elemento
        if (this->empty() || this->prim == this->ult) return;

        //Vamos a crear dos pseudo-colas: la de positivos y la de negativos, en un solo recorrido de la cola. las dos estarán separadas.
        Nodo* posFirst = nullptr;
        Nodo* posUlt = nullptr;
        Nodo* negFirst = nullptr;
        Nodo* negUlt = nullptr;

        Nodo* curr = this->prim;

        while (curr != nullptr) {
            Nodo* sigCurr = curr->sig;

            //Si es positivo, a la lista de positivos
            if (curr->elem >= 0) {
                //Si es el primero en la lista, es la cabeza y la cola
                if (posFirst == nullptr) {
                    posFirst = curr;
                    posUlt = curr;
                }
                //Le metemos al final
                else {
                    posUlt->sig = curr;
                    posUlt = curr;
                }
            }
            //Igual pero con negativos
            else {
                if (negFirst == nullptr) {
                    negFirst = curr;
                    negUlt = curr;
                }
                else {
                    negUlt->sig = curr;
                    negUlt = curr;
                }
            }
            //Siempre será el último en su lista, el siguiente a él siempre será nada
            curr->sig = nullptr;

            //Avanzamos el actual hasta el final de la lista
            curr = sigCurr;
        }

        //Reordenamos la lista de negativos para que sea al revés.
        Nodo* negInvFirst = nullptr;
        Nodo* negInvLast = negFirst;
        curr = negFirst;

        while (curr != nullptr) {
            //Guardamos el siguiente al actual
            Nodo* sigCurr = curr->sig;

            //El siguiente al actual será el primero de la lista invertida
            curr->sig = negInvFirst;
            //El primero de la lista invertida será el actual
            negInvFirst = curr;

            //Avanzamos al siguiente nodo
            curr = sigCurr;
        }

        //Juntamos las dos listas
        if (posFirst != nullptr && negInvFirst != nullptr) {
            negInvLast->sig = posFirst;

            this->prim = negInvFirst;
            this->ult = posUlt;
        }
        //Sólo hay negativos
        else if (negInvFirst != nullptr) {
            this->prim = negInvFirst;
            this->ult = negInvLast;
        }
        //Sólo hay positivos
        else {
            this->prim = posFirst;
            this->ult = posUlt;
        }
    }


};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, e;
    queue_plus<int> q;
    std::cin >> n;
    if (n == 0) return false;
    for (int i = 0; i < n; ++i) {
        std::cin >> e;
        q.push(e);
    }

    q.reordena();

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }

    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
    return true;
}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}