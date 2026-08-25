#ifndef SIMBOLO_H
#define SIMBOLO_H
#include "../Estructuras/CadenaManual.h"

class Simbolo {
private:
    CadenaManual Valor;

public:
    Simbolo();
    Simbolo(const char* ValorNuevo);

    void EstablecerValor(const char* ValorNuevo);

    const CadenaManual& ObtenerValor() const;

    bool TieneValor(const CadenaManual& ValorBuscado) const;
    bool TieneValor(const char* ValorBuscado) const;
};

#endif
