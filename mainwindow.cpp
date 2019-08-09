#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    deviceHandler = new Device();
    connect(deviceHandler, SIGNAL(updateChanged()), this, SLOT(displayUpdate()));
    connect(deviceHandler, SIGNAL(scanFinished()), this, SLOT(updateDevicesBox()));
}


// Scan all available devices
void MainWindow::on_scanDevicesButton_clicked()
{
    deviceHandler->startDeviceDiscovery();
}

void MainWindow::on_scanServicesButton_clicked()
{
    QVariant selectedDevice = ui->devicesListBox->currentData();
    QString selectedDeviceName = ui->devicesListBox->currentText();
    //DeviceInfo *selectedDevice =
}

void MainWindow::on_connectDeviceButton_clicked()
{
    ui->infosTextEdit->setPlainText("connecting device...");
}

void MainWindow::displayUpdate()
{
    ui->infosTextEdit->setPlainText(deviceHandler->getUpdate());

    if(!deviceHandler->state())
        updateDevicesBox();
}

void MainWindow::updateDevicesBox()
{
    QSequentialIterable devicesList = getDevicesList();
    for(int i=0; i < devicesList.size(); i++){
        DeviceInfo selectedDeviceInfo = devicesList.at(i).value<DeviceInfo>();
        ui->devicesListBox->addItem(selectedDeviceInfo.getName(), devicesList.at(i));
    }

//    QList<DeviceInfo *> devicesList = getDevicesList();
//    for(int i=0; i < devicesList.size(); i++){
//        ui->devicesListBox->addItem(devicesList.at(i)->getName(), devicesList.at(i));
//    }

}

QSequentialIterable MainWindow::getDevicesList()
{
    QVariant variant = deviceHandler->getDevices();
    return variant.value<QSequentialIterable>();
}

MainWindow::~MainWindow()
{
    delete ui;
}
