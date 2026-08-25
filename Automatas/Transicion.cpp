#include "Transicion.h"
#include "Estado.h"
#include "Simbolo.h"

Transicion::Transicion() {
    Origen = nullptr;
    SimboloTransicion = nullptr;
    Destino = nullptr;
}

Transicion::Transicion(Estado* EstadoOrigen, Simbolo* SimboloUsado, Estado* EstadoDestino) {
    Origen = EstadoOrigen;
    SimboloTransicion = SimboloUsado;
    Destino = EstadoDestino;
}

void Transicion::EstablecerOrigen(Estado* EstadoOrigen) {
    Origen = EstadoOrigen;
}

void Transicion::EstablecerSimbolo(Simbolo* SimboloUsado) {
    SimboloTransicion = SimboloUsado;
}

void Transicion::EstablecerDestino(Estado* EstadoDestino) {
    Destino = EstadoDestino;
}

Estado* Transicion::ObtenerOrigen() const {
    return Origen;
}

Simbolo* Transicion::ObtenerSimbolo() const {
    return SimboloTransicion;
}

Estado* Transicion::ObtenerDestino() const {
    return Destino;
}

bool Transicion::Coincide(Estado* EstadoOrigen, Simbolo* SimboloUsado) const {
    return Origen == EstadoOrigen && SimboloTransicion == SimboloUsado;
}
