#ifndef CONTROLLERLISTENER_H
#define CONTROLLERLISTENER_H

#include <QObject>
#include <QThread>
#include <QVariant>

#include <QDebug>
#include <QJsonObject>
#include "ControllerListenerRoot.h"
#include "header/Controller/CardDto.h"
#include "header/Database/Database.h"
#include "header/IronLogicDependency/ZGuard.h"
#include "header/Server/WebJsonApi.h"


class ControllerListener: public ControllerListenerRoot
{
    Q_OBJECT
public:
    explicit ControllerListener(HANDLE hEvent,
                                HANDLE hCtr,
                                PZG_CTR_INFO pInfo,
                                CartDto *CartDtoObject,
                                const int DefaultPassDirection,
                                DatabaseControllerPostgreSQL *database);

    ~ControllerListener();

    bool getBThreadActive() const override;
    void setBThreadActive(bool newBThreadActive) override;



protected:
    void run() override;

    HRESULT CheckNotifyMsgs() override;
    void ShowEvents(int nStart, int nCount) override;
    // Событие
    void ShowEvent(PZG_CTR_EVENT pEvent) override;
private:

    HANDLE hEvent;
    bool bThreadActive = true;
    QJsonObject messages_for_send;
    QElapsedTimer fullTimeEvent;
    int pWrIndx;
    int pRdIdx;
    int g_nCtrMaxEvents;
    int g_nAppReadEventIdx;
    bool g_fProximity;
    HANDLE hCtr = nullptr;
    PZG_N_NEW_EVENT_INFO pInfoLastEvent = nullptr;
    PZG_CTR_INFO rCtrInfo;
    QJsonObject eventUNKNOWN_KEY;
    WebJsonApi *pObjWebJsonApi;
    QString LastKeyCard = "";
    CartDto *CartDtoObject = nullptr;

    void SendAndPrint(QJsonObject DataToSend);

    void CheckNotifyMsgsAlternative();

    void Processing_Event_Button_Open(
        PZG_CTR_EVENT pEv
        );

    void Processing_Event_Key(
        PZG_CTR_EVENT pEv
        );

    void Processing_Event_Unknown_Key(
        PZG_CTR_EVENT pEv
        );

    void Processing_Event_Mode_State(
        PZG_CTR_EVENT pEv
        );

    void Processing_Event_Change_Electro(
        PZG_CTR_EVENT pEv
        );

    void Processing_Event_Fire_State(
        PZG_CTR_EVENT pEv
        );

signals:
    void controller_signal_new_msg(QString message);

    //Сигнал для отправки уведомление
    //о совершении событий в контролере
    void controller_signal_new_event(QJsonObject event);


};

#endif // CONTROLLERLISTENER_H
