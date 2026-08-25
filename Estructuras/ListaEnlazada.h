#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include "Nodo.h"

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* Primero;
    Nodo<T>* Ultimo;
    int Cantidad;

    void CopiarDesde(const ListaEnlazada<T>& OtraLista) {
        Nodo<T>* Actual = OtraLista.Primero;
        while (Actual != nullptr) {
            Agregar(Actual->ObtenerDato());
            Actual = Actual->ObtenerSiguiente();
        }
    }

public:
    ListaEnlazada() {
        Primero = nullptr;
        Ultimo = nullptr;
        Cantidad = 0;
    }

    ListaEnlazada(const ListaEnlazada<T>& OtraLista) {
        Primero = nullptr;
        Ultimo = nullptr;
        Cantidad = 0;

        CopiarDesde(OtraLista);
    }

    ~ListaEnlazada() {
        Limpiar();
    }

    ListaEnlazada<T>& operator=(const ListaEnlazada<T>& OtraLista) {
        if (this != &OtraLista) {
            Limpiar();
            CopiarDesde(OtraLista);
        }

        return *this;
    }

    void Agregar(const T& DatoNuevo) {
        Nodo<T>* NuevoNodo = new Nodo<T>(DatoNuevo);

        if (Primero == nullptr) {
            Primero = NuevoNodo;
            Ultimo = NuevoNodo;
        } else {
            Ultimo->EstablecerSiguiente(NuevoNodo);
            Ultimo = NuevoNodo;
        }
        Cantidad++;
    }

    void AgregarAlInicio(const T& DatoNuevo) {
        Nodo<T>* NuevoNodo = new Nodo<T>(DatoNuevo);

        NuevoNodo->EstablecerSiguiente(Primero);
        Primero = NuevoNodo;

        if (Ultimo == nullptr) {
            Ultimo = NuevoNodo;
        }
        Cantidad++;
    }

    bool Obtener(int Posicion, T& Resultado) const {
        if (Posicion < 0 || Posicion >= Cantidad) {
            return false;
        }

        Nodo<T>* Actual = Primero;
        int Indice = 0;

        while (Indice < Posicion) {
            Actual = Actual->ObtenerSiguiente();
            Indice++;
        }

        Resultado = Actual->ObtenerDato();
        return true;
    }

    bool EliminarEnPosicion(int Posicion) {
        if (Posicion < 0 || Posicion >= Cantidad) {
            return false;
        }

        if (Posicion == 0) {
            Nodo<T>* NodoEliminar = Primero;

            Primero = Primero->ObtenerSiguiente();
            delete NodoEliminar;
            Cantidad--;

            if (Cantidad == 0) {
                Ultimo = nullptr;
            }

            return true;
        }

        Nodo<T>* Anterior = Primero;
        int Indice = 0;

        while (Indice < Posicion - 1) {
            Anterior = Anterior->ObtenerSiguiente();
            Indice++;
        }

        Nodo<T>* NodoEliminar = Anterior->ObtenerSiguiente();

        Anterior->EstablecerSiguiente(
            NodoEliminar->ObtenerSiguiente()
            );

        if (NodoEliminar == Ultimo) {
            Ultimo = Anterior;
        }

        delete NodoEliminar;
        Cantidad--;
        return true;
    }

    void Limpiar() {
        Nodo<T>* Actual = Primero;

        while (Actual != nullptr) {
            Nodo<T>* Siguiente = Actual->ObtenerSiguiente();

            delete Actual;

            Actual = Siguiente;
        }

        Primero = nullptr;
        Ultimo = nullptr;
        Cantidad = 0;
    }

    int ObtenerCantidad() const {
        return Cantidad;
    }

    bool EstaVacia() const {
        return Cantidad == 0;
    }

    Nodo<T>* ObtenerPrimero() const {
        return Primero;
    }
};

#endif
