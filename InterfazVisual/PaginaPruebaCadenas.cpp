#include "PaginaPruebaCadenas.h"
#include "../Automatas/RegistroAutomatas.h"
#include "../Automatas/Automata.h"
#include "../Automatas/Simbolo.h"
#include "../Operaciones/OperacionUnion.h"
#include "../Procesamiento/ProcesadorCadenas.h"
#include "../Procesamiento/ResultadoProcesamiento.h"
#include "../Procesamiento/PasoProcesamiento.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QByteArray>
#include <QScrollBar>
#include <QSizePolicy>

PaginaPruebaCadenas::PaginaPruebaCadenas(RegistroAutomatas* RegistroCompartido, QWidget* parent) : QWidget(parent) {
    Registro = RegistroCompartido;
    Operacion = new OperacionUnion();
    Procesador = new ProcesadorCadenas();
    AutomataUnion = nullptr;

    ResultadoAutomata1 = new ResultadoProcesamiento();
    ResultadoAutomata2 = new ResultadoProcesamiento();
    ResultadoUnion = new ResultadoProcesamiento();

    ConstruirInterfaz();
    AplicarEstilos();
    ActualizarAutomatasGuardados();
}

PaginaPruebaCadenas::~PaginaPruebaCadenas() {
    if (AutomataUnion != nullptr) {
        delete AutomataUnion;
    }
    delete ResultadoAutomata1;
    delete ResultadoAutomata2;
    delete ResultadoUnion;
    delete Procesador;
    delete Operacion;
}

void PaginaPruebaCadenas::ConstruirInterfaz() {
    QVBoxLayout* LayoutPrincipal = new QVBoxLayout(this);
    LayoutPrincipal->setContentsMargins(50, 15, 50, 15);
    LayoutPrincipal->setSpacing(10);

    QLabel* Titulo = new QLabel("PRUEBA DE CADENAS");
    Titulo->setAlignment(Qt::AlignCenter);

    QFont FuenteTitulo;
    FuenteTitulo.setPointSize(27);
    FuenteTitulo.setBold(true);
    Titulo->setFont(FuenteTitulo);

    LayoutPrincipal->addWidget(Titulo);
    LayoutPrincipal->addSpacing(8);

    QHBoxLayout* LayoutAutomatas = new QHBoxLayout();
    LayoutAutomatas->setSpacing(12);

    QLabel* EtiquetaAutomata1 = new QLabel("Automata A:");
    QLabel* EtiquetaAutomata2 = new QLabel("Automata B:");

    ComboAutomata1 = new QComboBox();
    ComboAutomata2 = new QComboBox();
    ComboAutomata1->setFixedHeight(42);
    ComboAutomata2->setFixedHeight(42);

    LayoutAutomatas->addWidget(EtiquetaAutomata1);
    LayoutAutomatas->addWidget(ComboAutomata1, 1);
    LayoutAutomatas->addWidget(EtiquetaAutomata2);
    LayoutAutomatas->addWidget(ComboAutomata2, 1);
    LayoutPrincipal->addLayout(LayoutAutomatas);

    QHBoxLayout* LayoutCadena = new QHBoxLayout();
    LayoutCadena->setSpacing(12);

    QLabel* EtiquetaCadena = new QLabel("Cadena a evaluar:");

    EntradaCadena = new QLineEdit();
    EntradaCadena->setFixedHeight(42);

    QPushButton* BotonProbar = new QPushButton("PROBAR CADENA");
    BotonProbar->setFixedSize(190, 42);

    LayoutCadena->addWidget(EtiquetaCadena);
    LayoutCadena->addWidget(EntradaCadena, 1);
    LayoutCadena->addWidget(BotonProbar);
    LayoutPrincipal->addLayout(LayoutCadena);

    MensajeGeneral = new QLabel();
    MensajeGeneral->setMinimumHeight(28);

    LayoutPrincipal->addWidget(MensajeGeneral);

    QFont FuenteSeccion;
    FuenteSeccion.setPointSize(17);
    FuenteSeccion.setBold(true);

    QHBoxLayout* LayoutIndividuales = new QHBoxLayout();
    LayoutIndividuales->setSpacing(12);

    QVBoxLayout* LayoutAutomata1 = new QVBoxLayout();
    LayoutAutomata1->setSpacing(6);

    QLabel* TituloAutomata1 = new QLabel("AUTOMATA A");
    TituloAutomata1->setFont(FuenteSeccion);

    EtiquetaNombreAutomata1 = new QLabel("Sin selección");
    EtiquetaNombreAutomata1->setWordWrap(true);

    SalidaAutomata1 = new QPlainTextEdit();
    SalidaAutomata1->setReadOnly(true);
    SalidaAutomata1->setFixedHeight(140);
    SalidaAutomata1->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    SalidaAutomata1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SalidaAutomata1->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    LayoutAutomata1->addWidget(TituloAutomata1);
    LayoutAutomata1->addWidget(EtiquetaNombreAutomata1);
    LayoutAutomata1->addWidget(SalidaAutomata1);

    QVBoxLayout* LayoutAutomata2 = new QVBoxLayout();
    LayoutAutomata2->setSpacing(6);

    QLabel* TituloAutomata2 = new QLabel("AUTOMATA B");
    TituloAutomata2->setFont(FuenteSeccion);

    EtiquetaNombreAutomata2 = new QLabel("Sin selección");
    EtiquetaNombreAutomata2->setWordWrap(true);

    SalidaAutomata2 = new QPlainTextEdit();
    SalidaAutomata2->setReadOnly(true);
    SalidaAutomata2->setFixedHeight(140);
    SalidaAutomata2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    SalidaAutomata2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SalidaAutomata2->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    LayoutAutomata2->addWidget(TituloAutomata2);
    LayoutAutomata2->addWidget(EtiquetaNombreAutomata2);
    LayoutAutomata2->addWidget(SalidaAutomata2);
    LayoutIndividuales->addLayout(LayoutAutomata1, 1);
    LayoutIndividuales->addLayout(LayoutAutomata2, 1);
    LayoutPrincipal->addLayout(LayoutIndividuales);
    LayoutPrincipal->addSpacing(8);

    QVBoxLayout* LayoutUnion = new QVBoxLayout();
    LayoutUnion->setSpacing(6);

    QLabel* TituloUnion = new QLabel("AUTOMATA UNIÓN");
    TituloUnion->setFont(FuenteSeccion);

    EtiquetaNombreUnion = new QLabel("Unión no generada");
    EtiquetaNombreUnion->setWordWrap(true);

    SalidaUnion = new QPlainTextEdit();
    SalidaUnion->setReadOnly(true);
    SalidaUnion->setFixedHeight(155);
    SalidaUnion->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    SalidaUnion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SalidaUnion->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    LayoutUnion->addWidget(TituloUnion);
    LayoutUnion->addWidget(EtiquetaNombreUnion);
    LayoutUnion->addWidget(SalidaUnion);
    LayoutPrincipal->addLayout(LayoutUnion);
    LayoutPrincipal->addSpacing(8);

    VeredictoTriple = new QLabel();
    VeredictoTriple->setMinimumHeight(30);
    VeredictoTriple->setAlignment(Qt::AlignCenter);
    VeredictoTriple->setWordWrap(true);

    QFont FuenteVeredicto;
    FuenteVeredicto.setPointSize(15);
    FuenteVeredicto.setBold(true);
    VeredictoTriple->setFont(FuenteVeredicto);

    LayoutPrincipal->addWidget(VeredictoTriple);

    QHBoxLayout* LayoutBotones = new QHBoxLayout();

    QPushButton* BotonVolver = new QPushButton("VOLVER");
    QPushButton* BotonLimpiar = new QPushButton("LIMPIAR");

    BotonVolver->setFixedSize(150, 40);
    BotonLimpiar->setFixedSize(150, 40);

    LayoutBotones->addWidget(BotonVolver);
    LayoutBotones->addStretch();
    LayoutBotones->addWidget(BotonLimpiar);
    LayoutPrincipal->addLayout(LayoutBotones);

    connect(BotonProbar, &QPushButton::clicked, this, &PaginaPruebaCadenas::ProbarCadena);
    connect(BotonLimpiar, &QPushButton::clicked, this, &PaginaPruebaCadenas::LimpiarPagina);
    connect(BotonVolver, &QPushButton::clicked, this, &PaginaPruebaCadenas::SolicitarVolver);
    connect(EntradaCadena, &QLineEdit::returnPressed, this, &PaginaPruebaCadenas::ProbarCadena);
    connect(ComboAutomata1, &QComboBox::currentIndexChanged, this, [this](int) {
        ActualizarEtiquetasAutomatas();
    });
    connect(ComboAutomata2, &QComboBox::currentIndexChanged, this, [this](int) {
        ActualizarEtiquetasAutomatas();
    });
}

void PaginaPruebaCadenas::AplicarEstilos() {
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

        QPlainTextEdit {
            background-color: white;
            color: black;
            border: 1px solid #9CA3AF;
            font-family: "Consolas";
            font-size: 15px;
            padding: 6px;
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

void PaginaPruebaCadenas::ActualizarAutomatasGuardados() {
    LimpiarPagina();

    ComboAutomata1->clear();
    ComboAutomata2->clear();

    if (Registro == nullptr) {
        MensajeGeneral->setText("No se pudo acceder a los automatas guardados.");
        ActualizarEtiquetasAutomatas();
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
        MensajeGeneral->setText("Debe guardar al menos dos automatas validados para probar cadenas.");
        ActualizarEtiquetasAutomatas();
        return;
    }

    ComboAutomata1->setCurrentIndex(0);
    ComboAutomata2->setCurrentIndex(1);

    MensajeGeneral->clear();
    ActualizarEtiquetasAutomatas();
}

void PaginaPruebaCadenas::ActualizarEtiquetasAutomatas() {
    if (ComboAutomata1->count() > 0 && ComboAutomata1->currentIndex() >= 0) {
        EtiquetaNombreAutomata1->setText("Seleccionado: " + ComboAutomata1->currentText());
    } else {
        EtiquetaNombreAutomata1->setText("Sin selección");
    }

    if (ComboAutomata2->count() > 0 && ComboAutomata2->currentIndex() >= 0) {
        EtiquetaNombreAutomata2->setText("Seleccionado: " + ComboAutomata2->currentText());
    } else {
        EtiquetaNombreAutomata2->setText("Sin seleccion");
    }
    EtiquetaNombreUnion->setText("Unión no generada");
}

void PaginaPruebaCadenas::ProbarCadena() {
    LimpiarResultados();

    if (Registro == nullptr || Registro->ObtenerCantidad() < 2) {
        MensajeGeneral->setText("Debe guardar al menos dos automatas validados.");
        return;
    }

    int Posicion1 = ComboAutomata1->currentIndex();
    int Posicion2 = ComboAutomata2->currentIndex();

    if (Posicion1 < 0 || Posicion2 < 0) {
        MensajeGeneral->setText("Debe seleccionar dos automatas.");
        return;
    }

    if (Posicion1 == Posicion2) {
        MensajeGeneral->setText("Debe seleccionar dos automatas diferentes.");
        return;
    }

    Automata* Automata1 = Registro->ObtenerAutomata(Posicion1);
    Automata* Automata2 = Registro->ObtenerAutomata(Posicion2);

    if (Automata1 == nullptr || Automata2 == nullptr) {
        MensajeGeneral->setText("No se pudieron obtener los automatas seleccionados.");
        return;
    }

    CadenaManual MensajeError;

    AutomataUnion = Operacion->Unir(Automata1, Automata2, MensajeError);
    if (AutomataUnion == nullptr) {
        MensajeGeneral->setText(ConvertirAQString(MensajeError));
        return;
    }
    CadenaManual Cadena = ConvertirACadenaManual(EntradaCadena->text());

    bool Correcto1 = Procesador->Procesar(Automata1, Cadena, *ResultadoAutomata1);
    bool Correcto2 = Procesador->Procesar(Automata2, Cadena, *ResultadoAutomata2);
    bool CorrectoUnion = Procesador->Procesar(AutomataUnion, Cadena, *ResultadoUnion);

    QString NombreAutomata1 = ComboAutomata1->currentText();
    QString NombreAutomata2 = ComboAutomata2->currentText();
    QString CadenaEvaluada = EntradaCadena->text();

    if (CadenaEvaluada.isEmpty()) {
        CadenaEvaluada = "ε";
    }

    EtiquetaNombreAutomata1->setText("Seleccionado: " + NombreAutomata1);
    EtiquetaNombreAutomata2->setText("Seleccionado: " + NombreAutomata2);
    EtiquetaNombreUnion->setText("Unión de: " + NombreAutomata1 + " y " + NombreAutomata2);

    MostrarProceso(ResultadoAutomata1, SalidaAutomata1, "AUTOMATA A", NombreAutomata1, CadenaEvaluada);
    MostrarProceso(ResultadoAutomata2, SalidaAutomata2, "AUTOMATA B", NombreAutomata2, CadenaEvaluada);
    MostrarProceso(ResultadoUnion, SalidaUnion, "AUTOMATA UNIÓN", "Unión de " + NombreAutomata1 + " y " + NombreAutomata2, CadenaEvaluada);

    if (!Correcto1 || !Correcto2 || !CorrectoUnion) {
        MensajeGeneral->setText("La cadena no pudo procesarse completamente. Revise los errores mostrados.");
        VeredictoTriple->clear();
        return;
    }

    if (Cadena.EstaVacia()) {
        MensajeGeneral->setText("Cadena vacia ε procesada correctamente.");
    } else {
        MensajeGeneral->setText("Cadena procesada correctamente.");
    }

    QString Veredicto = "VEREDICTO TRIPLE   |   Automata A: ";

    if (ResultadoAutomata1->EsAceptada()) {
        Veredicto += "ACEPTADA";
    } else {
        Veredicto += "RECHAZADA";
    }
    Veredicto += "   |   Automata B: ";

    if (ResultadoAutomata2->EsAceptada()) {
        Veredicto += "ACEPTADA";
    } else {
        Veredicto += "RECHAZADA";
    }
    Veredicto += "   |   Unión: ";

    if (ResultadoUnion->EsAceptada()) {
        Veredicto += "ACEPTADA";
    } else {
        Veredicto += "RECHAZADA";
    }
    VeredictoTriple->setText(Veredicto);
}

void PaginaPruebaCadenas::MostrarProceso(ResultadoProcesamiento* Resultado, QPlainTextEdit* Salida, const QString& Titulo, const QString& NombreAutomata, const QString& CadenaEvaluada) {
    Salida->clear();

    if (Resultado == nullptr) {
        return;
    }

    QString Texto = ConstruirProcesoConDelta(Resultado, Titulo, NombreAutomata, CadenaEvaluada);
    Salida->setPlainText(Texto);
    Salida->verticalScrollBar()->setValue(0);
}

QString PaginaPruebaCadenas::ConstruirProcesoConDelta(ResultadoProcesamiento* Resultado, const QString& Titulo, const QString& NombreAutomata, const QString& CadenaEvaluada) const {
    QString Texto;

    if (Resultado == nullptr) {
        return Texto;
    }

    QString EstadoInicial = ConvertirAQString(Resultado->ObtenerEstadoInicial());

    Texto += "w = ";
    Texto += CadenaEvaluada;
    Texto += "\n\n";

    if (EstadoInicial.isEmpty()) {
        Texto += "No hay estado inicial disponible.";
        return Texto;
    }

    Texto += "δ̂(";
    Texto += EstadoInicial;
    Texto += ", ε) = ";
    Texto += EstadoInicial;
    Texto += "\n\n";

    QString PrefijoAnterior = "ε";
    QString PrefijoActual;

    Nodo<PasoProcesamiento*>* Actual = Resultado->ObtenerPrimerPaso();

    while (Actual != nullptr) {
        PasoProcesamiento* PasoActual = Actual->ObtenerDato();

        if (PasoActual != nullptr) {
            QString Origen = ConvertirAQString(PasoActual->ObtenerEstadoOrigen());
            QString Simbolo = ConvertirAQString(PasoActual->ObtenerSimboloLeido());
            QString Destino = ConvertirAQString(PasoActual->ObtenerEstadoDestino());

            PrefijoActual += Simbolo;

            Texto += "δ̂(";
            Texto += EstadoInicial;
            Texto += ", ";
            Texto += PrefijoActual;
            Texto += ") = δ(δ̂(";
            Texto += EstadoInicial;
            Texto += ", ";
            Texto += PrefijoAnterior;
            Texto += "), ";
            Texto += Simbolo;
            Texto += ")\n";

            Texto += "             = δ(";
            Texto += Origen;
            Texto += ", ";
            Texto += Simbolo;
            Texto += ")\n";
            Texto += "             = ";
            Texto += Destino;
            Texto += "\n\n";

            PrefijoAnterior = PrefijoActual;
        }
        Actual = Actual->ObtenerSiguiente();
    }

    Texto += "Recorrido: ";
    Texto += ConstruirRecorrido(Resultado);
    Texto += "\n";

    if (!Resultado->EsCorrecto()) {
        Texto += "\nError: ";
        Texto += ConvertirAQString(Resultado->ObtenerMensajeError());
        return Texto;
    }

    Texto += "\nEstado alcanzado: ";
    Texto += ConvertirAQString(Resultado->ObtenerEstadoAlcanzado());
    Texto += "\n¿Es estado final?: ";

    if (Resultado->EsAceptada()) {
        Texto += "SI";
    } else {
        Texto += "NO";
    }
    Texto += "\nResultado: ";

    if (Resultado->EsAceptada()) {
        Texto += "ACEPTADA";
    } else {
        Texto += "RECHAZADA";
    }
    return Texto;
}

QString PaginaPruebaCadenas::ConstruirRecorrido(ResultadoProcesamiento* Resultado) const {
    if (Resultado == nullptr) {
        return "";
    }

    QString Texto = ConvertirAQString(Resultado->ObtenerEstadoInicial());
    Nodo<PasoProcesamiento*>* Actual = Resultado->ObtenerPrimerPaso();

    while (Actual != nullptr) {
        PasoProcesamiento* PasoActual = Actual->ObtenerDato();

        if (PasoActual != nullptr) {
            Texto += " -> ";
            Texto += ConvertirAQString(PasoActual->ObtenerEstadoDestino());
        }
        Actual = Actual->ObtenerSiguiente();
    }
    return Texto;
}

void PaginaPruebaCadenas::LimpiarResultados() {
    if (AutomataUnion != nullptr) {
        delete AutomataUnion;
        AutomataUnion = nullptr;
    }

    ResultadoAutomata1->Limpiar();
    ResultadoAutomata2->Limpiar();
    ResultadoUnion->Limpiar();

    SalidaAutomata1->clear();
    SalidaAutomata2->clear();
    SalidaUnion->clear();

    MensajeGeneral->clear();
    VeredictoTriple->clear();

    EtiquetaNombreUnion->setText("Unión no generada");
}

void PaginaPruebaCadenas::LimpiarPagina() {
    EntradaCadena->clear();
    LimpiarResultados();
    ActualizarEtiquetasAutomatas();
}

QString PaginaPruebaCadenas::ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const {
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

CadenaManual PaginaPruebaCadenas::ConvertirACadenaManual(const QString& Texto) const {
    QByteArray Datos = Texto.toUtf8();
    return CadenaManual(Datos.constData());
}

QString PaginaPruebaCadenas::ConvertirAQString(const CadenaManual& Texto) const {
    QByteArray Datos;
    int Posicion = 0;

    while (Posicion < Texto.ObtenerLongitud()) {
        Datos.append(Texto.ObtenerCaracter(Posicion));
        Posicion++;
    }
    return QString::fromUtf8(Datos);
}
