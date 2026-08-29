#include "PaginaCrearAutomata.h"
#include "VistaAutomata.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Estado.h"
#include "../Automatas/Simbolo.h"
#include "../Automatas/Transicion.h"
#include "../Automatas/RegistroAutomatas.h"
#include "../Validacion/ValidadorDFA.h"
#include "../Validacion/ResultadoValidacion.h"
#include "../Validacion/ErrorValidacion.h"
#include "../Estructuras/CadenaManual.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QFont>
#include <QByteArray>
#include <QString>
#include <QScrollArea>
#include <QSizePolicy>

PaginaCrearAutomata::PaginaCrearAutomata(RegistroAutomatas* RegistroCompartido, QWidget* parent) : QWidget(parent) {
    Registro = RegistroCompartido;
    AutomataActual = new Automata();
    Validador = new ValidadorDFA();
    Resultado = new ResultadoValidacion();

    ConstruirInterfaz();
    AplicarEstilos();
}

PaginaCrearAutomata::~PaginaCrearAutomata() {
    delete Resultado;
    delete Validador;
    delete AutomataActual;
}

void PaginaCrearAutomata::ConstruirInterfaz() {
    QVBoxLayout* LayoutPrincipal = new QVBoxLayout(this);
    LayoutPrincipal->setContentsMargins(60, 20, 60, 20);
    LayoutPrincipal->setSpacing(7);

    QLabel* Titulo = new QLabel("CREAR Y VALIDAR AUTOMATA");
    Titulo->setAlignment(Qt::AlignCenter);

    QFont FuenteTitulo;
    FuenteTitulo.setPointSize(35);
    FuenteTitulo.setBold(true);
    Titulo->setFont(FuenteTitulo);

    LayoutPrincipal->addWidget(Titulo);
    LayoutPrincipal->addSpacing(5);

    QGridLayout* LayoutDatos = new QGridLayout();
    LayoutDatos->setHorizontalSpacing(12);
    LayoutDatos->setVerticalSpacing(8);

    QLabel* EtiquetaEstado = new QLabel("Estado:");
    EntradaEstado = new QLineEdit();
    QPushButton* BotonAgregarEstado = new QPushButton("AGREGAR");

    EtiquetaEstado->setFixedWidth(130);
    EntradaEstado->setFixedHeight(40);
    BotonAgregarEstado->setFixedSize(130, 40);

    LayoutDatos->addWidget(EtiquetaEstado, 0, 0);
    LayoutDatos->addWidget(EntradaEstado, 0, 1);
    LayoutDatos->addWidget(BotonAgregarEstado, 0, 2);

    QLabel* EtiquetaSimbolo = new QLabel("Símbolo:");
    EntradaSimbolo = new QLineEdit();
    QPushButton* BotonAgregarSimbolo = new QPushButton("AGREGAR");

    EntradaSimbolo->setFixedHeight(40);
    BotonAgregarSimbolo->setFixedSize(130, 40);

    LayoutDatos->addWidget(EtiquetaSimbolo, 1, 0);
    LayoutDatos->addWidget(EntradaSimbolo, 1, 1);
    LayoutDatos->addWidget(BotonAgregarSimbolo, 1, 2);

    QLabel* EtiquetaInicial = new QLabel("Estado inicial:");
    ComboEstadoInicial = new QComboBox();
    ComboEstadoInicial->setFixedHeight(40);

    LayoutDatos->addWidget(EtiquetaInicial, 2, 0);
    LayoutDatos->addWidget(ComboEstadoInicial, 2, 1);

    QLabel* EtiquetaFinal = new QLabel("Estado final:");
    ComboEstadoFinal = new QComboBox();
    ComboEstadoFinal->setFixedHeight(40);

    QPushButton* BotonAgregarFinal = new QPushButton("AGREGAR");
    BotonAgregarFinal->setFixedSize(130, 40);

    LayoutDatos->addWidget(EtiquetaFinal, 3, 0);
    LayoutDatos->addWidget(ComboEstadoFinal, 3, 1);
    LayoutDatos->addWidget(BotonAgregarFinal, 3, 2);

    EtiquetaEstadosFinales = new QLabel("Estados finales: Ninguno");
    LayoutDatos->addWidget(EtiquetaEstadosFinales, 4, 1, 1, 2);

    LayoutPrincipal->addLayout(LayoutDatos);
    LayoutPrincipal->addSpacing(4);

    QLabel* EtiquetaTransiciones = new QLabel("TRANSICIONES");

    QFont FuenteSeccion;
    FuenteSeccion.setPointSize(17);
    FuenteSeccion.setBold(true);
    EtiquetaTransiciones->setFont(FuenteSeccion);

    LayoutPrincipal->addWidget(EtiquetaTransiciones);

    QHBoxLayout* LayoutTransicion = new QHBoxLayout();

    ComboOrigen = new QComboBox();
    ComboSimbolo = new QComboBox();
    ComboDestino = new QComboBox();

    ComboOrigen->setFixedHeight(40);
    ComboSimbolo->setFixedHeight(40);
    ComboDestino->setFixedHeight(40);

    QPushButton* BotonAgregarTransicion = new QPushButton("AGREGAR TRANSICION");
    BotonAgregarTransicion->setFixedSize(190, 40);

    LayoutTransicion->addWidget(new QLabel("Origen:"));
    LayoutTransicion->addWidget(ComboOrigen);
    LayoutTransicion->addWidget(new QLabel("Simbolo:"));
    LayoutTransicion->addWidget(ComboSimbolo);
    LayoutTransicion->addWidget(new QLabel("Destino:"));
    LayoutTransicion->addWidget(ComboDestino);
    LayoutTransicion->addWidget(BotonAgregarTransicion);
    LayoutPrincipal->addLayout(LayoutTransicion);

    TablaTransiciones = new QTableWidget();
    TablaTransiciones->setColumnCount(3);
    TablaTransiciones->setRowCount(0);
    TablaTransiciones->setHorizontalHeaderItem(0, new QTableWidgetItem("Origen"));
    TablaTransiciones->setHorizontalHeaderItem(1, new QTableWidgetItem("Simbolo"));
    TablaTransiciones->setHorizontalHeaderItem(2, new QTableWidgetItem("Destino"));
    TablaTransiciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    TablaTransiciones->verticalHeader()->setDefaultSectionSize(30);
    TablaTransiciones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TablaTransiciones->setSelectionMode(QAbstractItemView::NoSelection);
    TablaTransiciones->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    TablaTransiciones->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    TablaTransiciones->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    TablaTransiciones->setMinimumHeight(220);
    TablaTransiciones->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    Vista = new VistaAutomata();
    Vista->EstablecerAutomata(AutomataActual);
    Vista->setMinimumWidth(0);
    Vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QScrollArea* AreaAutomata = new QScrollArea();
    AreaAutomata->setWidget(Vista);
    AreaAutomata->setWidgetResizable(true);
    AreaAutomata->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    AreaAutomata->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AreaAutomata->setMinimumHeight(220);
    AreaAutomata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* LayoutVisualizacion = new QHBoxLayout();
    LayoutVisualizacion->setSpacing(12);
    LayoutVisualizacion->addWidget(TablaTransiciones, 1);
    LayoutVisualizacion->addWidget(AreaAutomata, 1);

    LayoutPrincipal->addLayout(LayoutVisualizacion, 1);

    QLabel* EtiquetaValidacion = new QLabel("RESULTADO DE VALIDACION");
    EtiquetaValidacion->setFont(FuenteSeccion);

    SalidaValidacion = new QPlainTextEdit();
    SalidaValidacion->setReadOnly(true);
    SalidaValidacion->setFixedHeight(85);
    SalidaValidacion->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    SalidaValidacion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SalidaValidacion->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    QVBoxLayout* LayoutValidacion = new QVBoxLayout();
    LayoutValidacion->setContentsMargins(0, 0, 0, 0);
    LayoutValidacion->setSpacing(4);
    LayoutValidacion->addWidget(EtiquetaValidacion);
    LayoutValidacion->addWidget(SalidaValidacion);

    QHBoxLayout* LayoutResultado = new QHBoxLayout();
    LayoutResultado->setContentsMargins(0, 0, 0, 0);
    LayoutResultado->setSpacing(12);
    LayoutResultado->addLayout(LayoutValidacion, 1);
    LayoutResultado->addStretch(1);

    LayoutPrincipal->addLayout(LayoutResultado);

    QHBoxLayout* LayoutBotones = new QHBoxLayout();
    QPushButton* BotonVolver = new QPushButton("VOLVER");
    QPushButton* BotonLimpiar = new QPushButton("LIMPIAR");
    QPushButton* BotonGuardar = new QPushButton("GUARDAR AUTOMATA");
    QPushButton* BotonValidar = new QPushButton("VALIDAR AUTOMATA");

    BotonVolver->setFixedSize(150, 45);
    BotonLimpiar->setFixedSize(150, 45);
    BotonGuardar->setFixedSize(200, 45);
    BotonValidar->setFixedSize(200, 45);

    LayoutBotones->addWidget(BotonVolver);
    LayoutBotones->addStretch();
    LayoutBotones->addWidget(BotonLimpiar);
    LayoutBotones->addWidget(BotonGuardar);
    LayoutBotones->addWidget(BotonValidar);
    LayoutPrincipal->addLayout(LayoutBotones);

    connect(BotonAgregarEstado, &QPushButton::clicked, this, &PaginaCrearAutomata::AgregarEstado);
    connect(BotonAgregarSimbolo, &QPushButton::clicked, this, &PaginaCrearAutomata::AgregarSimbolo);
    connect(BotonAgregarFinal, &QPushButton::clicked, this, &PaginaCrearAutomata::AgregarEstadoFinal);
    connect(BotonAgregarTransicion, &QPushButton::clicked, this, &PaginaCrearAutomata::AgregarTransicion);
    connect(BotonValidar, &QPushButton::clicked, this, &PaginaCrearAutomata::ValidarAutomata);
    connect(BotonLimpiar, &QPushButton::clicked, this, &PaginaCrearAutomata::LimpiarAutomata);
    connect(BotonGuardar, &QPushButton::clicked, this, &PaginaCrearAutomata::GuardarAutomata);
    connect(BotonVolver, &QPushButton::clicked, this, &PaginaCrearAutomata::SolicitarVolver);
    connect(ComboEstadoInicial, &QComboBox::currentIndexChanged, this, [this](int) {
        AutomataActual->EstablecerValidado(false);
        Vista->Refrescar();
    });
}

void PaginaCrearAutomata::AplicarEstilos() {
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

        QLineEdit, QComboBox {
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

void PaginaCrearAutomata::AgregarEstado() {
    QString Texto = EntradaEstado->text();

    if (Texto.isEmpty()) {
        SalidaValidacion->setPlainText("Debe ingresar un estado.");
        return;
    }

    QByteArray Datos = Texto.toUtf8();
    AutomataActual->AgregarEstado(Datos.constData());

    ComboEstadoInicial->addItem(Texto);
    ComboEstadoFinal->addItem(Texto);
    ComboOrigen->addItem(Texto);
    ComboDestino->addItem(Texto);

    if (ComboEstadoInicial->count() == 1) {
        ComboEstadoInicial->setCurrentIndex(-1);
    }
    EntradaEstado->clear();
    SalidaValidacion->clear();
    Vista->Refrescar();
}

void PaginaCrearAutomata::AgregarSimbolo() {
    QString Texto = EntradaSimbolo->text();

    if (Texto.isEmpty()) {
        SalidaValidacion->setPlainText("Debe ingresar un simbolo.");
        return;
    }

    QByteArray Datos = Texto.toUtf8();
    AutomataActual->AgregarSimbolo(Datos.constData());
    ComboSimbolo->addItem(Texto);
    EntradaSimbolo->clear();
    SalidaValidacion->clear();
    Vista->Refrescar();
}

void PaginaCrearAutomata::AgregarEstadoFinal() {
    if (ComboEstadoFinal->currentIndex() < 0) {
        SalidaValidacion->setPlainText("Debe seleccionar un estado final.");
        return;
    }

    QByteArray Datos = ComboEstadoFinal->currentText().toUtf8();
    Estado* EstadoFinal = AutomataActual->BuscarEstado(Datos.constData());

    if (EstadoFinal == nullptr) {
        SalidaValidacion->setPlainText("El estado seleccionado no existe.");
        return;
    }

    if (AutomataActual->EsEstadoFinal(EstadoFinal)) {
        SalidaValidacion->setPlainText("El estado ya fue agregado como final.");
        return;
    }
    AutomataActual->AgregarEstadoFinal(EstadoFinal);
    ActualizarEstadosFinales();
    SalidaValidacion->clear();
    Vista->Refrescar();
}

void PaginaCrearAutomata::AgregarTransicion() {
    if (ComboOrigen->currentIndex() < 0 ||
        ComboSimbolo->currentIndex() < 0 ||
        ComboDestino->currentIndex() < 0) {
        SalidaValidacion->setPlainText("Debe seleccionar origen, simbolo y destino.");
        return;
    }

    QByteArray TextoOrigen = ComboOrigen->currentText().toUtf8();
    QByteArray TextoSimbolo = ComboSimbolo->currentText().toUtf8();
    QByteArray TextoDestino = ComboDestino->currentText().toUtf8();

    Estado* Origen = AutomataActual->BuscarEstado(TextoOrigen.constData());
    Simbolo* SimboloUsado = AutomataActual->BuscarSimbolo(TextoSimbolo.constData());
    Estado* Destino = AutomataActual->BuscarEstado(TextoDestino.constData());

    AutomataActual->AgregarTransicion(Origen, SimboloUsado, Destino);
    int Fila = TablaTransiciones->rowCount();
    TablaTransiciones->insertRow(Fila);
    TablaTransiciones->setItem(Fila, 0, new QTableWidgetItem(ComboOrigen->currentText()));
    TablaTransiciones->setItem(Fila, 1, new QTableWidgetItem(ComboSimbolo->currentText()));
    TablaTransiciones->setItem(Fila, 2, new QTableWidgetItem(ComboDestino->currentText()));
    TablaTransiciones->scrollToBottom();
    SalidaValidacion->clear();
    Vista->Refrescar();
}

void PaginaCrearAutomata::ValidarAutomata() {
    if (ComboEstadoInicial->currentIndex() >= 0) {
        QByteArray TextoInicial = ComboEstadoInicial->currentText().toUtf8();
        Estado* Inicial = AutomataActual->BuscarEstado(TextoInicial.constData());
        AutomataActual->EstablecerEstadoInicial(Inicial);
    } else {
        AutomataActual->EstablecerEstadoInicial(nullptr);
    }

    Validador->Validar(*AutomataActual, *Resultado);
    Vista->Refrescar();
    SalidaValidacion->clear();

    if (Resultado->EsValido()) {
        SalidaValidacion->setPlainText("Automata valido.");
        return;
    }
    Nodo<ErrorValidacion*>* Actual = Resultado->ObtenerPrimerError();

    while (Actual != nullptr) {
        ErrorValidacion* Error = Actual->ObtenerDato();

        if (Error != nullptr) {
            SalidaValidacion->appendPlainText(ConvertirAQString(Error->ObtenerMensaje()));
        }
        Actual = Actual->ObtenerSiguiente();
    }
}

void PaginaCrearAutomata::LimpiarAutomata() {
    AutomataActual->Vaciar();
    Resultado->Limpiar();

    EntradaEstado->clear();
    EntradaSimbolo->clear();

    ComboEstadoInicial->clear();
    ComboEstadoFinal->clear();
    ComboOrigen->clear();
    ComboSimbolo->clear();
    ComboDestino->clear();

    TablaTransiciones->setRowCount(0);
    EtiquetaEstadosFinales->setText("Estados finales: Ninguno");
    SalidaValidacion->clear();
    Vista->Refrescar();
}

void PaginaCrearAutomata::ActualizarEstadosFinales() {
    Nodo<Estado*>* Actual = AutomataActual->ObtenerPrimerEstadoFinal();

    if (Actual == nullptr) {
        EtiquetaEstadosFinales->setText("Estados finales: Ninguno");
        return;
    }

    QString Texto = "Estados finales: ";
    bool PrimerEstado = true;

    while (Actual != nullptr) {
        Estado* EstadoActual = Actual->ObtenerDato();

        if (EstadoActual != nullptr) {
            if (!PrimerEstado) {
                Texto += ", ";
            }
            Texto += ConvertirAQString(EstadoActual->ObtenerNombre());
            PrimerEstado = false;
        }
        Actual = Actual->ObtenerSiguiente();
    }
    EtiquetaEstadosFinales->setText(Texto);
}

CadenaManual PaginaCrearAutomata::ConvertirACadenaManual(const QString& Texto) const {
    QByteArray Datos = Texto.toUtf8();
    return CadenaManual(Datos.constData());
}

QString PaginaCrearAutomata::ConvertirAQString(const CadenaManual& Texto) const {
    QByteArray Datos;
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        Datos.append(Texto.ObtenerCaracter(Posicion));
        Posicion++;
    }
    return QString::fromUtf8(Datos);
}

void PaginaCrearAutomata::GuardarAutomata() {
    if (Registro == nullptr) {
        SalidaValidacion->setPlainText("No se pudo acceder al registro de automatas.");
        return;
    }

    if (!AutomataActual->EstaValidado()) {
        SalidaValidacion->setPlainText("Debe validar correctamente el automata antes de guardarlo.");
        return;
    }

    Automata* AutomataGuardado = AutomataActual;

    if (!Registro->GuardarAutomata(AutomataGuardado)) {
        SalidaValidacion->setPlainText("No se pudo guardar el automata.");
        return;
    }

    int Numero = Registro->ObtenerCantidad();
    QString Nombre = ConstruirNombreAutomata(AutomataGuardado, Numero);

    AutomataActual = new Automata();
    Vista->EstablecerAutomata(AutomataActual);

    LimpiarAutomata();
    SalidaValidacion->setPlainText(Nombre + " guardado.");
}

QString PaginaCrearAutomata::ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const {
    QString Nombre = "Automata ";
    Nombre += QString::number(Numero);
    Nombre += " (Σ={";

    Nodo<Simbolo*>* Actual = AutomataGuardado->ObtenerPrimerSimbolo();
    bool PrimerSimbolo = true;

    while (Actual != nullptr) {
        Simbolo* SimboloActual = Actual->ObtenerDato();

        if (SimboloActual != nullptr) {
            if (!PrimerSimbolo) {
                Nombre += ",";
            }
            Nombre += ConvertirAQString(SimboloActual->ObtenerValor());
            PrimerSimbolo = false;
        }
        Actual = Actual->ObtenerSiguiente();
    }

    Nombre += "})";
    return Nombre;
}
