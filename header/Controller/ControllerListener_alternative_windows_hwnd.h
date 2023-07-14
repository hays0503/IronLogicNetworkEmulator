#ifndef CONTROLLERLISTENER_ALTERNATIVE_WINDOWS_HWND_H
#define CONTROLLERLISTENER_ALTERNATIVE_WINDOWS_HWND_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include <Windows.h>
#include <QDebug>
#include <QJsonObject>
#include "header/Controller/CardDto.h"
#include "header/IronLogicDependency/ZGuard.h"
#include "header/Server/WebJsonApi.h"
#include "header/Database/Database.h"
#include "header/Controller/ControllerListenerRoot.h"

class ControllerListener_alternative_windows_hwnd: public ControllerListenerRoot
{
    Q_OBJECT
public:
    explicit ControllerListener_alternative_windows_hwnd(HANDLE hEvent,
        HANDLE hCtr,
        PZG_CTR_INFO pInfo,
        CartDto *CartDtoObject,
        const int DefaultPassDirection,
        DatabaseControllerPostgreSQL *database);

    bool getBThreadActive() const override;
    void setBThreadActive(bool newBThreadActive) override;

    HRESULT CheckNotifyMsgs() override;
    void CheckNotifyMsgsAlternative();
protected:
    void run() override;


    void ShowEvents(int nStart, int nCount) override;
    void ShowEvent(PZG_CTR_EVENT pEvent) override;
private:

    HANDLE hEvent;
    bool bThreadActive = true;

    QElapsedTimer fullTimeEvent;

    int pWrIndx;
    int pRdIdx;
    int g_nCtrMaxEvents;
    int g_nAppReadEventIdx;
    bool g_fProximity;
    HANDLE hCtr = nullptr;
    PZG_N_NEW_EVENT_INFO pInfoLastEvent = nullptr;
    PZG_CTR_INFO rCtrInfo;
    WebJsonApi *pObjWebJsonApi;
    QJsonObject eventUNKNOWN_KEY;
    QJsonObject messages_for_send;
    QString LastKeyCard = "";
    CartDto *CartDtoObject = nullptr;



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

#endif // CONTROLLERLISTENER_ALTERNATIVE_WINDOWS_HWND_H
