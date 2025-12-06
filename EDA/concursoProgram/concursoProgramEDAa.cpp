
//Enrique Juan Gamboa
// EDA-GDV35

#include <iostream>
#include <fstream>
#include <string>
#include "hashmap_eda.h"
#include <algorithm>


//Rompe con el uso de unordered map!
//using namespace std;

struct ProbInfo {
    bool resuelto = false;
    int tiempoAcierto = 0;
    int intentosAcierto = 0;
};

struct TeamInfo {
    std::string nombre;
    unordered_map<std::string, ProbInfo> probs;
    int resueltos = 0;
    int tiempoTotal = 0;
};

struct TeamRes {
    std::string nombre;
    int resueltos = 0;
    int tiempoTotal = 0;

    bool operator<(const TeamRes& other) const {
        int rDiff = resueltos - other.resueltos;
        if (rDiff != 0)
            return rDiff > 0;

        int tDiff = tiempoTotal - other.tiempoTotal;
        if (tDiff != 0)
            return tDiff < 0;

        return nombre < other.nombre;
    }
};

// El coste variará dependiendo del número de equipos y problemas: si es mayor el de equipos, el coste será O(e*log(e)). Si es el de problemas, puede llegar a ser O(p)
std::vector<TeamRes> procesaEnvios(unordered_map<std::string, TeamInfo>& resultados) {
    std::string equipo, problema, veredicto;
    int minuto;

    std::vector<TeamRes> toRet;

    std::cin >> equipo;
    //Bucle de coste lineal en función al Nº problemas --> coste O(p)
    while (equipo != "FIN") {
        std::cin >> problema >> minuto >> veredicto;

        //Si no está el equipo, lo meto
        if (resultados.count(equipo) == 0) {

            resultados[equipo] = TeamInfo();
            resultados[equipo].nombre = equipo;
        }

        //Procesado de la info
        TeamInfo& team = resultados[equipo];
        ProbInfo& prob = team.probs[problema];
        //Si no está resuelto el problema aún
        if (!prob.resuelto) {
            //Miramos si esta correcto
            if (veredicto == "AC") {
                //si sí, lo asiganmos como resuelto y calculamos cosillas
                prob.resuelto = true;
                prob.tiempoAcierto = minuto;

                team.resueltos++;
                team.tiempoTotal += prob.tiempoAcierto + prob.intentosAcierto * 20;
            }
            //Si no está correcto, es un intento fallido y se suma al contador del problema
            else
                prob.intentosAcierto++;
        }


            std::cin >> equipo;
    }

    //Bucle de coste lineal en función al Nº equipos --> coste O(e)
    for (auto& team : resultados) {
        TeamRes t;
        t.nombre = team.second.nombre;
        t.resueltos = team.second.resueltos;
        t.tiempoTotal = team.second.tiempoTotal;

        toRet.push_back(t);
    }
    
    //Algoritmo de ordenación en función al Nº de equipos --> coste O(e*log(e))
     std::sort(toRet.begin(), toRet.end());


     return toRet;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    
    unordered_map<std::string, TeamInfo> teams;


    std::vector<TeamRes> rank = procesaEnvios(teams);



    for (auto& team : rank)
        std::cout << team.nombre << " " << team.resueltos << " " << team.tiempoTotal << "\n";


    std::cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#define DOMJUDGE
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::std::cin to casos.txt
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