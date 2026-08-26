#include "ValidadorDFA.h"
#include "ResultadoValidacion.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"
#include "../Estructuras/CadenaManual.h"

void ValidadorDFA::Validar(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Resultado.Limpiar();
    AutomataEvaluado.EstablecerValidado(false);

    ValidarNoVacuidad(AutomataEvaluado, Resultado);
    ValidarEstadosDuplicados(AutomataEvaluado, Resultado);
    ValidarSimbolosDuplicados(AutomataEvaluado, Resultado);
    ValidarSimbolosPermitidos(AutomataEvaluado, Resultado);
    ValidarEstadoInicial(AutomataEvaluado, Resultado);
    ValidarEstadosFinales(AutomataEvaluado, Resultado);
    ValidarIntegridadTransiciones(AutomataEvaluado, Resultado);
    ValidarTotalidadYDeterminismo(AutomataEvaluado, Resultado);

    if (Resultado.EsValido()) {
        AutomataEvaluado.EstablecerValidado(true);
    }
}

void ValidadorDFA::ValidarNoVacuidad(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    if (AutomataEvaluado.ObtenerCantidadEstados() == 0) {
        CadenaManual Mensaje("El conjunto de estados no puede estar vacio");
        Resultado.AgregarError(Mensaje);
    }

    if (AutomataEvaluado.ObtenerCantidadSimbolos() == 0) {
        CadenaManual Mensaje("El alfabeto no puede estar vacio");
        Resultado.AgregarError(Mensaje);
    }
}

void ValidadorDFA::ValidarEstadosDuplicados(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Estado*>* Actual = AutomataEvaluado.ObtenerPrimerEstado();

    while (Actual != nullptr) {
        Estado* EstadoActual = Actual->ObtenerDato();
        Nodo<Estado*>* Comparado = Actual->ObtenerSiguiente();

        while (Comparado != nullptr) {
            Estado* EstadoComparado = Comparado->ObtenerDato();

            if (EstadoActual != nullptr && EstadoComparado != nullptr) {
                if (EstadoActual->TieneNombre(EstadoComparado->ObtenerNombre())) {
                    CadenaManual Mensaje("El estado '");
                    Mensaje.AgregarCadena(EstadoActual->ObtenerNombre());
                    Mensaje.AgregarTexto("' esta duplicado");
                    Resultado.AgregarError(Mensaje);
                }
            }
            Comparado = Comparado->ObtenerSiguiente();
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

void ValidadorDFA::ValidarSimbolosDuplicados(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Simbolo*>* Actual = AutomataEvaluado.ObtenerPrimerSimbolo();

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();
        Nodo<Simbolo*>* Comparado = Actual->ObtenerSiguiente();

        while (Comparado != nullptr) {
            Simbolo* SimboloComparado = Comparado->ObtenerDato();

            if (SimboloActual != nullptr && SimboloComparado != nullptr) {
                if (SimboloActual->TieneValor(SimboloComparado->ObtenerValor())) {
                    CadenaManual Mensaje("El simbolo '");
                    Mensaje.AgregarCadena(SimboloActual->ObtenerValor());
                    Mensaje.AgregarTexto("' esta duplicado en el alfabeto");
                    Resultado.AgregarError(Mensaje);
                }
            }
            Comparado = Comparado->ObtenerSiguiente();
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

void ValidadorDFA::ValidarSimbolosPermitidos(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Simbolo*>* Actual = AutomataEvaluado.ObtenerPrimerSimbolo();

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();

        if (SimboloActual != nullptr) {
            const CadenaManual& Valor = SimboloActual->ObtenerValor();

            if (Valor.EstaVacia()) {
                CadenaManual Mensaje("El alfabeto contiene un simbolo vacio");
                Resultado.AgregarError(Mensaje);
            } else if (Valor.EsIgual("ε") || Valor.EsIgual("λ")) {
                CadenaManual Mensaje("El simbolo '");
                Mensaje.AgregarCadena(Valor);
                Mensaje.AgregarTexto("' no esta permitido en el alfabeto");
                Resultado.AgregarError(Mensaje);
            }

            if (ContieneEspacio(Valor)) {
                CadenaManual Mensaje("El simbolo '");
                Mensaje.AgregarCadena(Valor);
                Mensaje.AgregarTexto("' contiene espacios en blanco");
                Resultado.AgregarError(Mensaje);
            }

            if (ContieneGuion(Valor)) {
                CadenaManual Mensaje("El simbolo '");
                Mensaje.AgregarCadena(Valor);
                Mensaje.AgregarTexto("' contiene un guion no permitido");
                Resultado.AgregarError(Mensaje);
            }
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

bool ValidadorDFA::ContieneEspacio(const CadenaManual& Texto) const {
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        char Caracter = Texto.ObtenerCaracter(Posicion);
        if (Caracter == ' ' || Caracter == '\t' || Caracter == '\n' || Caracter == '\r') {
            return true;
        }
        Posicion++;
    }
    return false;
}

bool ValidadorDFA::ContieneGuion(const CadenaManual& Texto) const {
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        if (Texto.ObtenerCaracter(Posicion) == '-') {
            return true;
        }
        Posicion++;
    }
    return false;
}

void ValidadorDFA::ValidarEstadoInicial(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Estado* EstadoInicial = AutomataEvaluado.ObtenerEstadoInicial();

    if (EstadoInicial == nullptr) {
        CadenaManual Mensaje("El automata no tiene un estado inicial definido");
        Resultado.AgregarError(Mensaje);
        return;
    }

    if (!AutomataEvaluado.PerteneceEstado(EstadoInicial)) {
        CadenaManual Mensaje("El estado inicial '");
        Mensaje.AgregarCadena(EstadoInicial->ObtenerNombre());
        Mensaje.AgregarTexto("' no pertenece al conjunto de estados");
        Resultado.AgregarError(Mensaje);
    }
}

void ValidadorDFA::ValidarEstadosFinales(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Estado*>* Actual = AutomataEvaluado.ObtenerPrimerEstadoFinal();

    while (Actual != nullptr) {
        Estado* EstadoFinal = Actual->ObtenerDato();

        if (EstadoFinal == nullptr) {
            CadenaManual Mensaje("Existe un estado final sin definir");
            Resultado.AgregarError(Mensaje);
        } else if (!AutomataEvaluado.PerteneceEstado(EstadoFinal)) {
            CadenaManual Mensaje("El estado final '");
            Mensaje.AgregarCadena(EstadoFinal->ObtenerNombre());
            Mensaje.AgregarTexto("' no pertenece al conjunto de estados");
            Resultado.AgregarError(Mensaje);
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

void ValidadorDFA::ValidarIntegridadTransiciones(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Transicion*>* Actual = AutomataEvaluado.ObtenerPrimeraTransicion();

    while (Actual != nullptr) {
        Transicion* TransicionActual = Actual->ObtenerDato();

        if (TransicionActual == nullptr) {
            CadenaManual Mensaje("Existe una transicion sin definir");
            Resultado.AgregarError(Mensaje);
            Actual = Actual->ObtenerSiguiente();
            continue;
        }

        Estado* Origen = TransicionActual->ObtenerOrigen();
        Simbolo* SimboloUsado = TransicionActual->ObtenerSimbolo();
        Estado* Destino = TransicionActual->ObtenerDestino();

        if (Origen == nullptr) {
            CadenaManual Mensaje("Existe una transicion sin estado de origen");
            Resultado.AgregarError(Mensaje);
        } else if (!AutomataEvaluado.PerteneceEstado(Origen)) {
            CadenaManual Mensaje("El estado de origen '");
            Mensaje.AgregarCadena(Origen->ObtenerNombre());
            Mensaje.AgregarTexto("' no esta registrado en el conjunto de estados");
            Resultado.AgregarError(Mensaje);
        }

        if (SimboloUsado == nullptr) {
            CadenaManual Mensaje("Existe una transicion sin simbolo");
            Resultado.AgregarError(Mensaje);
        } else if (!AutomataEvaluado.PerteneceSimbolo(SimboloUsado)) {
            CadenaManual Mensaje("El simbolo '");
            Mensaje.AgregarCadena(SimboloUsado->ObtenerValor());
            Mensaje.AgregarTexto("' de una transicion no pertenece al alfabeto");
            Resultado.AgregarError(Mensaje);
        }

        if (Destino == nullptr) {
            CadenaManual Mensaje("Existe una transicion sin estado de destino");
            Resultado.AgregarError(Mensaje);
        } else if (!AutomataEvaluado.PerteneceEstado(Destino)) {
            CadenaManual Mensaje("El estado de destino '");
            Mensaje.AgregarCadena(Destino->ObtenerNombre());
            Mensaje.AgregarTexto("' no esta registrado en el conjunto de estados");
            Resultado.AgregarError(Mensaje);
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

void ValidadorDFA::ValidarTotalidadYDeterminismo(Automata& AutomataEvaluado, ResultadoValidacion& Resultado) {
    Nodo<Estado*>* NodoEstado = AutomataEvaluado.ObtenerPrimerEstado();

    while (NodoEstado != nullptr) {
        Estado* EstadoActual = NodoEstado->ObtenerDato();
        Nodo<Simbolo*>* NodoSimbolo = AutomataEvaluado.ObtenerPrimerSimbolo();

        while (NodoSimbolo != nullptr) {
            Simbolo* SimboloActual = NodoSimbolo->ObtenerDato();

            if (EstadoActual != nullptr && SimboloActual != nullptr) {
                int Cantidad = AutomataEvaluado.ContarTransiciones(EstadoActual, SimboloActual);

                if (Cantidad == 0) {
                    CadenaManual Mensaje("El estado '");
                    Mensaje.AgregarCadena(EstadoActual->ObtenerNombre());
                    Mensaje.AgregarTexto("' carece de transicion para el simbolo '");
                    Mensaje.AgregarCadena(SimboloActual->ObtenerValor());
                    Mensaje.AgregarTexto("'.");
                    Resultado.AgregarError(Mensaje);
                } else if (Cantidad > 1) {
                    CadenaManual Mensaje("El estado '");
                    Mensaje.AgregarCadena(EstadoActual->ObtenerNombre());
                    Mensaje.AgregarTexto("' posee mas de una transicion para el simbolo '");
                    Mensaje.AgregarCadena(SimboloActual->ObtenerValor());
                    Mensaje.AgregarTexto("'.");
                    Resultado.AgregarError(Mensaje);
                }
            }
            NodoSimbolo = NodoSimbolo->ObtenerSiguiente();
        }
        NodoEstado = NodoEstado->ObtenerSiguiente();
    }
}
