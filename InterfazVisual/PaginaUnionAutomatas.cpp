#include "PaginaUnionAutomatas.h"
#include "VistaAutomata.h"
#include "../Automatas/RegistroAutomatas.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"
#include "../Operaciones/OperacionUnion.h"
#include "../Estructuras/CadenaManual.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QFont>
#include <QScrollArea>
#include <QSizePolicy>

PaginaUnionAutomatas::PaginaUnionAutomatas(RegistroAutomatas* RegistroCompartido, QWidget* parent) : QWidget(parent) {
    Registro = RegistroCompartido;
    Operacion = new OperacionUnion();
    AutomataResultado = nullptr;

    ConstruirInterfaz();
    AplicarEstilos();
    ActualizarAutomatasGuardados();
}

PaginaUnionAutomatas::~PaginaUnionAutomatas() {
    if (AutomataResultado != nullptr) {
        delete AutomataResultado;
    }
    delete Operacion;
}

void PaginaUnionAutomatas::ConstruirInterfaz() {
    QVBoxLayout* LayoutPrincipal = new QVBoxLayout(this);
    LayoutPrincipal->setContentsMargins(60, 25, 60, 25);
    LayoutPrincipal->setSpacing(10);

    QLabel* Titulo = new QLabel("UNIÓN DE AUTOMATAS");
    Titulo->setAlignment(Qt::AlignCenter);

    QFont FuenteTitulo;
    FuenteTitulo.setPointSize(35);
    FuenteTitulo.setBold(true);
    Titulo->setFont(FuenteTitulo);

    LayoutPrincipal->addWidget(Titulo);
    LayoutPrincipal->addSpacing(10);

    QHBoxLayout* LayoutSeleccion = new QHBoxLayout();
    LayoutSeleccion->setSpacing(12);

    QLabel* EtiquetaAutomata1 = new QLabel("Automata A:");
    QLabel* EtiquetaAutomata2 = new QLabel("Automata B:");

    ComboAutomata1 = new QComboBox();
    ComboAutomata2 = new QComboBox();
    ComboAutomata1->setFixedHeight(42);
    ComboAutomata2->setFixedHeight(42);

    QPushButton* BotonUnion = new QPushButton("REALIZAR UNIÓN");
    BotonUnion->setFixedSize(190, 42);

    LayoutSeleccion->addWidget(EtiquetaAutomata1);
    LayoutSeleccion->addWidget(ComboAutomata1);
    LayoutSeleccion->addWidget(EtiquetaAutomata2);
    LayoutSeleccion->addWidget(ComboAutomata2);
    LayoutSeleccion->addWidget(BotonUnion);
    LayoutPrincipal->addLayout(LayoutSeleccion);

    MensajeResultado = new QLabel();
    MensajeResultado->setMinimumHeight(30);
    LayoutPrincipal->addWidget(MensajeResultado);

    QLabel* EtiquetaResultado = new QLabel("AUTOMATA RESULTANTE");

    QFont FuenteSeccion;
    FuenteSeccion.setPointSize(17);
    FuenteSeccion.setBold(true);
    EtiquetaResultado->setFont(FuenteSeccion);

    LayoutPrincipal->addWidget(EtiquetaResultado);

    TablaResultado = new QTableWidget();
    TablaResultado->setColumnCount(3);
    TablaResultado->setRowCount(0);
    TablaResultado->setHorizontalHeaderItem(0, new QTableWidgetItem("Origen"));
    TablaResultado->setHorizontalHeaderItem(1, new QTableWidgetItem("Simbolo"));
    TablaResultado->setHorizontalHeaderItem(2, new QTableWidgetItem("Destino"));
    TablaResultado->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    TablaResultado->verticalHeader()->setDefaultSectionSize(30);
    TablaResultado->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TablaResultado->setSelectionMode(QAbstractItemView::NoSelection);
    TablaResultado->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    TablaResultado->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    TablaResultado->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    TablaResultado->setMinimumHeight(280);
    TablaResultado->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    Vista = new VistaAutomata();
    Vista->EstablecerAutomata(nullptr);
    Vista->setMinimumWidth(0);
    Vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QScrollArea* AreaAutomata = new QScrollArea();
    AreaAutomata->setWidget(Vista);
    AreaAutomata->setWidgetResizable(true);
    AreaAutomata->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    AreaAutomata->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AreaAutomata->setMinimumHeight(280);
    AreaAutomata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* LayoutResultado = new QHBoxLayout();
    LayoutResultado->setSpacing(12);
    LayoutResultado->addWidget(TablaResultado, 1);
    LayoutResultado->addWidget(AreaAutomata, 1);
    LayoutPrincipal->addLayout(LayoutResultado, 1);

    QLabel* EtiquetaComponentes = new QLabel("COMPONENTES DEL RESULTADO");
    EtiquetaComponentes->setFont(FuenteSeccion);

    ResumenResultado = new QPlainTextEdit();
    ResumenResultado->setReadOnly(true);
    ResumenResultado->setFixedHeight(120);
    ResumenResultado->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ResumenResultado->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ResumenResultado->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    LayoutPrincipal->addWidget(EtiquetaComponentes);
    LayoutPrincipal->addWidget(ResumenResultado);

    QHBoxLayout* LayoutBotones = new QHBoxLayout();

    QPushButton* BotonVolver = new QPushButton("VOLVER");
    QPushButton* BotonLimpiar = new QPushButton("LIMPIAR");

    BotonVolver->setFixedSize(150, 45);
    BotonLimpiar->setFixedSize(150, 45);

    LayoutBotones->addWidget(BotonVolver);
    LayoutBotones->addStretch();
    LayoutBotones->addWidget(BotonLimpiar);
    LayoutPrincipal->addLayout(LayoutBotones);

    connect(BotonUnion, &QPushButton::clicked, this, &PaginaUnionAutomatas::RealizarUnion);
    connect(BotonLimpiar, &QPushButton::clicked, this, &PaginaUnionAutomatas::LimpiarResultado);
    connect(BotonVolver, &QPushButton::clicked, this, &PaginaUnionAutomatas::SolicitarVolver);
}

void PaginaUnionAutomatas::AplicarEstilos() {
    setStyleSheet(R"(
        QWidget {
            background-color: white;
            color: black;
            font-family: "Segoe UI";
        }

        QLabel {
            font-size: 16px;
            font-weight: bold;
        }

        QComboBox {
            background-color: white;
            color: black;
            border: 1px solid #9CA3AF;
            padding: 5px;
            font-size: 15px;
        }

        QTableWidget {
            background-color: white;
            color: black;
            border: 1px solid #9CA3AF;
            font-size: 15px;
        }

        QHeaderView::section {
            background-color: #E5E7EB;
            color: black;
            font-weight: bold;
            border: 1px solid #D1D5DB;
            padding: 5px;
        }

        QPlainTextEdit {
            background-color: white;
            color: black;
            border: 1px solid #9CA3AF;
            font-size: 15px;
        }

        QPushButton {
            background-color: #2563EB;
            color: white;
            border: none;
            font-size: 15px;
            font-weight: bold;
        }
    )");
}

void PaginaUnionAutomatas::ActualizarAutomatasGuardados() {
    LimpiarResultado();

    ComboAutomata1->clear();
    ComboAutomata2->clear();

    if (Registro == nullptr) {
        MensajeResultado->setText("No se pudo acceder a los automatas guardados.");
        return;
    }

    Nodo<Automata*>* Actual = Registro->ObtenerPrimerAutomata();
    int Numero = 1;

    while (Actual != nullptr) {
        Automata* AutomataGuardado = Actual->ObtenerDato();

        if (AutomataGuardado != nullptr) {
            QString Nombre = ConstruirNombreAutomata(AutomataGuardado, Numero);

            ComboAutomata1->addItem(Nombre);
            ComboAutomata2->addItem(Nombre);
        }
        Numero++;
        Actual = Actual->ObtenerSiguiente();
    }

    if (Registro->ObtenerCantidad() < 2) {
        MensajeResultado->setText("Debe guardar al menos dos automatas validados para realizar la union.");
        return;
    }
    ComboAutomata1->setCurrentIndex(0);
    ComboAutomata2->setCurrentIndex(1);
    MensajeResultado->clear();
}

void PaginaUnionAutomatas::RealizarUnion() {
    LimpiarResultado();

    if (Registro == nullptr || Registro->ObtenerCantidad() < 2) {
        MensajeResultado->setText("Debe guardar al menos dos automatas validados.");
        return;
    }

    int Posicion1 = ComboAutomata1->currentIndex();
    int Posicion2 = ComboAutomata2->currentIndex();

    if (Posicion1 < 0 || Posicion2 < 0) {
        MensajeResultado->setText("Debe seleccionar dos automatas.");
        return;
    }

    if (Posicion1 == Posicion2) {
        MensajeResultado->setText("Debe seleccionar dos autómatas diferentes.");
        return;
    }

    Automata* Automata1 = Registro->ObtenerAutomata(Posicion1);
    Automata* Automata2 = Registro->ObtenerAutomata(Posicion2);

    if (Automata1 == nullptr || Automata2 == nullptr) {
        MensajeResultado->setText("No se pudieron obtener los autómatas seleccionados.");
        return;
    }

    CadenaManual MensajeError;

    AutomataResultado = Operacion->Unir(
        Automata1,
        Automata2,
        MensajeError
        );

    if (AutomataResultado == nullptr) {
        MensajeResultado->setText(ConvertirAQString(MensajeError));
        return;
    }

    MensajeResultado->setText("Unión realizada correctamente.");

    MostrarTabla();
    MostrarResumen();
    Vista->EstablecerAutomata(AutomataResultado);
    Vista->Refrescar();
}

void PaginaUnionAutomatas::LimpiarResultado() {
    Vista->EstablecerAutomata(nullptr);

    if (AutomataResultado != nullptr) {
        delete AutomataResultado;
        AutomataResultado = nullptr;
    }
    TablaResultado->setRowCount(0);
    ResumenResultado->clear();
    MensajeResultado->clear();
}

void PaginaUnionAutomatas::MostrarTabla() {
    if (AutomataResultado == nullptr) {
        return;
    }

    TablaResultado->setRowCount(0);

    Nodo<Transicion*>* Actual = AutomataResultado->ObtenerPrimeraTransicion();

    while (Actual != nullptr) {
        Transicion* TransicionActual = Actual->ObtenerDato();

        if (TransicionActual != nullptr) {
            int Fila = TablaResultado->rowCount();
            TablaResultado->insertRow(Fila);
            TablaResultado->setItem(Fila, 0, new QTableWidgetItem(FormatearEstado(TransicionActual->ObtenerOrigen())));

            if (TransicionActual->ObtenerSimbolo() != nullptr) {
                TablaResultado->setItem(Fila, 1, new QTableWidgetItem(ConvertirAQString(TransicionActual->ObtenerSimbolo()->ObtenerValor())));
            }
            TablaResultado->setItem(Fila, 2, new QTableWidgetItem(FormatearEstado(TransicionActual->ObtenerDestino())));
        }
        Actual = Actual->ObtenerSiguiente();
    }
    TablaResultado->scrollToTop();
}

void PaginaUnionAutomatas::MostrarResumen() {
    if (AutomataResultado == nullptr) {
        return;
    }

    QString Texto;
    Texto += "Estados: {";

    Nodo<Estado*>* NodoEstado = AutomataResultado->ObtenerPrimerEstado();
    bool Primero = true;

    while (NodoEstado != nullptr) {
        Estado* EstadoActual = NodoEstado->ObtenerDato();

        if (EstadoActual != nullptr) {
            if (!Primero) {
                Texto += ", ";
            }
            Texto += ConvertirAQString(EstadoActual->ObtenerNombre());
            Primero = false;
        }
        NodoEstado = NodoEstado->ObtenerSiguiente();
    }

    Texto += "}\n";
    Texto += "Alfabeto: {";

    Nodo<Simbolo*>* NodoSimbolo = AutomataResultado->ObtenerPrimerSimbolo();
    Primero = true;

    while (NodoSimbolo != nullptr) {
        Simbolo* SimboloActual = NodoSimbolo->ObtenerDato();

        if (SimboloActual != nullptr) {
            if (!Primero) {
                Texto += ", ";
            }
            Texto += ConvertirAQString(SimboloActual->ObtenerValor());
            Primero = false;
        }
        NodoSimbolo = NodoSimbolo->ObtenerSiguiente();
    }

    Texto += "}\n";
    Texto += "Estado inicial: ";

    Estado* Inicial = AutomataResultado->ObtenerEstadoInicial();

    if (Inicial != nullptr) {
        Texto += ConvertirAQString(Inicial->ObtenerNombre());
    }

    Texto += "\n";
    Texto += "Estados finales: {";

    Nodo<Estado*>* NodoFinal = AutomataResultado->ObtenerPrimerEstadoFinal();
    Primero = true;

    while (NodoFinal != nullptr) {
        Estado* EstadoFinal = NodoFinal->ObtenerDato();

        if (EstadoFinal != nullptr) {
            if (!Primero) {
                Texto += ", ";
            }
            Texto += ConvertirAQString(EstadoFinal->ObtenerNombre());
            Primero = false;
        }
        NodoFinal = NodoFinal->ObtenerSiguiente();
    }
    Texto += "}";
    ResumenResultado->setPlainText(Texto);
}

QString PaginaUnionAutomatas::ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const {
    QString Nombre = "Automata ";
    Nombre += QString::number(Numero);
    Nombre += " (Σ={";

    Nodo<Simbolo*>* Actual = AutomataGuardado->ObtenerPrimerSimbolo();
    bool Primero = true;

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();

        if (SimboloActual != nullptr) {
            if (!Primero) {
                Nombre += ",";
            }
            Nombre += ConvertirAQString(SimboloActual->ObtenerValor());
            Primero = false;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    Nombre += "})";
    return Nombre;
}

QString PaginaUnionAutomatas::FormatearEstado(Estado* EstadoActual) const {
    if (EstadoActual == nullptr || AutomataResultado == nullptr) {
        return "";
    }
    QString Texto;

    if (AutomataResultado->ObtenerEstadoInicial() == EstadoActual) {
        Texto += "-> ";
    }
    Texto += ConvertirAQString(EstadoActual->ObtenerNombre());

    if (AutomataResultado->EsEstadoFinal(EstadoActual)) {
        Texto += " *";
    }
    return Texto;
}

QString PaginaUnionAutomatas::ConvertirAQString(const CadenaManual& Texto) const {
    QString Resultado;
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        char Caracter = Texto.ObtenerCaracter(Posicion);
        Resultado.append(QChar(static_cast<unsigned char>(Caracter)));
        Posicion++;
    }
    return Resultado;
}
