#ifndef SERVERHTTP_H
#define SERVERHTTP_H

#include "header/Server/WebJsonApiServer.h"
#include <QHttpServer>
#include <QHttpServerResponse>

//#if QT_CONFIG(ssl)
//#  include <QSslCertificate>
//#  include <QSslKey>
//#endif


#include <QCoreApplication>
#include <QFile>
#include <QJsonObject>
#include <QString>


class ServerHttp : public QObject
{
    Q_OBJECT

public:
    explicit ServerHttp(QObject *parent = nullptr);

    inline QString host(const QHttpServerRequest &request);

    int StartServer();


    QHttpServer *getHttpServer() const;
    
    WebJsonApiServer *getObjWebJsonApi() const;

private:
    QHttpServer *httpServer;
    WebJsonApiServer *objWebJsonApi;
};



#endif // SERVERHTTP_H
