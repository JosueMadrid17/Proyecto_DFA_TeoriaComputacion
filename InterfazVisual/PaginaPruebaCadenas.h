#ifndef PAGINAPRUEBACADENAS_H
#define PAGINAPRUEBACADENAS_H
#include <QWidget>
#include <QString>
#include "../Estructuras/CadenaManual.h"

class QComboBox;
class QLineEdit;
class QPlainTextEdit;
class QLabel;
class RegistroAutomatas;
class OperacionUnion;
class ProcesadorCadenas;
class ResultadoProcesamiento;
class Automata;

class PaginaPruebaCadenas : public QWidget {
    Q_OBJECT

private:
    RegistroAutomatas* Registro;
    OperacionUnion* Operacion;
    ProcesadorCadenas* Procesador;

    Automata* AutomataUnion;
    ResultadoProcesamiento* ResultadoAutomata1;
    ResultadoProcesamiento* ResultadoAutomata2;
    ResultadoProcesamiento* ResultadoUnion;

    QComboBox* ComboAutomata1;
    QComboBox* ComboAutomata2;
    QLineEdit* EntradaCadena;

    QPlainTextEdit* SalidaAutomata1;
    QPlainTextEdit* SalidaAutomata2;
    QPlainTextEdit* SalidaUnion;

    QLabel* MensajeGeneral;
    QLabel* VeredictoTriple;
    QLabel* EtiquetaNombreAutomata1;
    QLabel* EtiquetaNombreAutomata2;
    QLabel* EtiquetaNombreUnion;

    void ConstruirInterfaz();
    void AplicarEstilos();
    void ProbarCadena();
    void LimpiarResultados();
    void LimpiarPagina();
    void ActualizarEtiquetasAutomatas();
    void MostrarProceso(ResultadoProcesamiento* Resultado, QPlainTextEdit* Salida, const QString& Titulo, const QString& NombreAutomata, const QString& CadenaEvaluada);

    QString ConstruirProcesoConDelta(ResultadoProcesamiento* Resultado, const QString& Titulo, const QString& NombreAutomata, const QString& CadenaEvaluada) const;
    QString ConstruirRecorrido(ResultadoProcesamiento* Resultado) const;
    QString ConstruirNombreAutomata(Automata* AutomataGuardado, int Numero) const;

    CadenaManual ConvertirACadenaManual(const QString& Texto) const;
    QString ConvertirAQString(const CadenaManual& Texto) const;

signals:
    void SolicitarVolver();

public:
    PaginaPruebaCadenas(RegistroAutomatas* RegistroCompartido, QWidget* parent = nullptr);
    ~PaginaPruebaCadenas();

    void ActualizarAutomatasGuardados();
};

#endif
