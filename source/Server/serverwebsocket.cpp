#include "header/Server/serverwebsocket.h"
#include "qthread.h"

ServerWebSocket::ServerWebSocket(quint16 port, QObject *parent): QObject(parent), stopServer(false)
{
    server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);
    connect(server, &QWebSocketServer::newConnection, this, &ServerWebSocket::onNewConnection);
    if(port != NULL){
        if (!server->listen(QHostAddress::Any, port))
        {
            qFatal("Не удалось запустить сервер");
        }
    }
    else
    {
        if (!server->listen(QHostAddress::Any))
        {
            qFatal("Не удалось запустить сервер");
        }
    }

    qDebug() << "Сервер слушает " << server->serverUrl();

    qDebug() << "Сервер слушает порт" << server->serverPort();
}

void ServerWebSocket::onNewConnection()
{

    QWebSocket *socket = server->nextPendingConnection();
    this->connectedClients.append(socket);
    qDebug() << "Новый клиент подключился: Socket="<<socket;
    qDebug() << "this->connectedClients: "<<this->connectedClients.last();
    connect(socket, &QWebSocket::disconnected, this, &ServerWebSocket::onSocketDisconnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &ServerWebSocket::onTextMessageReceived);


}

void ServerWebSocket::onSocketDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        qDebug() << "Клиент отключился";
        connectedClients.removeOne(socket);
        socket->deleteLater();
    }
}

void ServerWebSocket::onTextMessageReceived(const QString &message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        qDebug() << "Получено сообщение:" << message;
        socket->sendTextMessage(message); // Отправка ответного сообщения клиенту

        // Отправка сообщения всем подключенным клиентам
        sendMessageToAllClients(message);
    }
}

void ServerWebSocket::sendMessage(const QString &message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        socket->sendTextMessage(message);
    }
}

void ServerWebSocket::sendMessageToAllClients(const QString &message)
{
    foreach (QWebSocket *clientSocket, this->connectedClients) {
        qDebug() << "clientSocket: "<<clientSocket;
        clientSocket->sendTextMessage(message);
    }
}

void ServerWebSocket::onStarted()
{
    // Реализация метода onStarted
}

void ServerWebSocket::onFinished()
{
    // Реализация метода onFinished
}

void ServerWebSocket::slot_CWT_send_msg_ws(QString text)
{
    this->sendMessageToAllClients(text);
}

QWebSocketServer *ServerWebSocket::getServer() const
{
    return server;
}
