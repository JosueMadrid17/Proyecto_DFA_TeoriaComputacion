#include "VentanaPrincipal.h"
#include "PaginaCrearAutomata.h"
#include "PaginaUnionAutomatas.h"
#include "../Automatas/RegistroAutomatas.h"
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QCursor>

VentanaPrincipal::VentanaPrincipal(QWidget* parent) : QMainWindow(parent) {
    Registro = new RegistroAutomatas();
    ConstruirInterfaz();
}

VentanaPrincipal::~VentanaPrincipal() {
    delete Registro;
}

void VentanaPrincipal::ConstruirInterfaz() {
    setWindowTitle("Sistema de Autómatas Finitos Deterministas");

    Paginas = new QStackedWidget(this);
    setCentralWidget(Paginas);

    AplicarEstilos();

    PaginaCreacion = new PaginaCrearAutomata(Registro);
    PaginaUnion = new PaginaUnionAutomatas(Registro);

    ConstruirPaginaInicio();

    Paginas->addWidget(PaginaCreacion);
    Paginas->addWidget(PaginaUnion);
    Paginas->setCurrentWidget(PaginaInicio);

    connect(PaginaCreacion, &PaginaCrearAutomata::SolicitarVolver, this, [this]() {
        Paginas->setCurrentWidget(PaginaInicio);
    });
    connect(PaginaUnion, &PaginaUnionAutomatas::SolicitarVolver, this, [this]() {
        Paginas->setCurrentWidget(PaginaInicio);
    });
}

void VentanaPrincipal::AplicarEstilos() {
    setStyleSheet(R"(
        QMainWindow {
            background-color: white;
        }

        QWidget {
            background-color: white;
            color: black;
            font-family: "Segoe UI";
        }

        QLabel {
            background-color: transparent;
            border: none;
            color: black;
        }

        QPushButton {
            background-color: #2563EB;
            color: white;
            border: none;
            font-size: 18px;
            font-weight: bold;
        }
    )");
}

void VentanaPrincipal::ConstruirPaginaInicio() {
    PaginaInicio = new QWidget();

    QVBoxLayout* LayoutPrincipal = new QVBoxLayout(PaginaInicio);
    LayoutPrincipal->setContentsMargins(200, 70, 200, 70);
    LayoutPrincipal->setAlignment(Qt::AlignCenter);

    QLabel* Titulo = new QLabel("SISTEMA DE AUTÓMATAS FINITOS DETERMINISTAS");
    Titulo->setAlignment(Qt::AlignCenter);

    QFont FuenteTitulo;
    FuenteTitulo.setPointSize(30);
    FuenteTitulo.setBold(true);
    Titulo->setFont(FuenteTitulo);

    QLabel* Subtitulo = new QLabel("TEORÍA DE LA COMPUTACIÓN");
    Subtitulo->setAlignment(Qt::AlignCenter);

    QFont FuenteSubtitulo;
    FuenteSubtitulo.setPointSize(17);
    FuenteSubtitulo.setBold(true);
    Subtitulo->setFont(FuenteSubtitulo);

    QPushButton* BotonCrearAutomata = new QPushButton("CREAR Y VALIDAR AUTÓMATA");
    connect(BotonCrearAutomata, &QPushButton::clicked, this, [this]() {
        Paginas->setCurrentWidget(PaginaCreacion);
    });
    QPushButton* BotonUnion = new QPushButton("UNIÓN DE AUTÓMATAS");
    connect(BotonUnion, &QPushButton::clicked, this, [this]() {
        PaginaUnion->ActualizarAutomatasGuardados();
        Paginas->setCurrentWidget(PaginaUnion);
    });
    QPushButton* BotonPruebaCadenas = new QPushButton("PRUEBA DE CADENAS");

    BotonCrearAutomata->setFixedSize(540, 72);
    BotonUnion->setFixedSize(540, 72);
    BotonPruebaCadenas->setFixedSize(540, 72);
    BotonCrearAutomata->setCursor(Qt::PointingHandCursor);
    BotonUnion->setCursor(Qt::PointingHandCursor);
    BotonPruebaCadenas->setCursor(Qt::PointingHandCursor);

    LayoutPrincipal->addStretch();
    LayoutPrincipal->addWidget(Titulo, 0, Qt::AlignHCenter);
    LayoutPrincipal->addSpacing(8);
    LayoutPrincipal->addWidget(Subtitulo, 0, Qt::AlignHCenter);
    LayoutPrincipal->addSpacing(45);
    LayoutPrincipal->addWidget(BotonCrearAutomata, 0, Qt::AlignHCenter);
    LayoutPrincipal->addSpacing(12);
    LayoutPrincipal->addWidget(BotonUnion, 0, Qt::AlignHCenter);
    LayoutPrincipal->addSpacing(12);
    LayoutPrincipal->addWidget(BotonPruebaCadenas, 0, Qt::AlignHCenter);
    LayoutPrincipal->addStretch();

    Paginas->addWidget(PaginaInicio);
}
