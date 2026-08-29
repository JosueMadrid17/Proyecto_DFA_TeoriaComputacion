#ifndef PAGINAUNIONAUTOMATAS_H
#define PAGINAUNIONAUTOMATAS_H
#include <QWidget>
#include <QString>

class QComboBox;
class QTableWidget;
class QPlainTextEdit;
class QLabel;
class VistaAutomata;
class RegistroAutomatas;
class OperacionUnion;
class Automata;
class Estado;
class CadenaManual;

class PaginaUnionAutomatas : public QWidget {
    Q_OBJECT

private:
    RegistroAutomatas* Registro;
    OperacionUnion* Operacion;
    Automata* AutomataResultado;

    QComboBox* ComboAutomata1;
    QComboBox* ComboAutomata2;

    QTableWidget* TablaResultado;
    QPlainTextEdit* ResumenResultado;
    QLabel* MensajeResultado;
    VistaAutomata* Vista;

    void ConstruirInterfaz();
    void AplicarEstilos();
    void RealizarUnion();
    void LimpiarResultado();
    void MostrarTabla();
    void MostrarResumen();

    QString ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const;
    QString FormatearEstado(Estado* EstadoActual) const;
    QString ConvertirAQString(const CadenaManual& Texto) const;

signals:
    void SolicitarVolver();

public:
    PaginaUnionAutomatas(RegistroAutomatas* RegistroCompartido, QWidget* parent = nullptr);
    ~PaginaUnionAutomatas();

    void ActualizarAutomatasGuardados();
};

#endif
