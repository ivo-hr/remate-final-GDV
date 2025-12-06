/*
ENRIQUE JUAN GAMBOA
EDA-GDV36
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility>
#include <list>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

using paciente = string;
using gravedad = int;

class urgencias {
protected:

    // Tres colas: permiten borrar/insertar O(1) y mantener orden por gravedad.
    list<paciente> cola[3];

    struct InfoPaciente {
        gravedad g;
        list<paciente>::iterator it;
    };

    // Hashmap: acceso O(1) para existencia, gravedad y posición exacta.
    unordered_map<paciente, InfoPaciente> mapaPacientes;

    // Set: mantiene recuperados ordenados y sin repetición automáticamente.
    set<paciente> conjuntoRecuperados;

public:

    //  insertar en lista y hashmap es O(1). Coste O(1) promedio.
    void nuevo_paciente(paciente p, gravedad g) {
        if (g < 1 || g > 3) throw domain_error("Gravedad incorrecta");
        if (mapaPacientes.count(p)) throw domain_error("Paciente repetido");

        int i = g - 1;
        cola[i].push_back(p);
        auto itLista = prev(cola[i].end());
        mapaPacientes.emplace(p, InfoPaciente{ g, itLista });
    }

    //  obtener gravedad en hashmap es O(1). Coste O(1) promedio.
    int gravedad_actual(paciente p) const {
        auto it = mapaPacientes.find(p);
        if (it == mapaPacientes.end()) throw domain_error("Paciente inexistente");
        return it->second.g;
    }

    //  recorrer 3 colas y pop_front es O(1). Coste O(1) promedio.
    paciente siguiente() {
        for (int i = 2; i >= 0; --i) {
            if (!cola[i].empty()) {
                paciente p = cola[i].front();
                cola[i].pop_front();
                mapaPacientes.erase(p);
                return p;
            }
        }
        throw domain_error("No hay pacientes");
    }

    //  borrar por iterador y recolocar en list es O(1). Coste O(1) promedio.
    void mejora(paciente p) {
        auto it = mapaPacientes.find(p);
        if (it == mapaPacientes.end()) throw domain_error("Paciente inexistente");

        gravedad g = it->second.g;
        int i = g - 1;

        if (g == 1) { // leve → recuperado
            cola[i].erase(it->second.it);
            mapaPacientes.erase(it);
            conjuntoRecuperados.insert(p);
            return;
        }

        cola[i].erase(it->second.it);
        gravedad gNueva = g - 1;
        int iNueva = gNueva - 1;

        cola[iNueva].push_front(p);
        it->second.g = gNueva;
        it->second.it = cola[iNueva].begin();
    }

    //  recorrer set ordenado para copiar. Coste O(R).
    list<paciente> recuperados() const {
        list<paciente> res;
        for (const auto& p : conjuntoRecuperados) res.push_back(p);
        return res;
    }
};

bool resuelveCaso() {
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin) return false;

    urgencias sala;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            }
            else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            }
            else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto& p : lista) cout << ' ' << p;
                cout << '\n';
            }
            else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            }
        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }

        cin >> orden;
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