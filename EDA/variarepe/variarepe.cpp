//enjuga
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void generar_variaciones(int m, int n, string palabra_actual, vector<string>& resultado) {
    // Caso base: si la palabra tiene la longitud deseada, la añadimos al resultado
    if (palabra_actual.length() == n) {
        resultado.push_back(palabra_actual);
        return;
    }

    // Caso recursivo: añadimos cada letra posible y continuamos
    for (int i = 0; i < m; i++) {
        char letra = 'a' + i;  // Convertimos índice a letra (a, b, c, ...)
        generar_variaciones(m, n, palabra_actual + letra, resultado);
    }
}

void generar_variaciones_norep(int m, int n, string palabra_actual, bool usado[], vector<string>& resultado) {
    // Caso base: si la palabra tiene la longitud deseada, la añadimos al resultado
    if (palabra_actual.length() == n) {
        resultado.push_back(palabra_actual);
        return;
    }

    // Caso recursivo: añadimos cada letra posible y continuamos
    for (int i = 0; i < m; i++) {
        //Saltarnos la letra si se va a repetir
        if (!usado[i]) {
            char letra = 'a' + i;  // Convertimos índice a letra (a, b, c, ...)
            usado[i] = true;
            generar_variaciones_norep(m, n, palabra_actual + letra, usado, resultado);
            usado[i] = false; //Para lo sieguente que se haga
            }

    }
}

/**
 * Resuelve un caso de prueba generando todas las variaciones.
 *
 * @param m número de letras a considerar (las m primeras del alfabeto)
 * @param n tamaño de cada palabra
 */
void resolver_caso(int m, int n) {
    vector<string> resultado;
    bool usado[26] = {false};
    generar_variaciones_norep(m, n, "", usado, resultado);

    // Imprimir todas las variaciones
    for (const string& palabra : resultado) {
        cout << palabra << endl;
    }
    cout << endl;  // Línea en blanco después de cada caso
}

int main() {
    int m, n;

    // Lectura de entrada y procesamiento
    while (cin >> m >> n) {
        resolver_caso(m, n);
    }

    return 0;
}