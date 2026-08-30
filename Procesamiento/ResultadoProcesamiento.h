#ifndef RESULTADOPROCESAMIENTO_H
#define RESULTADOPROCESAMIENTO_H
#include "../Estructuras/ListaEnlazada.h"
#include "../Estructuras/CadenaManual.h"

class PasoProcesamiento;

class ResultadoProcesamiento {
private:
    ListaEnlazada<PasoProcesamiento*> Pasos;
    CadenaManual EstadoInicial;
    CadenaManual EstadoAlcanzado;
    CadenaManual MensajeError;
    bool Aceptada;
    bool Correcto;

public:
    ResultadoProcesamiento();
    ~ResultadoProcesamiento();
    ResultadoProcesamiento(const ResultadoProcesamiento&) = delete;
    ResultadoProcesamiento& operator=(const ResultadoProcesamiento&) = delete;

    void Limpiar();
    void AgregarPaso(const CadenaManual& Origen, const CadenaManual& Simbolo, const CadenaManual& Destino);
    void EstablecerEstadoInicial(const CadenaManual& Estado);
    void EstablecerEstadoAlcanzado(const CadenaManual& Estado);
    void MarcarCorrecto(bool Aceptacion);
    void EstablecerError(const CadenaManual& Error);

    bool EsAceptada() const;
    bool EsCorrecto() const;
    int ObtenerCantidadPasos() const;

    const CadenaManual& ObtenerEstadoInicial() const;
    const CadenaManual& ObtenerEstadoAlcanzado() const;
    const CadenaManual& ObtenerMensajeError() const;
    Nodo<PasoProcesamiento*>* ObtenerPrimerPaso() const;
};

#endif
