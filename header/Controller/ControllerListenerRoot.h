#ifndef CONTROLLERLISTENERROOT_H
#define CONTROLLERLISTENERROOT_H

#include "header/IronLogicDependency/ZGuard.h"
#include "header/Controller/controllerutility.h"
#include <QThread>

class ControllerListenerRoot: public QThread
{
    public:
        virtual bool getBThreadActive() const = 0;
        virtual void setBThreadActive(bool newBThreadActive)  = 0;

        virtual HRESULT CheckNotifyMsgs() = 0;
        virtual void ShowEvents(int nStart, int nCount) = 0;
        virtual void ShowEvent(
            PZG_CTR_EVENT pEvent // Событие
            ) = 0;


};

#endif // CONTROLLERLISTENERROOT_H
