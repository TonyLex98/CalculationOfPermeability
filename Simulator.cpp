#include "Simulator.h"

Simulator::Simulator(QObject *parent) :
    QObject(parent)
{
    pump = new Pump();
    presure_sensors = new PressureSensors();
    sample_parameters = new SampleParameters();
    fluid_parameters = new FluidParameters();
}

Simulator::~Simulator()
{
    delete pump;
    delete presure_sensors;
    delete sample_parameters;
    delete fluid_parameters;
}

void Simulator::run()
{
    while (m_running)
    {
        if(m_simulator_start){

            m_simulator_start = false;
            qDebug()<<"Симулятор запущен";

            double current_preasure = 0;
            double current_flowRate = 0;
            double D1minD2_pressure = 0;

            current_preasure = pump->GetCurrent_pressure();

            if(pump->getFlowRate_mode()){
                current_flowRate = pump->GetSet_value_flowRate();
            }
            if(pump->getPressure_mode()){
                current_flowRate = pump->GetCurrent_flowRate();
            }
            if(pump->getStop_mode()){
                current_flowRate = 0;
            }

            D1minD2_pressure = presure_sensors->getCurrent_D1minD2_pressure();

            double nu = fluid_parameters->getCurrentNu();

            double length = sample_parameters->getLength();

            double area = sample_parameters->GetArea();

            double permability = calculatePermability(nu, current_flowRate, length, D1minD2_pressure, area);

            emit signal_CurrentPreassure(current_preasure);
            emit signal_CurrentFlowRate(current_flowRate);
            emit signal_CurrentD1minD2(D1minD2_pressure);
            emit signal_Permability(permability);

            qDebug()<<"current_preasure: " <<current_preasure;
            qDebug()<<"current_flowRate: " <<current_flowRate;
            qDebug()<<"nu: " <<nu;
            qDebug()<<"length: " <<length;
            qDebug()<<"D1minD2_pressure: " <<D1minD2_pressure;
            qDebug()<<"area: " <<area;
            qDebug()<<"Проницаемость: " << permability;
        }
    }

    emit finished();
}

double Simulator::calculatePermability(double nu, double flowRate, double length, double dPreassure, double area)
{
    return koeff_si*nu*flowRate*length/dPreassure/area;
}

bool Simulator::simulator_start() const
{
    return m_simulator_start;
}

void Simulator::setSimulator_start(bool newSimulator_start)
{
    if (m_simulator_start == newSimulator_start)
        return;
    m_simulator_start = newSimulator_start;
    emit simulator_startChanged();
}

bool Simulator::running() const
{
    return m_running;
}

void Simulator::setRunning(bool newRunning)
{
    if (m_running == newRunning)
        return;
    m_running = newRunning;
    emit runningChanged();
}
