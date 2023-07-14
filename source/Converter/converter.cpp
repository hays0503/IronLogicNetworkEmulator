#include "header/Converter/converter.h"
#include "header/IronLogicDependency/ZGuard.h"
#include "qdebug.h"


#include <QObject>


Converter::Converter(LPCWSTR CvtPortName)
{


    this->CvtPortName = CvtPortName;
    this->oZGL = new CZGuardLoader();

    if (!this->oZGL->IsLoaded())
    {
        Q_ASSERT_X(!this->oZGL->IsLoaded(),
                   "Ошибка с SDK Guard",
                   "Не могу загрузить библеотеку ZGuard");
        qDebug() << " {Converter} - Load ZGuard error 0x%X.\n" << this->oZGL->m_nStatus;
        throw std::exception("Problemy s dll vozmozhno ona otsutstvuyet");
    }


    HRESULT Result = ZG_Initialize(ZP_IF_NO_MSG_LOOP);
    qDebug() << " {Converter} - Result ZG_Initialize  " << Result;
    if (Result!=S_OK) {
        Q_ASSERT_X(Result!=S_OK,
                   "Ошибка с SDK Guard",
                   "Не могу провести инициализацию библеотеки ZGuard");
        return;
    }


    _ZG_CVT_OPEN_PARAMS rOp;
    ZeroMemory(&rOp, sizeof(rOp));
    //Тип порта
    rOp.nType = CvtPortType;
    //Имя порта
    rOp.pszName = CvtPortName;
    //Скорость порта
    rOp.nSpeed = ZG_SPEED_57600;

    Result = ZG_Cvt_Open(&this->hCvt, &rOp, NULL);

    if(Result != S_OK){
        Q_ASSERT_X(Result!=S_OK,
                   "Ошибка с Конвертером",
                   "Не могу открыть конвертер");
        qDebug() << " {Converter} - Result ZG_Cvt_Open  " << Result;
        throw std::exception("Problemy okritiem konvertera");
        return;
    }




    _ZP_WAIT_SETTINGS SetWaitSetting = {0};
    SetWaitSetting.nReplyTimeout = 200;
    SetWaitSetting.nMaxTries = 2;
    SetWaitSetting.nCheckPeriod= 200;
    Result = 0;

    _ZP_DD_GLOBAL_SETTINGS pSettings = {0};
    pSettings.rScanWS = SetWaitSetting;
    pSettings.nScanDevPeriod = 200;

    Result = ZP_DD_SetGlobalSettings(&pSettings);
        if(Result!=S_OK)
        {
            qDebug() << " {Class Controller} - Ошибка ZP_DD_SetGlobalSettings";
            qDebug() << Result;
        };



}

int Converter::AddNewController(int PhisicalAdressInConverter,
                                 const QObject *receiver,
                                 const int DefaultPassDirection,
                                DatabaseControllerPostgreSQL *database)
{
    try {
        qDebug()<<"\n {Converter} - Попытка создание контролера:";

        Controller *ObjectController = new Controller(  this->hCvt,
                                                        PhisicalAdressInConverter,
                                                        DefaultPassDirection,
                                                        database);
        qDebug()<<" {Converter} -SerialNumberController: "<<ObjectController->rCtrInfo->nSn;
        qDebug()<<" {Converter} -ObjectController: "<<ObjectController;

        this->MapControllers.insert(ObjectController->rCtrInfo->nSn,ObjectController);

        this->subscriptionController(receiver,ObjectController->rCtrInfo->nSn);

        ObjectController->GetAllKeyInController();

        return ObjectController->rCtrInfo->nSn;

    } catch (std::exception stdexception) {

        Q_ASSERT_X(false,
                   "Ошибка при добавлении контролера",
                   "Произошла ошибка смотри логи консоли");

        qDebug()<<"Случилось исключение "<< stdexception.what();
    }
}


void Converter::subscriptionController(const QObject *receiver,qint32 SerialNumberController)
{
    qDebug()<<"\n {Converter} --Начало--subscriptionController----------";
    qDebug()<<" {Converter} -Серийный номер :"<<SerialNumberController;
    qDebug()<<" {Converter} -Подписался на событие controller_signal_new_msg=>AddTextInList";
    QObject::connect(this->MapControllers.value(SerialNumberController)->getObjectControllerListener(),
                     SIGNAL(controller_signal_new_msg(QString)),
                     receiver,
                     SLOT(AddTextInList(QString)));

    QObject::connect(this->MapControllers.value(SerialNumberController),
                     SIGNAL(controller_update_card(qint32,QVariant)),
                     receiver,
                     SLOT(slots_controller_update_card(qint32,QVariant)));

    //Подписываемся на событие controller_signal_new_event=>sendMessageToClient
    QObject::connect(this->MapControllers.value(SerialNumberController)->getObjectControllerListener(),
                    SIGNAL(controller_signal_new_event(QJsonObject)),
                    receiver,
                    SLOT(sendMessageToClient(QJsonObject)));

    qDebug()<<" {Converter} --Конец--subscriptionController----------";

}


Converter::~Converter()
{
    qDebug()<<" {Converter} -Converter::~Converter()";
    if (hCvt != NULL)
        ZG_CloseHandle(hCvt);
    ZG_Finalyze();
}
