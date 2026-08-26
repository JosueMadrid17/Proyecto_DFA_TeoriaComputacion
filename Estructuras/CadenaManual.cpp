#include "CadenaManual.h"

CadenaManual::CadenaManual() {
    Primero = nullptr;
    Ultimo = nullptr;
    Longitud = 0;
}

CadenaManual::CadenaManual(const char* Texto) {
    Primero = nullptr;
    Ultimo = nullptr;
    Longitud = 0;

    Asignar(Texto);
}

CadenaManual::CadenaManual(const CadenaManual& OtraCadena) {
    Primero = nullptr;
    Ultimo = nullptr;
    Longitud = 0;

    CopiarDesde(OtraCadena);
}

CadenaManual::~CadenaManual() {
    Limpiar();
}

CadenaManual& CadenaManual::operator=(const CadenaManual& OtraCadena) {
    if (this != &OtraCadena) {
        Limpiar();
        CopiarDesde(OtraCadena);
    }
    return *this;
}

void CadenaManual::Asignar(const char* Texto) {
    Limpiar();

    if (Texto == nullptr) {
        return;
    }

    const char* Actual = Texto;

    while (*Actual != '\0') {
        AgregarCaracter(*Actual);
        Actual++;
    }
}

void CadenaManual::AgregarCaracter(char Caracter) {
    Nodo<char>* NuevoNodo = new Nodo<char>(Caracter);

    if (Primero == nullptr) {
        Primero = NuevoNodo;
        Ultimo = NuevoNodo;
    } else {
        Ultimo->EstablecerSiguiente(NuevoNodo);
        Ultimo = NuevoNodo;
    }
    Longitud++;
}

void CadenaManual::Limpiar() {
    Nodo<char>* Actual = Primero;

    while (Actual != nullptr) {
        Nodo<char>* Siguiente = Actual->ObtenerSiguiente();
        delete Actual;
        Actual = Siguiente;
    }

    Primero = nullptr;
    Ultimo = nullptr;
    Longitud = 0;
}

void CadenaManual::CopiarDesde(const CadenaManual& OtraCadena) {
    Nodo<char>* Actual = OtraCadena.Primero;

    while (Actual != nullptr) {
        AgregarCaracter(Actual->ObtenerDato());
        Actual = Actual->ObtenerSiguiente();
    }
}

int CadenaManual::ObtenerLongitud() const {
    return Longitud;
}

bool CadenaManual::EstaVacia() const {
    return Longitud == 0;
}

char CadenaManual::ObtenerCaracter(int Posicion) const {
    if (Posicion < 0 || Posicion >= Longitud) {
        return '\0';
    }

    Nodo<char>* Actual = Primero;
    int Indice = 0;

    while (Indice < Posicion) {
        Actual = Actual->ObtenerSiguiente();
        Indice++;
    }
    return Actual->ObtenerDato();
}

bool CadenaManual::EsIgual(const CadenaManual& OtraCadena) const {
    if (Longitud != OtraCadena.Longitud) {
        return false;
    }

    Nodo<char>* ActualA = Primero;
    Nodo<char>* ActualB = OtraCadena.Primero;

    while (ActualA != nullptr && ActualB != nullptr) {
        if (ActualA->ObtenerDato() != ActualB->ObtenerDato()) {
            return false;
        }

        ActualA = ActualA->ObtenerSiguiente();
        ActualB = ActualB->ObtenerSiguiente();
    }

    return true;
}

bool CadenaManual::EsIgual(const char* Texto) const {
    if (Texto == nullptr) {
        return Longitud == 0;
    }

    Nodo<char>* Actual = Primero;
    const char* CaracterTexto = Texto;

    while (Actual != nullptr && *CaracterTexto != '\0') {
        if (Actual->ObtenerDato() != *CaracterTexto) {
            return false;
        }

        Actual = Actual->ObtenerSiguiente();
        CaracterTexto++;
    }
    return Actual == nullptr && *CaracterTexto == '\0';
}

void CadenaManual::AgregarTexto(const char* Texto) {
    if (Texto == nullptr) {
        return;
    }

    const char* Actual = Texto;

    while (*Actual != '\0') {
        AgregarCaracter(*Actual);
        Actual++;
    }
}

void CadenaManual::AgregarCadena(const CadenaManual& OtraCadena) {
    Nodo<char>* Actual = OtraCadena.Primero;

    while (Actual != nullptr) {
        AgregarCaracter(Actual->ObtenerDato());
        Actual = Actual->ObtenerSiguiente();
    }
}
