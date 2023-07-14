#include "header/Server/serverhttp.h"

using namespace Qt::StringLiterals;

ServerHttp::ServerHttp(QObject *parent)
    : QObject(parent)
{
    this->httpServer = new QHttpServer(this);
    this->objWebJsonApi = new WebJsonApiServer();
    this->StartServer();
}


inline QString ServerHttp::host(const QHttpServerRequest &request)
{
    return QString::fromLatin1(request.value("Host"));
}

int ServerHttp::StartServer(){


    httpServer->route("/json", [] {
        return QJsonObject{
            {
                {"key1", "1"},
                {"key2", "2"},
                {"key3", "3"}
            }
        };
    });

    httpServer->route("/",QHttpServerRequest::Method::Post,[this](const QHttpServerRequest &request) {
                        return objWebJsonApi->ServerResponsePost(request);
                      });

    httpServer->route("/",QHttpServerRequest::Method::Get,[this](const QHttpServerRequest &request) {
        return objWebJsonApi->ServerResponseGet(request);
    });



//    // Basic authentication example (RFC 7617)
//    httpServer->route("/auth", [](const QHttpServerRequest &request) {
//        auto auth = request.value("authorization").simplified();

//        if (auth.size() > 6 && auth.first(6).toLower() == "basic ") {
//            auto token = auth.sliced(6);
//            auto userPass = QByteArray::fromBase64(token);

//            if (auto colon = userPass.indexOf(':'); colon > 0) {
//                auto userId = userPass.first(colon);
//                auto password = userPass.sliced(colon + 1);

//                if (userId == "Aladdin" && password == "open sesame")
//                    return QHttpServerResponse("text/plain", "Success\n");
//            }
//        }
//        QHttpServerResponse response("text/plain", "Authentication required\n",
//                                     QHttpServerResponse::StatusCode::Unauthorized);
//        response.setHeader("WWW-Authenticate", R"(Basic realm="Simple example", charset="UTF-8")");
//        return response;
//    });

    httpServer->afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Server", "Qt HTTP Server");
        return std::move(resp);
    });

    const auto port = httpServer->listen(QHostAddress::Any,8081);
    if (!port) {
        qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                  "Server failed to listen on a port.");
        return -1;
    }

//#if QT_CONFIG(ssl)
//    const auto sslCertificateChain =
//        QSslCertificate::fromPath(QStringLiteral(":/assets/certificate.crt"));
//    if (sslCertificateChain.empty()) {
//        qWarning() << QCoreApplication::translate("QHttpServerExample",
//                                                  "Couldn't retrieve SSL certificate from file.");
//        return -1;
//    }
//    QFile privateKeyFile(QStringLiteral(":/assets/private.key"));
//    if (!privateKeyFile.open(QIODevice::ReadOnly)) {
//        qWarning() << QCoreApplication::translate("QHttpServerExample",
//                                                  "Couldn't open file for reading: %1")
//                          .arg(privateKeyFile.errorString());
//        return -1;
//    }
//    httpServer->sslSetup(sslCertificateChain.front(), QSslKey(&privateKeyFile, QSsl::Rsa));
//    privateKeyFile.close();

//    const auto sslPort = httpServer->listen(QHostAddress::Any);
//    if (!sslPort) {
//        qWarning() << QCoreApplication::translate("QHttpServerExample",
//                                                  "Server failed to listen on a port.");
//        return -1;
//    }

//    qInfo().noquote()
//        << QCoreApplication::translate("QHttpServerExample",
//                                       "Running on http://127.0.0.1:%1/ and "
//                                       "https://127.0.0.1:%2/ (Press CTRL+C to quit)")
//               .arg(port).arg(sslPort);
//#else

    qInfo().noquote()
        << QCoreApplication::translate("QHttpServerExample",
                                       "Running on http://127.0.0.1:%1/"
                                       "(Press CTRL+C to quit)").arg(port);

//#endif

    return 0;
}

QHttpServer *ServerHttp::getHttpServer() const
{
    return httpServer;
}

WebJsonApiServer *ServerHttp::getObjWebJsonApi() const
{
    return objWebJsonApi;
}

