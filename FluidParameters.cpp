#include "FluidParameters.h"

FluidParameters::FluidParameters(QObject *parent) :
    QObject(parent)
{
    QPair<QString, double> fluid_1;
    fluid_1.first = "Нефть";
    fluid_1.second = 15;

    QPair<QString, double> fluid_2;
    fluid_2.first = "Вода";
    fluid_2.second = 10;

    fluids.push_back(fluid_1);
    fluids.push_back(fluid_2);

}

void FluidParameters::setCurrentNu(QString fluid_name)
{
    for(int i = 0; i<fluids.size();i++){
        if(fluids[i].first == fluid_name){
            current_nu = fluids[i].second;

            emit signal_currentNuWasChanged(current_nu);
            return;
        }
    }
}

double FluidParameters::getCurrentNu()
{
    return current_nu;
}

void FluidParameters::slot_sendSignal_fluids()
{
    emit signal_fluids(fluids);
}

void FluidParameters::slot_changeNu(QString fluid_name, double nu_l)
{
    for(int i = 0; i<fluids.size();i++){
        if(fluids[i].first == fluid_name){
            fluids[i].second = nu_l;
            current_nu = fluids[i].second;

            emit signal_NuWasChanged(current_nu);
            //sendSignal_fluids();
            return;
        }
    }
}
