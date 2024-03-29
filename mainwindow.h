#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_scanDevicesButton_clicked();
    void on_connectDeviceButton_clicked();
    void on_scanServicesButton_clicked();
    void displayUpdate();
    void updateDevicesBox();
    QList<QVariant> getDevicesList();
    void updateServicesBox();
    QList<QVariant> getServicesList();
    QList<QVariant> getCharacteristicsList();
    void displayCharacteristicsList();

private:
    Ui::MainWindow *ui;
    Device *deviceHandler;
    CharacteristicInfo *notificationCharacteristic;
};

#endif // MAINWINDOW_H
