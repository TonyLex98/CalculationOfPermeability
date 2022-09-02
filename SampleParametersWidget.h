#ifndef SAMPLEPARAMETERSWIDGET_H
#define SAMPLEPARAMETERSWIDGET_H

#include <QWidget>

namespace Ui {
class SampleParametersWidget;
}

class SampleParametersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SampleParametersWidget(QWidget *parent = nullptr);
    ~SampleParametersWidget();

private slots:
    void on_lineEdit_length_returnPressed();

    void on_lineEdit_diameter_returnPressed();

    void on_pushButton_close_clicked();

signals:
    void signal_changeSampleLength(double length);
    void signal_changeSampleDiameter(double diameter);

private:
    Ui::SampleParametersWidget *ui;
};

#endif // SAMPLEPARAMETERSWIDGET_H
