#ifndef FLUIDPARAMETERS_H
#define FLUIDPARAMETERS_H

#include <QObject>
#include <QList>
#include <QPair>

class FluidParameters: public QObject
{
    Q_OBJECT
public:
    explicit FluidParameters(QObject *parent = 0);
    double getCurrentNu();

public slots:
    void slot_changeNu(QString fluid, double nu);
    void setCurrentNu(QString fluid_name);
    void slot_sendSignal_fluids();

signals:
    void signal_fluids(QList<QPair<QString, double>> fluids);
    void signal_currentNuWasChanged(double nu);
    void signal_NuWasChanged(double nu);

private:
    double current_nu = 15;
    QList<QPair<QString, double>> fluids;

};

#endif // FLUIDPARAMETERS_H
