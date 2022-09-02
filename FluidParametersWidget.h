#ifndef FLUIDPARAMETERSWIDGET_H
#define FLUIDPARAMETERSWIDGET_H

#include <QWidget>
#include <FluidParameters.h>
#include <QDebug>

namespace Ui {
class FluidParametersWidget;
}

class FluidParametersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FluidParametersWidget(QWidget *parent = nullptr);
    ~FluidParametersWidget();

public slots:
    void slot_setFluids(QList<QPair<QString, double>> fluids);
    void slot_NuWasChanged(double nu);

private slots:
    void on_pushButton_close_clicked();

    void on_comboBox_fluids_currentTextChanged(const QString &arg1);

    void on_lineEdit_fluid_returnPressed();

    void on_pushButton_change_nu_clicked();

signals:
    void signal_changeNu(QString fluid, double nu);
    void signal_FluidParametersWidgetClose();

private:
    Ui::FluidParametersWidget *ui;
    QList<QPair<QString, double>> fluids;
};

#endif // FLUIDPARAMETERSWIDGET_H
