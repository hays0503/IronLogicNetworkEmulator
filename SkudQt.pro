QT       += core gui websockets httpserver concurrent network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/Controller/ControllerListener.cpp \
    source/Controller/ControllerListener_alternative.cpp \
    source/Controller/ControllerListener_alternative_windows_hwnd.cpp \
    source/Controller/controllerutility.cpp \
    source/Converter/ConverterWorkerThread.cpp \
    source/IronLogicDependency/Utils.cpp \
    source/IronLogicDependency/ZGuard.cpp \
    source/IronLogicDependency/ZPort.cpp \
    source/Controller/controllermanipulator.cpp \
    source/Controller/controller.cpp \
    source/Converter/converter.cpp \
    source/Server/ServerWorkerThread.cpp \
    source/Server/WebJsonApi.cpp \
    source/Server/WebJsonApiServer.cpp \
    source/Server/clienthttp.cpp \
    source/Server/serverwebsocket.cpp \
    source/Server/serverhttp.cpp \
    source/Gui/mainwindow.cpp \
    source/Database/Database.cpp \
    source/main.cpp \


HEADERS += \
    header/Controller/CardDto.h \
    header/Controller/ControllerListener.h \
    header/Controller/ControllerListenerRoot.h \
    header/Controller/ControllerListener_alternative.h \
    header/Controller/ControllerListener_alternative_windows_hwnd.h \
    header/Controller/controllermanipulator.h \
    header/Controller/controllerutility.h \
    header/Converter/ConverterWorkerThread.h \
    header/IronLogicDependency/Utils.h\
    header/IronLogicDependency/ZGuard.h \
    header/IronLogicDependency/ZPort.h \
    header/IronLogicDependency/ZBase.h \
    header/IronLogicDependency/ZRetrConst.h \
    header/IronLogicDependency/ControllersStruct.h \
    header/Controller/controller.h \
    header/Converter/converter.h \
    header/Server/ServerWorkerThread.h \
    header/Server/Utils.h \
    header/Server/WebJsonApi.h \
    header/Server/WebJsonApiServer.h \
    header/Server/clienthttp.h \
    header/Server/serverhttp.h \
    header/Server/serverwebsocket.h \
    header/Database/Database.h \
    header/Gui/mainwindow.h \


FORMS += \
    ui/mainwindow.ui

TRANSLATIONS += \
    SkudQt_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -luser32


DISTFILES += \
    lib/ZGuard.dll \
    lib/ZGuard.lib

win32: LIBS += -L$$PWD/lib/ -lZGuard

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
