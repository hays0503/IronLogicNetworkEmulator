#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "header/Converter/ConverterWorkerThread.h"
#include "header/Server/ServerWorkerThread.h"
#include "header/Server/serverwebsocket.h"
#include "header/Converter/converter.h"
#include "header/Database/Database.h"
#include "qtableview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Converter *ConverterObject = nullptr;
    ConverterWorkerThread* ObjectConverterWorkerThread = nullptr;

    ServerWorkerThread* ObjectServerWorkerThread = nullptr;

    ServerHttp *objServer = nullptr;
    ClientHttp *objClient = nullptr;

    DatabaseControllerPostgreSQL *DatabaseController = nullptr;


private slots:
    void AddTextInList(QString message);

    void slots_controller_update_card(qint32 SerialNumberController,
                                   QVariant Keys);

    void on_runServerButton_clicked();

    void on_endEmulatorButton_clicked();

    void on_openDoorButton_clicked();

    void sendMessageToClient(QJsonObject message);

    void slots_accessGranted(int sn);


signals:
    void open_door(qint32 SerialNumberController,QString text);

    void signal_update_cards(qint32 SerialNumberController,
                             QVariant Keys);

    void signal_send_msg_ws(QString text);

    void signal_Lisen_Controller(qint32 SerialNumberController);

private:
    Ui::MainWindow *ui;
    ServerWebSocket *ServerObject;
    QSqlTableModel  *ModelSqlConstroller = nullptr;
    QSqlTableModel  *ModelSqlAutoStartEnable = nullptr;
    QSqlTableModel  *ModelSqlCredentialServerData = nullptr;
    QSqlTableModel  *ModelSqlComPort = nullptr;

    void setDataModelSqlController(
        QSqlTableModel  *Model,
        QTableView *UiTable,
        QString NameTable);

    void RunProgram();




protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;

};
#endif // MAINWINDOW_H
