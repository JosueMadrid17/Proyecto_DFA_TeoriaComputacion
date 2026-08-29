#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H
#include <QMainWindow>

class QWidget;
class QStackedWidget;
class PaginaCrearAutomata;
class RegistroAutomatas;

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* Paginas;
    QWidget* PaginaInicio;
    PaginaCrearAutomata* PaginaCreacion;
    RegistroAutomatas* Registro;

    void ConstruirInterfaz();
    void ConstruirPaginaInicio();
    void AplicarEstilos();

public:
    VentanaPrincipal(QWidget* parent = nullptr);
    ~VentanaPrincipal();
};

#endif
