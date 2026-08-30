#ifndef PROCESADORCADENAS_H
#define PROCESADORCADENAS_H
#include "../Estructuras/CadenaManual.h"

class Automata;
class ResultadoProcesamiento;

class ProcesadorCadenas {
public:
    ProcesadorCadenas();

    bool Procesar(Automata* AutomataEvaluado, const CadenaManual& Cadena, ResultadoProcesamiento& Resultado) const;
};

#endif
