#include "SampleParameters.h"

SampleParameters::SampleParameters(QObject *parent) :
    QObject(parent)
{

}

double SampleParameters::GetArea()
{
    area = M_PI*pow(diameter,2)/4;
    return area;
}

void SampleParameters::setLength(double length_l)
{
    length = length_l;
    emit signal_SampleLengthWasChandged(length);
}

double SampleParameters::getLength()
{
    return length;
}

void SampleParameters::setDiameter(double diameter_l)
{
    diameter = diameter_l;
    emit signal_SampleDiameterWasChandged(diameter);
}
