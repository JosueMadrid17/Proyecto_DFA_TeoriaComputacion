#ifndef RESULTADOVALIDACION_H
#define RESULTADOVALIDACION_H
#include "../Estructuras/ListaEnlazada.h"

class ErrorValidacion;
class CadenaManual;

class ResultadoValidacion {
private:
    ListaEnlazada<ErrorValidacion*> Errores;
    bool Valido;

public:
    ResultadoValidacion();
    ~ResultadoValidacion();
    ResultadoValidacion(const ResultadoValidacion&) = delete;
    ResultadoValidacion& operator=(const ResultadoValidacion&) = delete;

    void AgregarError(const CadenaManual& Mensaje);
    void Limpiar();

    bool EsValido() const;
    int ObtenerCantidadErrores() const;

    Nodo<ErrorValidacion*>* ObtenerPrimerError() const;
};

#endif
