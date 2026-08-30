#include "ResultadoProcesamiento.h"
#include "PasoProcesamiento.h"

ResultadoProcesamiento::ResultadoProcesamiento() {
    Aceptada = false;
    Correcto = false;
}

ResultadoProcesamiento::~ResultadoProcesamiento() {
    Limpiar();
}

void ResultadoProcesamiento::Limpiar() {
    Nodo<PasoProcesamiento*>* Actual = Pasos.ObtenerPrimero();

    while (Actual != nullptr) {
        delete Actual->ObtenerDato();
        Actual = Actual->ObtenerSiguiente();
    }

    Pasos.Limpiar();
    EstadoInicial.Asignar("");
    EstadoAlcanzado.Asignar("");
    MensajeError.Asignar("");
    Aceptada = false;
    Correcto = false;
}

void ResultadoProcesamiento::AgregarPaso(const CadenaManual& Origen, const CadenaManual& Simbolo, const CadenaManual& Destino) {
    PasoProcesamiento* NuevoPaso = new PasoProcesamiento(Origen, Simbolo, Destino);
    Pasos.Agregar(NuevoPaso);
}

void ResultadoProcesamiento::EstablecerEstadoInicial(const CadenaManual& Estado) {
    EstadoInicial = Estado;
}

void ResultadoProcesamiento::EstablecerEstadoAlcanzado(const CadenaManual& Estado) {
    EstadoAlcanzado = Estado;
}

void ResultadoProcesamiento::MarcarCorrecto(bool Aceptacion) {
    Aceptada = Aceptacion;
    Correcto = true;
    MensajeError.Asignar("");
}

void ResultadoProcesamiento::EstablecerError(const CadenaManual& Error) {
    MensajeError = Error;
    Aceptada = false;
    Correcto = false;
}

bool ResultadoProcesamiento::EsAceptada() const {
    return Aceptada;
}

bool ResultadoProcesamiento::EsCorrecto() const {
    return Correcto;
}

int ResultadoProcesamiento::ObtenerCantidadPasos() const {
    return Pasos.ObtenerCantidad();
}

const CadenaManual& ResultadoProcesamiento::ObtenerEstadoInicial() const {
    return EstadoInicial;
}

const CadenaManual& ResultadoProcesamiento::ObtenerEstadoAlcanzado() const {
    return EstadoAlcanzado;
}

const CadenaManual& ResultadoProcesamiento::ObtenerMensajeError() const {
    return MensajeError;
}

Nodo<PasoProcesamiento*>* ResultadoProcesamiento::ObtenerPrimerPaso() const {
    return Pasos.ObtenerPrimero();
}
