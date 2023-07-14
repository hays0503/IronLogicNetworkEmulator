#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H


#include <QObject>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class ClientHttp: public QObject
{
    Q_OBJECT

    public:
        explicit ClientHttp(QString adressClient,
                            QObject *parent = nullptr);

    public slots:

        void sendEvent(QJsonObject json);

    signals:
        void signals_accessGranted(int sn);

    private:
        QString adress;
        QNetworkAccessManager *manager;
        QNetworkReply *reply;
};

#endif // CLIENTHTTP_H
