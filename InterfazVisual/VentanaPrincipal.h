#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H
#include <QMainWindow>

class QWidget;
class QStackedWidget;

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* Paginas;
    QWidget* PaginaInicio;

    void ConstruirInterfaz();
    void ConstruirPaginaInicio();
    void AplicarEstilos();

public:
    VentanaPrincipal(QWidget* parent = nullptr);
    ~VentanaPrincipal();
};

#endif
