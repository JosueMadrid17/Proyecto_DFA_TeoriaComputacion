#ifndef PAGINACREARAUTOMATA_H
#define PAGINACREARAUTOMATA_H
#include <QWidget>

class QLineEdit;
class QComboBox;
class QLabel;
class QTableWidget;
class QPlainTextEdit;
class QString;
class Automata;
class ValidadorDFA;
class ResultadoValidacion;
class CadenaManual;
class VistaAutomata;

class PaginaCrearAutomata : public QWidget {
    Q_OBJECT

private:
    Automata* AutomataActual;
    ValidadorDFA* Validador;
    ResultadoValidacion* Resultado;
    VistaAutomata* Vista;

    QLineEdit* EntradaEstado;
    QLineEdit* EntradaSimbolo;

    QComboBox* ComboEstadoInicial;
    QComboBox* ComboEstadoFinal;
    QComboBox* ComboOrigen;
    QComboBox* ComboSimbolo;
    QComboBox* ComboDestino;

    QLabel* EtiquetaEstadosFinales;

    QTableWidget* TablaTransiciones;
    QPlainTextEdit* SalidaValidacion;

    void ConstruirInterfaz();
    void AplicarEstilos();
    void AgregarEstado();
    void AgregarSimbolo();
    void AgregarEstadoFinal();
    void AgregarTransicion();
    void ValidarAutomata();
    void LimpiarAutomata();
    void ActualizarEstadosFinales();

    CadenaManual ConvertirACadenaManual(const QString& Texto) const;
    QString ConvertirAQString(const CadenaManual& Texto) const;

signals:
    void SolicitarVolver();

public:
    PaginaCrearAutomata(QWidget* parent = nullptr);
    ~PaginaCrearAutomata();
};

#endif
