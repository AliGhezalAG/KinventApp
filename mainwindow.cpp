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
    connect(deviceHandler, SIGNAL(servicesScanFinished()), this, SLOT(updateServicesBox()));
}


// Scan all available devices
void MainWindow::on_scanDevicesButton_clicked()
{
    deviceHandler->startDeviceDiscovery();
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
    QVariant selectedService = ui->servicesBox->currentData();
    ServiceInfo *selectedServiceInfo = selectedService.value<ServiceInfo*>();
    deviceHandler->connectToService(selectedServiceInfo->getUuid());
    displayCharacteristicsList();
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

void MainWindow::updateServicesBox()
{
    QList<QVariant> servicesList = getServicesList();
    for(int i=0; i < servicesList.size(); i++){
        ServiceInfo *selectedServiceInfo = servicesList.at(i).value<ServiceInfo*>();
        ui->servicesBox->addItem(selectedServiceInfo->getName(), servicesList.at(i));
    }
}

QList<QVariant> MainWindow::getServicesList()
{
    QVariant variant = deviceHandler->getServices();
    QSequentialIterable iterable = variant.value<QSequentialIterable>();
    QList<QVariant> servicesList = {};
    for (const QVariant &v : iterable) {
        servicesList.append(v);
    }
    return servicesList;
}

void MainWindow::displayCharacteristicsList()
{
    QList<QVariant> characteristicsList = getCharacteristicsList();
    QString infosText = "";
    for(int i=0; i < characteristicsList.size(); i++){
        CharacteristicInfo *characteristicInfo = characteristicsList.at(i).value<CharacteristicInfo*>();
        infosText.append(characteristicInfo->getName() + " : ");
        infosText.append(characteristicInfo->getUuid() + " : ");
        infosText.append(characteristicInfo->getPermission() + "\n");
        if(characteristicInfo->getUuid().compare("49535343-1e4d-4bd9-ba61-23c647249616", Qt::CaseInsensitive) == 0)
            notificationCharacteristic = characteristicInfo;
    }
    infosText.append(notificationCharacteristic->getValue() + "\n");
    ui->infosTextEdit->append(infosText);
}

QList<QVariant> MainWindow::getCharacteristicsList()
{
    QVariant variant = deviceHandler->getCharacteristics();
    QSequentialIterable iterable = variant.value<QSequentialIterable>();
    QList<QVariant> characteristicsList = {};
    for (const QVariant &v : iterable) {
        characteristicsList.append(v);
    }
    return characteristicsList;
}

MainWindow::~MainWindow()
{
    delete ui;
}
