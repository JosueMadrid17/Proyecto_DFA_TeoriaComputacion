#include "ResultadoValidacion.h"
#include "ErrorValidacion.h"
#include "../Estructuras/CadenaManual.h"

ResultadoValidacion::ResultadoValidacion() {
    Valido = true;
}

ResultadoValidacion::~ResultadoValidacion() {
    Limpiar();
}

void ResultadoValidacion::AgregarError(const CadenaManual& Mensaje) {
    ErrorValidacion* NuevoError = new ErrorValidacion(Mensaje);
    Errores.Agregar(NuevoError);
    Valido = false;
}

void ResultadoValidacion::Limpiar() {
    Nodo<ErrorValidacion*>* Actual = Errores.ObtenerPrimero();

    while (Actual != nullptr) {
        delete Actual->ObtenerDato();
        Actual = Actual->ObtenerSiguiente();
    }
    Errores.Limpiar();
    Valido = true;
}

bool ResultadoValidacion::EsValido() const {
    return Valido;
}

int ResultadoValidacion::ObtenerCantidadErrores() const {
    return Errores.ObtenerCantidad();
}

Nodo<ErrorValidacion*>* ResultadoValidacion::ObtenerPrimerError() const {
    return Errores.ObtenerPrimero();
}
