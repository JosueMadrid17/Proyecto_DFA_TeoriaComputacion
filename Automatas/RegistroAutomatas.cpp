#include "RegistroAutomatas.h"
#include "Automata.h"

RegistroAutomatas::RegistroAutomatas() {}

RegistroAutomatas::~RegistroAutomatas() {
    Nodo<Automata*>* Actual = AutomatasGuardados.ObtenerPrimero();

    while (Actual != nullptr) {
        delete Actual->ObtenerDato();
        Actual = Actual->ObtenerSiguiente();
    }
    AutomatasGuardados.Limpiar();
}

bool RegistroAutomatas::GuardarAutomata(Automata* NuevoAutomata) {
    if (NuevoAutomata == nullptr) {
        return false;
    }

    if (!NuevoAutomata->EstaValidado()) {
        return false;
    }

    AutomatasGuardados.Agregar(NuevoAutomata);
    return true;
}

Automata* RegistroAutomatas::ObtenerAutomata(int Posicion) const {
    if (Posicion < 0 || Posicion >= AutomatasGuardados.ObtenerCantidad()) {
        return nullptr;
    }

    Nodo<Automata*>* Actual = AutomatasGuardados.ObtenerPrimero();
    int Indice = 0;

    while (Actual != nullptr) {
        if (Indice == Posicion) {
            return Actual->ObtenerDato();
        }
        Indice++;
        Actual = Actual->ObtenerSiguiente();
    }
    return nullptr;
}

int RegistroAutomatas::ObtenerCantidad() const {
    return AutomatasGuardados.ObtenerCantidad();
}

Nodo<Automata*>* RegistroAutomatas::ObtenerPrimerAutomata() const {
    return AutomatasGuardados.ObtenerPrimero();
}
