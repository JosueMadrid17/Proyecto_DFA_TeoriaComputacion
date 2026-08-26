#ifndef ERRORVALIDACION_H
#define ERRORVALIDACION_H
#include "../Estructuras/CadenaManual.h"

class ErrorValidacion {
private:
    CadenaManual Mensaje;

public:
    ErrorValidacion();
    ErrorValidacion(const CadenaManual& MensajeNuevo);

    void EstablecerMensaje(const CadenaManual& MensajeNuevo);
    const CadenaManual& ObtenerMensaje() const;
};

#endif
