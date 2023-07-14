#include "header/Converter/ConverterWorkerThread.h"
#include "header/Converter/converter.h"
#include <QObject>
#include "qdebug.h"


ConverterWorkerThread::ConverterWorkerThread(QObject *MainWindow,
                                             QObject *HttpServer,
                                             DatabaseControllerPostgreSQL *pDatabaseController)
{

    this->MainWindow = MainWindow;

    this->DatabaseController = pDatabaseController;

    QObject::connect(MainWindow,
                     SIGNAL(open_door(qint32,QString)),
                     this,
                     SLOT(slot_CWT_open_door(qint32,QString)));

    QObject::connect(MainWindow,
                     SIGNAL(signal_update_cards(qint32,QVariant)),
                     HttpServer,
                     SLOT(slots_WebJsonApiServer_update_cards(qint32,QVariant)));

    #ifdef Listener_alternative_windows_hwnd

        QObject::connect(
            MainWindow,
            SIGNAL(signal_Lisen_Controller(qint32)),
            this,
            SLOT(slot_CWT_lisen_Controller(qint32))
            );

    #endif

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_open_door(qint32,QString)),
                     this,
                     SLOT(slot_CWT_open_door(qint32,QString)));

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_set_mode(qint32,qint32)),
                     this,
                     SLOT(slot_CWT_set_mode(qint32,qint32)));

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_clear_cards(qint32)),
                     this,
                     SLOT(slot_CWT_clear_cards(qint32)));

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_add_cards(qint32,QString)),
                     this,
                     SLOT(slot_CWT_add_cards(qint32,QString)));

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_del_cards(qint32,QString)),
                     this,
                     SLOT(slot_CWT_del_cards(qint32,QString)));

    QObject::connect(HttpServer,
                     SIGNAL(signal_WebJsonApiServer_update_bank_cards(qint32)),
                     this,
                     SLOT(slot_CWT_update_bank_cards(qint32)));

}

ConverterWorkerThread::~ConverterWorkerThread()
{
    foreach (auto ControllerListener, this->ConverterObject->MapControllers) {
        ControllerListener->StopControllerListener();
    }
    delete ConverterObject;
}

void ConverterWorkerThread::run()
{
    try {
        this->ConverterObject = new Converter(L"COM6");
    }
    catch (QString e) {
        qDebug()<<" {ConverterWorkerThread} - Ошибка инициализации ConverterObject"<<e;
	}

    auto InfoControlers =  this->DatabaseController->getInfoController();

    QList<int> SerialNumber;

    foreach (auto Controller, InfoControlers) {
        //id:0
        //address_in_converter:1
        //serial_number:2
        //name_controller:3
        //banks:4
        //priority:5
        //controller.mode:6
        //active:7
        //send_power_on:8
        //index_event:9

        int Active = Controller.value(7).toInt();//Active

        if(Active==1)
        {

            int check_correct_sn = this->ConverterObject->AddNewController(
                                                                            Controller.value(1).toInt(),
                                                                            this->MainWindow,
                                                                            1,
                                                                            this->DatabaseController
                                                                            );
            Q_ASSERT_X(check_correct_sn ==Controller.value(2).toInt(),
                       "ConverterWorkerThread - Случилось страшное ошибка при инициализации контроллера\n",
                       "Проверь и сопоставьте серийные номера в базе данных с контроллерами"
                       "и их адресами в конвертере возможна потенциальная ошибка по невнимательности!"
                       );
            if(check_correct_sn !=Controller.value(2).toInt())
            {
                qDebug()<<"The serial number of the controller does not match the serial number in the database";
                qDebug()<<check_correct_sn<<" !=" << Controller.value(2).toInt();
            }


            SerialNumber.emplace_back(Controller.value(2).toInt());//serial_number:2

        }

    };

    foreach (auto Controller, InfoControlers) {
        //id:0
        //address_in_converter:1
        //serial_number:2
        //name_controller:3
        //banks:4
        //priority:5
        //controller.mode:6
        //active:7
        //send_power_on:8
        //index_event:9

        int Active = Controller.value(7).toInt();//Active

        if(Active==1)
        {

            this->ConverterObject->MapControllers.value(SerialNumber.takeFirst())->StartControllerListener();

        }

    };

}

void ConverterWorkerThread::slot_CWT_lisen_Controller(qint32 SerialNumberController)
{
    qDebug() << " {ConverterWorkerThread} - void ConverterWorkerThread::slot_CWT_lisen_Controller(qint32 SerialNumberController)";
    this->ConverterObject->MapControllers.value(SerialNumberController)->Listen_Controller();
}


void ConverterWorkerThread::slot_CWT_set_active(qint32 SerialNumberController, QString text)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_set_active =>"<<text;
    qErrnoWarning("Не реализованна");
}

void ConverterWorkerThread::slot_CWT_open_door(qint32 SerialNumberController,QString text)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_open_door =>"<<text;
    this->ConverterObject->MapControllers.value(SerialNumberController)->OpenDoor();
}

void ConverterWorkerThread::slot_CWT_set_mode(qint32 SerialNumberController, qint32 mode)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_set_mode =>"<<mode;
    this->ConverterObject->MapControllers.value(SerialNumberController)->SetModeBlock(mode);
}

void ConverterWorkerThread::slot_CWT_set_timezone(qint32 SerialNumberController, QString text)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_set_timezone =>"<<text;
    qErrnoWarning("Не реализованна");
}

void ConverterWorkerThread::slot_CWT_set_door_params(qint32 SerialNumberController, QString text)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_set_door_params =>"<<text;
    qErrnoWarning("Не реализованна");
}

void ConverterWorkerThread::slot_CWT_add_cards(qint32 SerialNumberController, QString Card)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_add_cards =>"<<Card;
    this->ConverterObject->MapControllers.value(SerialNumberController)->tryAddCard(Card);
}

void ConverterWorkerThread::slot_CWT_del_cards(qint32 SerialNumberController, QString Card)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_del_cards =>"<<Card;
    this->ConverterObject->MapControllers.value(SerialNumberController)->tryDeleteCard(Card);
}

void ConverterWorkerThread::slot_CWT_clear_cards(qint32 SerialNumberController)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_clear_cards";
    this->ConverterObject->MapControllers.value(SerialNumberController)->ClearCards();

}

void ConverterWorkerThread::slot_CWT_read_cards(qint32 SerialNumberController)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_read_cards";
    qErrnoWarning("Не реализованна");
}

void ConverterWorkerThread::slot_CWT_update_bank_cards(qint32 SerialNumberController)
{
    qDebug()<<"ConverterWorkerThread::slot_CWT_update_bank_cards";
    this->ConverterObject->MapControllers.value(SerialNumberController)->GetAllKeyInController();
}

