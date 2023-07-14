#include "header/Gui/mainwindow.h"
#include "qassert.h"
#include "ui_mainwindow.h"

#include <QListView>
#include <QStringListModel>
#include <QtConcurrent>
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Получение дескриптора окна Qt
    WId winId = this->winId();
    qDebug() << "Qt window ID:" << winId;

    // Подключение к WinAPI для получения сообщений
    HWND hWnd = reinterpret_cast<HWND>(winId);
    if (SetProp(hWnd, L"MainWindow", this) == FALSE)
    {
        qCritical() << "Failed to set Qt window property";
    }
    this->installEventFilter(this);

    ui->setupUi(this);
    QStringListModel *model = new QStringListModel();
    ui->object_listView->setModel(model);

    // Инициализуриуем объект клиента и сервера
    this->objClient = nullptr;
    this->objServer = nullptr;

    // Если сервер не иницализирован и не запущен , то запускаем его.
    if(this->DatabaseController== nullptr)
    {
        this->DatabaseController = new DatabaseControllerPostgreSQL();

        setDataModelSqlController(ModelSqlConstroller,
                                  ui->tableViewController,
                                  "controller");

        setDataModelSqlController(ModelSqlAutoStartEnable,
                                  ui->tableViewAutoStart,
                                  "auto_start");

        setDataModelSqlController(ModelSqlCredentialServerData,
                                  ui->tableCredentialServerData,
                                  "credential_server_data");

        setDataModelSqlController(ModelSqlComPort,
                                  ui->tableComPort,
                                  "com_port");

        if(this->DatabaseController->getAutoStart())
        {
            RunProgram();
        }

    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddTextInList(QString message)
{
    QStringListModel *model = qobject_cast<QStringListModel *>(ui->object_listView->model());
    if (model)
    {
        QStringList stringList = model->stringList();
        stringList.append(message);
        model->setStringList(stringList);
    }
}

void MainWindow::slots_controller_update_card(qint32 SerialNumberController, QVariant Keys)
{
    qDebug() << " {MainWindow} - MainWindow::slots_controller_update_card(qint32 SerialNumberController, QVariant Keys)";
    qDebug() << " {MainWindow} - SerialNumberController:=" << SerialNumberController << "Keys:=" << Keys;
    emit signal_update_cards(SerialNumberController, Keys);
}

void MainWindow::setDataModelSqlController(
    QSqlTableModel  *Model,
    QTableView *UiTable,
    QString NameTable)
{
    Q_ASSERT(this->DatabaseController->getConnect().isOpen());
    Model = new QSqlTableModel(nullptr,this->DatabaseController->getConnect());
    Model->setTable(NameTable);
    Model->setEditStrategy(QSqlTableModel::OnFieldChange);
    Model->select();
    UiTable->setModel(Model);
    UiTable->setColumnHidden(0, true);
    UiTable->resizeColumnsToContents();
    UiTable->show();
}

void MainWindow::RunProgram()
{
    // Если сервер не иницализирован и не запущен , то запускаем его.
    if(this->DatabaseController!= nullptr)
    {


        // Если сервер не иницализирован и не запущен , то запускаем его.
        if (this->objServer == nullptr)
        {
            this->objServer = new ServerHttp();
        }

        // Если клиент не иницализирован и не запущен , то запускаем его.
        if (this->objClient == nullptr)
        {
            this->objClient = new ClientHttp(this->DatabaseController->getIpClient());
            // this->objClient = new ClientHttp("http://192.168.0.63/");
            // this->objClient = new ClientHttp("http://127.0.0.1:5000/api");
            connect(this->objClient,
                    SIGNAL(signals_accessGranted(int)),
                    this,
                    SLOT(slots_accessGranted(int)));
        }

        // Eсли WS сокен не инициализирован
        if (this->ObjectServerWorkerThread == nullptr)
        {
            this->ObjectServerWorkerThread = new ServerWorkerThread();
            connect(this,
                    SIGNAL(signal_send_msg_ws(QString)),
                    this->ObjectServerWorkerThread,
                    SLOT(slot_send_msg_ws(QString)));

            this->ObjectServerWorkerThread->start();
        }

        if (this->ObjectConverterWorkerThread == nullptr)
        {
            this->ObjectConverterWorkerThread = new ConverterWorkerThread(
                this,
                this->objServer->getObjWebJsonApi(),
                this->DatabaseController);
            this->ObjectConverterWorkerThread->start();
        }
    }{
        Q_ASSERT_X(this->DatabaseController!= nullptr,
                   "Главное окно - \n",
                   "База данных не иницализированна или не доступна ?"
                   );
    }
}

void MainWindow::on_runServerButton_clicked()
{
    RunProgram();
}

void MainWindow::on_endEmulatorButton_clicked()
{
    delete this->ObjectConverterWorkerThread;
    this->ObjectConverterWorkerThread = nullptr;
}

void MainWindow::on_openDoorButton_clicked()
{
    qDebug("---------------------------------");
    qDebug(" emit open_door('opendoor13080')");
    emit open_door(4225, "opendoor13080");
}

void MainWindow::slots_accessGranted(int sn)
{
    emit open_door(sn, "opendoor");
}

void MainWindow::sendMessageToClient(QJsonObject message)
{
    // Отправка сообщение клиенту на сервер
    // Адресс сервера http://127.0.0.1:5000/api

    // Если клиент иницализирован и запущен , то отправляем сообщение.
    if (this->objClient != nullptr)
    {
        this->objClient->sendEvent(message);
    }
    else
    {
        // Клиент не иницализирован и не запущен.
        qDebug() << "Error: objClient == nullptr / Клиент не иницализирован и не запущен.";
    }

    QJsonDocument doc(message);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    emit signal_send_msg_ws(strJson);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    Q_UNUSED(eventType);
    MSG *msg = static_cast<MSG *>(message);

    const UINT TYPEMSG = WM_USER + 1;

    if (msg->message == TYPEMSG)
    {
        emit signal_Lisen_Controller(4225);

        HWND hWnd = msg->hwnd;
        UINT msgId = msg->message;
        WPARAM wParam = msg->wParam;
        LPARAM lParam = msg->lParam;

        // Обработка сообщения из WinAPI
        qDebug() << "Received WinAPI message:"
                 << "hWnd =" << hWnd
                 << "message =" << msgId
                 << "wParam =" << wParam
                 << "lParam =" << lParam;
    }

    // Возвращаем false, чтобы сообщение также обработалось стандартным обработчиком окна
    return QMainWindow::nativeEvent(eventType, message, result);
}
