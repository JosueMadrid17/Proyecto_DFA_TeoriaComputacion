#include "Simbolo.h"

Simbolo::Simbolo() {}

Simbolo::Simbolo(const char* ValorNuevo) {
    Valor.Asignar(ValorNuevo);
}

Simbolo::Simbolo(const CadenaManual& ValorNuevo) {
    Valor = ValorNuevo;
}

void Simbolo::EstablecerValor(const char* ValorNuevo) {
    Valor.Asignar(ValorNuevo);
}

const CadenaManual& Simbolo::ObtenerValor() const {
    return Valor;
}

void Simbolo::EstablecerValor(const CadenaManual& ValorNuevo) {
    Valor = ValorNuevo;
}

bool Simbolo::TieneValor(const CadenaManual& ValorBuscado) const {
    return Valor.EsIgual(ValorBuscado);
}

bool Simbolo::TieneValor(const char* ValorBuscado) const {
    return Valor.EsIgual(ValorBuscado);
}
