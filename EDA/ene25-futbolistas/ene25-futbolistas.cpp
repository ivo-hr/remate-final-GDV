/*
enjuga
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <utility>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>



using namespace std;

using Jugador = string;
using Equipo = string;



class GestorFutbolistas {
private:
    struct infoJugador {
        Equipo actual;
        unordered_set<Equipo> historico;
    };
    unordered_map<Jugador, infoJugador> infoJugadores;

    struct infoEquipo {
        list<Jugador> jugadores;
        unordered_map < Jugador, list<Jugador>::iterator> posJugador;
    };

    unordered_map<Equipo, infoEquipo> infoEquipos;
public:

    // Coste: O(1) al hacerse todo con hash maps y listas con iteradores
    void fichar(const Jugador& jugador, const Equipo& equipo) {
        //Busca el jugador actual, o lo crea
        auto& jugAct = infoJugadores[jugador];

        // Si existía de antes, borrarlo del equipo anterior si es diferente
        if (!jugAct.actual.empty() && jugAct.actual != equipo) {
            auto& eqAnt = infoEquipos[jugAct.actual];
            auto it = eqAnt.posJugador[jugador];
            eqAnt.jugadores.erase(it);
            eqAnt.posJugador.erase(jugador);
        }

        //Si no está ya en el equipo (incluye la creación de un jugador nuevo)
        if (jugAct.actual != equipo) {
            jugAct.actual = equipo;
            jugAct.historico.insert(equipo);

            //Actualización de la info del equipo actual (o crea el equipo)
            infoEquipos[equipo].jugadores.push_front(jugador);
            infoEquipos[equipo].posJugador[jugador] = infoEquipos[equipo].jugadores.begin();
        }
    }

    // Coste: O(1): se accede directamente a la info del jugador.
    Equipo equipoActual(const Jugador& jugador) const {

        auto it = infoJugadores.find(jugador);

        if (it != infoJugadores.end()) return it->second.actual;


        throw domain_error("Jugador inexistente");
    }

    // Coste: O(1) se accede directamente a la info del equipo
    int fichados(const Equipo& equipo) const {

        auto it = infoEquipos.find(equipo);

        if (it != infoEquipos.end()) return it->second.jugadores.size();

        throw domain_error("Equipo inexistente");
    }

    // Coste: O(min(n, j)), siendo j el número de jugadores en el equipo dado, es lo que hace el bucle for.
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        
        auto eqAct = infoEquipos.find(equipo);
        if (eqAct == infoEquipos.end()) throw domain_error("Equipo inexistente");
        
        list<Jugador> toRet;

        int i = 0;
        for (auto it = eqAct->second.jugadores.begin(); it != eqAct->second.jugadores.end() && i < n; it++) {
            toRet.push_back(*it);
            i++;
        }
        
        return toRet;
    }

    // Coste: O(1), .find() es lo más costoso y tiene ese coste.
    int cuantosEquipos(const Jugador& jugador) const {
        auto it = infoJugadores.find(jugador);

        if (it == infoJugadores.end()) return 0;

        return it->second.historico.size();
    }
};


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!cin) return false;

    GestorFutbolistas gestor;
    while (operacion != "FIN") {
        try {
            if (operacion == "fichar") {
                string jugador, equipo;
                cin >> jugador >> equipo;
                gestor.fichar(jugador, equipo);
            }
            else if (operacion == "equipo_actual") {
                string jugador;
                cin >> jugador;
                string equipo = gestor.equipoActual(jugador);
                cout << "El equipo de " << jugador << " es " << equipo << endl;
            }
            else if (operacion == "fichados") {
                string equipo;
                cin >> equipo;
                int n = gestor.fichados(equipo);
                cout << "Jugadores fichados por " << equipo << ": " << n << endl;
            }
            else if (operacion == "ultimos_fichajes") {
                string equipo;
                int n;
                cin >> equipo >> n;
                list<string> ultimos = gestor.ultimosFichajes(equipo, n);
                cout << "Ultimos fichajes de " << equipo << ": ";
                for (const auto& jugador : ultimos) {
                    cout << jugador << " ";
                }
                cout << endl;
            }
            else if (operacion == "cuantos_equipos") {
                string jugador;
                cin >> jugador;
                int n = gestor.cuantosEquipos(jugador);
                cout << "Equipos que han fichado a " << jugador << ": " << n << endl;
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }

    cout << "---\n";
    return true;
}

#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
