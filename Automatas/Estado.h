#ifndef ESTADO_H
#define ESTADO_H
#include "../Estructuras/CadenaManual.h"

class Estado {
private:
    CadenaManual Nombre;

public:
    Estado();
    Estado(const char* NombreNuevo);
    Estado(const CadenaManual& NombreNuevo);

    void EstablecerNombre(const char* NombreNuevo);
    void EstablecerNombre(const CadenaManual& NombreNuevo);

    const CadenaManual& ObtenerNombre() const;

    bool TieneNombre(const CadenaManual& NombreBuscado) const;
    bool TieneNombre(const char* NombreBuscado) const;
};

#endif
