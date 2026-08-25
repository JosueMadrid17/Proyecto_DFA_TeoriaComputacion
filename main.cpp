#include "VentanaPrincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Aplicacion(argc, argv);
    VentanaPrincipal Ventana;
    Ventana.showMaximized();
    return Aplicacion.exec();
}
