//  Implementación del TAD Set con array dinámico ordenado y sin repeticiones

#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Set {
protected:
    static const int TAM_INICIAL = 5; // tamaño inicial del array dinámico

    // número de elementos del array
    int nelems;

    // tamaño del array
    int capacidad;

    // puntero al array que contiene los elementos ordenados (redimensionable)
    T* array;

public:

    // constructor: conjunto vacío
    Set() : nelems(0), capacidad(TAM_INICIAL), array(new T[capacidad]) {}

    // constructor: conjunto vacío reservando espacio para initCap elementos
    Set(int initCap) : nelems(0), capacidad(initCap), array(new T[capacidad]) {}

    // destructor
    ~Set() {
        libera();
    }

    // constructor por copia
    Set(Set<T> const& other) {
        copia(other);
    }

    // operador de asignación
    Set<T>& operator=(Set<T> const& other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }

    // Añadir un elemento. O(n), n=nelems
    void add(T const& elem) {
        bool found;
        int pos;

        /* binSearch(elem,found,pos);
        if (!found){
            shiftRightFrom(pos+1);
            array[pos+1] = elem;
            ++nelems;
            if (nelems == capacidad)
                amplia(capacidad*2);
        }*/

        // Usando busq. binaria de librería STL
        T* it = lower_bound(array, array+nelems, elem);
        if (it == array+nelems || *it != elem){
            pos = it - array; // Aritmética de punteros
            shiftRightFrom(pos);
            array[pos] = elem;
            ++nelems;
            if (nelems == capacidad)
                amplia(capacidad*2);
        }
    }

    // Borrar elemento elem. O(n), n=nelems
    void remove(T const& elem){
        bool found;
        int pos;

        /*binSearch(elem,found,pos);
        if (found) {
            shiftLeftFrom(pos);
            --nelems;
        }*/

        // Usando busq. binaria de librería STL
        T* it = lower_bound(array, array+nelems, elem);
        if (it != array+nelems && *it == elem) {
            pos = it - array; // Aritmética de punteros
            shiftLeftFrom(pos);
            --nelems;
        }
    }

    // Chequear pertenencia de e. O(log(n)), n=nelems
    bool contains(T const& elem) const {
        bool found;
        int pos;

        /*binSearch(elem,found,pos);
        return found;*/

        // Usando busq. binaria de librería STL
        return binary_search(array, array+nelems, elem);
    }

    // Consultar si el conjunto está vacío
    bool empty() const {
        return nelems == 0;
    }

    // Consultar tamaño. O(1)
    int size() const {
        return nelems;
    }

    // Relación de equivalencia. O(n), n = nelems
    bool operator==(Set<T>& other) const {
        if (nelems == other.nelems)
            return std::equal(array, array + nelems, other.array);
        else
            return false;
    }

    template <class E>
    friend ostream& operator<<(ostream& out, const Set<E>& s);


    // ----------------------------------------------------------
    // enrique juan gamboa
    // EDA-GDV35
    // ----------------------------------------------------------

    // Devuelve el máximo elemento. O(1) (El set esta ordenado ya)
    T getMax() const {
        if (nelems == 0) throw std::runtime_error("Conjunto vacío");
        return array[nelems - 1];
    }

    // Elimina el máximo elemento. O(1) (El set esta ordenado ya)
    void removeMax() {
        if (nelems == 0) throw std::runtime_error("Conjunto vacío");
        --nelems;
    }

    // Devuelve el mínimo elemento. O(1) (El set esta ordenado ya)
    T getMin() const {
        if (nelems == 0) throw std::runtime_error("Conjunto vacío");
        return array[0];
    }

    // Elimina el mínimo elemento. O(n) (El set esta ordenado ya), pero hay que desplazar todos los elems una pos)
    void removeMin() {
        if (nelems == 0) throw std::runtime_error("Conjunto vacío");
        for (int i = 1; i < nelems; ++i)
            array[i - 1] = array[i];
        --nelems;
    }


    // Operador de unión ||
    // Complejidad: O(n + m), donde n y m son los tamaños de los conjuntos.
    // Se recorren ambos arrays ordenados simultáneamente.
    Set<T> operator||(const Set<T>& other) const {
        Set<T> result(nelems + other.nelems);
        int i = 0, j = 0;

        while (i < nelems && j < other.nelems) {
            if (array[i] < other.array[j]) {
                result.add(array[i]);
                ++i;
            } else if (other.array[j] < array[i]) {
                result.add(other.array[j]);
                ++j;
            } else { // iguales
                result.add(array[i]);
                ++i; ++j;
            }
        }

        // Añadir los elementos restantes
        while (i < nelems) {
            result.add(array[i]);
            ++i;
        }
        while (j < other.nelems) {
            result.add(other.array[j]);
            ++j;
        }

        return result;
    }

    // ----------------------------------------------------------
    // Operador de intersección &&
    // Complejidad: O(n + m), donde n y m son los tamaños de los conjuntos.
    // Se recorren ambos arrays ordenados simultáneamente.
    Set<T> operator&&(const Set<T>& other) const {
        Set<T> result(min(nelems, other.nelems));
        int i = 0, j = 0;

        while (i < nelems && j < other.nelems) {
            if (array[i] < other.array[j]) {
                ++i;
            } else if (other.array[j] < array[i]) {
                ++j;
            } else { // iguales
                result.add(array[i]);
                ++i; ++j;
            }
        }

        return result;
    }

protected:

    void libera() {
        delete[] array;
    }

    // this está sin inicializar
    void copia(Set const& other) {
        capacidad = other.nelems + TAM_INICIAL;
        nelems = other.nelems;
        array = new T[capacidad];
        for (int i = 0; i < nelems; ++i)
            array[i] = other.array[i];
    }

    void amplia(int nuevaCap) {
        T * viejo = array;
        capacidad = nuevaCap;
        array = new T[capacidad];
        for (int i = 0; i < nelems; ++i)
            array[i] = std::move(viejo[i]);
        delete[] viejo;
    }

    void binSearch(const T& x, bool& found, int& pos) const {
        // Pre: los size primeros elementos de array están ordenados
        //      size >= 0

        pos = binSearchAux(x, 0, nelems - 1);
        found = (pos >= 0) && (pos < nelems) && (array[pos] == x);

        // Post : devuelve el mayor índice i (0 <= i <= nelems-1) que cumple
        //        array[i] <= x
        //        si x es menor que todos los elementos de array, devuelve -1
        //        found es true si x esta en array[0..nelems-1]
    }

    int binSearchAux(const T& x, int a, int b) const {
        // Pre: array está ordenado entre 0 .. nelems-1
        //      ( 0 <= a <= nelems ) && ( -1 <= b <= nelems ) && ( a <= b+1 )
        //      todos los elementos a la izquierda de 'a' son <= x
        //      todos los elementos a la derecha de 'b' son > x

        int p, m;

        if (a == b + 1)
            p = a - 1;
        else if (a <= b) {
            m = (a + b) / 2;
            if (array[m] <= x)
                p = binSearchAux(x, m + 1, b);
            else
                p = binSearchAux(x, a, m - 1);
        }
        return p;

        // Post: devuelve el mayor índice i (0 <= i <= nelems-1) que cumple
        //       array[i] <= x
        //       si x es menor que todos los elementos de array, devuelve -1
    }

    void shiftRightFrom(int i){
        for (int j = nelems; j > i; j--)
            array[j] = array[j-1];
    }

    void shiftLeftFrom(int i){
        for (; i < nelems-1; i++)
            array[i] = array[i+1];
    }

};

template <class T>
ostream& operator<<(ostream& out, Set<T> const& set) {
    //out << "{";
    //for (int i = 0; i < set.nelems-1; i++)
    //    out << set.array[i] << ",";
    //if (set.nelems > 0) out << set.array[set.nelems-1];
    //out << "}";
    for (int i = 0; i < set.nelems; ++i) {
        if (i) out << " ";
        out << set.array[i];
    }

    return out;
}

#endif //SET_H
