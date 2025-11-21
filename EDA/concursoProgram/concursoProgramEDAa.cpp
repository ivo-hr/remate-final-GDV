
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


void procesaEnvios(unordered_map<std::string, TeamInfo>& resultados) {
    std::string equipo, problema, veredicto;
    int minuto;

    std::cin >> equipo;
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
        if (prob.resuelto == false) {
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


}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    
    unordered_map<std::string, TeamInfo> res;


    procesaEnvios(res);

    // Se imprime la salida
    std::vector<TeamInfo> rank;

    //Metemos los equipos en un vector
    for (auto& r : res)
        rank.push_back(r.second);

    auto comparador = [](const TeamInfo& a, const TeamInfo& b) {

        //NumResueltos
        int rDiff = b.resueltos - a.resueltos;
        if (rDiff != 0)
            return rDiff < 0;

        //Tiempo en resolver
        int tDiff = b.tiempoTotal - a.tiempoTotal;
        if (tDiff != 0)
            return tDiff > 0;
        

        //Orden alfabético
        return a.nombre < b.nombre;

        };

    std::sort(rank.begin(), rank.end(), comparador);


    for (auto& team : rank)
        std::cout << team.nombre << " " << team.resueltos << " " << team.tiempoTotal << "\n";


    std::cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
//#define DOMJUDGE
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