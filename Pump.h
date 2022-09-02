#ifndef PUMP_H
#define PUMP_H

#include <QObject>
#include <QPair>
#include <QList>
#include <QRandomGenerator>

class Pump : public QObject
{
    Q_OBJECT
public:
    explicit Pump(QObject *parent = 0);

    bool getPressure_mode();
    bool getFlowRate_mode();
    bool getStop_mode();

    double GetCurrent_pressure();
    double GetCurrent_flowRate();

    double GetSet_value_pressure();

    double GetSet_value_flowRate();


signals:
    void nameChanged();
    void current_flowRateChanged();
    void current_pressureChanged();
    void signal_PumpMode(bool pressure_mode, bool flowRate_mode, bool stop_mode);

public slots:
    void StopPump();
    void SwitchPressure_mode();
    void SwitchFlowRate_mode();

    void SetSet_value_pressure(double set_value_pressure_l);
    void SetSet_value_flowRate(double set_value_flowRate_l);

private:
    double current_pressure = 0;
    double current_flowRate = 0;

    bool pressure_mode = false;
    bool flowRate_mode = false;
    bool stop_mode = false;

    double set_value_pressure;
    double set_value_flowRate;

    QRandomGenerator r_generator;
    double dif_rand_pressure = 100;
    double dif_rand_flowRate = 100;


};

#endif // PUMP_H
