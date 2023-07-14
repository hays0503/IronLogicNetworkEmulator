#ifndef CONVERTERWORKERTHREAD_H
#define CONVERTERWORKERTHREAD_H

#include "qthread.h"
#include <QObject>
#include "header/Converter/converter.h"
#include "header/Database/Database.h"

class ConverterWorkerThread : public QThread
{
    Q_OBJECT

public:

    QObject *MainWindow;
    const char *MainWindowMemberSignal;

    ConverterWorkerThread(QObject *MainWindow,
                          QObject *HttpServer,
                          DatabaseControllerPostgreSQL *pDatabaseController);
    ~ConverterWorkerThread();
    void run();

    Converter* ConverterObject;

    DatabaseControllerPostgreSQL *DatabaseController;


public slots:

    void slot_CWT_lisen_Controller(qint32 SerialNumberController);

    void slot_CWT_set_active(qint32 SerialNumberController, QString text);

    void slot_CWT_open_door(qint32 SerialNumberController, QString text);

    void slot_CWT_set_mode(qint32 SerialNumberController, qint32 mode);

    void slot_CWT_set_timezone(qint32 SerialNumberController, QString text);

    void slot_CWT_set_door_params(qint32 SerialNumberController, QString text);

    void slot_CWT_add_cards(qint32 SerialNumberController, QString Card);

    void slot_CWT_del_cards(qint32 SerialNumberController, QString Card);

    void slot_CWT_clear_cards(qint32 SerialNumberController);

    void slot_CWT_read_cards(qint32 SerialNumberController);

    void slot_CWT_update_bank_cards(qint32 SerialNumberController);

};



#endif // CONVERTERWORKERTHREAD_H
