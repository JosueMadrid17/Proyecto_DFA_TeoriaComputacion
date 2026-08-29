#include "OperacionUnion.h"
#include "EstadoCompuesto.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"

bool OperacionUnion::VerificarAlfabetos(Automata* Automata1, Automata* Automata2, CadenaManual& MensajeError) const {
    Nodo<Simbolo*>* Actual1 = Automata1->ObtenerPrimerSimbolo();

    while (Actual1 != nullptr) {
        Simbolo* SimboloActual = Actual1->ObtenerDato();

        if (SimboloActual != nullptr) {
            Simbolo* Encontrado = Automata2->BuscarSimbolo(SimboloActual->ObtenerValor());
            if (Encontrado == nullptr) {
                MensajeError.Asignar("El simbolo '");
                MensajeError.AgregarCadena(SimboloActual->ObtenerValor());
                MensajeError.AgregarTexto("' del Automata 1 no existe en el Automata 2.");
                return false;
            }
        }
        Actual1 = Actual1->ObtenerSiguiente();
    }
    Nodo<Simbolo*>* Actual2 = Automata2->ObtenerPrimerSimbolo();

    while (Actual2 != nullptr) {
        Simbolo* SimboloActual = Actual2->ObtenerDato();

        if (SimboloActual != nullptr) {
            Simbolo* Encontrado = Automata1->BuscarSimbolo(SimboloActual->ObtenerValor());
            if (Encontrado == nullptr) {
                MensajeError.Asignar("El simbolo '");
                MensajeError.AgregarCadena(SimboloActual->ObtenerValor());
                MensajeError.AgregarTexto("' del Automata 2 no existe en el Automata 1.");
                return false;
            }
        }
        Actual2 = Actual2->ObtenerSiguiente();
    }
    return true;
}

CadenaManual OperacionUnion::ConstruirNombreEstadoCompuesto(Estado* Estado1, Estado* Estado2) const {
    CadenaManual Nombre("(");

    Nombre.AgregarCadena(Estado1->ObtenerNombre());
    Nombre.AgregarTexto("_A, ");
    Nombre.AgregarCadena(Estado2->ObtenerNombre());
    Nombre.AgregarTexto("_B)");
    return Nombre;
}

EstadoCompuesto* OperacionUnion::BuscarEstadoCompuesto(ListaEnlazada<EstadoCompuesto*>& EstadosCompuestos, Estado* Estado1, Estado* Estado2) const {
    Nodo<EstadoCompuesto*>* Actual = EstadosCompuestos.ObtenerPrimero();

    while (Actual != nullptr) {
        EstadoCompuesto* EstadoActual = Actual->ObtenerDato();

        if (EstadoActual != nullptr && EstadoActual->Coincide(Estado1, Estado2)) {
            return EstadoActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

void OperacionUnion::LiberarEstadosCompuestos(ListaEnlazada<EstadoCompuesto*>& EstadosCompuestos) const {
    Nodo<EstadoCompuesto*>* Actual = EstadosCompuestos.ObtenerPrimero();

    while (Actual != nullptr) {
        delete Actual->ObtenerDato();
        Actual = Actual->ObtenerSiguiente();
    }
    EstadosCompuestos.Limpiar();
}

Automata* OperacionUnion::Unir(Automata* Automata1, Automata* Automata2, CadenaManual& MensajeError) {
    MensajeError.Asignar("");

    if (Automata1 == nullptr || Automata2 == nullptr) {
        MensajeError.Asignar("Debe seleccionar dos autómatas.");
        return nullptr;
    }

    if (!Automata1->EstaValidado() || !Automata2->EstaValidado()) {
        MensajeError.Asignar("Los dos autómatas deben estar validados antes de realizar la unión.");
        return nullptr;
    }

    if (!VerificarAlfabetos(Automata1, Automata2, MensajeError)) {
        return nullptr;
    }

    Automata* Resultado = new Automata();
    ListaEnlazada<EstadoCompuesto*> EstadosCompuestos;

    Nodo<Simbolo*>* NodoSimbolo = Automata1->ObtenerPrimerSimbolo();

    while (NodoSimbolo != nullptr) {
        Simbolo* SimboloActual = NodoSimbolo->ObtenerDato();

        if (SimboloActual != nullptr) {
            Resultado->AgregarSimbolo(SimboloActual->ObtenerValor());
        }
        NodoSimbolo = NodoSimbolo->ObtenerSiguiente();
    }
    Nodo<Estado*>* NodoEstado1 = Automata1->ObtenerPrimerEstado();

    while (NodoEstado1 != nullptr) {
        Estado* Estado1 = NodoEstado1->ObtenerDato();
        Nodo<Estado*>* NodoEstado2 = Automata2->ObtenerPrimerEstado();

        while (NodoEstado2 != nullptr) {
            Estado* Estado2 = NodoEstado2->ObtenerDato();

            if (Estado1 != nullptr && Estado2 != nullptr) {
                CadenaManual Nombre = ConstruirNombreEstadoCompuesto(Estado1, Estado2);
                Estado* EstadoResultado = Resultado->AgregarEstado(Nombre);

                EstadoCompuesto* NuevoEstadoCompuesto = new EstadoCompuesto(Estado1, Estado2, EstadoResultado);
                EstadosCompuestos.Agregar(NuevoEstadoCompuesto);

                if (Automata1->EsEstadoFinal(Estado1) || Automata2->EsEstadoFinal(Estado2)) {
                    Resultado->AgregarEstadoFinal(EstadoResultado);
                }
            }
            NodoEstado2 = NodoEstado2->ObtenerSiguiente();
        }
        NodoEstado1 = NodoEstado1->ObtenerSiguiente();
    }

    EstadoCompuesto* InicialCompuesto = BuscarEstadoCompuesto(
        EstadosCompuestos,
        Automata1->ObtenerEstadoInicial(),
        Automata2->ObtenerEstadoInicial()
        );

    if (InicialCompuesto == nullptr) {
        MensajeError.Asignar("No se pudo determinar el estado inicial del autómata unión.");
        LiberarEstadosCompuestos(EstadosCompuestos);
        delete Resultado;
        return nullptr;
    }

    Resultado->EstablecerEstadoInicial(InicialCompuesto->ObtenerEstadoResultado());

    Nodo<EstadoCompuesto*>* NodoCompuesto = EstadosCompuestos.ObtenerPrimero();

    while (NodoCompuesto != nullptr) {
        EstadoCompuesto* EstadoActual = NodoCompuesto->ObtenerDato();

        if (EstadoActual != nullptr) {
            Nodo<Simbolo*>* SimboloNodo = Automata1->ObtenerPrimerSimbolo();

            while (SimboloNodo != nullptr) {
                Simbolo* Simbolo1 = SimboloNodo->ObtenerDato();

                if (Simbolo1 != nullptr) {
                    Simbolo* Simbolo2 = Automata2->BuscarSimbolo(Simbolo1->ObtenerValor());
                    Transicion* Transicion1 = Automata1->BuscarTransicion(
                        EstadoActual->ObtenerEstadoAutomata1(),
                        Simbolo1
                        );

                    Transicion* Transicion2 = Automata2->BuscarTransicion(
                        EstadoActual->ObtenerEstadoAutomata2(),
                        Simbolo2
                        );

                    if (Transicion1 == nullptr || Transicion2 == nullptr) {
                        MensajeError.Asignar("No se pudo calcular una transición del autómata unión.");
                        LiberarEstadosCompuestos(EstadosCompuestos);
                        delete Resultado;
                        return nullptr;
                    }

                    EstadoCompuesto* DestinoCompuesto = BuscarEstadoCompuesto(
                        EstadosCompuestos,
                        Transicion1->ObtenerDestino(),
                        Transicion2->ObtenerDestino()
                        );

                    if (DestinoCompuesto == nullptr) {
                        MensajeError.Asignar("No se encontró el estado compuesto de destino.");
                        LiberarEstadosCompuestos(EstadosCompuestos);
                        delete Resultado;
                        return nullptr;
                    }

                    Simbolo* SimboloResultado = Resultado->BuscarSimbolo(Simbolo1->ObtenerValor());
                    Resultado->AgregarTransicion(
                        EstadoActual->ObtenerEstadoResultado(),
                        SimboloResultado,
                        DestinoCompuesto->ObtenerEstadoResultado()
                        );
                }
                SimboloNodo = SimboloNodo->ObtenerSiguiente();
            }
        }
        NodoCompuesto = NodoCompuesto->ObtenerSiguiente();
    }

    Resultado->EstablecerValidado(true);
    LiberarEstadosCompuestos(EstadosCompuestos);
    return Resultado;
}
