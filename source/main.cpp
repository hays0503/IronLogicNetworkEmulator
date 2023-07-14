#include "header/Gui/mainwindow.h"
#include <qboxlayout>
#include <qpushbutton>
#include <QLineEdit>
#include <QTextEdit>

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLocale>


//GNU GPL V2, 2015-02-07
#include <QMessageBox>
#include <windows.h>
#define CONSOLE_COLUMNS 80
#define CONSOLE_ROWS    5000
#define YOURCONSOLETITLE "Your_Console_Title"

typedef struct{

    CONSOLE_SCREEN_BUFFER_INFOEX conScreenBuffInfoEX;

    HANDLE con_screenbuf;
    HWND hwndConsole;
    HMENU consoleMenu ;
    QString consoleTitle;

    QMessageBox mBox;
    QString localMsg;
    QString errorMessage;
    BOOL errorCode;

} consoleT;

static consoleT *console;

BOOL WINAPI catchCTRL( DWORD ctrlMsg ){

    if( ctrlMsg == CTRL_C_EVENT ){

        HWND hwndWin = GetConsoleWindow();
        ShowWindow(hwndWin,SW_FORCEMINIMIZE);
    }

    return TRUE;
}

void removeCloseMenu(){

    int i;

    for( i = 0; i < 10; i++){

        console->hwndConsole = FindWindowW( NULL, console->consoleTitle.toStdWString().data());

        if(console->hwndConsole != NULL)
            break;
    }

    if( !(console->errorCode = 0) && (console->hwndConsole == NULL))
        console->errorMessage += QString("\nFindWindowW error: %1 \n").arg(console->errorCode);

    if( !(console->errorCode = 0) &&  !(console->consoleMenu = GetSystemMenu( console->hwndConsole, FALSE )) )
        console->errorMessage += QString("GetSystemMenu error: %1 \n").arg(console->errorCode);

    if(!(console->errorCode = DeleteMenu( console->consoleMenu, SC_CLOSE, MF_BYCOMMAND )))
        console->errorMessage += QString("DeleteMenu error: %1 \n").arg(console->errorCode);
}

void initialiseConsole(){

    console->conScreenBuffInfoEX.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    console->consoleMenu = NULL;
    console->consoleTitle = YOURCONSOLETITLE;
    console->con_screenbuf = INVALID_HANDLE_VALUE;
    console->errorCode = 0;
    console->errorMessage = "";
    console->hwndConsole = NULL;
    console->localMsg = "";

    if(!(console->errorCode = FreeConsole()))
        console->errorMessage += QString("\nFreeConsole error: %1 \n").arg(console->errorCode);

    if(!(console->errorCode = AllocConsole()))
        console->errorMessage += QString("\nAllocConsole error: %1 \n").arg(console->errorCode);

    if( (console->errorCode = -1) && (INVALID_HANDLE_VALUE ==(console->con_screenbuf = CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ,0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))))
        console->errorMessage += QString("\nCreateConsoleScreenBuffer error: %1 \n").arg(console->errorCode);

    if(!(console->errorCode = SetConsoleActiveScreenBuffer(console->con_screenbuf)))
        console->errorMessage += QString("\nSetConsoleActiveScreenBuffer error: %1 \n").arg(console->errorCode);

    if(!(console->errorCode = GetConsoleScreenBufferInfoEx(console->con_screenbuf, &console->conScreenBuffInfoEX)))
        console->errorMessage += QString("\nGetConsoleScreenBufferInfoEx error: %1 \n").arg(console->errorCode);

    console->conScreenBuffInfoEX.dwSize.X = CONSOLE_COLUMNS;
    console->conScreenBuffInfoEX.dwSize.Y = CONSOLE_ROWS;

    if(!(console->errorCode = SetConsoleScreenBufferInfoEx(console->con_screenbuf, &console->conScreenBuffInfoEX)))
        console->errorMessage += QString("\nSetConsoleScreenBufferInfoEx error: %1 \n").arg(console->errorCode);

    if(!(console->errorCode = SetConsoleTitleW(console->consoleTitle.toStdWString().data())))
        console->errorMessage += QString("SetConsoleTitle error: %1 \n").arg(console->errorCode);

    SetConsoleCtrlHandler(NULL, FALSE);
    SetConsoleCtrlHandler(catchCTRL, TRUE);

    removeCloseMenu();

    if(console->errorMessage.length() > 0){
        console->mBox.setText(console->errorMessage);
        console->mBox.show();
    }

}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){


    if((console->con_screenbuf != INVALID_HANDLE_VALUE)){

        switch (type) {

        case QtDebugMsg:
            console->localMsg = console->errorMessage + "Debug: " + msg;
            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
            break;

        case QtWarningMsg:
            console->localMsg = console->errorMessage + "Warning: " + msg;
            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length() , NULL, NULL );
            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
            break;

        case QtCriticalMsg:
            console->localMsg = console->errorMessage + "Critical: " + msg;
            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
            break;

        case QtFatalMsg:
            console->localMsg = console->errorMessage + "Fatal: " + msg;
            WriteConsoleW(console->con_screenbuf, console->localMsg.toStdWString().data(), console->localMsg.toStdWString().length(), NULL, NULL );
            WriteConsoleA(console->con_screenbuf, "\n--\n", 4, NULL, NULL );
            abort();
        }
    }
}

int main(int argc, char *argv[])
{

//    qInstallMessageHandler(messageHandler);

    QApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SkudQt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

//    console = new consoleT();
//    initialiseConsole();


    MainWindow w;
    w.show();


    return a.exec();
}
