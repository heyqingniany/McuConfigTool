#include "mainwindow.h"

#include <QNetworkDatagram>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , udpSocket(new QUdpSocket(this))
    , interfaceComboBox(new QComboBox(this))
    , messageLineEdit(new QLineEdit(this))
    , sendButton(new QPushButton("Send UDP Broadcast", this))
    , responseListWidget(new QListWidget(this))
{
    setWindowTitle("ConfigTool");

    pupulateNetworkInterfaces();

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(interfaceComboBox);
    layout->addWidget(messageLineEdit);
    layout->addWidget(sendButton);
    layout->addWidget(responseListWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendBroadcast);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::processPendingDatagrams);
}

MainWindow::~MainWindow() {
    // Cleanup if necessary
}

void MainWindow::pupulateNetworkInterfaces()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for(const QNetworkInterface &interface : interfaces){
        if(interface.flags() & QNetworkInterface::IsUp &&
            interface.flags() & QNetworkInterface::IsRunning &&
            !(interface.flags() & QNetworkInterface::IsLoopBack)){
            interfaceComboBox->addItem(interface.humanReadableName(), interface.name());
        }
    }
}

void MainWindow::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString receivedMessage = QString::fromUtf8(datagram);

        responseListWidget->addItem(
            QString("Reiceived from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(receivedMessage)
            );
    }
}



void MainWindow::sendBroadcast()
{
    QByteArray datagram = "FIND";
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);

}
