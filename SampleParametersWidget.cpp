#include "SampleParametersWidget.h"
#include "ui_SampleParametersWidget.h"

SampleParametersWidget::SampleParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SampleParametersWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SubWindow);
}

SampleParametersWidget::~SampleParametersWidget()
{
    delete ui;
}

void SampleParametersWidget::on_lineEdit_length_returnPressed()
{
    emit signal_changeSampleLength(ui->lineEdit_length->text().toDouble());
}


void SampleParametersWidget::on_lineEdit_diameter_returnPressed()
{
    emit signal_changeSampleDiameter(ui->lineEdit_diameter->text().toDouble());
}


void SampleParametersWidget::on_pushButton_close_clicked()
{
    this->close();
}

