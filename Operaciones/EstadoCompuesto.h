#ifndef ESTADOCOMPUESTO_H
#define ESTADOCOMPUESTO_H

class Estado;

class EstadoCompuesto {
private:
    Estado* EstadoAutomata1;
    Estado* EstadoAutomata2;
    Estado* EstadoResultado;

public:
    EstadoCompuesto(Estado* Estado1, Estado* Estado2, Estado* Resultado);

    Estado* ObtenerEstadoAutomata1() const;
    Estado* ObtenerEstadoAutomata2() const;
    Estado* ObtenerEstadoResultado() const;

    bool Coincide(Estado* Estado1, Estado* Estado2) const;
};

#endif
