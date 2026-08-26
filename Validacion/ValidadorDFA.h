#ifndef VALIDADORDFA_H
#define VALIDADORDFA_H

class Automata;
class ResultadoValidacion;
class CadenaManual;

class ValidadorDFA {
private:
    void ValidarNoVacuidad(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarEstadosDuplicados(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarSimbolosDuplicados(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarSimbolosPermitidos(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarEstadoInicial(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarEstadosFinales(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarIntegridadTransiciones(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
    void ValidarTotalidadYDeterminismo(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);

    bool ContieneEspacio(const CadenaManual& Texto) const;
    bool ContieneGuion(const CadenaManual& Texto) const;

public:
    void Validar(Automata& AutomataEvaluado, ResultadoValidacion& Resultado);
};

#endif
