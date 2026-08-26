#include "ErrorValidacion.h"

ErrorValidacion::ErrorValidacion() {}

ErrorValidacion::ErrorValidacion(const CadenaManual& MensajeNuevo) {
    Mensaje = MensajeNuevo;
}

void ErrorValidacion::EstablecerMensaje(const CadenaManual& MensajeNuevo) {
    Mensaje = MensajeNuevo;
}

const CadenaManual& ErrorValidacion::ObtenerMensaje() const {
    return Mensaje;
}
