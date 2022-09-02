#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    spw = new SampleParametersWidget();
    simulator = new Simulator();
    thread_simulator = new QThread();
    fluid_param_widg = new FluidParametersWidget();

    timer_period = new QTimer();
    //Подключение таймера к слоту, который запускает поток симуляции
    connect(timer_period, &QTimer::timeout, this, &Widget::slot_StartSimulation);

    // Запуск выполнения метода run будет осуществляться по сигналу запуска от соответствующего потока
    connect(thread_simulator, &QThread::started, simulator, &Simulator::run);

    // Остановка потока будет выполняться по сигналу finished от соответствующего объекта в потоке
    connect(simulator, &Simulator::finished, thread_simulator, &QThread::terminate);

    //Подключаем сигналы и слоты для взаимодействия интерфейса с параметрами образца в породе
    connect(spw, &SampleParametersWidget::signal_changeSampleLength, simulator->sample_parameters,&SampleParameters::setLength, Qt::QueuedConnection);
    connect(spw, &SampleParametersWidget::signal_changeSampleDiameter, simulator->sample_parameters,&SampleParameters::setDiameter, Qt::QueuedConnection);
    connect(simulator->sample_parameters,&SampleParameters::signal_SampleLengthWasChandged, this, &Widget::slot_SampleLengthWasChandged, Qt::QueuedConnection);
    connect(simulator->sample_parameters,&SampleParameters::signal_SampleDiameterWasChandged, this, &Widget::slot_SampleDiameterWasChandged, Qt::QueuedConnection);

    connect(simulator->fluid_parameters, &FluidParameters::signal_fluids, fluid_param_widg,&FluidParametersWidget::slot_setFluids, Qt::QueuedConnection);
    connect(simulator->fluid_parameters, &FluidParameters::signal_fluids, this ,&Widget::slot_setFluids, Qt::QueuedConnection);
    connect(this,&Widget::signal_changeFluid,simulator->fluid_parameters, &FluidParameters::setCurrentNu, Qt::QueuedConnection);
    connect(simulator->fluid_parameters, &FluidParameters::signal_currentNuWasChanged, this ,&Widget::slot_currentNuWasChanged, Qt::QueuedConnection);
    connect(fluid_param_widg,&FluidParametersWidget::signal_changeNu,simulator->fluid_parameters, &FluidParameters::slot_changeNu, Qt::QueuedConnection);
    connect(fluid_param_widg, &FluidParametersWidget::signal_FluidParametersWidgetClose, simulator->fluid_parameters, &FluidParameters::slot_sendSignal_fluids, Qt::QueuedConnection);
    connect(this, &Widget::signal_sendSignal_fluids, simulator->fluid_parameters, &FluidParameters::slot_sendSignal_fluids, Qt::QueuedConnection);
    connect(simulator->fluid_parameters, &FluidParameters::signal_NuWasChanged, fluid_param_widg,&FluidParametersWidget::slot_NuWasChanged, Qt::QueuedConnection);

    connect(simulator,&Simulator::signal_CurrentPreassure, this, &Widget::slot_CurrentPreassure, Qt::QueuedConnection);
    connect(simulator,&Simulator::signal_CurrentFlowRate, this, &Widget::slot_CurrentFlowRate, Qt::QueuedConnection);
    connect(simulator,&Simulator::signal_CurrentD1minD2, this, &Widget::slot_CurrentD1minD2, Qt::QueuedConnection);
    connect(simulator,&Simulator::signal_Permability, this, &Widget::slot_Permability, Qt::QueuedConnection);

    connect(this, &Widget::signal_setSet_value_D1_pressure, simulator->presure_sensors, &PressureSensors::setSet_value_D1_pressure, Qt::QueuedConnection);
    connect(this, &Widget::signal_setSet_value_D2_pressure, simulator->presure_sensors, &PressureSensors::setSet_value_D2_pressure, Qt::QueuedConnection);

    connect(this, &Widget::signal_StopPump, simulator->pump, &Pump::StopPump, Qt::QueuedConnection);
    connect(this, &Widget::signal_SwitchFlowRate_mode, simulator->pump, &Pump::SwitchFlowRate_mode, Qt::QueuedConnection);
    connect(this, &Widget::signal_SwitchPressure_mode, simulator->pump, &Pump::SwitchPressure_mode, Qt::QueuedConnection);

    connect(this, &Widget::signal_SetSet_value_flowRate, simulator->pump, &Pump::SetSet_value_flowRate, Qt::QueuedConnection);
    connect(this, &Widget::signal_SetSet_value_pressure, simulator->pump, &Pump::SetSet_value_pressure, Qt::QueuedConnection);

    connect(simulator->pump, &Pump::signal_PumpMode, this, &Widget::slot_PumpMode, Qt::QueuedConnection);


    simulator->moveToThread(thread_simulator);    // Передаём объекты в соответствующие потоки

    //Устанавливаю изображение схемы установки:
    QPixmap pix;
    if(!pix.load(":/images/scheme.png")){
        qDebug()<<"Failed to load image";
    }
    ui->label_image->setPixmap(pix);

    //Устанавливаю картинки кнопок:
    QPixmap pix_1;
    if(!pix_1.load(":/images/on_button.png")){
        qDebug()<<"Failed to load image";
    }
    ui->pushButton_pressure->setIcon(QIcon(pix_1));
    ui->pushButton_flowRate->setIcon(QIcon(pix_1));

    //this->setFixedSize(this->size());

    //Запускаю поток и таймер
    on_lineEdit_Period_returnPressed();
}

Widget::~Widget()
{
    delete ui;
    delete simulator;
    thread_simulator->quit();
    thread_simulator->wait();

    delete thread_simulator;
    delete fluid_param_widg;

    delete spw;

}

void Widget::slot_setFluids(QList<QPair<QString, double> > fluids_l)
{
    fluids = fluids_l;

    ui->comboBox_fiuid->clear();

    for(auto fluid: fluids){
        ui->comboBox_fiuid->addItem(fluid.first);
    }
    qDebug()<<"Widget:"<< fluids;
    ui->label_fluid->setText("Вязкость: "+QString::number(fluids_l.at(ui->comboBox_fiuid->currentIndex()).second)+" мПа*с");
}

void Widget::slot_currentNuWasChanged(double current_nu)
{
    qDebug()<<"slot_currentNuWasChanged" << fluids;
    ui->label_fluid->setText("Вязкость: "+QString::number(current_nu)+" мПа*с");
}

void Widget::slot_SampleLengthWasChandged(double length)
{
    ui->label_length->setText("Длина: " + QString::number(length) + " мм");
}

void Widget::slot_SampleDiameterWasChandged(double diameter)
{
    ui->label_diameter->setText("Диаметр: " + QString::number(diameter) + " мм");
}

void Widget::slot_CurrentPreassure(double current_preasure)
{
    ui->lineEdit_current_pressure->setText(QString::number(current_preasure));
}

void Widget::slot_CurrentFlowRate(double current_flowRate)
{
    ui->lineEdit_current_flowRate->setText(QString::number(current_flowRate));
}

void Widget::slot_CurrentD1minD2(double D1minD2_pressure)
{
    ui->lineEdit_D2minD1->setText(QString::number(D1minD2_pressure));
}

void Widget::slot_Permability(double permability)
{
    ui->label_permability->setText("Проницаемость 10^-3 мкм2: "+QString::number(permability));
}

void Widget::slot_PumpMode(bool pressure_mode_l, bool flowRate_mode_l, bool stop_mode_l)
{
    pressure_mode = pressure_mode_l;
    flowRate_mode = flowRate_mode_l;
    stop_mode = stop_mode_l;

    cofigIconOnButtons();
}

void Widget::on_pushButton_changeSampleParameters_clicked()
{
    spw->show();
}

void Widget::on_pushButton_pressure_clicked()
{
    if(pressure_mode){
        emit signal_StopPump();
    }
    else{
        emit signal_SwitchPressure_mode();
        emit signal_SetSet_value_pressure(ui->lineEdit_set_value_pressure->text().toDouble());
    }

}

void Widget::on_pushButton_flowRate_clicked()
{
    if(flowRate_mode){
        emit signal_StopPump();
    }
    else{
        emit signal_SwitchFlowRate_mode();
        emit signal_SetSet_value_flowRate(ui->lineEdit_set_value_flowRate->text().toDouble());
    }

}

void Widget::cofigIconOnButtons()
{
    QPixmap pix;

    if(stop_mode){

        if(!pix.load(":/images/on_button.png")){
            qDebug()<<"Failed to load image";
        }
        ui->pushButton_pressure->setIcon(QIcon(pix));
        ui->pushButton_flowRate->setIcon(QIcon(pix));

        ui->lineEdit_PumpMode->setText("Остановлен");
        return;

    }
    else if(pressure_mode){

        if(!pix.load(":/images/off_button.png")){
            qDebug()<<"Failed to load image";
        }
        ui->pushButton_pressure->setIcon(QIcon(pix));

        ui->lineEdit_PumpMode->setText("Давление");

        if(!pix.load(":/images/on_button.png")){
            qDebug()<<"Failed to load image";
        }
        ui->pushButton_flowRate->setIcon(QIcon(pix));

        return;
    }
    else if(flowRate_mode){

        if(!pix.load(":/images/off_button.png")){
            qDebug()<<"Failed to load image";
        }
        ui->pushButton_flowRate->setIcon(QIcon(pix));

        ui->lineEdit_PumpMode->setText("Расход");

        if(!pix.load(":/images/on_button.png")){
            qDebug()<<"Failed to load image";
        }
        ui->pushButton_pressure->setIcon(QIcon(pix));

        return;
    }

}

void Widget::on_lineEdit_Period_returnPressed()
{
    simulator->setRunning(true);
    thread_simulator->start();
    timer_period->start(ui->lineEdit_Period->text().toDouble()); // И запустим таймер

}

void Widget::on_lineEdit_set_value_pressure_returnPressed()
{
    signal_SetSet_value_pressure(ui->lineEdit_set_value_pressure->text().toDouble());
}

void Widget::on_lineEdit_set_value_flowRate_returnPressed()
{
    //if((simulator->pump->getFlowRate_mode())||(simulator->pump->getPressure_mode())){
    signal_SetSet_value_flowRate(ui->lineEdit_set_value_flowRate->text().toDouble());
    //}
}

void Widget::slot_StartSimulation()
{
    simulator->setSimulator_start(true);
    //thread_simulator->start();
}

void Widget::on_pushButton_changeFluid_clicked()
{
    fluid_param_widg->show();
    emit signal_sendSignal_fluids();
}

void Widget::on_pushButton_D1_zero_clicked()
{
    emit signal_setSet_value_D1_pressure(0);
    ui->lineEdit_D1->setText(QString::number(0));
}

void Widget::on_pushButton_D2_zero_clicked()
{
    emit signal_setSet_value_D2_pressure(0);
    ui->lineEdit_D2->setText(QString::number(0));
}


void Widget::on_comboBox_fiuid_currentTextChanged(const QString &arg1)
{
    emit signal_changeFluid(ui->comboBox_fiuid->currentText());
}


void Widget::on_lineEdit_D1_returnPressed()
{
    emit signal_setSet_value_D1_pressure(ui->lineEdit_D1->text().toDouble());
}


void Widget::on_lineEdit_D2_returnPressed()
{
    emit signal_setSet_value_D2_pressure(ui->lineEdit_D2->text().toDouble());
}

