#ifndef PRESSURESENSORS_H
#define PRESSURESENSORS_H

#include <QObject>
#include <QRandomGenerator>

class PressureSensors : public QObject
{
public:
    explicit PressureSensors(QObject *parent = 0);

    double getCurrent_D1minD2_pressure();

    double getCurrent_D1_pressure();
    double getCurrent_D2_pressure();

public slots:
    void setSet_value_D1_pressure(double set_value_D1_pressure_l);
    void setSet_value_D2_pressure(double set_value_D2_pressure_l);

private:
    double set_value_D1_pressure = 0;
    double set_value_D2_pressure = 0;

    double current_D1_pressure = 0;
    double current_D2_pressure = 0;
    double current_D1minD2_pressure = 0;

    QRandomGenerator r_generator;
    double dif_rand_pressure = 10000;

public slots:
    //void run(); // метод, в котором будет выполняться расчет разности давления на датчиках

};

#endif // PRESSURESENSORS_H
