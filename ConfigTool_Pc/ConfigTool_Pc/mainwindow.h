#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QUdpSocket *udpSocket;
    QComboBox *interfaceComboBox;
    QLineEdit *messageLineEdit;
    QPushButton *sendButton;
    QListWidget *responseListWidget;

    void pupulateNetworkInterfaces();

private slots:
    void sendBroadcast();
    void processPendingDatagrams();
};
#endif // MAINWINDOW_H
