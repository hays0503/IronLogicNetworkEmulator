#ifndef SERVERWORKERTHREAD_H
#define SERVERWORKERTHREAD_H

#include "header/Server/WebJsonApi.h"
#include "qthread.h"
#include <QObject>
#include "header/Server/serverhttp.h"
#include "header/Server/clienthttp.h"
#include "header/Server/serverwebsocket.h"

class ServerWorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit ServerWorkerThread(QObject *parent = nullptr);
    ~ServerWorkerThread();

    QObject *MainWindow = nullptr;
    const char *memberSignal = nullptr;


    ServerWebSocket *objServerWebSocket = nullptr;
    void startServer();
    //    ServerWorkerThread();

    void run() override;

signals:
    void signal_CWT_send_msg_ws(QString text);

public slots:
    void slot_send_msg_ws(QString text);

private:
signals:
    void operationCompleted(const QString &result);
};

#endif // SERVERWORKERTHREAD_H
