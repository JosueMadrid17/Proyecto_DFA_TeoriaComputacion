#ifndef REGISTROAUTOMATAS_H
#define REGISTROAUTOMATAS_H
#include "../Estructuras/ListaEnlazada.h"

class Automata;

class RegistroAutomatas {
private:
    ListaEnlazada<Automata*> AutomatasGuardados;

public:
    RegistroAutomatas();
    ~RegistroAutomatas();

    bool GuardarAutomata(Automata* NuevoAutomata);
    Automata* ObtenerAutomata(int Posicion) const;

    int ObtenerCantidad() const;
    Nodo<Automata*>* ObtenerPrimerAutomata() const;
};

#endif
