#ifndef SERVERWEBSOCKET_H
#define SERVERWEBSOCKET_H

#include <QCoreApplication>
//QtWebSockets
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocket>
//QtNetwork
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
//QJson
#include <QJsonDocument>
#include <QJsonObject>


class ServerWebSocket : public QObject
{
    Q_OBJECT
public:
    ServerWebSocket(quint16 port, QObject *parent = nullptr);

    // Обработчик нового подключения
    void onNewConnection();

    // Обработчик отключения клиента
    void onSocketDisconnected();

    // Обработчик получения текстового сообщения от клиента
    void onTextMessageReceived(const QString& message);

    void sendMessage(const QString &message);
    QWebSocketServer *getServer() const;
    bool stopServer;
    void sendMessageToAllClients(const QString &message);
private:
    QWebSocketServer *server;
    QList<QWebSocket *> connectedClients; // список подключенных клиентов

signals:
    void messageReceived(const QString &message);
    void signal_new_msg(const QString& message);
public slots:
    void onStarted();
    void onFinished();
    void slot_CWT_send_msg_ws(QString text);

};

#endif // SERVERWEBSOCKET_H
