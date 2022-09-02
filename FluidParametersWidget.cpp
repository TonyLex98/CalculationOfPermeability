#include "FluidParametersWidget.h"
#include "ui_FluidParametersWidget.h"

FluidParametersWidget::FluidParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FluidParametersWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SubWindow);
}

FluidParametersWidget::~FluidParametersWidget()
{
    delete ui;
}

void FluidParametersWidget::on_pushButton_close_clicked()
{
    emit signal_FluidParametersWidgetClose();
    this->close();
}

void FluidParametersWidget::on_comboBox_fluids_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox_fluids->currentIndex()!=-1){
        ui->lineEdit_fluid->setText(QString::number(fluids.at(ui->comboBox_fluids->currentIndex()).second));
    }
}

void FluidParametersWidget::slot_NuWasChanged(double nu)
{
    ui->lineEdit_fluid->setText(QString::number(nu));
    qDebug()<<"slot_NuWasChanged" << fluids;
    fluids[ui->comboBox_fluids->currentIndex()].second = nu;
}

void FluidParametersWidget::slot_setFluids(QList<QPair<QString, double> > fluids_l)
{
    fluids = fluids_l;

    ui->comboBox_fluids->clear();

    for(auto fluid: fluids){
        ui->comboBox_fluids->addItem(fluid.first);
    }
    qDebug()<<"FluidParametersWidget:"<< fluids;
    ui->lineEdit_fluid->setText(QString::number(fluids_l.at(ui->comboBox_fluids->currentIndex()).second));
}


void FluidParametersWidget::on_lineEdit_fluid_returnPressed()
{
    on_pushButton_change_nu_clicked();
}


void FluidParametersWidget::on_pushButton_change_nu_clicked()
{
    emit signal_changeNu(fluids.at(ui->comboBox_fluids->currentIndex()).first,ui->lineEdit_fluid->text().toDouble());
}

