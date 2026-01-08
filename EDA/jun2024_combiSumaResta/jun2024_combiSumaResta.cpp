/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:

Preguntas:

Indica y explica el formato de la tupla solución: vector<char> signos, de tamaño n-1, indicando los signos entre cada número.
Alternativamente, se puede hacer de vector<int> signos, alamacenando +1 o menos 1, para multiplicar cada índice.

¿Cuándo se da el caso peor? Cuando tiene que probar varias veces cada combinación de signos

Indica cuántas llamadas (en función de n) genera el algoritmo en dicho caso.
Al ser la tupla solución el signo que va entre n(i) y n(i+1) (positivo o negativo) el peor caso es recorrer cada caso de signo,
siendo así 2^(n-1)

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema y justificación del coste
bool entreSignos(vector<int>& nums, vector<int>& soluc, int n, int M, int k, int sumAct) {

    //Caso base: llegamos al final
    if (k == n) {
        if (sumAct + nums[k] == M) {
            soluc[k-1] = +1;
            //Realmente la suma al actual no hace falta; ya tenemos la solucion
            //sumAct += nums[k];

            //Hemos encontrado solución, cortamos ya la busqueda
            return true;
        }
        else if (sumAct - nums[k] == M) {
            soluc[k-1] = -1;
            //Realmente la suma al actual no hace falta; ya tenemos la solucion
            //sumAct -= nums[k];

            //Hemos encontrado solución, cortamos ya la busqueda
            return true;
        }
        //No hay solución, y hemos probado todas las combis :(
        else {
            return false;
        }
    }


    //Poda aquí: si la suma/resta de todos los números restantes da menor que/mayor que M, saltamos la búsqueda por esta rama
    int temp = 0;
    for (int i = k; i <= n; i++) {
        temp += nums[i];
    }
    if ((sumAct + temp < M) || (sumAct - temp > M)) {
        return false;
    }

    
    //Probamos suma:
    sumAct += nums[k];
    soluc[k-1] = +1;
    //Si se soluciona, escapamos sin calcular la rama de la resta
    if (entreSignos(nums, soluc, n, M, k + 1, sumAct)) return true;

    //Reiniciamos
    sumAct -= nums[k];



    //Probamos resta
    sumAct -= nums[k];
    soluc[k-1] = -1;
    //Si se soluciona, escapamos
    if (entreSignos(nums, soluc, n, M, k + 1, sumAct)) return true;


    //Si llegamos hasta aquí, no hay solución
    return false;




}

void resuelveCaso() {
    int n = 0, M;
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v)
        cin >> e;

    //Caso base: n = 0
    if (n == 0) {
        //Comprobamos si M es 0 (es el único numero al que se puede llegar con 0 elementos)
        if (M == 0) {
            cout << "SI" << endl;
            return;
        }
        else {
            cout << "NO" << endl;
            return;
        }

    }

    //Caso base: n = 1
    if (n == 1) {
        //Devolvemos si el número v[0] es igual a M, ya que no se puede realizar ninguna operación
        cout << (v[0] == M ? "SI" : "NO") << endl;
        return;
    }

    vector<int> soluc(n-1);
    // llamada a función que resuelve el problema

    //Empezamos con la primera suma/resta, y el número actual es el primer número del vector
    bool solucionado = entreSignos(v, soluc, n-1, M, 1, v[0]);
    // salida de datos

    cout << (solucionado ? "SI" : "NO") << endl;

}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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