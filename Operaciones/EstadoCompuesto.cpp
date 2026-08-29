#include "EstadoCompuesto.h"

EstadoCompuesto::EstadoCompuesto(Estado* Estado1, Estado* Estado2, Estado* Resultado) {
    EstadoAutomata1 = Estado1;
    EstadoAutomata2 = Estado2;
    EstadoResultado = Resultado;
}

Estado* EstadoCompuesto::ObtenerEstadoAutomata1() const {
    return EstadoAutomata1;
}

Estado* EstadoCompuesto::ObtenerEstadoAutomata2() const {
    return EstadoAutomata2;
}

Estado* EstadoCompuesto::ObtenerEstadoResultado() const {
    return EstadoResultado;
}

bool EstadoCompuesto::Coincide(Estado* Estado1, Estado* Estado2) const {
    return EstadoAutomata1 == Estado1 && EstadoAutomata2 == Estado2;
}
