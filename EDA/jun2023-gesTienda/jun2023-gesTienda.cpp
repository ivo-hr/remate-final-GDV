/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include <unordered_map>
#include <queue>
#include <map>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
            (_anio == other._anio && _mes < other._mes) ||
            (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h) {
    int d, m, a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream& salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

using Codigo = string;
using Cliente = string;

class Tienda {
private:

    struct infoProd {
        map<Fecha, int> entradas;
        int cantTotal = 0;
        queue<Cliente> enEspera;
    };

    unordered_map<Codigo, infoProd> productos;

public:
    //Coste: O(log(f) + c), siendo f la fecha que creamos y accedemos y c el número de clientes en la lista de espera.
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {
        auto& prodAct = productos[cod];

        prodAct.entradas[f] += cant;
        prodAct.cantTotal += cant;
        vector<Cliente> toRet;

        //Si hay gente en la lista de espera, se puede suponer que no quedan cosas en otras fechas 
        // y el total es la cantidad que acabamos de sumar -> les damos de esta entrega hasta que 
        // se acaben existencias o se vacíe la lista de espera
        while (prodAct.cantTotal > 0 && !prodAct.enEspera.empty()) {
            prodAct.entradas[f]--;
            prodAct.cantTotal--;
            toRet.push_back(prodAct.enEspera.front());
            prodAct.enEspera.pop();
        }
    

        return toRet;
    }

    //Coste en caso peor: O(n), n siendo los registros de fecha, y habiendo existencias sólo en la ultima fecha del mapa
    pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli) {

        pair<bool, Fecha> toRet = { false, {0,0,0} };

        //Si no existe el producto se crea para poder añadir al cliente a su lista de espera, 
        // pero ya se return false
        auto& prodAct = productos[cod];
        if (prodAct.cantTotal <= 0) {
            prodAct.enEspera.push(cli);
            return { false, {0,0,0} };
        }
        
        //Si pasamos el primer if ya sabemos que hay productos en alguna fecha, 
        // las recorremos en orden hasta encontrar una con productos
        for (auto it = prodAct.entradas.begin(); it != prodAct.entradas.end(); it++) {
            if (it->second > 0) {
                //Le quitamos los productos a la fecha y a la cuenta total
                it->second--;
                prodAct.cantTotal--;
                
                //Devolvemos true y la fecha
                return { true, it->first };
            }
        }

        //Para el mensaje de error
        return { false, {0,0,0} };
    }

    //Coste: O(1), se busca el producto con el mapa
    int cuantos(Codigo const& cod) const {
        auto it = productos.find(cod);

        if (it == productos.end()) return 0;
        else return it->second.cantTotal;
    }

    //Coste: O(1), se busca el producto con el mapa
    bool hay_esperando(Codigo const& cod) const {
        auto it = productos.find(cod);

        if (it == productos.end()) return false;
        else return !it->second.enEspera.empty();
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        }
        else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool, Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            }
            else
                cout << "EN ESPERA\n";
        }
        else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        }
        else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
    return true;
}


#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}