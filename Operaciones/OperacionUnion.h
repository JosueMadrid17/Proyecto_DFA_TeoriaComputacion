#ifndef OPERACIONUNION_H
#define OPERACIONUNION_H
#include "../Estructuras/ListaEnlazada.h"
#include "../Estructuras/CadenaManual.h"

class Automata;
class Estado;
class EstadoCompuesto;

class OperacionUnion {
private:
    bool VerificarAlfabetos(Automata* Automata1, Automata* Automata2, CadenaManual& MensajeError) const;

    EstadoCompuesto* BuscarEstadoCompuesto(ListaEnlazada<EstadoCompuesto*>& EstadosCompuestos, Estado* Estado1, Estado* Estado2) const;
    CadenaManual ConstruirNombreEstadoCompuesto(Estado* Estado1, Estado* Estado2) const;

    void LiberarEstadosCompuestos(ListaEnlazada<EstadoCompuesto*>& EstadosCompuestos) const;

public:
    Automata* Unir(Automata* Automata1, Automata* Automata2, CadenaManual& MensajeError);
};

#endif
