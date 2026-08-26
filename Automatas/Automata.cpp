#include "Automata.h"
#include "Estado.h"
#include "Simbolo.h"
#include "Transicion.h"

Automata::Automata() {
    EstadoInicial = nullptr;
    Validado = false;
}

Automata::~Automata() {
    Vaciar();
}

Estado* Automata::AgregarEstado(const char* Nombre) {
    Estado* NuevoEstado = new Estado(Nombre);
    Estados.Agregar(NuevoEstado);
    Validado = false;
    return NuevoEstado;
}

Simbolo* Automata::AgregarSimbolo(const char* Valor) {
    Simbolo* NuevoSimbolo = new Simbolo(Valor);
    Alfabeto.Agregar(NuevoSimbolo);
    Validado = false;
    return NuevoSimbolo;
}

Transicion* Automata::AgregarTransicion(Estado* Origen, Simbolo* SimboloUsado, Estado* Destino) {
    Transicion* NuevaTransicion = new Transicion(Origen, SimboloUsado, Destino);
    Transiciones.Agregar(NuevaTransicion);
    Validado = false;
    return NuevaTransicion;
}

void Automata::EstablecerEstadoInicial(Estado* NuevoEstadoInicial) {
    EstadoInicial = NuevoEstadoInicial;
    Validado = false;
}

void Automata::AgregarEstadoFinal(Estado* NuevoEstadoFinal) {
    EstadosFinales.Agregar(NuevoEstadoFinal);
    Validado = false;
}

Estado* Automata::BuscarEstado(const CadenaManual& NombreBuscado) const {
    Nodo<Estado*>* Actual = Estados.ObtenerPrimero();

    while (Actual != nullptr) {
        Estado* EstadoActual = Actual->ObtenerDato();

        if (EstadoActual != nullptr && EstadoActual->TieneNombre(NombreBuscado)) {
            return EstadoActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

Estado* Automata::BuscarEstado(const char* NombreBuscado) const {
    Nodo<Estado*>* Actual = Estados.ObtenerPrimero();

    while (Actual != nullptr) {
        Estado* EstadoActual = Actual->ObtenerDato();

        if (EstadoActual != nullptr && EstadoActual->TieneNombre(NombreBuscado)) {
            return EstadoActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

Simbolo* Automata::BuscarSimbolo(const CadenaManual& ValorBuscado) const {
    Nodo<Simbolo*>* Actual = Alfabeto.ObtenerPrimero();

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();

        if (SimboloActual != nullptr && SimboloActual->TieneValor(ValorBuscado)) {
            return SimboloActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

Simbolo* Automata::BuscarSimbolo(const char* ValorBuscado) const {
    Nodo<Simbolo*>* Actual = Alfabeto.ObtenerPrimero();

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();

        if (SimboloActual != nullptr && SimboloActual->TieneValor(ValorBuscado)) {
            return SimboloActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

Transicion* Automata::BuscarTransicion(Estado* Origen, Simbolo* SimboloUsado) const {
    Nodo<Transicion*>* Actual = Transiciones.ObtenerPrimero();

    while (Actual != nullptr) {
        Transicion* TransicionActual = Actual->ObtenerDato();

        if (TransicionActual != nullptr && TransicionActual->Coincide(Origen, SimboloUsado)) {
            return TransicionActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

int Automata::ContarTransiciones(Estado* Origen, Simbolo* SimboloUsado) const {
    int Cantidad = 0;
    Nodo<Transicion*>* Actual = Transiciones.ObtenerPrimero();

    while (Actual != nullptr) {
        Transicion* TransicionActual = Actual->ObtenerDato();

        if (TransicionActual != nullptr && TransicionActual->Coincide(Origen, SimboloUsado)) {
            Cantidad++;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return Cantidad;
}

bool Automata::PerteneceEstado(Estado* EstadoBuscado) const {
    Nodo<Estado*>* Actual = Estados.ObtenerPrimero();

    while (Actual != nullptr) {
        if (Actual->ObtenerDato() == EstadoBuscado) {
            return true;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return false;
}

bool Automata::PerteneceSimbolo(Simbolo* SimboloBuscado) const {
    Nodo<Simbolo*>* Actual = Alfabeto.ObtenerPrimero();

    while (Actual != nullptr) {
        if (Actual->ObtenerDato() == SimboloBuscado) {
            return true;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return false;
}

bool Automata::EsEstadoFinal(Estado* EstadoBuscado) const {
    Nodo<Estado*>* Actual = EstadosFinales.ObtenerPrimero();

    while (Actual != nullptr) {
        if (Actual->ObtenerDato() == EstadoBuscado) {
            return true;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return false;
}

Estado* Automata::ObtenerEstadoInicial() const {
    return EstadoInicial;
}

Nodo<Estado*>* Automata::ObtenerPrimerEstado() const {
    return Estados.ObtenerPrimero();
}

Nodo<Simbolo*>* Automata::ObtenerPrimerSimbolo() const {
    return Alfabeto.ObtenerPrimero();
}

Nodo<Estado*>* Automata::ObtenerPrimerEstadoFinal() const {
    return EstadosFinales.ObtenerPrimero();
}

Nodo<Transicion*>* Automata::ObtenerPrimeraTransicion() const {
    return Transiciones.ObtenerPrimero();
}

int Automata::ObtenerCantidadEstados() const {
    return Estados.ObtenerCantidad();
}

int Automata::ObtenerCantidadSimbolos() const {
    return Alfabeto.ObtenerCantidad();
}

int Automata::ObtenerCantidadEstadosFinales() const {
    return EstadosFinales.ObtenerCantidad();
}

int Automata::ObtenerCantidadTransiciones() const {
    return Transiciones.ObtenerCantidad();
}

bool Automata::EstaValidado() const {
    return Validado;
}

void Automata::EstablecerValidado(bool EstadoValidacion) {
    Validado = EstadoValidacion;
}

void Automata::Vaciar() {
    Nodo<Transicion*>* ActualTransicion = Transiciones.ObtenerPrimero();

    while (ActualTransicion != nullptr) {
        delete ActualTransicion->ObtenerDato();
        ActualTransicion = ActualTransicion->ObtenerSiguiente();
    }

    Transiciones.Limpiar();
    EstadosFinales.Limpiar();

    Nodo<Simbolo*>* ActualSimbolo = Alfabeto.ObtenerPrimero();

    while (ActualSimbolo != nullptr) {
        delete ActualSimbolo->ObtenerDato();
        ActualSimbolo = ActualSimbolo->ObtenerSiguiente();
    }

    Alfabeto.Limpiar();

    Nodo<Estado*>* ActualEstado = Estados.ObtenerPrimero();

    while (ActualEstado != nullptr) {
        delete ActualEstado->ObtenerDato();
        ActualEstado = ActualEstado->ObtenerSiguiente();
    }

    Estados.Limpiar();
    EstadoInicial = nullptr;
    Validado = false;
}
