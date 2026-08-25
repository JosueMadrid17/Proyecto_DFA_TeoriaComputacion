#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T Dato;
    Nodo<T>* Siguiente;

public:
    Nodo(const T& DatoNuevo) {
        Dato = DatoNuevo;
        Siguiente = nullptr;
    }

    T& ObtenerDato() {
        return Dato;
    }

    const T& ObtenerDato() const {
        return Dato;
    }

    Nodo<T>* ObtenerSiguiente() const {
        return Siguiente;
    }

    void EstablecerSiguiente(Nodo<T>* NodoSiguiente) {
        Siguiente = NodoSiguiente;
    }
};

#endif
