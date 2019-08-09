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
    if(deviceHandler->isScanFinished()){
        updateDevicesBox();
        deviceHandler->setScanFinished();
    }
}

void MainWindow::on_scanServicesButton_clicked()
{
    ui->infosTextEdit->setPlainText("Scanning services ...");

    QVariant selectedDevice = ui->devicesListBox->currentData();
    DeviceInfo *selectedDeviceInfo = selectedDevice.value<DeviceInfo*>();
    deviceHandler->scanServices(selectedDeviceInfo->getAddress());
}

void MainWindow::on_connectDeviceButton_clicked()
{
    ui->infosTextEdit->setPlainText("connecting device...");
}

void MainWindow::displayUpdate()
{
    ui->infosTextEdit->setPlainText(deviceHandler->getUpdate());
}

void MainWindow::updateDevicesBox()
{
    QList<QVariant> devicesList = getDevicesList();
    for(int i=0; i < devicesList.size(); i++){
        DeviceInfo *selectedDeviceInfo = devicesList.at(i).value<DeviceInfo*>();
        ui->devicesListBox->addItem(selectedDeviceInfo->getName(), devicesList.at(i));
    }
}

QList<QVariant> MainWindow::getDevicesList()
{
    QVariant variant = deviceHandler->getDevices();
    QSequentialIterable iterable = variant.value<QSequentialIterable>();
    QList<QVariant> devicesList = {};
    for (const QVariant &v : iterable) {
        devicesList.append(v);
    }
    return devicesList;
}

MainWindow::~MainWindow()
{
    delete ui;
}
