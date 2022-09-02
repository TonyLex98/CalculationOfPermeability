#ifndef SAMPLEPARAMETERS_H
#define SAMPLEPARAMETERS_H

#include <QObject>
#include <QtMath>

class SampleParameters: public QObject
{
    Q_OBJECT
public:
    explicit SampleParameters(QObject *parent = 0);

    double GetArea();

    double getLength();

signals:
    void signal_SampleLengthWasChandged(double length);
    void signal_SampleDiameterWasChandged(double diameter);

public slots:
    void setLength(double length_l);
    void setDiameter(double diameter_l);

private:
    double length = 60;
    double diameter = 29.95;
    double area = 0;

};

#endif // SAMPLEPARAMETERS_H
