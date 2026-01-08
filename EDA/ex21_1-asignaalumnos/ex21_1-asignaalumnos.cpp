#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e << " ";
    return out;
}

/*
EXPLICACIÓN DE LA SOLUCIÓN:

Tupla solución:
- vector<vector<int>> asignaciones: asignaciones[tarea] = {alumno1, alumno2}
  Indica qué 2 alumnos realizan cada tarea

Marcadores:
- tareasXalumno[i]: número de tareas asignadas al alumno i (no puede superar t)
- alumnosXtarea[k]: número de alumnos asignados a la tarea k (debe ser 2)
- sumaAct: suma actual de preferencias
- sumaMax: mejor suma encontrada hasta ahora

Recorrido del árbol:
- Para cada tarea K, asignamos 2 alumnos
- Probamos todas las combinaciones posibles de alumnos
- Cuando una tarea tiene 2 alumnos, pasamos a la siguiente

*/

// función que resuelve el problema
void resolver(int k, int a, int t, int n,
    vector<vector<int>>& preferencias,
    vector<vector<int>>& asignaciones,
    vector<int>& tareasXalumno,
    int sumaAct, int& sumaMax,
    vector<vector<int>>& mejorSol,
    vector<int>& maxNotaXtarea) {

    // Caso base: hemos asignado 2 alumnos a todas las tareas
    if (k == n) {
        if (sumaAct > sumaMax) {
            sumaMax = sumaAct;
            mejorSol = asignaciones;
        }
        return;
    }

    //Poda
    int cota = 0;
    for (int i = k; i < n; i++) {
        cota += maxNotaXtarea[i];
    }
    // Si la suma de lo mejor que puede pasar (sin contar límites) con la suma actual 
    // no es mejor de lo que ya ha pasado, pasamos de recorrerlo.
    if (sumaAct + cota <= sumaMax) return;

    // Asignamos el primer alumno a la tarea k
    for (int i = 0; i < a; i++) {
        if (tareasXalumno[i] < t) { // El alumno puede hacer más tareas
            // Marcar primer alumno
            tareasXalumno[i]++;
            asignaciones[k][0] = i;
            sumaAct += preferencias[i][k];

            // Asignamos el segundo alumno a la tarea k
            // Para evitar repeticiones, j > i
            for (int j = i + 1; j < a; j++) {
                if (tareasXalumno[j] < t) { // El alumno puede hacer más tareas
                    // Marcar segundo alumno
                    tareasXalumno[j]++;
                    asignaciones[k][1] = j;
                    sumaAct += preferencias[j][k];

                    // Recursión: pasar a la siguiente tarea
                    resolver(k + 1, a, t, n, preferencias, asignaciones,
                        tareasXalumno, sumaAct, sumaMax, mejorSol, maxNotaXtarea);

                    // Desmarcar segundo alumno
                    tareasXalumno[j]--;
                    sumaAct -= preferencias[j][k];
                }
            }

            // Desmarcar primer alumno
            tareasXalumno[i]--;
            sumaAct -= preferencias[i][k];
        }
    }
}

// Resuelve un caso de prueba
bool resuelveCaso() {
    int n, a, t;
    cin >> n >> a >> t;
    if (n == 0 && a == 0 && t == 0) return false;

    // Leer preferencias
    vector<vector<int>> preferencias(a, vector<int>(n));
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> preferencias[i][j];
        }
    }

    //PODA
    vector<int> maxNotaXtarea(n, 0);
    for (int tarea = 0; tarea < n; tarea++) {
        int n1 = 0, n2 = 0;
        for (int alum = 0; alum < a; alum++) {
            if (n1 < preferencias[alum][tarea]) {
                n2 = n1;
                n1 = preferencias[alum][tarea];
            }
            else if (n2 < preferencias[alum][tarea]) {
                n2 = preferencias[alum][tarea];
            }
        }
        maxNotaXtarea[tarea] = n1 + n2;
    }

    vector<vector<int>> asignaciones(n, vector<int>(2, -1)); // 2 alumnos por tarea
    vector<vector<int>> mejorSol(n, vector<int>(2, -1));
    vector<int> tareasXalumno(a, 0);
    int sumaMax = 0;


   

    // Resolver
    resolver(0, a, t, n, preferencias, asignaciones, tareasXalumno, 0, sumaMax, mejorSol, maxNotaXtarea);

    // Imprimir solución
    cout << sumaMax << endl;

    // Para depurar: imprimir las asignaciones
    /*
    for (int i = 0; i < n; i++) {
        cout << mejorSol[i][0] << " " << mejorSol[i][1] << " ";
    }
    cout << endl;
    */

    return true;
}

#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}