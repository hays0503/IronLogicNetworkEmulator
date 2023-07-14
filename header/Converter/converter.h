#ifndef CONVERTER_H
#define CONVERTER_H

#include "header/Controller/controller.h"
#include "header/IronLogicDependency/Utils.h"

//#include <QThread>
#include <QString>
#include <QMap>
#include <QObject>

class Converter : public QObject
{
    Q_OBJECT
public:
    Converter(LPCWSTR CvtPortName);

    int AddNewController(int PhisicalAdressInConverter,
                          const QObject *receiver,
                          const int DefaultPassDirection,
                         DatabaseControllerPostgreSQL *database);

    void subscriptionController(const QObject *receiver,qint32 SerialNumberController);

    QMap<qint32,Controller*> MapControllers;

    ~Converter();
private:
    //Инициализация
    CZGuardLoader* oZGL;
    LPCWSTR CvtPortName;
    const ZP_PORT_TYPE CvtPortType = ZP_PORT_COM;

    //Контролер HANDLE
    HANDLE hCvt;


};

#endif // CONVERTER_H
