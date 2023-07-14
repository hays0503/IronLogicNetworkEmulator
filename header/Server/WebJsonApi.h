#ifndef WEBJSONAPI_H
#define WEBJSONAPI_H

#include <QObject>
#include <QJsonObject>

class WebJsonApi: public QObject
{
    private:
        const int SerialNumber = 0;
        const QString TypeController = "";
        const int DefaultPassDirection = -1;
        const QString ip = "";

    public:
        WebJsonApi(const int SerialNumber,
                   const QString &TypeController,
                   const int DefaultPassDirection,
                   const QString &ip);

        QJsonObject ClientPowerOn(QString fw,
            QString conn_fw,
            int active,
            int mode);

        QJsonObject ClientCheckAccess(
            QString Card,
            int Reader);

        QJsonObject ClientPing(
            int active,
            int mode);

        QJsonObject ClientEvent(
            QJsonArray SendEvents
            );

        QJsonObject ClientChangeMode(QDateTime TimeEvent,
            int Flag
            );


        QJsonObject ClientChangeElectro(
            QDateTime TimeEvent,
            int Flag
            );

        QJsonObject ClientFireEvent(QDateTime TimeEvent,
            int Flag);

        QJsonObject ClientEventCard(int EventCode,
            QString Card,
            QDateTime TimeEvent,
            int Flag,
            int nDirect);

        QJsonObject ClientOpenButton(
            QDateTime TimeEvent,
            int nDirect);




        QJsonObject WrapperMessageClient(QJsonObject
            Msg);

};


#endif // WEBJSONAPI_H
