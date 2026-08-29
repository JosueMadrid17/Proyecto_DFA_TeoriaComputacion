#include "Estado.h"

Estado::Estado() {}

Estado::Estado(const char* NombreNuevo) {
    Nombre.Asignar(NombreNuevo);
}

Estado::Estado(const CadenaManual& NombreNuevo) {
    Nombre = NombreNuevo;
}

void Estado::EstablecerNombre(const char* NombreNuevo) {
    Nombre.Asignar(NombreNuevo);
}

const CadenaManual& Estado::ObtenerNombre() const {
    return Nombre;
}

void Estado::EstablecerNombre(const CadenaManual& NombreNuevo) {
    Nombre = NombreNuevo;
}

bool Estado::TieneNombre(const CadenaManual& NombreBuscado) const {
    return Nombre.EsIgual(NombreBuscado);
}

bool Estado::TieneNombre(const char* NombreBuscado) const {
    return Nombre.EsIgual(NombreBuscado);
}
