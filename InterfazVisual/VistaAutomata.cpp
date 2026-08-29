#include "VistaAutomata.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"
#include "../Estructuras/CadenaManual.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

VistaAutomata::VistaAutomata(QWidget* parent) : QWidget(parent) {
    AutomataVisualizado = nullptr;

    QVBoxLayout* LayoutPrincipal = new QVBoxLayout(this);
    LayoutPrincipal->setContentsMargins(20, 20, 20, 20);

    AreaTexto = new QLabel();
    AreaTexto->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    AreaTexto->setWordWrap(false);

    QFont Fuente("Consolas");
    Fuente.setPointSize(11);
    AreaTexto->setFont(Fuente);

    LayoutPrincipal->addWidget(AreaTexto);

    setMinimumWidth(0);
    setMinimumHeight(280);
    setStyleSheet("background-color: white; border: 1px solid #9CA3AF;");
    ActualizarVista();
}

void VistaAutomata::EstablecerAutomata(Automata* NuevoAutomata) {
    AutomataVisualizado = NuevoAutomata;
    ActualizarVista();
}

void VistaAutomata::Refrescar() {
    ActualizarVista();
}

void VistaAutomata::ActualizarVista() {
    if (AutomataVisualizado == nullptr || !AutomataVisualizado->EstaValidado()) {
        AreaTexto->setText("Valide el automata para visualizarlo.");
        AjustarTamano();
        return;
    }
    AreaTexto->setText(ConstruirDiagrama());
    AjustarTamano();
}

void VistaAutomata::AjustarTamano() {
    if (AutomataVisualizado == nullptr) {
        resize(700, 280);
        return;
    }

    int CantidadEstados = AutomataVisualizado->ObtenerCantidadEstados();
    int CantidadSimbolos = AutomataVisualizado->ObtenerCantidadSimbolos();
    int LineasPorEstado = CantidadSimbolos + 2;
    int Alto = 50 + (CantidadEstados * LineasPorEstado * 24);

    if (Alto < 280) {
        Alto = 280;
    }
    setMinimumHeight(Alto);
}

QString VistaAutomata::ConstruirDiagrama() const {
    QString Diagrama;

    Nodo<Estado*>* NodoEstado = AutomataVisualizado->ObtenerPrimerEstado();

    while (NodoEstado != nullptr) {
        Estado* EstadoActual = NodoEstado->ObtenerDato();

        if (EstadoActual != nullptr) {
            bool EsInicial = AutomataVisualizado->ObtenerEstadoInicial() == EstadoActual;
            bool EsFinal = AutomataVisualizado->EsEstadoFinal(EstadoActual);

            if (EsInicial) {
                Diagrama += "INICIO -> ";
            } else if (EsFinal) {
                Diagrama += "FINAL  -> ";
            } else {
                Diagrama += "          ";
            }

            Diagrama += FormatearEstado(EstadoActual);
            Diagrama += "\n";

            Nodo<Transicion*>* NodoTransicion = AutomataVisualizado->ObtenerPrimeraTransicion();

            while (NodoTransicion != nullptr) {
                Transicion* TransicionActual = NodoTransicion->ObtenerDato();

                if (TransicionActual != nullptr && TransicionActual->ObtenerOrigen() == EstadoActual) {
                    Simbolo* SimboloUsado = TransicionActual->ObtenerSimbolo();
                    Estado* Destino = TransicionActual->ObtenerDestino();

                    Diagrama += "          |-- ";

                    if (SimboloUsado != nullptr) {
                        Diagrama += ConvertirAQString(SimboloUsado->ObtenerValor());
                    }
                    Diagrama += " --> ";
                    Diagrama += FormatearEstado(Destino);
                    Diagrama += "\n";
                }
                NodoTransicion = NodoTransicion->ObtenerSiguiente();
            }
            Diagrama += "\n";
        }
        NodoEstado = NodoEstado->ObtenerSiguiente();
    }
    return Diagrama;
}

QString VistaAutomata::FormatearEstado(Estado* EstadoActual) const {
    if (EstadoActual == nullptr) {
        return "[ ? ]";
    }

    QString Nombre = ConvertirAQString(EstadoActual->ObtenerNombre());

    if (AutomataVisualizado->EsEstadoFinal(EstadoActual)) {
        return "[[ " + Nombre + " ]]";
    }
    return "[ " + Nombre + " ]";
}

QString VistaAutomata::ConvertirAQString(const CadenaManual& Texto) const {
    QString Resultado;
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        char Caracter = Texto.ObtenerCaracter(Posicion);
        Resultado.append(QChar(static_cast<unsigned char>(Caracter)));
        Posicion++;
    }
    return Resultado;
}
