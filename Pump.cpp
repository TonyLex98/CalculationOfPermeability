#include "Pump.h"

Pump::Pump(QObject *parent) :
    QObject(parent)
{
    StopPump();
}

void Pump::StopPump()
{
    pressure_mode = false;
    flowRate_mode = false;
    stop_mode = true;

    emit signal_PumpMode(pressure_mode,flowRate_mode, stop_mode);

}

void Pump::SwitchPressure_mode()
{
    pressure_mode = true;
    flowRate_mode = false;
    stop_mode = false;

    emit signal_PumpMode(pressure_mode,flowRate_mode, stop_mode);
}

void Pump::SwitchFlowRate_mode()
{
    pressure_mode = false;
    flowRate_mode = true;
    stop_mode = false;

    emit signal_PumpMode(pressure_mode,flowRate_mode, stop_mode);
}

bool Pump::getPressure_mode()
{
    return pressure_mode;
}

bool Pump::getFlowRate_mode()
{
    return flowRate_mode;
}

bool Pump::getStop_mode()
{
    return stop_mode;
}

double Pump::GetCurrent_pressure()
{
    current_pressure = set_value_pressure + r_generator.generateDouble()/dif_rand_pressure;
    return current_pressure;
}

double Pump::GetCurrent_flowRate()
{
    current_flowRate = set_value_flowRate + r_generator.generateDouble()/dif_rand_flowRate;
    return current_flowRate;
}

double Pump::GetSet_value_pressure()
{
    return set_value_pressure;
}

void Pump::SetSet_value_pressure(double set_value_pressure_l)
{
    set_value_pressure = set_value_pressure_l;
}

double Pump::GetSet_value_flowRate()
{
    return set_value_flowRate;
}

void Pump::SetSet_value_flowRate(double set_value_flowRate_l)
{
    set_value_flowRate = set_value_flowRate_l;
}
