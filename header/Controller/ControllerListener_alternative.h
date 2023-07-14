#ifndef CONTROLLERLISTENER_ALTERNATIVE_H
#define CONTROLLERLISTENER_ALTERNATIVE_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include <Windows.h>
#include <QDebug>
#include <QJsonObject>
#include "header/Controller/CardDto.h"
#include "header/Controller/ControllerListenerRoot.h"
#include "header/Database/Database.h"
#include "header/IronLogicDependency/ZGuard.h"
#include "header/Server/WebJsonApi.h"


class ControllerListenerAlternative: public ControllerListenerRoot
{
    Q_OBJECT
public:
    explicit ControllerListenerAlternative(HANDLE hEvent,
                                           HANDLE hCtr,
                                           PZG_CTR_INFO pInfo,
                                           CartDto *CartDtoObject,
                                           const int DefaultPassDirection,
                                           DatabaseControllerPostgreSQL *database);
    ~ControllerListenerAlternative();



    bool getBThreadActive() const override;
    void setBThreadActive(bool newBThreadActive) override;

protected:
    void run() override;

    void ShowEvents(int nStart, int nCount) override;

private:
    HANDLE hEvent;
    bool bThreadActive = true;

    int pWrIndx;
    int pRdIdx;


    QElapsedTimer fullTimeEvent;
    int g_nCtrMaxEvents;
    int g_nAppReadEventIdx;
    bool g_fProximity;
    HANDLE hCtr = nullptr;
    PZG_CTR_INFO rCtrInfo;
    QJsonObject eventUNKNOWN_KEY;
    WebJsonApi *pObjWebJsonApi;
    QString LastKeyCard = "";
    CartDto *CartDtoObject = nullptr;
    DatabaseControllerPostgreSQL *database;

    void CheckNotifyMsgsAlternative();

    void SendAndPrint(QJsonObject DataToSend);

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

#endif // CONTROLLERLISTENER_ALTERNATIVE_H
