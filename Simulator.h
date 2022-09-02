#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <Pump.h>
#include <PressureSensors.h>
#include <SampleParameters.h>
#include <FluidParameters.h>
#include <QtDebug>

class Simulator : public QObject
{
    Q_PROPERTY(bool simulator_start READ simulator_start WRITE setSimulator_start NOTIFY simulator_startChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_OBJECT
public:
    explicit Simulator(QObject *parent = 0);
    ~Simulator();

    Pump *pump;
    PressureSensors *presure_sensors;
    SampleParameters *sample_parameters;
    FluidParameters *fluid_parameters;

    double calculatePermability(double nu, double flowRate, double length, double dPreassure, double area);

    bool simulator_start() const;
    void setSimulator_start(bool newSimulator_start);

    bool running() const;
    void setRunning(bool newRunning);

public slots:
    void run();


signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run

    void simulator_startChanged();

    void runningChanged();

    void signal_CurrentPreassure(double current_preasure);
    void signal_CurrentFlowRate(double current_flowRate);
    void signal_CurrentD1minD2(double current_D1minD2);
    void signal_Permability(double permability);


private:
    double koeff_si = 60000;//1.666666666666666666666;
    bool m_simulator_start = false;
    bool m_running;
};

#endif // SIMULATOR_H
