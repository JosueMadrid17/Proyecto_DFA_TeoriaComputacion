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
class RegistroAutomatas;

class PaginaCrearAutomata : public QWidget {
    Q_OBJECT

private:
    Automata* AutomataActual;
    ValidadorDFA* Validador;
    ResultadoValidacion* Resultado;
    VistaAutomata* Vista;
    RegistroAutomatas* Registro;

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
    void GuardarAutomata();

    CadenaManual ConvertirACadenaManual(const QString& Texto) const;
    QString ConvertirAQString(const CadenaManual& Texto) const;
    QString ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const;

signals:
    void SolicitarVolver();

public:
    PaginaCrearAutomata(RegistroAutomatas* RegistroCompartido, QWidget* parent = nullptr);
    ~PaginaCrearAutomata();
};

#endif
