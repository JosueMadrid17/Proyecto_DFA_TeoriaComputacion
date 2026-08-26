#ifndef CADENAMANUAL_H
#define CADENAMANUAL_H
#include "Nodo.h"

class CadenaManual {
private:
    Nodo<char>* Primero;
    Nodo<char>* Ultimo;
    int Longitud;

    void Limpiar();
    void CopiarDesde(const CadenaManual& OtraCadena);

public:
    CadenaManual();
    CadenaManual(const char* Texto);
    CadenaManual(const CadenaManual& OtraCadena);
    ~CadenaManual();

    CadenaManual& operator=(const CadenaManual& OtraCadena);

    void Asignar(const char* Texto);
    void AgregarCaracter(char Caracter);
    void AgregarTexto(const char* Texto);
    void AgregarCadena(const CadenaManual& OtraCadena);

    int ObtenerLongitud() const;
    bool EstaVacia() const;
    char ObtenerCaracter(int Posicion) const;

    bool EsIgual(const CadenaManual& OtraCadena) const;
    bool EsIgual(const char* Texto) const;
};

#endif
