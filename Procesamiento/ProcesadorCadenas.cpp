#include "ProcesadorCadenas.h"
#include "ResultadoProcesamiento.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"

ProcesadorCadenas::ProcesadorCadenas() {}

bool ProcesadorCadenas::Procesar(Automata* AutomataEvaluado, const CadenaManual& Cadena, ResultadoProcesamiento& Resultado) const {
    Resultado.Limpiar();

    if (AutomataEvaluado == nullptr) {
        CadenaManual Error("No se pudo acceder al automata.");
        Resultado.EstablecerError(Error);
        return false;
    }

    if (!AutomataEvaluado->EstaValidado()) {
        CadenaManual Error("El automata debe estar validado antes de procesar una cadena.");
        Resultado.EstablecerError(Error);
        return false;
    }

    Estado* EstadoActual = AutomataEvaluado->ObtenerEstadoInicial();

    if (EstadoActual == nullptr) {
        CadenaManual Error("El automata no tiene un estado inicial valido.");
        Resultado.EstablecerError(Error);
        return false;
    }

    Resultado.EstablecerEstadoInicial(EstadoActual->ObtenerNombre());
    Resultado.EstablecerEstadoAlcanzado(EstadoActual->ObtenerNombre());

    int Posicion = 0;
    while (Posicion < Cadena.ObtenerLongitud()) {
        CadenaManual TextoSimbolo;
        TextoSimbolo.AgregarCaracter(Cadena.ObtenerCaracter(Posicion));

        Simbolo* SimboloActual = AutomataEvaluado->BuscarSimbolo(TextoSimbolo);

        if (SimboloActual == nullptr) {
            CadenaManual Error("El simbolo '");
            Error.AgregarCadena(TextoSimbolo);
            Error.AgregarTexto("' no pertenece al alfabeto del automata.");

            Resultado.EstablecerError(Error);
            return false;
        }

        Transicion* TransicionActual = AutomataEvaluado->BuscarTransicion(EstadoActual, SimboloActual);

        if (TransicionActual == nullptr) {
            CadenaManual Error("No existe una transicion definida para el estado '");
            Error.AgregarCadena(EstadoActual->ObtenerNombre());
            Error.AgregarTexto("' con el simbolo '");
            Error.AgregarCadena(SimboloActual->ObtenerValor());
            Error.AgregarTexto("'.");

            Resultado.EstablecerError(Error);
            return false;
        }

        Estado* EstadoDestino = TransicionActual->ObtenerDestino();

        if (EstadoDestino == nullptr) {
            CadenaManual Error("La transicion encontrada no tiene un estado destino valido.");
            Resultado.EstablecerError(Error);
            return false;
        }

        Resultado.AgregarPaso(
            EstadoActual->ObtenerNombre(),
            SimboloActual->ObtenerValor(),
            EstadoDestino->ObtenerNombre()
            );
        EstadoActual = EstadoDestino;
        Resultado.EstablecerEstadoAlcanzado(EstadoActual->ObtenerNombre());
        Posicion++;
    }

    bool Aceptacion = AutomataEvaluado->EsEstadoFinal(EstadoActual);
    Resultado.MarcarCorrecto(Aceptacion);
    return true;
}
