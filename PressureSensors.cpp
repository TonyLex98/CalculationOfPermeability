#include "PressureSensors.h"

PressureSensors::PressureSensors(QObject *parent) :
    QObject(parent)
{

}

double PressureSensors::getCurrent_D1minD2_pressure()
{
    return getCurrent_D1_pressure() - getCurrent_D2_pressure();
}

double PressureSensors::getCurrent_D1_pressure()
{
    current_D1_pressure = set_value_D1_pressure + r_generator.generateDouble()/dif_rand_pressure;
    return current_D1_pressure;
}

double PressureSensors::getCurrent_D2_pressure()
{
    current_D2_pressure = set_value_D2_pressure + r_generator.generateDouble()/dif_rand_pressure;
    return current_D2_pressure;
}

void PressureSensors::setSet_value_D1_pressure(double set_value_D1_pressure_l)
{
    set_value_D1_pressure = set_value_D1_pressure_l;
}

void PressureSensors::setSet_value_D2_pressure(double set_value_D2_pressure_l)
{
    set_value_D2_pressure = set_value_D2_pressure_l;
}


