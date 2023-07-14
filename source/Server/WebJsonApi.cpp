#include "header/Server/WebJsonApi.h"
#include "qjsonarray.h"


QJsonObject WebJsonApi::ClientPowerOn(
    QString fw,
    QString conn_fw,
    int active,
    int mode)
{
    QJsonObject PowerOn;
    /*
    {
    "id": 123456789,
    "operation": "power_on",
    "fw": "1.0.1",
    "conn_fw": "2.0.2",
    "active": 0,
    "mode": 0,
    "controller_ip": "192.168.0.222"
    }
    operation - название операции.
    fw - версия прошивки контроллера.
    conn_fw - версия прошивки модуля связи.
    active - признак активированности контроллера.
    mode - режим работы контроллера(смотри SET_MODE).
    controller_ip - IP адрес контроллера в локальной сети.
    */

    PowerOn["id"] = 1;
    PowerOn["operation"] = "power_on";
    PowerOn["fw"] =  fw;
    PowerOn["conn_fw"] = conn_fw;
    PowerOn["active"] = active;
    PowerOn["mode"] = mode;
    PowerOn["controller_ip"]=ip;

    return WrapperMessageClient(PowerOn);
}

QJsonObject WebJsonApi::ClientCheckAccess(
    QString Card,
    int Reader)
{
    QJsonObject CheckAccess;
    /*
    {
    "id": 123456789,
    "operation": "check_access",
    "card": "00B5009EC1A8",
    "reader": 1
    }
    card - номер карты в шестнадцатеричном виде (см. ПРИЛОЖЕНИЕ 2).
    reader - считыватель, к которому приложена карта. 1- вход, 2 - выход.
    */

    CheckAccess["id"]=1;
    CheckAccess["operation"]="check_access";
    CheckAccess["card"]=Card;
    CheckAccess["reader"]=Reader;

    return WrapperMessageClient(CheckAccess);
}

QJsonObject WebJsonApi::ClientPing(int active, int mode)
{
    QJsonObject Ping;
    /*
    {
    "id": 123456789,
    "operation": "ping",
    "active": 1,
    "mode": 0
    }
    active, mode - смотри POWER_ON.
    */
    Ping["id"]=1;
    Ping["operation"]="ping";
    Ping["active"]=active;
    Ping["mode"]=mode;

    return WrapperMessageClient(Ping);
}

QJsonObject WebJsonApi::ClientEvent(QJsonArray SendEvents)
{
    QJsonObject Event;
    /*
    {
    "id": 123456789,
    "operation": "events",
    "events":   [
                    {
                    "event": 4,
                    "card": "00B5009EC1A8",
                    "time": "2015-06-25 16:36:01",
                    "flag": 0
                    },
                    {
                    "event": 16,
                    "card": "00BA00FE32A2",
                    "time": "2015-06-25 16:36:02",
                    "flag": 0
                    }
                ]
    }

    */
    Event["id"]=1;
    Event["operation"]="events";
    Event["events"]=SendEvents;


    return Event;
}


QJsonObject WebJsonApi::ClientChangeMode(
    QDateTime TimeEvent,
    int Flag
    )
{
    QJsonObject ChangeMode;
    QJsonArray Events;
    /*
        {
        "event": 37,
        "card": "ChangeMode",
        "time": "2015-06-25 16:36:01",
        "flag": 0
        }
    */
    ChangeMode["event"]=37;
    ChangeMode["card"]="ChangeMode";
    ChangeMode["time"]=TimeEvent.toString("yyyy-MM-dd hh:mm:ss");
    ChangeMode["flag"]=Flag;

    Events.append(ChangeMode);

    auto sendEvent = this->ClientEvent(Events);

    return WrapperMessageClient(sendEvent);
}

QJsonObject WebJsonApi::ClientChangeElectro(
    QDateTime TimeEvent,
    int Flag
    )
{
    QJsonObject ChangeElectro;
    QJsonArray Events;
    /*
        {
        "event": 21,
        "card": "ChangeElectro",
        "time": "2015-06-25 16:36:01",
        "flag": 0
        }
    */
    ChangeElectro["event"]=21;
    ChangeElectro["card"]="ChangeElectro";
    ChangeElectro["time"]=TimeEvent.toString("yyyy-MM-dd hh:mm:ss");
    ChangeElectro["flag"]=Flag;

    Events.append(ChangeElectro);

    auto sendEvent = this->ClientEvent(Events);

    return WrapperMessageClient(sendEvent);
}

QJsonObject WebJsonApi::ClientFireEvent(
    QDateTime TimeEvent,
    int Flag)
{
    QJsonObject ChangeElectro;
    QJsonArray Events;
    /*
        {
        "event": 38,
        "card": "FireEvent",
        "time": "2015-06-25 16:36:01",
        "flag": 0
        }
    */
    ChangeElectro["event"]=38;
    ChangeElectro["card"]="ChangeElectro";
    ChangeElectro["time"]=TimeEvent.toString("yyyy-MM-dd hh:mm:ss");
    ChangeElectro["flag"]=Flag;

    Events.append(ChangeElectro);

    auto sendEvent = this->ClientEvent(Events);

    return WrapperMessageClient(sendEvent);
}

QJsonObject WebJsonApi::ClientEventCard(
    int EventCode,
    QString Card,
    QDateTime TimeEvent,
    int Flag,
    int nDirect = -1)
{
    QJsonObject EventCard;
    QJsonArray Events;
    /*
        {
        "event": 4,
        "card": "00B5009EC1A8",
        "time": "2015-06-25 16:36:01",
        "flag": 0
        }
    */
    EventCard["event"]=EventCode;
    EventCard["card"]=Card;
    EventCard["time"]=TimeEvent.toString("yyyy-MM-dd hh:mm:ss");
    EventCard["flag"]=Flag;
    EventCard["direct"] = nDirect == -1 ?  this->DefaultPassDirection:nDirect ;
    EventCard["reader"] = nDirect == -1 ?  this->DefaultPassDirection:nDirect ;

    Events.append(EventCard);

    auto sendEvent = this->ClientEvent(Events);

    return WrapperMessageClient(sendEvent);
}

QJsonObject WebJsonApi::ClientOpenButton(QDateTime TimeEvent,int nDirect)
{
    QJsonObject eventBUT_OPEN;
    eventBUT_OPEN["event"] = 1;
    eventBUT_OPEN["card"] = "OpenButtonPressed";
    eventBUT_OPEN["direct"] = nDirect == -1 ?  this->DefaultPassDirection:nDirect ;
    eventBUT_OPEN["reader"] = nDirect == -1 ?  this->DefaultPassDirection:nDirect ;
    eventBUT_OPEN["flag"] = 0;
    eventBUT_OPEN["time"] = TimeEvent.toString("yyyy-MM-dd hh:mm:ss");

    QJsonArray jsonMessagesArray;
    jsonMessagesArray.append(eventBUT_OPEN);

    auto sendEvent = this->ClientEvent(jsonMessagesArray);

    return WrapperMessageClient(sendEvent);
}

QJsonObject WebJsonApi::WrapperMessageClient(QJsonObject Msg)
{
    QJsonObject messages_for_send;
    messages_for_send["type"] = TypeController;
    messages_for_send["sn"] = SerialNumber;


    QJsonArray jsonMessagesArray;
    jsonMessagesArray.append(Msg);

    messages_for_send["messages"] = jsonMessagesArray;

    return messages_for_send;
}



WebJsonApi::WebJsonApi(const int SerialNumber, const QString &TypeController, const int DefaultPassDirection,const QString &ip) :
    SerialNumber(SerialNumber),
    TypeController(TypeController),
    DefaultPassDirection(DefaultPassDirection),
    ip(ip)
{}
