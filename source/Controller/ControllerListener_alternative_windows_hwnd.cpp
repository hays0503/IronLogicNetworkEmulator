#include "header/Controller/ControllerListener_alternative_windows_hwnd.h"
#include "header/IronLogicDependency/ZPort.h"
#include "header/IronLogicDependency/Utils.h"

ControllerListener_alternative_windows_hwnd::ControllerListener_alternative_windows_hwnd(
    HANDLE hEvent,
    HANDLE hCtr,
    PZG_CTR_INFO pInfo,
    CartDto *CartDtoObject,
    const int DefaultPassDirection,
    DatabaseControllerPostgreSQL *database)
{

    this->hEvent = hEvent;
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - this->hEvent = hEvent;";

    this->hCtr = hCtr;
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - this->hCtr = hCtr";

    this->rCtrInfo = pInfo;
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - this->rCtrInfo = pInfo;";

    this->CartDtoObject = CartDtoObject;


    QString ip = database->getIpClient();

    this->pObjWebJsonApi = new WebJsonApi(
        this->rCtrInfo->nSn,                                                 // Серийный номер
        QString::fromUtf8(CtrTypeStrsStdString[int(this->rCtrInfo->nType)]), // Тип контролера
        DefaultPassDirection,                                                 // направление прохода по умолчанию
        ip
        );
}

bool ControllerListener_alternative_windows_hwnd::getBThreadActive() const
{
    return bThreadActive;
}

void ControllerListener_alternative_windows_hwnd::setBThreadActive(bool newBThreadActive)
{
    bThreadActive = newBThreadActive;
}

void ControllerListener_alternative_windows_hwnd::run()
{

    this->g_nCtrMaxEvents = rCtrInfo->nMaxEvents;
    this->g_fProximity = (rCtrInfo->nFlags & ZG_CTR_F_PROXIMITY) != 0;

    this->pWrIndx = 0;
    this->pRdIdx = 0;

    DWORD nMask = 0x7;
    // Пишем время открытие замка в 4 сек
    HRESULT Result = ZG_Ctr_WriteLockTimes(this->hCtr, nMask, 4000, 0, 0, 0);
    if (Result != S_OK)
    {
        qDebug() << " {ControllerListener_alternative_windows_hwnd} ZG_Ctr_WriteLockTimes  - Ошибка в установке времени открытия замка";
        throw std::exception("{ControllerListener_alternative_windows_hwnd} ZG_Ctr_WriteLockTimes");
    }

    Z_KEYNUM pNum;
    Result = ZG_Ctr_ReadLastKeyNum(this->hCtr, &pNum);
    if (Result != S_OK)
    {
        qDebug() << " {ControllerListener_alternative_windows_hwnd} ZG_Ctr_ReadLastKeyNum  - Ошибка";
        throw std::exception(" {ControllerListener_alternative_windows_hwnd} ZG_Ctr_ReadLastKeyNum  - Ошибка");
    }
    else
    {
        this->LastKeyCard = QString::fromUtf8(readKeyInBufferHex(pNum).c_str());
    }

    Result = ZG_Ctr_ReadEventIdxs(
        this->hCtr,     // Дискриптор Контролера
        &this->pWrIndx, // Указатель записи события
        &this->pRdIdx   // Указатель чтения слбытий
    );

    if (Result != S_OK)
    {
        qDebug() << " {ControllerListener_alternative_windows_hwnd} ZG_Ctr_ReadEventIdxs  - Ошибка";
        throw std::exception(" {ControllerListener_alternative_windows_hwnd} ZG_Ctr_ReadEventIdxs  - Ошибка");
    }

    this->g_nAppReadEventIdx = this->pWrIndx;

    while (this->bThreadActive)
    {
        //        qDebug()<<" {ControllerListener_alternative_windows_hwnd} - Thread controller start - Потоки для контролера включены и слушают событие !";

        //        if (WaitForSingleObject(this->hEvent, INFINITE) == WAIT_OBJECT_0)
        //        {
        //            fullTimeEvent.start();
        //            ResetEvent(this->hEvent);
        //            if (this->hEvent != nullptr)
        //            {
        //                qDebug()<<" {ControllerListener_alternative_windows_hwnd} - НОВОЕ СОБЫТИЕ !";
        //                this->CheckNotifyMsgs();
        //            }

        //        }
    }
}

HRESULT ControllerListener_alternative_windows_hwnd::CheckNotifyMsgs()
{

    HRESULT hr;
    UINT nMsg;
    LPARAM nMsgParam;

    while ((hr = ZG_Ctr_GetNextMessage(this->hCtr, &nMsg, &nMsgParam)) == S_OK)
    {

        qDebug() << " {ControllerListener_alternative_windows_hwnd} - НОВОЕ СОБЫТИЕ ! - ЦИКЛ";
        qDebug() << " {ControllerListener_alternative_windows_hwnd} - nMsg:" << nMsg;
        switch (nMsg)
        {
        case ZG_N_CTR_NEW_EVENT:
        {

            this->pInfoLastEvent = PZG_N_NEW_EVENT_INFO(nMsgParam);
            this->ShowEvents(pInfoLastEvent->nReadIdx, pInfoLastEvent->nNewCount);
            this->g_nAppReadEventIdx = pInfoLastEvent->nWriteIdx;
        }
        break;
        }
    }
    if (hr == ZP_S_NOTFOUND)
        hr = S_OK;
    return hr;
}

void ControllerListener_alternative_windows_hwnd::ShowEvents(
    int nStart, // С какой начмнаем читать
    int nCount  // Сколько событий нужно прочесть
)
{
    //    0 milliseconds,0 milliseconds,0 milliseconds
    _ZG_CTR_EVENT aEvents[6];
    PZG_CTR_EVENT pEv;
    int i, j, nIdx, nCnt;

    i = 0;

    // 1025 milliseconds , 1020 milliseconds ,1023 milliseconds
    while (i < nCount)
    {

        // 0 milliseconds ,0 milliseconds , 0 milliseconds, 0 milliseconds
        nIdx = (nStart + i) % this->g_nCtrMaxEvents;
        nCnt = (nCount - i);
        if (nCnt > _countof(aEvents))
            nCnt = _countof(aEvents);

        if ((nIdx + nCnt) > this->g_nCtrMaxEvents)
            nCnt = (this->g_nCtrMaxEvents - nIdx);

        // 1020 milliseconds, 1023 milliseconds,1015 milliseconds,1014 milliseconds,1016 milliseconds
        if (ZG_Ctr_ReadEvents(this->hCtr, nIdx, &aEvents[i], nCnt, NULL, NULL) != S_OK)
        {
            qDebug() << "Ошибка ZG_Ctr_ReadEvents";
            return;
        }

        // 4 milliseconds,0 milliseconds,1 milliseconds
        for (j = 0; j < nCnt; j++)
        {

            pEv = &aEvents[j];
            qDebug() << " {ControllerListener_alternative_windows_hwnd} - pEv->nType=" << pEv->nType;
            switch (pEv->nType)
            {
            case ZG_EV_KEY_DOOR_BLOCK:
            {
                Processing_Event_Button_Open(pEv);
                DWORD nMask = 0x7;
                ZG_Ctr_WriteLockTimes(this->hCtr, nMask, 3000, 0, 0, 0);
                ZG_Ctr_OpenLock(this->hCtr, 0);
            }
            break;
            case ZG_EV_BUT_OPEN:
            {
                Processing_Event_Button_Open(pEv);
            }
            break;
            case ZG_EV_ELECTRO_ON:
            case ZG_EV_ELECTRO_OFF:
            {
                Processing_Event_Change_Electro(pEv);
            }
            break;
            case ZG_EV_FIRE_STATE:
            {
                Processing_Event_Fire_State(pEv);
            }
            break;
            case ZG_EV_SECUR_STATE:
            {
            }
            break;
            case ZG_EV_MODE_STATE:
            {
                Processing_Event_Mode_State(pEv);
            }
            break;
            case ZG_EV_KEY_OPEN:
            case ZG_EV_KEY_ACCESS:
            {
                Processing_Event_Key(pEv);
            }
            break;
            // Если не известный ключ то
            // Сначало срабатывает событие
            // ZG_EV_UNKNOWN_KEY потом ZG_EV_KEY_NOT_FOUND
            case ZG_EV_UNKNOWN_KEY:
            case ZG_EV_KEY_NOT_FOUND:
            {
                // 0 milliseconds,//1 milliseconds//1 milliseconds
                Processing_Event_Unknown_Key(pEv);
            }
            break;
            default:
            {
            }
            break;
            }
        }

        i += nCnt;
    }
}

void ControllerListener_alternative_windows_hwnd::ShowEvent(
    PZG_CTR_EVENT pEvent // Событие
)
{
    switch (pEvent->nType)
    {
    case ZG_EV_BUT_OPEN:
    {
        Processing_Event_Button_Open(pEvent);
    }
    case ZG_EV_ELECTRO_ON:
    case ZG_EV_ELECTRO_OFF:
    {
        _ZG_EV_TIME rTime;
        ZG_EC_SUB_EV nSubEvent;
        DWORD nPowerFlags;
        ZG_Ctr_DecodeEcEvent(this->hCtr, pEvent->aData, &rTime, &nSubEvent, &nPowerFlags);

        QJsonObject eventELECTRO;
        eventELECTRO["event"] = 21;
        eventELECTRO["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if (ZG_EV_ELECTRO_ON == pEvent->nType)
            eventELECTRO["type"] = 1;
        else
            eventELECTRO["type"] = 0;
        eventELECTRO["flag"] = int(nPowerFlags);

        QJsonObject event;
        event["id"] = 123456789;
        event["operation"] = "events";
        event["events"] = eventELECTRO;

        emit controller_signal_new_event(event);
    }
    break;
    case ZG_EV_FIRE_STATE:
    {
        _ZG_EV_TIME rTime;
        ZG_FIRE_SUB_EV nSubEvent;
        DWORD nFireFlags;
        ZG_Ctr_DecodeFireEvent(this->hCtr, pEvent->aData, &rTime, &nSubEvent, &nFireFlags);
        QJsonObject eventFIRE_STATE;
        eventFIRE_STATE["event"] = 38;
        eventFIRE_STATE["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        eventFIRE_STATE["flag"] = int(nFireFlags);

        QJsonObject event;
        event["id"] = 123456789;
        event["operation"] = "events";
        event["events"] = eventFIRE_STATE;

        emit controller_signal_new_event(event);
    }
    break;
    case ZG_EV_SECUR_STATE:
    {
    }
    break;
    case ZG_EV_MODE_STATE:
    {
    }
    break;
    case ZG_EV_KEY_OPEN:
    case ZG_EV_KEY_ACCESS:
    {
        Processing_Event_Key(pEvent);
    }
    break;
    // Если не известный ключ то
    // Сначало срабатывает событие
    // ZG_EV_UNKNOWN_KEY потом ZG_EV_KEY_NOT_FOUND
    case ZG_EV_UNKNOWN_KEY:
    case ZG_EV_KEY_NOT_FOUND:
    {
        // 0 milliseconds,//1 milliseconds//1 milliseconds
        Processing_Event_Unknown_Key(pEvent);
    }
    break;
    default:
    {
    }
    break;
    }
}

void ControllerListener_alternative_windows_hwnd::CheckNotifyMsgsAlternative()
{
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - 1";
    fullTimeEvent.start();
    _ZG_CTR_CLOCK pClock;
    Z_KEYNUM pNum;
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2";
    HRESULT Result = ZG_Ctr_ReadRTCState(this->hCtr, &pClock, &this->pWrIndx, &this->pRdIdx, &pNum);
    if (Result != S_OK)
    {
        qDebug() << "ZG_Ctr_ReadRTCState - ошибка";
    }
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - 3";
    int nNewCount;
    if (this->pWrIndx >= this->g_nAppReadEventIdx)
        nNewCount = (this->pWrIndx - this->g_nAppReadEventIdx);
    else
        nNewCount = (this->g_nCtrMaxEvents - this->g_nAppReadEventIdx + this->pWrIndx);
    qDebug() << " {ControllerListener_alternative_windows_hwnd} - 4";

    if (nNewCount > 0)
    {
        qDebug() << " {ControllerListener_alternative_windows_hwnd} - 5";
        QString keycard = QString::fromUtf8(readKeyInBufferHex(pNum).c_str());
        qDebug() << " {ControllerListener_alternative_windows_hwnd} - 6";
        bool keyequal = this->LastKeyCard.compare(keycard, Qt::CaseInsensitive);
        qDebug() << " {ControllerListener_alternative_windows_hwnd} - 7";
        if (keyequal)
        {
            // Новая карта приложенна - значит событие с карточкой
            this->LastKeyCard = keycard;

            QDateTime CurrTime = QDateTime::currentDateTime();
            qDebug() << " {ControllerListener_alternative_windows_hwnd} - 9";
            if (this->CartDtoObject->KeyInController->contains(keycard))
            {
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 10";
                qDebug() << " {Class ControllerListener_alternative_windows_hwnd} -  Карта в контролере существует";
                // Ключ найден, дверь открыта Вход=4 Выход=5
                QJsonObject DataToSend = this->pObjWebJsonApi->ClientEventCard(
                    5, // Ключ найден, дверь открыта Выход=5
                    keycard,
                    CurrTime,
                    0,
                    -1);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 11";

                emit controller_signal_new_event(DataToSend);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 12";
                QJsonDocument doc(DataToSend);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 13";
                emit controller_signal_new_msg(strJson);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 14";
            }
            else
            {
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2:1";
                qDebug() << " {Class ControllerListener_alternative_windows_hwnd} -  Карта в НЕ контролере существует";
                // Ключ не найден в банке ключей Вход=2 Выход=3

                QJsonObject DataToSend = this->pObjWebJsonApi->ClientEventCard(
                    3, // Ключ не найден в банке ключей  Выход=3
                    keycard,
                    CurrTime,
                    0,
                    -1);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2:2";
                emit controller_signal_new_event(DataToSend);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2:3";
                QJsonDocument doc(DataToSend);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2:4";
                emit controller_signal_new_msg(strJson);
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 2:5";
            }
        }
        else
        {

            qDebug() << " {Class ControllerListener_alternative_windows_hwnd} -  Карта старая совпадает с новой  ";
            qDebug() << " {ControllerListener_alternative_windows_hwnd} - 3:1";
            INT nShowCount;
            while (nNewCount > 0)
            {
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 3:2";
                nShowCount = min(nNewCount, 5);
                this->ShowEvents(this->g_nAppReadEventIdx, nShowCount);
                nNewCount -= nShowCount;
                g_nAppReadEventIdx = (g_nAppReadEventIdx + nShowCount) % g_nCtrMaxEvents;
                qDebug() << " {ControllerListener_alternative_windows_hwnd} - 3:3";
            }
        }

        this->g_nAppReadEventIdx = this->pWrIndx;
        qDebug() << "ZG_EV_KEY_NOT_FOUND - Время выполнения функции: " << fullTimeEvent.elapsed() << " миллисекунд";
    }
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Button_Open(PZG_CTR_EVENT pEv)
{
    _ZG_EV_TIME rTime;
    ZG_CTR_DIRECT nDirect;
    INT nKeyIdx, nKeyBank;
    ZG_Ctr_DecodePassEvent(this->hCtr, pEv->aData, &rTime, &nDirect, &nKeyIdx, &nKeyBank);

    QDateTime dateTime;
    dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
    dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

    auto messages_for_send = this->pObjWebJsonApi->ClientOpenButton(dateTime, nDirect);

    emit controller_signal_new_event(messages_for_send);

    QJsonDocument doc(messages_for_send);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    emit controller_signal_new_msg(strJson);
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Key(PZG_CTR_EVENT pEv)
{
    _ZG_EV_TIME rTime;
    ZG_CTR_DIRECT nDirect;
    INT nKeyIdx, nKeyBank;
    ZG_Ctr_DecodePassEvent(this->hCtr, pEv->aData, &rTime, &nDirect, &nKeyIdx, &nKeyBank);

    QDateTime dateTime;
    dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
    dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

    QJsonObject DataToSend = this->pObjWebJsonApi->ClientCheckAccess(
        this->LastKeyCard,
        1);

    emit controller_signal_new_event(DataToSend);

    //    auto messages_for_send = this->pObjWebJsonApi->ClientEventCard(
    //        pEv->nType,
    //        this->LastKeyCard,
    //        dateTime,
    //        0,
    //        int(nDirect));

    //    emit controller_signal_new_event(messages_for_send);
    //    QJsonDocument doc(messages_for_send);

    QJsonDocument doc(DataToSend);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    emit controller_signal_new_msg(strJson);
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Unknown_Key(PZG_CTR_EVENT pEv)
{
    if (pEv->nType == ZG_EV_UNKNOWN_KEY)
    {
    }
    else
    {
        // Тут мы формируем до конца событие добавляя поля время и сторону где была приложенна карта
        _ZG_EV_TIME rTime;
        ZG_CTR_DIRECT nDirect;
        INT nKeyIdx, nKeyBank;
        ZG_Ctr_DecodePassEvent(this->hCtr, pEv->aData, &rTime, &nDirect, &nKeyIdx, &nKeyBank);

        QDateTime dateTime;
        dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
        dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

        auto messages_for_send = this->pObjWebJsonApi->ClientEventCard(
            ZG_EV_UNKNOWN_KEY,
            this->LastKeyCard,
            dateTime,
            0,
            int(nDirect));

        emit controller_signal_new_event(messages_for_send);

        QJsonDocument doc(messages_for_send);
        QString strJson(doc.toJson(QJsonDocument::Compact));

        emit controller_signal_new_msg(strJson);
    }
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Mode_State(PZG_CTR_EVENT pEv)
{
    _ZG_EV_TIME rTime;
    ZG_CTR_MODE nMode;
    ZG_MODE_SUB_EV nSubEvent;
    ZG_Ctr_DecodeModeEvent(this->hCtr, pEv->aData, &rTime, &nMode, &nSubEvent);

    QDateTime dateTime;
    dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
    dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

    auto messages_for_send = this->pObjWebJsonApi->ClientChangeMode(
        dateTime,
        nMode);

    emit controller_signal_new_event(messages_for_send);

    QJsonDocument doc(messages_for_send);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    emit controller_signal_new_msg(strJson);
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Change_Electro(PZG_CTR_EVENT pEv)
{
    _ZG_EV_TIME rTime;
    ZG_EC_SUB_EV nSubEvent;
    DWORD nPowerFlags;
    ZG_Ctr_DecodeEcEvent(this->hCtr, pEv->aData, &rTime, &nSubEvent, &nPowerFlags);

    QDateTime dateTime;
    dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
    dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

    auto messages_for_send = this->pObjWebJsonApi->ClientChangeElectro(
        dateTime,
        nPowerFlags);

    emit controller_signal_new_event(messages_for_send);

    QJsonDocument doc(messages_for_send);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    emit controller_signal_new_msg(strJson);
}

void ControllerListener_alternative_windows_hwnd::Processing_Event_Fire_State(PZG_CTR_EVENT pEv)
{
    _ZG_EV_TIME rTime;
    ZG_FIRE_SUB_EV nSubEvent;
    DWORD nFireFlags;
    ZG_Ctr_DecodeFireEvent(this->hCtr, pEv->aData, &rTime, &nSubEvent, &nFireFlags);

    QDateTime dateTime;
    dateTime.setDate(QDate(QDate::currentDate().year(), rTime.nMonth, rTime.nDay));
    dateTime.setTime(QTime(rTime.nHour, rTime.nMinute, rTime.nSecond));

    auto messages_for_send = this->pObjWebJsonApi->ClientFireEvent(
        dateTime,
        int(nFireFlags));

    emit controller_signal_new_event(messages_for_send);

    QJsonDocument doc(messages_for_send);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    emit controller_signal_new_msg(strJson);
}
