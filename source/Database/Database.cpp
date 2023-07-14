#include "./header/Database/Database.h"

#include <QCoreApplication>
#include <QDebug>

DatabaseControllerPostgreSQL::DatabaseControllerPostgreSQL(const QString &config_file_path)
{
    QSettings config(config_file_path, QSettings::IniFormat);

    QString host = config.value("postgresql/host").toString();
    QString port = config.value("postgresql/port").toString();
    QString databaseName = config.value("postgresql/database").toString();
    QString user = config.value("postgresql/user").toString();
    QString password = config.value("postgresql/password").toString();

    Q_ASSERT_X(QSqlDatabase::isDriverAvailable("QPSQL"),
               "Ошибка при иницализации Базы данных",
               "Не могу найти драйвер отвечающий за подключения к базе данных PostgreSql");

    database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName(host);
    database.setPort(port.toInt());
    database.setDatabaseName(databaseName);
    database.setUserName(user);
    database.setPassword(password);

    if (!database.open()) {
        qDebug() << "Failed to connect to PostgreSQL database.";
    }else{
        qDebug() << "Open database successes";
    }
}

QSqlDatabase DatabaseControllerPostgreSQL::getConnect()
{
    return database;
}

QList<QVariantList> DatabaseControllerPostgreSQL::getInfoController()
{
    QSqlQuery query(database);
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
    QString sqlScript = "SELECT id, address_in_converter, serial_number, name_controller, banks, priority, controller.mode, active, send_power_on, index_event  FROM controller";
    query.exec(sqlScript);

    QList<QVariantList> result;
    while (query.next())
    {
        QVariantList row;
        row << query.value(0) << query.value(1) << query.value(2) << query.value(3)
            << query.value(4) << query.value(5)<< query.value(6) << query.value(7)
            << query.value(9);
        result.append(row);
    }

    return result;
}

QList<QVariantList> DatabaseControllerPostgreSQL::getInfoActiveAndModeController()
{
    QSqlQuery query(database);
    QString sqlScript = "SELECT serial_number, active, mode FROM controller";
    query.exec(sqlScript);

    QList<QVariantList> result;
    while (query.next())
    {
        QVariantList row;
        row << query.value(0) << query.value(1) << query.value(2);
        result.append(row);
    }

    return result;
}

QString DatabaseControllerPostgreSQL::getInfoComport()
{
    QSqlQuery query(database);
    QString sqlScript = "SELECT * FROM com_port WHERE id = 0";
    query.exec(sqlScript);
    query.next();

    QString comport = query.value(1).toString();
    qDebug() << "Программа запущена на порту" << comport;

    return comport;
}

bool DatabaseControllerPostgreSQL::getInfoBonusBypass()
{
    QSqlQuery query(database);
    QString sqlScript = "SELECT bonus_bypass FROM bonus_bypass_table WHERE id = 0";
    query.exec(sqlScript);
    query.next();

    return query.value(0).toBool();
}

void DatabaseControllerPostgreSQL::setInfoBonusBypass(bool setBonus)
{
    QSqlQuery query(database);
    query.prepare("UPDATE bonus_bypass_table SET bonus_bypass = ? WHERE id = 0;");
    query.addBindValue(setBonus);
    query.exec();
}

int DatabaseControllerPostgreSQL::getModeBySN(int sn)
{
    QSqlQuery query(database);
    query.prepare("SELECT mode FROM controller WHERE serial_number = ?");
    query.addBindValue(sn);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

int DatabaseControllerPostgreSQL::getIndexEventBySN(int sn)
{
    QSqlQuery query(database);
    query.prepare("SELECT index_event FROM controller WHERE serial_number = ?");
    query.addBindValue(sn);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

void DatabaseControllerPostgreSQL::setIndexEventBySN(int sn, int index)
{
    QSqlQuery query(database);
    query.prepare("UPDATE controller SET index_event = ? WHERE serial_number = ?");
    query.addBindValue(index);
    query.addBindValue(sn);
    query.exec();
}

void DatabaseControllerPostgreSQL::setIpServer(const QString &ip)
{
    QSqlQuery query(database);
    query.prepare("UPDATE credential_server_data SET ip_server = ?");
    query.addBindValue(ip);
    query.exec();
}

void DatabaseControllerPostgreSQL::setIpClient(const QString &ip)
{
    QSqlQuery query(database);
    query.prepare("UPDATE credential_server_data SET ip_client = ?");
    query.addBindValue(ip);
    query.exec();
}

void DatabaseControllerPostgreSQL::setPortServer(int port)
{
    QSqlQuery query(database);
    query.prepare("UPDATE credential_server_data SET port_server = ?");
    query.addBindValue(port);
    query.exec();
}



QString DatabaseControllerPostgreSQL::getIpServer()
{
    QSqlQuery query(database);
    query.exec("SELECT ip_server FROM credential_server_data");
    query.next();

    return query.value(0).toString();
}



int DatabaseControllerPostgreSQL::getPortServer()
{
    QSqlQuery query(database);
    query.exec("SELECT port_server FROM credential_server_data");
    query.next();

    return query.value(0).toInt();
}

int DatabaseControllerPostgreSQL::getActiveBySN(int sn)
{
    QSqlQuery query(database);
    query.prepare("SELECT active FROM controller WHERE serial_number = ?");
    query.addBindValue(sn);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

int DatabaseControllerPostgreSQL::getSendPowerOnBySN(int sn)
{
    QSqlQuery query(database);
    query.prepare("SELECT send_power_on FROM controller WHERE serial_number = ?");
    query.addBindValue(sn);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

int DatabaseControllerPostgreSQL::getPriority(int sn)
{
    QSqlQuery query(database);
    query.prepare("SELECT priority FROM controller WHERE serial_number = ?");
    query.addBindValue(sn);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

void DatabaseControllerPostgreSQL::setSendPowerOnBySN(int sn, int mode)
{
    QSqlQuery query(database);
    query.prepare("UPDATE controller SET send_power_on = ? WHERE serial_number = ?");
    query.addBindValue(mode);
    query.addBindValue(sn);
    query.exec();
}

void DatabaseControllerPostgreSQL::setModeBySN(int sn, int mode)
{
    QSqlQuery query(database);
    query.prepare("UPDATE controller SET mode = ? WHERE serial_number = ?");
    query.addBindValue(mode);
    query.addBindValue(sn);
    query.exec();
}

void DatabaseControllerPostgreSQL::setActiveBySN(int sn, int active)
{
    QSqlQuery query(database);
    query.prepare("UPDATE controller SET active = ? WHERE serial_number = ?");
    query.addBindValue(active);
    query.addBindValue(sn);
    query.exec();
}

void DatabaseControllerPostgreSQL::deleteController(int index)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM controller WHERE id = ?");
    query.addBindValue(index);
    query.exec();
}

void DatabaseControllerPostgreSQL::updateController(int idVal, int addressVal, int serialVal, const QString &nameVal, int banksVal, int priorityVal, int selectIndex)
{
    QSqlQuery query(database);
    query.prepare("UPDATE controller SET address_in_converter = ?, serial_number = ?, name_controller = ?, banks = ?, priority = ? WHERE id = ?");
    query.addBindValue(addressVal);
    query.addBindValue(serialVal);
    query.addBindValue(nameVal);
    query.addBindValue(banksVal);
    query.addBindValue(priorityVal);
    query.addBindValue(selectIndex);
    query.exec();
}

void DatabaseControllerPostgreSQL::insertController(int idVal, int addressVal, int serialVal, const QString &nameVal, int banksVal, int priorityVal)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO controller (id, address_in_converter, serial_number, name_controller, banks, priority) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(idVal);
    query.addBindValue(addressVal);
    query.addBindValue(serialVal);
    query.addBindValue(nameVal);
    query.addBindValue(banksVal);
    query.addBindValue(priorityVal);
    query.exec();
}

void DatabaseControllerPostgreSQL::insertComport(const QString &comport)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO com_port (id, index_comport) VALUES (0, ?)");
    query.addBindValue(comport);
    query.exec();
}

void DatabaseControllerPostgreSQL::updateComport(const QString &comport)
{
    QSqlQuery query(database);
    query.prepare("UPDATE com_port SET index_comport = ? WHERE id = 0");
    query.addBindValue(comport);
    query.exec();
}

QString DatabaseControllerPostgreSQL::getComport()
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM com_port WHERE id = ?");
    query.addBindValue(0);
    query.exec();
    query.next();

    return query.value(1).toString();
}

void DatabaseControllerPostgreSQL::updateAutoStart(const QString &autoStartEnable)
{
    QSqlQuery query(database);
    query.prepare("UPDATE auto_start SET auto_start_enable = ? WHERE id = 0");
    query.addBindValue(autoStartEnable);
    query.exec();
}

bool DatabaseControllerPostgreSQL::getAutoStart()
{
    QSqlQuery query(database);
    query.prepare("SELECT auto_start_enable FROM auto_start WHERE id = ?");
    query.addBindValue(0);
    query.exec();
    query.next();

    return query.value(0).toBool();
}

QString DatabaseControllerPostgreSQL::getIpClient()
{
    QSqlQuery query(database);
    query.exec("SELECT ip_client FROM credential_server_data");
    query.next();

    return query.value(0).toString();
}
