#ifndef TRANSICION_H
#define TRANSICION_H

class Estado;
class Simbolo;

class Transicion {
private:
    Estado* Origen;
    Simbolo* SimboloTransicion;
    Estado* Destino;

public:
    Transicion();
    Transicion(Estado* EstadoOrigen, Simbolo* SimboloUsado, Estado* EstadoDestino);

    void EstablecerOrigen(Estado* EstadoOrigen);
    void EstablecerSimbolo(Simbolo* SimboloUsado);
    void EstablecerDestino(Estado* EstadoDestino);

    Estado* ObtenerOrigen() const;
    Simbolo* ObtenerSimbolo() const;
    Estado* ObtenerDestino() const;

    bool Coincide(Estado* EstadoOrigen, Simbolo* SimboloUsado) const;
};

#endif
