#include "header/Server/clienthttp.h"
#include "qjsonarray.h"
#include <QJsonDocument>

ClientHttp::ClientHttp(QString adressClient,
                       QObject *parent)
{
    this->adress = adressClient;
    qDebug()<<"AdressClient "<<adress;
    //    this->adress = "http://192.168.0.63";
    // Создание объекта QNetworkAccessManager

    this->manager = new QNetworkAccessManager(this);
}

void ClientHttp::sendEvent(QJsonObject json)
{
    // Тут добавим проверку что всё правильно

    // Подготовка к отправке
    QByteArray jsonData = QJsonDocument(json).toJson();

    // Создание запроса
    QNetworkRequest request((QUrl(adress)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Отправка запроса с данными JSON
    this->reply = manager->post(request, jsonData);

    // Обработка ответа
    QObject::connect(reply, &QNetworkReply::finished, [&]()
                     {

        if (reply->error() == QNetworkReply::NoError)
        {
            // Запрос успешно выполнен
            QByteArray responseData = reply->readAll();
            // Обработка полученных данных
            qDebug() << "Response data:" << responseData;
            // Конвертируем в json
            QJsonDocument document = QJsonDocument::fromJson(responseData);
            qDebug() << "document data:"<<document;
            QJsonArray messages = document["messages"].toArray();
            qDebug() << "messages data:"<<messages;
            // Ответ:
            //            {
            //                         "date": "2023-07-05 15:41:01",
            //                         "interval": 10,
            //                         "sn": 4225,
            //                         "messages": [
            //                                          {
            //                                              "id": 123456789,
            //                                              "operation": "check_access",
            //                                              "granted": 0
            //                                          }
            //                ]
            //            }

            foreach (auto  msg, messages) {
                auto object_json = msg.toObject();
                if (object_json["operation"] == "check_access")
                {
                    if (object_json["granted"] == 0)
                    {
                        qDebug() << "Access granted";
                        emit signals_accessGranted(document["sn"].toInt());
                    }
                    else
                    {
                        qDebug() << "Access denied";
                    }
                }
                else
                {
                    // Возникла ошибка при выполнении запроса
                    qDebug() << "Error:" << reply->errorString();
                }
            };
            // Освобождение ресурсов
            reply->deleteLater();
        } });
}
