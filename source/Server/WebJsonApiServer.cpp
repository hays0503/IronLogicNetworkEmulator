#include "header/Server/WebJsonApiServer.h"

void WebJsonApiServer::slots_WebJsonApiServer_update_cards(qint32 SerialNumberController,
                                                           QVariant Keys)
{
    qDebug() << " {WebJsonApi} - slots_WebJsonApi_update_cards(qint32 SerialNumberController,QVariant Keys)";
    this->KeysInController.insert(SerialNumberController, Keys);
}

WebJsonApiServer::WebJsonApiServer()
{
    TypeToNamePost.insert("set_active", COMMAND_SET_ACTIVE);
    TypeToNamePost.insert("open_door", COMMAND_OPEN_DOOR);
    TypeToNamePost.insert("set_mode", COMMAND_SET_MODE);
    TypeToNamePost.insert("set_timezone", COMMAND_SET_TIMEZONE);
    TypeToNamePost.insert("set_door_params", COMMAND_SET_DOOR_PARAMS);
    TypeToNamePost.insert("add_cards", COMMAND_ADD_CARDS);
    TypeToNamePost.insert("del_cards", COMMAND_DEL_CARDS);
    TypeToNamePost.insert("clear_cards", COMMAND_CLEAR_CARDS);
    TypeToNameGet.insert("read_cards", COMMAND_READ_CARDS);
}

QHttpServerResponse WebJsonApiServer::ServerResponsePost(const QHttpServerRequest &request)
{
    const std::optional<QJsonObject> json = byteArrayToJsonObject(request.body());

    if (!json || !json->contains("date") || !json->contains("interval") || !json->contains("messages") || !json->contains("sn"))
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);

    // Перечень операций
    QVariantMap jsonMap = json->toVariantMap();
    // Серийный номер контролера
    qint32 SerialNumberController = jsonMap["sn"].toInt();

    QVariantList messages = jsonMap["messages"].toList();

    // Проверка на коректность перчня команд(а существуют ли такие?)
    for (const QVariant &message : messages)
    {
        QVariantMap messageMap = message.toMap();
        QString operation = messageMap["operation"].toString();
        if (!TypeToNamePost.contains(operation))
        {
            QString textError = "Операция '" + operation + "' не существует.";
            return QHttpServerResponse(textError, QHttpServerResponder::StatusCode::BadRequest);
        }
    }

    for (const QVariant &message : messages)
    {
        QVariantMap messageMap = message.toMap();
        QString operation = messageMap["operation"].toString();
        qDebug() << " {WebJsonApi} - Operation:" << operation;
        this->ServerRunOperationPost(SerialNumberController, operation, messageMap);
    }

    return QHttpServerResponse(*json);
};

void WebJsonApiServer::ServerRunOperationPost(qint32 SerialNumberController, QString operationName, const QVariantMap &operationJson)
{

    switch (this->TypeToNamePost.value(operationName))
    {

    case COMMAND_SET_ACTIVE:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_SET_ACTIVE";
    }
    break;
    case COMMAND_OPEN_DOOR:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_OPEN_DOOR";
        qDebug() << " {WebJsonApiServer} - signal_WebJsonApi_open_door(" << SerialNumberController << ",Some text)";
        emit signal_WebJsonApiServer_open_door(SerialNumberController, "Some text");
    }
    break;
    case COMMAND_SET_MODE:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_SET_MODE";
        qDebug() << " {WebJsonApiServer} - signal_WebJsonApi_set_mode(" << SerialNumberController << "," << operationJson["mode"].toInt() << ")";
        emit signal_WebJsonApiServer_set_mode(SerialNumberController, operationJson["mode"].toInt());
    }
    break;
    case COMMAND_SET_TIMEZONE:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_SET_TIMEZONE";
    }
    break;
    case COMMAND_SET_DOOR_PARAMS:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_SET_DOOR_PARAMS";
    }
    break;
    case COMMAND_ADD_CARDS:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_ADD_CARDS";
        qDebug() << " {WebJsonApiServer} - signal_WebJsonApi_add_cards(" << SerialNumberController << "," << operationJson["mode"].toString() << ")";
        qDebug() << operationJson["cards"].toList();
        for (const QVariant &card : operationJson["cards"].toList())
        {
            emit signal_WebJsonApiServer_add_cards(SerialNumberController, card.toMap()["card"].toString());
        }
        //            emit signal_WebJsonApi_update_bank_cards(SerialNumberController);
    }
    break;
    case COMMAND_DEL_CARDS:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_DEL_CARDS";
        qDebug() << " {WebJsonApiServer} - signal_WebJsonApi_del_cards(" << SerialNumberController << "," << operationJson["card"].toString() << ")";
        for (const QVariant &card : operationJson["cards"].toList())
        {
            emit signal_WebJsonApiServer_del_cards(SerialNumberController, card.toMap()["card"].toString());
        }
    }
    break;
    case COMMAND_CLEAR_CARDS:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_CLEAR_CARDS";
        qDebug() << " {WebJsonApiServer} - signal_WebJsonApi_clear_cards(" << SerialNumberController << ",Some text)";
        emit signal_WebJsonApiServer_clear_cards(SerialNumberController);
    }
    break;
    default:
    {
        qDebug() << "COMMAND NOT FOUND";
    }
    break;
    }
}

QHttpServerResponse WebJsonApiServer::ServerResponseGet(const QHttpServerRequest &request)
{
    const std::optional<QJsonObject> json = byteArrayToJsonObject(request.body());

    if (!json || !json->contains("date") || !json->contains("interval") || !json->contains("messages") || !json->contains("sn"))
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);

    // Перечень операций
    QVariantMap jsonMap = json->toVariantMap();
    // Серийный номер контролера
    qint32 SerialNumberController = jsonMap["sn"].toInt();

    QVariantList messages = jsonMap["messages"].toList();

    // Проверка на коректность перчня команд(а существуют ли такие?)
    for (const QVariant &message : messages)
    {
        QVariantMap messageMap = message.toMap();
        QString operation = messageMap["operation"].toString();
        if (!TypeToNameGet.contains(operation))
        {
            QString textError = "Операция '" + operation + "' не существует.";
            return QHttpServerResponse(textError, QHttpServerResponder::StatusCode::BadRequest);
        }
    }

    for (const QVariant &message : messages)
    {
        QVariantMap messageMap = message.toMap();
        QString operation = messageMap["operation"].toString();
        qDebug() << " {WebJsonApiServer} - Operation:" << operation;
        qDebug() << " {WebJsonApiServer} - Ответ" << this->ServerRunOperationGet(SerialNumberController, operation, messageMap);
        QVariant responce = this->ServerRunOperationGet(SerialNumberController, operation, messageMap);

        QJsonDocument jsonDocument = QJsonDocument::fromVariant(responce);
        QByteArray jsonData = jsonDocument.toJson();

        QHttpServerResponse response(jsonData);
        response.setHeader("Content-Type", "application/json");

        return response;
    }

    return QHttpServerResponse(*json);
};

QVariant WebJsonApiServer::ServerRunOperationGet(qint32 SerialNumberController, QString operationName, const QVariantMap &operationJson)
{

    switch (TypeToNameGet.value(operationName))
    {
    case COMMAND_READ_CARDS:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND_READ_CARDS";

        QVariantMap rootMap;
        rootMap["type"] = QVariant("Z5RWEB");
        rootMap["sn"] = QVariant(SerialNumberController);

        QVariantList messagesList;

        QVariantMap messageMap;
        QVariantList cardsList;

        QVariant keysVariant = this->KeysInController.value(SerialNumberController);
        QStringList keysList = keysVariant.toStringList();

        for (const QString &key : keysList)
        {
            QVariantMap cardMap;
            cardMap["pos"] = cardsList.size();
            cardMap["card"] = QVariant(key);
            cardMap["flags"] = QVariant(0);
            cardMap["tz"] = QVariant(255);
            cardsList.append(QVariant(cardMap));
        }

        messageMap["cards"] = QVariant(cardsList);
        messagesList.append(QVariant(messageMap));

        rootMap["messages"] = QVariant(messagesList);

        return QVariant(rootMap);
    }
    break;
    default:
    {
        qDebug() << " {WebJsonApiServer} - COMMAND NOT FOUND";
    }
    break;
    }
};
