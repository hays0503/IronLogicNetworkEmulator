#include "header/Server/ServerWorkerThread.h"

ServerWorkerThread::ServerWorkerThread(QObject *parent)
    : QThread(parent),
      objServerWebSocket(nullptr)
{
}

ServerWorkerThread::~ServerWorkerThread()
{
    delete this->objServerWebSocket;    
}

void ServerWorkerThread::startServer()
{
    qDebug() << "Start WsServer";

    this->objServerWebSocket = new ServerWebSocket(56684);


    //    this->objServerWebSocket->moveToThread(this);

    connect(this,
            SIGNAL(signal_CWT_send_msg_ws(QString)),
            this->objServerWebSocket,
            SLOT(slot_CWT_send_msg_ws(QString)));

    // Создаем цикл событий и запускаем его
    QEventLoop eventLoop;

    eventLoop.exec();

    qDebug() << "End WsServer";
}

void ServerWorkerThread::run()
{

    this->startServer();
}

void ServerWorkerThread::slot_send_msg_ws(QString text)
{
    // this->objServerWebSocket->sendMessageToAllClients(text);
    emit signal_CWT_send_msg_ws(text);
}
