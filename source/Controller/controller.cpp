#include "header/Controller/controllerutility.h"
#include "header/IronLogicDependency/ZGuard.h"
#include "header/Controller/controller.h"
#include <QProgressDialog>
#include <vector>


Controller::Controller(HANDLE hCvt,
                       int PhisicalAdressInConverter,
                       const int DefaultPassDirection,
                       DatabaseControllerPostgreSQL *database)
{


    this->CartDtoObject = new CartDto();
    this->CartDtoObject->KeyInController = new QHash<QString, CardDtoAndIndex>;
    this->CartDtoObject->EmptyKeyIndexInController = new QList<int>;

    this->rCtrInfo = new _ZG_CTR_INFO;
    ZeroMemory(rCtrInfo, sizeof(*rCtrInfo));

    HRESULT Result = ZG_Ctr_Open(&this->hCtr,
                                 hCvt,
                                 PhisicalAdressInConverter,
                                 0,
                                 rCtrInfo,
                                 ZG_CTR_UNDEF);

    qDebug() << " {Class Controller} -  Result ZG_Ctr_Open" << Result;

    if (Result != S_OK)
    {
        switch (Result)
        {
        // E_INVALIDARG 80070057h Неправильные параметры.
        case -2147024809:
        {
            Q_ASSERT_X(Result!=S_OK,
                       "Ошибка с Контролером",
                       "Не могу открыть конроллер");
            qDebug() << " {Class Controller} -  ZG_Initialize: Access denied.";
            qDebug() << " {Class Controller} -  Run another program ?????";
            throw std::exception(" {Class Controller}- ZG_Ctr_Open: Access denied");
            break;
        }
        default:
        {
            Q_ASSERT_X(Result!=S_OK,
                       "Ошибка с Контролером",
                       "Не могу открыть конроллер - Не известная ошибка");
            qDebug() << " {Class Controller} -  ZG_Ctr_Open - Unknow error / Не известная ошибка";
            throw std::exception(" {Class Controller}- ZG_Ctr_Open -Unknow error / Не известная ошибка");
            break;
        }
        };
    }

    this->SerialNumberController = rCtrInfo->nSn;

    QDateTime CurrTime = QDateTime::currentDateTime();

    auto CurrData = CurrTime.date();

    _ZG_CTR_CLOCK Clock = {
        false,
        static_cast<WORD>(CurrData.year()),          // Год
        static_cast<WORD>(CurrData.month()),         // месяц
        static_cast<WORD>(CurrData.day()),           // день
        static_cast<WORD>(CurrTime.time().hour()),   // час
        static_cast<WORD>(CurrTime.time().minute()), // минута
        static_cast<WORD>(CurrTime.time().second())  // секунда
    };

    if (ZG_Ctr_SetClock(this->hCtr, &Clock)!=S_OK)
    {
        Q_ASSERT_X(Result!=S_OK,
                   "Ошибка с Контролером",
                   "Не удалось синхронезировате время на контролере");
        qDebug() << " {Class Controller} - ZG_Ctr_SetClock Не удалось синхронезировате время на контролере: " << rCtrInfo->nSn;
        return;
    }

    INT nRdIdx;
    ZG_Ctr_ReadEventIdxs(this->hCtr, &this->g_nAppReadEventIdx, &nRdIdx);

    this->g_nCtrMaxEvents = rCtrInfo->nMaxEvents;
    this->g_fProximity = (rCtrInfo->nFlags & ZG_CTR_F_PROXIMITY) != 0;

    bThreadActive = true;

    qDebug() << " {Class Controller} -  bThreadActive = true;";

    switch (database->getPriority(this->rCtrInfo->nSn)) {

    //На основе быстрого обхода по контролеру 500мс на один контролер
    //Время на срабатывание событие
    //(n-мс * на количество контролеров прямым опросом)+ Время на расшифровку (500мс на один контролер)
    case 1:
        {
            _ZG_CTR_NOTIFY_SETTINGS rNS = {0};
            this->objectControllerListener = new ControllerListenerAlternative(rNS.hEvent,
                                                                               this->hCtr,
                                                                               rCtrInfo,
                                                                               this->CartDtoObject,
                                                                               DefaultPassDirection,
                                                                               database);
        }
        break;
    //Событие на основе подписок на событие
    //Время на срабатывание событие(800мс)+ Время на расшифровку (500мс на один контролер)
    case 0:
        {
            if (this->hEvent == nullptr)
            this->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            _ZG_CTR_NOTIFY_SETTINGS rNS = {0};
            rNS.nNMask = ZG_NF_CTR_NEW_EVENT;
            rNS.hEvent = this->hEvent;
            rNS.nReadEvIdx = this->g_nAppReadEventIdx;
            rNS.nCheckStatePeriod = 50;

            Result = ZG_Ctr_SetNotification(this->hCtr, &rNS);
            if (Result != S_OK)
            {
            Q_ASSERT_X(Result!=S_OK,
                       "Ошибка с Контролером",
                       "Не удалось создать подписку на событие");
            qDebug() << " {Class Controller} -  Result ZG_Ctr_SetNotification" << Result;
            throw std::exception(" {Class Controller} ZG_Ctr_Open: Access denied");
            }
            this->objectControllerListener = new ControllerListener(rNS.hEvent,
                                                                    this->hCtr,
                                                                    rCtrInfo,
                                                                    this->CartDtoObject,
                                                                    DefaultPassDirection,
                                                                    database);
        }
        break;
    //Событие на основе подписок на событие (окна)
    //Время на срабатывание событие(800мс)+ Время на расшифровку (500мс на один контролер)
    case 2:
        {
            HWND hWnd = FindWindowEx(nullptr, nullptr, nullptr, L"MainWindow");

            _ZG_CTR_NOTIFY_SETTINGS rNS = {0};

            rNS.hWnd = hWnd;
            rNS.nWndMsgId = WM_USER + 1;
            rNS.nNMask = ZG_NF_CTR_NEW_EVENT;
            rNS.nReadEvIdx = this->g_nAppReadEventIdx;
            rNS.nCheckStatePeriod = 300;

            Result = ZG_Ctr_SetNotification(this->hCtr, &rNS);
            if (Result != S_OK)
            {
            Q_ASSERT_X(Result!=S_OK,
                       "Ошибка с Контролером",
                       "Не удалось создать подписку на событие");
            qDebug() << " {Class Controller} -  Result ZG_Ctr_SetNotification" << Result;
            throw std::exception(" {Class Controller} ZG_Ctr_Open: Access denied");
            }

            this->objectControllerListener = new ControllerListener_alternative_windows_hwnd(
                rNS.hEvent,
                this->hCtr,
                rCtrInfo,
                this->CartDtoObject,
                DefaultPassDirection,
                database);
        }
        break;
    default:
        break;
    }

};

void Controller::StartControllerListener()
{
    qDebug() << " {Class Controller} -  this->objectControllerListener = new ControllerListener(rNS.hEvent,this->hCtr);";
    this->objectControllerListener->moveToThread(&this->hThread);
    qDebug() << " {Class Controller} -  this->objectControllerListener->moveToThread(&this->hThread);";
    this->objectControllerListener->start();
    qDebug() << " {Class Controller} -  this->objectControllerListener->start();";
}

void Controller::StopControllerListener()
{
    this->objectControllerListener->setBThreadActive(false);
    this->objectControllerListener->quit();
    this->objectControllerListener->wait();

    delete this->rCtrInfo;

    delete this->CartDtoObject->EmptyKeyIndexInController;
    delete this->CartDtoObject->KeyInController;
    delete this->CartDtoObject;
};

// Функция для получения списка свободных индексов
QList<int> Controller::getFreeIndexes(const QSet<int> &occupiedIndexes, int totalKeys)
{
    QList<int> allIndexes;
    QList<int> freeIndexes;

    // Заполняем список allIndexes значениями от 0 до totalKeys-1
    for (int i = 0; i < totalKeys; ++i)
    {
        allIndexes.append(i);
    }

    // Ищем свободные индексы
    for (int index : allIndexes)
    {
        // Проверяем, содержится ли индекс в множестве занятых индексов
        if (!occupiedIndexes.contains(index))
        {
            // Если индекс не найден в множестве занятых индексов, добавляем его в список свободных индексов
            freeIndexes.append(index);
        }
    }

    return freeIndexes;
}

void Controller::GetAllKeyInController()
{
    qDebug() << " {Class Controller} -  GetAllKeyInController Начало:";

    ZG_ENUMCTRKEYSPROC ReadAllKeyLightWeight = [](INT nIdx,
                                                  PZG_CTR_KEY pKey,
                                                  INT nPos,
                                                  INT nMax,
                                                  PVOID pUserData) -> BOOL
    {
//        qDebug() << " {Class Controller} -  GetAllKeyInController 3:1";
        CartDto *pCartDto = static_cast<CartDto *>(pUserData);
//        qDebug() << " {Class Controller} -  GetAllKeyInController 3:2";
        QString KeyString = QString::fromStdString(readKeyInBufferHex(pKey->rNum));
//        qDebug() << " {Class Controller} -  GetAllKeyInController 3:3";

        if (pKey->fErased)
        {
//            qDebug() << " {Class Controller} -  GetAllKeyInController 3:4";
            pCartDto->EmptyKeyIndexInController->push_back(nIdx);
//            qDebug() << " {Class Controller} -  GetAllKeyInController 3:4:1";
        }
        else
        {
//            qDebug() << " {Class Controller} -  GetAllKeyInController 3:5";
            pCartDto->KeyInController->insert(KeyString, CardDtoAndIndex(qint32(nIdx), *pKey));
//            qDebug() << " {Class Controller} -  GetAllKeyInController 3:5:1";
        }
        return true;
    };

//    qDebug() << " {Class Controller} -  GetAllKeyInController 1:";

    if (!CartDtoObject->KeyInController->isEmpty())
        CartDtoObject->KeyInController->clear();

//    qDebug() << " {Class Controller} -  GetAllKeyInController 2:";

    if (!CartDtoObject->EmptyKeyIndexInController->isEmpty())
        CartDtoObject->EmptyKeyIndexInController->clear();

//    qDebug() << " {Class Controller} - GetAllKeyInController 3:";

    try
    {
        HRESULT Result = ZG_Ctr_EnumKeys(this->hCtr,
                                         0,
                                         ReadAllKeyLightWeight,
                                         (void *)this->CartDtoObject,
                                         0);
        if (Result != S_OK)
        {
            Q_ASSERT_X(Result!=S_OK,
                       "Ошибка с Контролером",
                       "Произошла ошибка при считывание ключей");
            qDebug() << " {Class Controller} -  Произошла ошибка при считывание ключей";
            qDebug() << " {Class Controller} - Result ZG_Ctr_EnumKeys  " << Result;
            throw std::runtime_error("Span is not found!");
        }
        else
        {
            qDebug() << " {Class Controller} - Result ZG_Ctr_EnumKeys  " << Result;
        }

//        qDebug() << " {Class Controller} -  GetAllKeyInController 4:";

        // Считаем свободные индексы(попытка ускорить добавление ключей)
        QList<qint32> indexWriteCards;
        for (auto Card : CartDtoObject->KeyInController->values())
        {
            indexWriteCards.push_back(Card.indexInController);
        }

//        qDebug() << " {Class Controller} -  GetAllKeyInController 5:";

        for (qint32 i = 0; i < rCtrInfo->nMaxKeys; ++i)
        {
            if (!indexWriteCards.contains(i))
            {
                CartDtoObject->EmptyKeyIndexInController->push_back(i);
            };
        };

//        qDebug() << " {Class Controller} -  GetAllKeyInController 6:";

        const QList Keys = CartDtoObject->KeyInController->keys();
        qint32 sn = this->SerialNumberController;
        QVariant KeysVariant = QVariant(Keys);

//        qDebug() << " {Class Controller} -  GetAllKeyInController 7:";

        emit controller_update_card(sn, KeysVariant);

        qDebug() << " {Class Controller} -  GetAllKeyInController Конец:";
    }
    catch (const std::exception &e)
    {
        Q_ASSERT_X(false,
                   "Ошибка с Контролером",
                   "Произошла ошибка при считывание ключей - не удалось выполнить операцию ");
        qDebug() << e.what();
    }


}

void Controller::OpenDoor()
{
    qDebug() << " {Class Controller} - --------OpenDoor----------------";
    qDebug() << " {Class Controller} -  Сигнал дошел до адресата: " << this->SerialNumberController;
    qDebug() << " {Class Controller} -  Адресс: " << this->hCtr;
    qDebug() << "-------------------------";
    ZG_Ctr_OpenLock(this->hCtr, 0);
}

void Controller::SetModeBlock(qint32 mode)
{
    switch (mode)
    {
    case ZG_MODE_NORMAL:
    {
        ZG_Ctr_SetCtrMode(this->hCtr, ZG_MODE_NORMAL);
        qDebug() << " {Class Controller} -  Установлен режим: Норма ";
    }
    break;
    case ZG_MODE_BLOCK:
    {
        ZG_Ctr_SetCtrMode(this->hCtr, ZG_MODE_BLOCK);
        qDebug() << " {Class Controller} -  Установлен режим: Блокировка ";
    }
    break;
    case ZG_MODE_FREE:
    {
        ZG_Ctr_SetCtrMode(this->hCtr, ZG_MODE_FREE);
        qDebug() << " {Class Controller} -  Установлен режим: Свободный проход ";
    }
    break;
    case ZG_MODE_WAIT:
    {
        ZG_Ctr_SetCtrMode(this->hCtr, ZG_MODE_WAIT);
        qDebug() << " {Class Controller} -  Установлен режим: Ожидание свободного прохода ";
    }
    break;
    }
}

void Controller::tryDeleteCard(QString Card)
{

    qDebug() << " {Class Controller} -  Controller::tryDeleteCard(QString " << Card << ")";

    if (CartDtoObject->KeyInController->contains(Card))
    {
        // Удаляем ключ (способом установки флага)
        qint32 nBankN = 0;
        CardDtoAndIndex deletedCard = CartDtoObject->KeyInController->take(Card);

        _ZG_CTR_KEY rKey = {0};
        rKey.fErased = true;

        if (ZG_Ctr_ClearKeys(this->hCtr,
                                           deletedCard.indexInController,
                                           1,
                                           nullptr,
                                           nullptr,
                                           nBankN)
                          !=S_OK)
        {
            Q_ASSERT_X(false,
                       "Ошибка с Контролером",
                       "Произошла ошибка при удаление ключа - не удалось выполнить операцию ");
            qDebug() << "\n\n\n{Class Controller} - {DLLINFO} Ошибка при удаление ключа   =>" << Card << "\n\n\n";
            return;
        }

        qDebug() << "\n\n\{Class Controller} - {DLLINFO} Ключ удален успешно ключ =>" << Card << "index: " << deletedCard.indexInController << "\n\n\n";
        const QList Keys = CartDtoObject->KeyInController->keys();
        qint32 sn = this->SerialNumberController;
        QVariant KeysVariant = QVariant(Keys);

        emit controller_update_card(sn, KeysVariant);
    }
    else
    {
        qDebug() << " {Class Controller} -  Карта в контролере не существует - отменяем удаление нечего удалять";
        return;
    }
}

void Controller::Listen_Controller()
{
#ifdef Listener_alternative_windows_hwnd
    qDebug() << " {Controller} - this->objectControllerListener->CheckNotifyMsgsAlternative()";

    try
    {
        qDebug() << " {Controller} - if(this->objectControllerListener != nullptr)";
        if (this->objectControllerListener != nullptr)
        {
            qDebug() << " {Controller} - this->objectControllerListener:" << this->objectControllerListener;
            this->objectControllerListener->CheckNotifyMsgsAlternative();
        }
        else
        {
            qDebug() << " {Controller} - Error this->objectControllerListener == nullptr";
        }
    }
    catch (std::exception &e)
    {
        qDebug("Error  - Listen_Controller ", e.what());
    }

#endif
}

void Controller::tryAddCard(QString Card)
{
    qDebug() << " {Class Controller} -  Controller::tryAddCard(QString " << Card << ")";

    if (CartDtoObject->KeyInController->contains(Card))
    {
        qDebug() << " {Class Controller} -  Карта в контролере существует";
        return;
    }
    else
    {
        unsigned int x;
        stringstream ss;
        ss << std::hex << Card.toStdString();
        ss >> x;
        std::byte bytes[sizeof x];
        std::copy(
            static_cast<const std::byte *>(static_cast<const void *>(&x)),
            static_cast<const std::byte *>(static_cast<const void *>(&x)) + sizeof x,
            bytes);
        std::reverse(bytes, bytes + sizeof x);

        _ZG_CTR_KEY rKey = {0}; //{ false, Num, ZG_KEY_NORMAL, ZG_KF_SHORTNUM, 0xFFh, aData1 };

        rKey.rNum[4] = bytes[0];
        rKey.rNum[3] = bytes[1];
        rKey.rNum[2] = bytes[2];
        rKey.rNum[1] = bytes[3];
        rKey.rNum[0] = std::byte(6);

        rKey.aData1[0] = 0x00;
        rKey.aData1[1] = 0x00;
        rKey.aData1[2] = 0x00;
        rKey.aData1[3] = 0x00;
        rKey.fErased = false;
        rKey.nType = ZG_KEY_NORMAL;
        rKey.nFlags = ZG_KF_SHORTNUM;
        rKey.nAccess = 0xFF;

        int nBankN = 0;
        int nKeyIdx = -1;

        if (!CartDtoObject->EmptyKeyIndexInController->empty())
        {

            nKeyIdx = CartDtoObject->EmptyKeyIndexInController->takeFirst();

            if (ZG_Ctr_WriteKeys(this->hCtr,nKeyIdx,&rKey,1,NULL,NULL,nBankN)!=S_OK){
                Q_ASSERT_X(false,
                           "Ошибка с Контролером",
                           "Произошла ошибка при добавление ключа - не удалось выполнить операцию ");
                return;
            }
            qDebug() << " {Class Controller} -  {DLLINFO} Ключ добавлен!\n";
            CartDtoObject->KeyInController->insert(Card, CardDtoAndIndex(nKeyIdx, rKey));
        }
        else
        {
            qDebug() << " {Class Controller} -  Задержка для коректной записи ключа: Начало";
            QThread::msleep(1500);
            qDebug() << " {Class Controller} -  Задержка для коректной записи ключа: Конец";
            if (ZG_Ctr_GetKeyTopIndex(this->hCtr,&nKeyIdx,nBankN) !=S_OK)
            {
                Q_ASSERT_X(false,
                           "Ошибка с Контролером",
                           "Произошла ошибка при добавление ключа - Не предведеный выход из функции добавление ключей - проблема с запросом верхней границы ключей ");
                qDebug() << "\nController - {DLLINFO} Не предведеный выход из функции добавление ключей\n";
                return;
            }

            qDebug() << " {Class Controller} -  {DLLINFO} nKeyIdx: " << nKeyIdx << '\n';

            if (ZG_Ctr_WriteKeys(this->hCtr,nKeyIdx,&rKey,1,NULL,NULL,nBankN) != S_OK)
            {
                Q_ASSERT_X(false,
                           "Ошибка с Контролером",
                           "Произошла ошибка при добавление ключа - не удалось выполнить операцию записи ключа");
                return;
            }
            qDebug() << " {Class Controller} - {DLLINFO} Ключ добавлен!\n";
            CartDtoObject->KeyInController->insert(Card, CardDtoAndIndex(nKeyIdx, rKey));
        }

        const QList Keys = CartDtoObject->KeyInController->keys();
        qint32 sn = this->SerialNumberController;
        QVariant KeysVariant = QVariant(Keys);

        emit controller_update_card(sn, KeysVariant);
    }
}



const ControllerListenerRoot* Controller::getObjectControllerListener()
{
    qDebug() << objectControllerListener;
    return this->objectControllerListener;
}

void Controller::ClearCards()
{

    // Стираем все ключи
    if(ZG_Ctr_ClearKeys(this->hCtr,
                     0,
                     MAXINT,
                     nullptr,
                     NULL,
                         0) != S_OK)
    {
        Q_ASSERT_X(false,
                   "Ошибка с Контролером",
                   "Произошла ошибка при удаление ключа - не удалось выполнить операцию удаление ключа");
    }
    // Если два банка в контроллере
    if (this->rCtrInfo->nFlags == ZG_CTR_F_2BANKS)
    {
        if(ZG_Ctr_ClearKeys(this->hCtr,
                             0,
                             MAXINT,
                             nullptr,
                             NULL,
                             1) != S_OK)
        {
            Q_ASSERT_X(false,
                       "Ошибка с Контролером",
                       "Произошла ошибка при удаление ключа - не удалось выполнить операцию удаление ключа (второй банк ключей)");
        }
    }
    this->CartDtoObject->KeyInController->clear();

    this->GetAllKeyInController();
}
