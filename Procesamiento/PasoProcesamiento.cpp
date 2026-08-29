#include "PasoProcesamiento.h"

PasoProcesamiento::PasoProcesamiento(const CadenaManual& Origen, const CadenaManual& Simbolo, const CadenaManual& Destino) {
    EstadoOrigen = Origen;
    SimboloLeido = Simbolo;
    EstadoDestino = Destino;
}

const CadenaManual& PasoProcesamiento::ObtenerEstadoOrigen() const {
    return EstadoOrigen;
}

const CadenaManual& PasoProcesamiento::ObtenerSimboloLeido() const {
    return SimboloLeido;
}

const CadenaManual& PasoProcesamiento::ObtenerEstadoDestino() const {
    return EstadoDestino;
}
