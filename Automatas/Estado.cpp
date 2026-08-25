#include "Estado.h"

Estado::Estado() {}

Estado::Estado(const char* NombreNuevo) {
    Nombre.Asignar(NombreNuevo);
}

void Estado::EstablecerNombre(const char* NombreNuevo) {
    Nombre.Asignar(NombreNuevo);
}

const CadenaManual& Estado::ObtenerNombre() const {
    return Nombre;
}

bool Estado::TieneNombre(const CadenaManual& NombreBuscado) const {
    return Nombre.EsIgual(NombreBuscado);
}

bool Estado::TieneNombre(const char* NombreBuscado) const {
    return Nombre.EsIgual(NombreBuscado);
}
