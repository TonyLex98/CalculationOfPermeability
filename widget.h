#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <SampleParametersWidget.h>
#include <Simulator.h>
#include <QTimer>
#include <QThread>
#include <FluidParametersWidget.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void signal_changeFluid(QString fluid);
    void signal_setSet_value_D1_pressure(double D1);
    void signal_setSet_value_D2_pressure(double D2);

    void signal_StopPump();
    void signal_SwitchPressure_mode();
    void signal_SwitchFlowRate_mode();

    void signal_SetSet_value_pressure(double set_value_pressure_l);
    void signal_SetSet_value_flowRate(double set_value_flowRate_l);

    void signal_sendSignal_fluids();


public slots:
    void slot_setFluids(QList<QPair<QString, double>> fluids);
    void slot_currentNuWasChanged(double current_nu);

    void slot_SampleLengthWasChandged(double length);
    void slot_SampleDiameterWasChandged(double diameter);

    void slot_CurrentPreassure(double current_preasure);
    void slot_CurrentFlowRate(double current_flowRate);
    void slot_CurrentD1minD2(double D1minD2_pressure);
    void slot_Permability(double permability);
    void slot_PumpMode(bool pressure_mode, bool flowRate_mode, bool stop_mode);

private slots:
    void on_pushButton_changeSampleParameters_clicked();

    void on_pushButton_pressure_clicked();

    void on_pushButton_flowRate_clicked();

    void on_lineEdit_Period_returnPressed();

    void on_lineEdit_set_value_pressure_returnPressed();

    void on_lineEdit_set_value_flowRate_returnPressed();

    void slot_StartSimulation();

    void on_pushButton_changeFluid_clicked();

    void on_pushButton_D1_zero_clicked();

    void on_pushButton_D2_zero_clicked();

    void on_comboBox_fiuid_currentTextChanged(const QString &arg1);

    void on_lineEdit_D1_returnPressed();

    void on_lineEdit_D2_returnPressed();

private:
    void cofigIconOnButtons();

    Ui::Widget *ui;
    Simulator *simulator;
    QThread *thread_simulator;


    SampleParametersWidget *spw;

    QTimer *timer_period;

    FluidParametersWidget *fluid_param_widg;

    QList<QPair<QString, double>> fluids;

    bool pressure_mode = false;
    bool flowRate_mode = false;
    bool stop_mode = true;


};
#endif // WIDGET_H
