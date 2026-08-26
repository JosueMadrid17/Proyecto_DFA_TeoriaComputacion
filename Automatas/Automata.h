#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "../Estructuras/ListaEnlazada.h"

class Estado;
class Simbolo;
class Transicion;
class CadenaManual;

class Automata {
private:
    ListaEnlazada<Estado*> Estados;
    ListaEnlazada<Simbolo*> Alfabeto;
    ListaEnlazada<Estado*> EstadosFinales;
    ListaEnlazada<Transicion*> Transiciones;

    Estado* EstadoInicial;
    bool Validado;

public:
    Automata();
    ~Automata();
    Automata(const Automata&) = delete;
    Automata& operator=(const Automata&) = delete;

    Estado* AgregarEstado(const char* Nombre);
    Simbolo* AgregarSimbolo(const char* Valor);
    Transicion* AgregarTransicion(Estado* Origen, Simbolo* SimboloUsado, Estado* Destino);

    void EstablecerEstadoInicial(Estado* NuevoEstadoInicial);
    void AgregarEstadoFinal(Estado* NuevoEstadoFinal);

    Estado* BuscarEstado(const CadenaManual& NombreBuscado) const;
    Estado* BuscarEstado(const char* NombreBuscado) const;
    Simbolo* BuscarSimbolo(const CadenaManual& ValorBuscado) const;
    Simbolo* BuscarSimbolo(const char* ValorBuscado) const;
    Transicion* BuscarTransicion(Estado* Origen, Simbolo* SimboloUsado) const;
    int ContarTransiciones(Estado* Origen, Simbolo* SimboloUsado) const;

    bool PerteneceEstado(Estado* EstadoBuscado) const;
    bool PerteneceSimbolo(Simbolo* SimboloBuscado) const;
    bool EsEstadoFinal(Estado* EstadoBuscado) const;

    Estado* ObtenerEstadoInicial() const;
    Nodo<Estado*>* ObtenerPrimerEstado() const;
    Nodo<Simbolo*>* ObtenerPrimerSimbolo() const;
    Nodo<Estado*>* ObtenerPrimerEstadoFinal() const;
    Nodo<Transicion*>* ObtenerPrimeraTransicion() const;

    int ObtenerCantidadEstados() const;
    int ObtenerCantidadSimbolos() const;
    int ObtenerCantidadEstadosFinales() const;
    int ObtenerCantidadTransiciones() const;

    bool EstaValidado() const;
    void EstablecerValidado(bool EstadoValidacion);
    void Vaciar();
};

#endif
