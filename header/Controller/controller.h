#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "header/IronLogicDependency/ZGuard.h"

#include "header/Controller/ControllerListener.h"
#include "header/Controller/ControllerListener_alternative.h"
#include "header/Controller/ControllerListener_alternative_windows_hwnd.h"




#include <QObject>
#include <QThread>
#include <QVariant>
#include <Windows.h>
#include <QDebug>


class Controller: public QObject
{
    Q_OBJECT
public:
    Controller(HANDLE hCvt,
               int PhisicalAdressInConverter,
               const int DefaultPassDirection,
               DatabaseControllerPostgreSQL *database);
    DWORD WINAPI NotifyThreadProc(LPVOID lpParameter);
    static DWORD WINAPI StaticNotifyThreadProc(LPVOID lpParameter);

    void StartControllerListener();
    void StopControllerListener();
    void GetAllKeyInController();
    void OpenDoor();
    void ClearCards();
    void SetModeBlock(qint32 mode);
    void ThreadProc();
    void tryAddCard(QString Card);
    void tryDeleteCard(QString Card);

    qint32 SerialNumberController=0;
    PZG_CTR_INFO rCtrInfo;
    CartDto *CartDtoObject = nullptr;


    void Listen_Controller();
    const ControllerListenerRoot* getObjectControllerListener();


signals:
    void controller_update_card(qint32 SerialNumberController,
                                QVariant Keys);


private:
    HANDLE hCtr = nullptr;
    HANDLE hEvent = nullptr;
    QThread hThread;
    int g_nCtrMaxEvents;
    bool g_fProximity;
    int g_nAppReadEventIdx;
    bool bThreadActive;

    ControllerListenerRoot *objectControllerListener = nullptr;

    QList<int> getFreeIndexes(const QSet<int>& occupiedIndexes, int totalKeys);



};

#endif // CONTROLLER_H
