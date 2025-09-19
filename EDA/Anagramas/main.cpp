// Enrique Juan Gamboa
// EDA-GDV35


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

//Coste O(n) al recorrer solo la longitud de las palabras y los 26 caracteres del alfabeto
bool resolver(std::vector<std::string> datos) {
    int lenPal = datos[0].size();
    //Vamos a contar cuántas veces aparece cada letra
    std::vector<int> numLetras(26, 0);

    for (int i = 0; i < lenPal; i++) {
        //Si aparece en la primera palabra, sumamos en su posición del vector
        //Restamos a por ser la primera letraa que puede aparecer, no queremos todo el ascii
        numLetras[datos[0][i] - 'a'] += 1;
        //Si aparece en la seguna, restamos
        numLetras[datos[1][i] - 'a'] -= 1;
    }
    //Buscamos en el vector de numLetras que sea todo 0 (hemos sumado y restado 1 por cada letra en cada palabra)
    for (int i = 0; i < numLetras.size(); i++)
        //Si encontramos un 1 o -1, pafuera
        if (numLetras[i] != 0)
            return false;

    //Si llegamos hasta aquí, es que ha salido todo bien
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    std::vector<std::string> datos(2);
    for (int i = 0; i < 2; i++) {
        std::cin >> datos[i];
    }

    if (resolver(datos))
        std::cout << "SI" << std::endl;
    else
        std::cout << "NO" << std::endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}