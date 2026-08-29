#ifndef VISTAAUTOMATA_H
#define VISTAAUTOMATA_H
#include <QWidget>
#include <QString>

class QLabel;
class Automata;
class Estado;
class CadenaManual;

class VistaAutomata : public QWidget {
    Q_OBJECT

private:
    Automata* AutomataVisualizado;
    QLabel* AreaTexto;

    void ActualizarVista();
    void AjustarTamano();

    QString ConstruirDiagrama() const;
    QString FormatearEstado(Estado* EstadoActual) const;
    QString ConvertirAQString(const CadenaManual& Texto) const;

public:
    VistaAutomata(QWidget* parent = nullptr);

    void EstablecerAutomata(Automata* NuevoAutomata);
    void Refrescar();
};

#endif
