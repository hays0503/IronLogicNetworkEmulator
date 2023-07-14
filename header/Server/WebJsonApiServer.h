#ifndef WEBJSONAPISERVER_H
#define WEBJSONAPISERVER_H


#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonObject>
#include <QHash>
#include <QObject>

#include "header/Server/Utils.h"


#define COMMAND_SET_ACTIVE      0
#define COMMAND_OPEN_DOOR       1
#define COMMAND_SET_MODE        2
#define COMMAND_SET_TIMEZONE    3

#define COMMAND_SET_DOOR_PARAMS 4
#define COMMAND_ADD_CARDS       5
#define COMMAND_DEL_CARDS       6
#define COMMAND_CLEAR_CARDS     7
#define COMMAND_READ_CARDS      8


class WebJsonApiServer :  public QObject
{
    Q_OBJECT

signals:
    void signal_WebJsonApiServer_set_active(qint32,QString);

    void signal_WebJsonApiServer_open_door(qint32,QString);

    void signal_WebJsonApiServer_set_mode(qint32,qint32);

    void signal_WebJsonApiServer_set_timezone(qint32,QString);

    void signal_WebJsonApiServer_set_door_params(qint32,QString);

    void signal_WebJsonApiServer_add_cards(qint32,QString);

    void signal_WebJsonApiServer_del_cards(qint32,QString);

    void signal_WebJsonApiServer_clear_cards(qint32);

    void signal_WebJsonApiServer_read_cards(qint32);

    void signal_WebJsonApiServer_update_bank_cards(qint32);

public slots:
    void slots_WebJsonApiServer_update_cards(qint32 SerialNumberController,
                                     QVariant Keys);

public:
    WebJsonApiServer();

    QHttpServerResponse ServerResponsePost(const QHttpServerRequest &request);
    void ServerRunOperationPost(qint32 SerialNumberController,
                          QString operationName,
                          const QVariantMap& operationJson);

    QHttpServerResponse ServerResponseGet(const QHttpServerRequest &request);
    QVariant ServerRunOperationGet(qint32 SerialNumberController,
                          QString operationName,
                          const QVariantMap& operationJson);

    QHash<QString,int>TypeToNamePost;
    QHash<QString,int>TypeToNameGet;
private:
    QHash<qint32,QVariant> KeysInController;

};

#endif // WEBJSONAPISERVER_H
