#ifndef DATABASECONTROLLERPOSTGRESQL_H
#define DATABASECONTROLLERPOSTGRESQL_H

#include <QtSql>

class DatabaseControllerPostgreSQL {
public:
    DatabaseControllerPostgreSQL(const QString& config_file_path = "./config/config.ini");
    QSqlDatabase getConnect();
    QList<QVariantList> getInfoController();
    QList<QVariantList> getInfoActiveAndModeController();
    QString getInfoComport();
    bool getInfoBonusBypass();
    void setInfoBonusBypass(bool setBonus);
    int getModeBySN(int sn);
    int getIndexEventBySN(int sn);
    void setIndexEventBySN(int sn, int index);
    void setIpServer(const QString& ip);
    void setPortServer(int port);
    QString getIpServer();
    int getPortServer();
    int getActiveBySN(int sn);
    int getSendPowerOnBySN(int sn);
    int getPriority(int sn);
    void setSendPowerOnBySN(int sn, int mode);
    void setModeBySN(int sn, int mode);
    void setActiveBySN(int sn, int active);
    void deleteController(int index);
    void updateController(int idVal,
                          int addressVal,
                          int serialVal,
                          const QString& nameVal,
                          int banksVal,
                          int priorityVal,
                          int selectIndex);
    void insertController(int idVal,
                          int addressVal,
                          int serialVal,
                          const QString& nameVal,
                          int banksVal,
                          int priorityVal);
    void insertComport(const QString& comport);
    void updateComport(const QString& comport);
    QString getComport();
    void updateAutoStart(const QString& autoStartEnable);
    bool getAutoStart();

    void setIpClient(const QString &ip);
    QString getIpClient();

private:
    QSqlDatabase database;
};

#endif // DATABASECONTROLLERPOSTGRESQL_H
