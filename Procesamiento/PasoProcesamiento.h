#ifndef PASOPROCESAMIENTO_H
#define PASOPROCESAMIENTO_H
#include "../Estructuras/CadenaManual.h"

class PasoProcesamiento {
private:
    CadenaManual EstadoOrigen;
    CadenaManual SimboloLeido;
    CadenaManual EstadoDestino;

public:
    PasoProcesamiento(const CadenaManual& Origen, const CadenaManual& Simbolo, const CadenaManual& Destino);

    const CadenaManual& ObtenerEstadoOrigen() const;
    const CadenaManual& ObtenerSimboloLeido() const;
    const CadenaManual& ObtenerEstadoDestino() const;
};

#endif
