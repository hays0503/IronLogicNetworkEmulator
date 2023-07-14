#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GUARDL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ZPORT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

// (rom) this is the switch to change between static and dynamic linking.
// (rom) it is enabled by default here.
// (rom) To disable simply change the '$' to a '.'.
//#define ZPORT_LINKONREQUEST


#ifndef ZPORT_LINKONREQUEST

#ifdef ZPORT_EXPORTS
#define ZPORT_API(type) extern "C" __declspec(dllexport) type __stdcall 
#else
#ifdef ZPORT_STATIC
#define ZPORT_API(type) extern "C" type __stdcall 
#else
#define ZPORT_API(type) extern "C" __declspec(dllimport) type __stdcall 
#endif
#endif
#else
#include <tchar.h>
#endif // !ZPORT_LINKONREQUEST

#define DEPRECATED_FN	__declspec(deprecated)


#include <windows.h>
#include <Unknwn.h>

#define ZP_SDK_VER_MAJOR	1
#define ZP_SDK_VER_MINOR	20

// Коды ошибок
#define ZP_S_CANCELLED					((HRESULT)0x00040201L)	// Отменено пользователем
#define ZP_S_NOTFOUND					((HRESULT)0x00040202L)	// Не найден (для функции ZP_FindSerialDevice)
#define ZP_S_TIMEOUT					((HRESULT)0x00040203L)
#define ZP_E_OPENNOTEXIST				((HRESULT)0x80040203L)	// Порт не существует
#define ZP_E_OPENPORT					((HRESULT)0x80040205L)	// Другая ошибка открытия порта
#define ZP_E_PORTIO						((HRESULT)0x80040206L)	// Ошибка порта (Конвертор отключен от USB?)
#define ZP_E_PORTSETUP					((HRESULT)0x80040207L)	// Ошибка настройки порта
#define ZP_E_LOADFTD2XX					((HRESULT)0x80040208L)	// Неудалось загрузить FTD2XX.DLL
#define ZP_E_SOCKET						((HRESULT)0x80040209L)	// Ошибка сокетов
#define ZP_E_SERVERCLOSE				((HRESULT)0x8004020AL)	// Дескриптор закрыт со стороны Сервера
#define ZP_E_NOTINITALIZED				((HRESULT)0x8004020BL)	// Не проинициализировано с помощью ZP_Initialize
#define ZP_E_INSUFFICIENTBUFFER			((HRESULT)0x8004020CL)	// Размер буфера слишком мал
#define ZP_E_NOCONNECT                  ((HRESULT)0x8004020DL)

#pragma pack(1)   // turn byte alignment on

#define ZP_MAX_PORT_NAME			31		// Максимальная длина имени порта (исключая завершающий '\0')
#define ZP_MAX_REG_DEV				16

// Флаги для функции ZP_Initialize
enum _ZP_INITIALIZE_FLAGS
{
	ZP_IF_NO_MSG_LOOP			= 0x0001,	// Приложение не имеет цикла обработки сообщений (Console or Service)
	ZP_IF_LOG					= 0x0002	// Записывать лог
};
typedef UINT ZP_INIT_FLAGS;

// Флаги для функции ZP_DD_SetNotification
enum _ZP_DD_FLAGS
{
	ZP_NF_EXIST					= 0x0001, // Уведомления о подключении/отключении порта (ZP_N_INSERT / ZP_N_REMOVE)
	ZP_NF_CHANGE				= 0x0002, // Уведомление о изменении параметров порта (ZP_N_CHANGE)
	ZP_NF_ERROR					= 0x0008, // Уведомление об ошибке в ните(thread), сканирующей порты (ZP_N_ERROR)
	ZP_NF_SDEVICE				= 0x0010, // Опрашивать устройства, подключенные по USB
	ZP_NF_IPDEVICE				= 0x0020, // Опрашивать IP устройства (конвертеры в режиме SERVER)
	ZP_NF_IPSDEVICE				= 0x0080, // Опрашивать IPS устройства (конвертеры в режиме CLIENT)
	ZP_NF_COMPLETED				= 0x0040, // Уведомления о завершении сканирования
	ZP_NF_DEVEXIST				= 0x0004, // Уведомления о подключении/отключении устройства (ZP_N_DEVINSERT / ZP_N_DEVREMOVE)
	ZP_NF_DEVCHANGE				= 0x0100, // Уведомления о изменении параметров устройства (ZP_N_DEVCHANGE)
	ZP_NF_UNIDCOM				= 0x1000, // Искать неопознанные com-порты
	ZP_NF_USECOM				= 0x2000  // По возможности использовать Com-порт
};
typedef UINT ZP_DD_FLAGS;

// Уведомления функции ZP_DD_SetNotification (wParam - MsgCode, lParam - MsgParam)
typedef enum _ZP_DD_NOTIFICATIONS
{
	ZP_N_INSERT					= 1, // Подключение порта. (PZP_N_EXIST_INFO)MsgParam - инфо о порте
	ZP_N_REMOVE					= 2, // Отключение порта. (PZP_N_EXIST_INFO)MsgParam - инфо о порте
	ZP_N_CHANGE					= 3, // Изменение параметров порта. (PZP_N_CHANGE_INFO)MsgParam - инфо об изменениях
	ZP_N_ERROR					= 4, // Произошла ошибка в потоке. (PHRESULT)MsgParam - код ошибки
	ZP_N_COMPLETED				= 5, // Сканирование завершено. (PINT)MsgParam - маска: b0-список com-портов, b1-список ip-портов, b2-информация об устройствах, b3-инициализация, b4-команда, <0-ошибка
	ZP_N_DEVINSERT				= 6, // Подключение устройства. (PZP_N_EXIST_DEVINFO)MsgParam - инфо о устройстве
	ZP_N_DEVREMOVE              = 7, // Отключение устройства. (PZP_N_EXIST_DEVINFO)MsgParam - инфо о устройстве
	ZP_N_DEVCHANGE				= 8 // Изменение параметров устройства. (PZP_N_CHANGE_DEVINFO)MsgParam - инфо об изменениях
} ZP_DD_NOTIFICATIONS;

// Параметры по умолчанию (тайм-ауты и периоды в миллисекундах)
#define ZP_IP_CONNECTTIMEOUT		4000		// Тайм-аут подключения по TCP для порта типа ZP_PORT_IP
#define ZP_IP_RESTOREPERIOD			3000		// Период восстановления утерянной TCP-связи (для порта типа ZP_PORT_IP)
#define ZP_IPS_CONNECTTIMEOUT		10000		// Тайм-аут подключения по TCP для порта типа ZP_PORT_IPS
#define ZP_USB_RESTOREPERIOD		3000		// Период восстановления утерянной связи (для портов типов ZP_PORT_COM и ZP_PORT_FT)
#define ZP_DTC_FINDUSBPERIOD		5000		// Период поиска USB-устройств (только поиск com-портов) (для детектора устройств)
#define ZP_DTC_FINDIPPERIOD			15000		// Период поиска IP-устройства по UDP (для детектора устройств)
#define ZP_DTC_SCANDEVPERIOD		INFINITE	// Период сканирования устройств, опросом портов (для детектора устройств)
#define ZP_SCAN_RCVTIMEOUT0			500			// Тайм-аут ожидания первого байта ответа на запрос при сканировании устройств
#define ZP_SCAN_RCVTIMEOUT			3000		// Тайм-аут ожидания ответа на запрос при сканировании устройств
#define ZP_SCAN_MAXTRIES			2			// Максимум попыток запроса при сканировании устройств
#define ZP_SCAN_CHECKPERIOD			INFINITE	// Период проверки входяших данных порта при сканировании портов
#define ZP_FINDIP_RCVTIMEOUT		1000		// Тайм-аут поиска ip-устройств по UDP
#define ZP_FINDIP_MAXTRIES			1			// Максимум попыток поиска ip-устройств по UDP

// Тип порта
enum ZP_PORT_TYPE
{
	ZP_PORT_UNDEF = 0,
	ZP_PORT_COM,		// Com-порт
	ZP_PORT_FT,			// FT-порт (через ftd2xx.dll по с/н USB, только для устройств, использующих этот драйвер)
	ZP_PORT_IP,			// Ip-порт (TCP-клиент)
	ZP_PORT_IPS			// IPS-порт (TCP-сервер)
};

// Имя порта
typedef WCHAR ZP_PORT_NAME[ZP_MAX_PORT_NAME + 1];

// Настройки ожидания исполнения функций
typedef struct _ZP_WAIT_SETTINGS
{
	UINT nReplyTimeout;			// Тайм-аут ожидания ответа
	INT nMaxTries;				// Количество попыток отправить запрос
	HANDLE hAbortEvent;			// Дескриптор стандартного объекта Event для отмены функции
	UINT nReplyTimeout0;		// Тайм-аут ожидания первого символа ответа
	UINT nCheckPeriod;			// Период проверки порта в мс (если =0 или =INFINITE, то по RX-событию)
	UINT nConnectTimeout;		// Тайм-аут подключения по TCP
	UINT nRestorePeriod;		// Период с которым будут осуществляться попытки восстановить утерянную TCP-связь
} *PZP_WAIT_SETTINGS;

// Флаги для ZP_OPEN_PARAMS.nFlags
enum _ZP_PORT_OPEN_FLAGS
{
	ZP_POF_NO_WAIT_CONNECT	= 0x0001,	// Не ждать завершения процедуры подключения
	ZP_POF_NO_CONNECT_ERR	= 0x0002,	// Не возвращать ошибку в случае когда нет связи
	ZP_POF_NO_DETECT_USB	= 0x0004	// Не использовать детектор USB-устройств (для ZP_PORT_FT и ZP_PORT_COM)
};
typedef UINT ZP_PO_FLAGS;
// Параметры открытия порта (для функции ZP_Open)
typedef struct _ZP_PORT_OPEN_PARAMS
{
	LPCWSTR szName;				// Имя порта
	ZP_PORT_TYPE nType;			// Тип порта
	UINT nBaud;					// Скорость порта
	CHAR nEvChar;				// Сигнальный символ
	BYTE nStopBits;				// Количество стоповых битов
	UINT nConnectTimeout;		// Тайм-аут подключения по TCP
	UINT nRestorePeriod;		// Период с которым будут осуществляться попытки восстановить утерянную TCP-связь
	ZP_PO_FLAGS nFlags;			// Флаги ZP_PF_...
}*PZP_PORT_OPEN_PARAMS;

// Флаги для уведомлений порта
enum _ZP_PORT_FLAGS
{
	ZP_PNF_RXEVENT		= 0x0001,	// Пришли новые данные от устройства
	ZP_PNF_STATUS		= 0x0002	// Изменилось состояние подключения порта
};
typedef UINT ZP_PN_FLAGS;

// Флаги порта (для nFlags в структуре ZP_PORT_INFO)
enum _ZP_PORT_INFO_FLAGS
{
	ZP_PIF_BUSY			= 0x0001,	// Порт занят
	ZP_PIF_USER			= 0x0002	// Порт, указанный пользователем (массив _ZP_PORT_ADDR)
};
typedef UINT ZP_PI_FLAGS;

// Информация о порте
typedef struct _ZP_PORT_INFO
{
	ZP_PORT_TYPE nType;			// Тип порта
	ZP_PORT_NAME szName;		// Имя порта
	ZP_PI_FLAGS nFlags;			// Флаги порта (ZP_PIF_...)
	ZP_PORT_NAME szFriendly;	// Дружественное имя порта
	UINT nDevTypes;				// Маска типов устройств
	WCHAR szOwner[64];			// Владелец порта (для функции ZP_EnumIpDevices)
} *PZP_PORT_INFO;

typedef struct _ZP_DEVICE_INFO
{
	UINT cbSize;				// Размер структуры
	UINT nTypeId;
	UINT nModel;				// Модель
	UINT nSn;					// С/н
	UINT nVersion;				// Версия прошивки
} *PZP_DEVICE_INFO;

// Состояние подключения
enum ZP_CONNECTION_STATUS
{
	ZP_CS_DISCONNECTED = 0,		// Отключен
	ZP_CS_CONNECTED,			// Подключен
	ZP_CS_CONNECTING,			// Идет подключение... (при первом подключении)
	ZP_CS_RESTORATION			// Восстанавление связи... (при следующих подключениях)
};

// Флаги для _ZP_DDN_PORT_INFO.nChangeMask и _ZP_DDN_DEVICE_INFO.nChangeMask
enum _ZP_DDN_PORT_INFO_FLAGS
{
	ZP_CIF_BUSY			= 0x0004,	// Изменилось состояние "порт занят"
	ZP_CIF_FRIENDLY		= 0x0008,	// Изменилось дружественное имя порта
	ZP_CIF_OWNER		= 0x0020,	// Изменился владелец порта (только для IP устройств)
	ZP_CIF_MODEL		= 0x0080,	// Изменилась модель устройства
	ZP_CIF_SN			= 0x0100,	// Изменился серийный номер устройства
	ZP_CIF_VERSION		= 0x0200,	// Изменилась версия прошивки устройства
	ZP_CIF_DEVPARAMS	= 0x0400,	// Изменились расширенные параметры устройства
	ZP_CIF_LIST			= 0x0800	// Изменился список портов (для _ZP_DDN_DEVICE_INFO) или устройств (для _ZP_DDN_PORT_INFO)
};
typedef UINT _ZP_DDNPI_FLAGS;
// Информация о порте
typedef struct _ZP_DDN_PORT_INFO
{
	_ZP_PORT_INFO rPort;
	PZP_DEVICE_INFO* aDevs;
	INT nDevCount;
	_ZP_DDNPI_FLAGS nChangeMask;	// Маска изменений (ZP_CIF_...)
} *PZP_DDN_PORT_INFO;

// Информация о устройстве
typedef struct _ZP_DDN_DEVICE_INFO
{
	PZP_DEVICE_INFO pInfo;
	PZP_PORT_INFO aPorts;
	INT nPortCount;
	_ZP_DDNPI_FLAGS nChangeMask;	// Маска изменений (ZP_CIF_...)
} *PZP_DDN_DEVICE_INFO;

// Callback-функции (функции обратного вызова)
typedef BOOL (CALLBACK* ZP_DEVICEPARSEPROC) (LPCVOID pReply, UINT nCount, PBOOL pPartially, 
	PZP_DEVICE_INFO pInfo, PZP_PORT_INFO pPortArr, INT nArrLen, PINT pPortCount);

// Настройки уведомлений (для функции ZP_DD_SetNotification)
typedef struct _ZP_DD_NOTIFY_SETTINGS
{
	ZP_DD_FLAGS nNMask;			// Маска типов уведомлений ZP_NF_

	HANDLE hEvent;				// Событие (объект синхронизации)
	HWND hWindow;				// Окно, принимиющее сообщение nWndMsgId
	UINT nWndMsgId;				// Сообщение для отправки окну hWnd

	DWORD nSDevTypes;			// Маска тивов устройств, подключенных к последовательному порту
	DWORD nIpDevTypes;			// Маска тивов Ip-устройств

	LPWORD aIps;				// Массив TCP-портов для подключения конвертеров в режиме "CLIENT" (если NULL, то не используется)
	INT nIpsCount;				// Количество TCP-портов
} *PZP_DD_NOTIFY_SETTINGS;

// Настройки для детектора устройств (для функций ZP_DD_SetGlobalSettings и ZP_DD_GetGlobalSettings)
typedef struct _ZP_DD_GLOBAL_SETTINGS
{
	UINT nCheckUsbPeriod;		// Период проверки состояния USB-портов (в миллисекундах) (=0 по умолчанию 5000)
	UINT nCheckIpPeriod;		// Период проверки состояния IP-портов (в миллисекундах) (=0 по умолчанию 15000)
	UINT nScanDevPeriod;		// Период сканирования устройств на USB- и IP-портах (в миллисекундах) (=0 по умолчанию никогда=INFINITE)

	UINT nIpReqTimeout;			// Тайм-аут ожидания ответа от ip-устройства при опросе по UDP
	INT nIpReqMaxTries;			// Количество попыток опроса ip-устройства по UDP
	_ZP_WAIT_SETTINGS rScanWS;	// Параметры ожидания при сканировании портов
} *PZP_DD_GLOBAL_SETTINGS;

typedef struct _ZP_DEVICE
{
	UINT nTypeId;					// Тип устройства
	LPCVOID pReqData;				// Данные запроса (может быть NULL)
	UINT nReqSize;					// Количество байт в запросе
	ZP_DEVICEPARSEPROC pfnParse;	// Функция разбора ответа
	UINT nDevInfoSize;				// Размер структуры ZP_DEVICE_INFO
} *PZP_DEVICE;

typedef struct _ZP_IP_DEVICE : _ZP_DEVICE
{
	WORD nReqPort;				// UDP-порт для запроса
	INT nMaxPort;				// Максимум портов у устройства (линий у конвертера)
} *PZP_IP_DEVICE;

typedef struct _ZP_USB_DEVICE : _ZP_DEVICE
{
	PDWORD pVidPids;			// Массив Vid,Pid USB-устройств MAKELONG(vid, pid)
	INT nVidPidCount;			// Размер массива Vid,Pid
	UINT nBaud;					// Скорость порта
	CHAR chEvent;				// Символ-признак конца передачи (если =0, нет символа)
	BYTE nStopBits;				// Стоповые биты (ONESTOPBIT=0, ONE5STOPBITS=1, TWOSTOPBITS=2)
	LPCWSTR pszBDesc;			// Описание устройства, предоставленное шиной (DEVPKEY_Device_BusReportedDeviceDesc)
} *PZP_USB_DEVICE;

typedef struct _ZP_PORT_ADDR
{
	ZP_PORT_TYPE nType;			// Тип порта
	LPCWSTR pName;				// Имя порта
	DWORD nDevTypes;			// Маска тивов устройств
} *PZP_PORT_ADDR;

// Флаги для параметра ZP_SEARCH_PARAMS.nFlags
enum _ZP_SEARCH_PARAMS_FLAGS
{
	ZP_SF_USECOM		= 0x0001,	// Использовать COM-порт по возможности
	ZP_SF_DETECTOR		= 0x0002,	// Использовать уже готовый список найденных устройств детектора (создается функцией ZP_SetNotification)
	ZP_SF_IPS			= 0x0004,	// Включить в список найденные IP-конвертеры в режиме CLIENT (не работает с флагом ZP_SF_DETECTOR)
	ZP_SF_UNID			= 0x0008,	// Включить в список неопознанные устройства
	ZP_SF_UNIDCOM		= 0x0010	// Опрашивать неопознанные com-порты
};
typedef UINT _ZP_SP_FLAGS;
// Параметры поиска устройств (для функции ZP_SearchDevices)
typedef struct _ZP_SEARCH_PARAMS
{
	UINT nDevMask;				// Маска устройств для сканирования портов (=0 не искать, =0xffffffff искать всё)
	UINT nIpDevMask;			// Маска IP устройств, сканируемых с помощью UDP-запроса (=0 не искать, =0xffffffff искать всё)
	PZP_PORT_ADDR pPorts;		// Список портов
	INT nPCount;				// Размер списка портов
	_ZP_SP_FLAGS nFlags;				// Флаги ZP_SF_...
	PZP_WAIT_SETTINGS pWait;	// Параметры ожидания для сканирования портов. Может быть =NULL.
	UINT nIpReqTimeout;			// Тайм-аут ожидания ответа от ip-устройства при опросе по UDP
	INT nIpReqMaxTries;			// Количество попыток опроса ip-устройства по UDP
}*PZP_SEARCH_PARAMS;



#pragma deprecated(ZP_STATUS)
#define ZP_STATUS						HRESULT
#pragma deprecated(ZP_SUCCESS)
#define ZP_SUCCESS						S_OK
#pragma deprecated(ZP_E_CANCELLED)
#define ZP_E_CANCELLED					ZP_S_CANCELLED
#pragma deprecated(ZP_E_NOT_FOUND)
#define ZP_E_NOT_FOUND					ZP_S_NOTFOUND
#pragma deprecated(ZP_E_INVALID_PARAM)
#define ZP_E_INVALID_PARAM				E_INVALIDARG
#pragma deprecated(ZP_E_OPEN_NOT_EXIST)
#define ZP_E_OPEN_NOT_EXIST				ZP_E_OPENNOTEXIST
#pragma deprecated(ZP_E_OPEN_ACCESS)
#define ZP_E_OPEN_ACCESS				ZP_E_OPENACCESS
#pragma deprecated(ZP_E_OPEN_PORT)
#define ZP_E_OPEN_PORT					ZP_E_OPENPORT
#pragma deprecated(ZP_E_PORT_IO_ERROR)
#define ZP_E_PORT_IO_ERROR				ZP_E_PORTIO
#pragma deprecated(ZP_E_PORT_SETUP)
#define ZP_E_PORT_SETUP					ZP_E_PORTSETUP
#pragma deprecated(ZP_E_LOAD_FTD2XX)
#define ZP_E_LOAD_FTD2XX				ZP_E_LOADFTD2XX
#pragma deprecated(ZP_E_INIT_SOCKET)
#define ZP_E_INIT_SOCKET				ZP_E_SOCKET
#pragma deprecated(ZP_E_NOT_ENOUGH_MEMORY)
#define ZP_E_NOT_ENOUGH_MEMORY			E_OUTOFMEMORY
#pragma deprecated(ZP_E_UNSUPPORT)
#define ZP_E_UNSUPPORT					E_NOINTERFACE
#pragma deprecated(ZP_E_NOT_INITALIZED)
#define ZP_E_NOT_INITALIZED				ZP_E_NOTINITALIZED
#pragma deprecated(ZP_E_CREATE_EVENT)
#define ZP_E_CREATE_EVENT				E_FAIL
#pragma deprecated(ZP_E_OTHER)
#define ZP_E_OTHER						E_FAIL
#pragma deprecated(ZP_NF_BUSY)
#define ZP_NF_BUSY						ZP_NF_CHANGE
#pragma deprecated(ZP_NF_FRIENDLY)
#define ZP_NF_FRIENDLY					ZP_NF_CHANGE
#pragma deprecated(ZP_N_STATE_CHANGED)
#define ZP_N_STATE_CHANGED				ZP_N_CHANGE
#pragma deprecated(_ZP_OPEN_PARAMS)
#define _ZP_OPEN_PARAMS					_ZP_PORT_OPEN_PARAMS
#pragma deprecated(PZP_OPEN_PARAMS)
#define PZP_OPEN_PARAMS					PZP_PORT_OPEN_PARAMS
#pragma deprecated(_ZP_N_CHANGE_STATE)
#define _ZP_N_CHANGE_STATE				_ZP_DDN_PORT_INFO
#pragma deprecated(PZP_N_CHANGE_STATE)
#define PZP_N_CHANGE_STATE				PZP_DDN_PORT_INFO
#pragma deprecated(ZP_NF_USEVCOM)
#define ZP_NF_USEVCOM					ZP_NF_USECOM
#pragma deprecated(ZP_NF_WND_SYNC)
#define ZP_NF_WND_SYNC					ZP_NF_WNDSYNC
#pragma deprecated(ZP_NF_WNDSYNC)
#define ZP_NF_WNDSYNC				0x4000	
#pragma deprecated(ZP_NF_ONLY_NOTIFY)
#define ZP_NF_ONLY_NOTIFY				ZP_NF_ONLYNOTIFY
#pragma deprecated(ZP_NF_ONLYNOTIFY)
#define ZP_NF_ONLYNOTIFY			0x8000
#pragma deprecated(ZP_PF_BUSY2)
#define ZP_PF_BUSY2						4
#pragma deprecated(ZP_PF_BUSY)
#define ZP_PF_BUSY						ZP_PIF_BUSY
#pragma deprecated(ZP_PF_USER)
#define ZP_PF_USER						ZP_PIF_USER
#pragma deprecated(ZP_E_OPENACCESS)
#define ZP_E_OPENACCESS					E_ACCESSDENIED
#pragma deprecated(ZP_IF_ERROR_LOG)
#define ZP_IF_ERROR_LOG				ZP_IF_LOG
#pragma deprecated(ZP_PF_NOWAITCONNECT)
#define ZP_PF_NOWAITCONNECT				ZP_POF_NO_WAIT_CONNECT
#pragma deprecated(ZP_PF_NOCONNECTERR)
#define ZP_PF_NOCONNECTERR				ZP_POF_NO_CONNECT_ERR
#pragma deprecated(ZP_PF_NOUSBDETECT)
#define ZP_PF_NOUSBDETECT				ZP_POF_NO_DETECT_USB
#pragma deprecated(_ZP_N_EXIST_INFO)
#define _ZP_N_EXIST_INFO				_ZP_DDN_PORT_INFO
#pragma deprecated(PZP_N_EXIST_INFO)
#define PZP_N_EXIST_INFO				PZP_DDN_PORT_INFO
#pragma deprecated(_ZP_N_CHANGE_INFO)
#define _ZP_N_CHANGE_INFO				_ZP_DDN_PORT_INFO
#pragma deprecated(PZP_N_CHANGE_INFO)
#define PZP_N_CHANGE_INFO				PZP_DDN_PORT_INFO
#pragma deprecated(_ZP_N_EXIST_DEVINFO)
#define _ZP_N_EXIST_DEVINFO				_ZP_DDN_DEVICE_INFO
#pragma deprecated(PZP_N_EXIST_DEVINFO)
#define PZP_N_EXIST_DEVINFO				PZP_DDN_DEVICE_INFO
#pragma deprecated(_ZP_N_CHANGE_DEVINFO)
#define _ZP_N_CHANGE_DEVINFO			_ZP_DDN_DEVICE_INFO
#pragma deprecated(PZP_N_CHANGE_DEVINFO)
#define PZP_N_CHANGE_DEVINFO			PZP_DDN_DEVICE_INFO
#pragma deprecated(_ZP_NOTIFY_SETTINGS)
#define _ZP_NOTIFY_SETTINGS			_ZP_DD_NOTIFY_SETTINGS
#pragma deprecated(PZP_NOTIFY_SETTINGS)
#define PZP_NOTIFY_SETTINGS			PZP_DD_NOTIFY_SETTINGS
#pragma deprecated(_ZP_DETECTOR_SETTINGS)
#define _ZP_DETECTOR_SETTINGS			_ZP_DD_GLOBAL_SETTINGS
#pragma deprecated(PZP_DETECTOR_SETTINGS)
#define PZP_DETECTOR_SETTINGS			PZP_DD_GLOBAL_SETTINGS
#pragma deprecated(ZP_CIF_PORTS)
#define ZP_CIF_PORTS			ZP_CIF_LIST
#pragma deprecated(ZP_CIF_DEVICES)
#define ZP_CIF_DEVICES			ZP_CIF_LIST
#pragma deprecated(_ZP_S_DEVICE)
#define _ZP_S_DEVICE			_ZP_USB_DEVICE
#pragma deprecated(PZP_S_DEVICE)
#define PZP_S_DEVICE			PZP_USB_DEVICE

typedef BOOL (CALLBACK* ZP_ENUMPORTSPROC) (PZP_PORT_INFO pInfo, PVOID pUserData);
typedef BOOL (CALLBACK* ZP_ENUMDEVICEPROC) (PZP_DEVICE_INFO pInfo, PZP_PORT_INFO pPort, PVOID pUserData);
typedef BOOL (CALLBACK* ZP_NOTIFYPROC) (UINT nMsg, LPARAM nMsgParam, PVOID pUserData);

#pragma pack() // turn byte alignment off

#ifndef ZPORT_LINKONREQUEST

// Возвращает версию библиотеки
ZPORT_API(DWORD) ZP_GetVersion();

// Инициализация/финализация библиотеки
ZPORT_API(HRESULT) ZP_Initialize(void** ppvObject, ZP_INIT_FLAGS nFlags);
ZPORT_API(HRESULT) ZP_Finalyze();

ZPORT_API(HRESULT) ZP_CloseHandle(HANDLE hHandle);

// Создает список подключенных портов
ZPORT_API(HRESULT) ZP_GetPortInfoList(PHANDLE pHandle, PINT pCount, UINT nSerDevs=0xffffffff, UINT nFlags=0);
ZPORT_API(HRESULT) ZP_GetPortInfo(HANDLE hHandle, INT nIdx, PZP_PORT_INFO pInfo);
// Ищет устройства, сканируя порты и(или) опрашивая ip-устройства по UDP
ZPORT_API(HRESULT) ZP_SearchDevices(PHANDLE pHandle, PZP_SEARCH_PARAMS pParams);
ZPORT_API(HRESULT) ZP_FindNextDevice(HANDLE hHandle, PZP_DEVICE_INFO pInfo, 
	PZP_PORT_INFO pPortArr, INT nArrLen, PINT pPortCount, UINT nTimeout=INFINITE);

// Уведомления о подключении/отключении устройств
ZPORT_API(HRESULT) ZP_DD_SetNotification(PHANDLE pHandle, PZP_DD_NOTIFY_SETTINGS pSettings);
ZPORT_API(HRESULT) ZP_DD_GetNextMessage(HANDLE hHandle, LPUINT pMsg, LPARAM* pMsgParam);
ZPORT_API(HRESULT) ZP_DD_SetGlobalSettings(PZP_DD_GLOBAL_SETTINGS pSettings);
ZPORT_API(HRESULT) ZP_DD_GetGlobalSettings(PZP_DD_GLOBAL_SETTINGS pSettings);
ZPORT_API(HRESULT) ZP_DD_Refresh(UINT nWaitMs=0);

ZPORT_API(HRESULT) ZP_SetServiceCtrlHandle(SERVICE_STATUS_HANDLE hSvc);
ZPORT_API(VOID) ZP_DeviceEventNotify(DWORD nEvType, PVOID pEvData);

// Разбота с портом
ZPORT_API(HRESULT) ZP_Port_Open(PHANDLE pHandle, PZP_PORT_OPEN_PARAMS pParams);
ZPORT_API(HRESULT) ZP_Port_SetBaudAndEvChar(HANDLE hHandle, UINT nBaud, CHAR chEvChar);
ZPORT_API(HRESULT) ZP_Port_GetBaudAndEvChar(HANDLE hHandle, LPUINT pBaud, PCHAR pEvChar);
ZPORT_API(HRESULT) ZP_Port_GetConnectionStatus(HANDLE hHandle, ZP_CONNECTION_STATUS* pValue, UINT* pSessionId);
ZPORT_API(HRESULT) ZP_Port_SetNotification(HANDLE hHandle, HANDLE hEvent, HWND hWnd, UINT nMsgId, ZP_PN_FLAGS nMsgMask);
ZPORT_API(HRESULT) ZP_Port_EnumMessages(HANDLE hHandle, PUINT pMsgs);

ZPORT_API(HRESULT) ZP_Port_Clear(HANDLE hHandle, BOOL fIn, BOOL fOut);
ZPORT_API(HRESULT) ZP_Port_Write(HANDLE hHandle, LPCVOID pBuf, UINT nCount);
ZPORT_API(HRESULT) ZP_Port_Read(HANDLE hHandle, LPVOID pBuf, UINT nCount, PUINT pRead);
ZPORT_API(HRESULT) ZP_Port_GetInCount(HANDLE hHandle, PUINT pCount);
ZPORT_API(HRESULT) ZP_Port_SetDtr(HANDLE hHandle, BOOL fState);
ZPORT_API(HRESULT) ZP_Port_SetRts(HANDLE hHandle, BOOL fState);

ZPORT_API(HRESULT) ZP_RegSerialDevice(PZP_USB_DEVICE pParams);
ZPORT_API(HRESULT) ZP_RegIpDevice(PZP_IP_DEVICE pParams);

#define ZP_L_ERROR		0
#define ZP_L_WARNING	1
#define ZP_L_INFO		2
#define MAKELOGTYPE(_type, _level)	(UINT(_level-1) * 3 + _type)
#ifdef ZP_LOG
ZPORT_API(HRESULT) ZP_SetLog(LPCWSTR pszSvrAddr, LPCWSTR pszFileName, UINT nFileTypeMask);
ZPORT_API(HRESULT) ZP_GetLog(LPWSTR pszSvrAddrBuf, UINT nSABufSize, LPWSTR pszFileNameBuf, UINT nFNBufSize, PUINT pFileTypeMask);
ZPORT_API(HRESULT) ZP_AddLog(WCHAR chSrc, UINT nType, UINT nMsgId, LPCWSTR pszText);
#else
inline HRESULT ZP_AddLog(WCHAR /*chSrc*/, UINT /*nType*/, UINT /*nMsgId*/, LPCWSTR /*pszText*/) { return 0; };
#endif // ZP_LOG

#else

//#define ZP_DLLNAME       _T("ZPort.dll")
#define ZP_DLLNAME       _T("ZGuard.dll")
//#define ZP_DLLNAME       _T("ZReader.dll")

extern "C"
{
	typedef DWORD (__stdcall* ZP_GETVERSION)();
	typedef HRESULT (__stdcall* ZP_INITIALIZE)(void** ppvObject, UINT nFlags);
	typedef HRESULT (__stdcall* ZP_FINALYZE)();
	typedef HRESULT (__stdcall* ZP_CLOSEHANDLE)(HANDLE hHandle);
	typedef HRESULT (__stdcall* ZP_GETPORTINFOLIST)(PHANDLE pHandle, PINT pCount, UINT nSerDevs/*=0xffffffff*/, UINT nFlags/*=0*/);
	typedef HRESULT (__stdcall* ZP_GETPORTINFO)(HANDLE hHandle, INT nIdx, PZP_PORT_INFO pInfo);
	typedef HRESULT (__stdcall* ZP_SEARCHDEVICES)(PHANDLE pHandle, PZP_SEARCH_PARAMS pParams);
	typedef HRESULT (__stdcall* ZP_FINDNEXTDEVICE)(HANDLE hHandle, PZP_DEVICE_INFO pInfo, 
		PZP_PORT_INFO pPortArr, INT nArrLen, PINT pPortCount, UINT nTimeout/*=INFINITE*/);
	typedef HRESULT (__stdcall* ZP_DD_SETNOTIFICATION)(PHANDLE pHandle, PZP_DD_NOTIFY_SETTINGS pSettings);
	typedef HRESULT (__stdcall* ZP_DD_GETNEXTMESSAGE)(HANDLE hHandle, LPUINT pMsg, LPARAM* pMsgParam);
	typedef HRESULT (__stdcall* ZP_DD_SETGLOBALSETTINGS)(PZP_DD_GLOBAL_SETTINGS pSettings);
	typedef HRESULT (__stdcall* ZP_DD_GETGLOBALSETTINGS)(PZP_DD_GLOBAL_SETTINGS pSettings);
	typedef HRESULT (__stdcall* ZP_DD_REFRESH)(UINT nWaitMs/*=0*/);
	typedef HRESULT (__stdcall* ZP_SETSERVICECTRLHANDLE)(SERVICE_STATUS_HANDLE hSvc);
	typedef VOID (__stdcall* ZP_DEVICEEVENTNOTIFY)(DWORD nEvType, PVOID pEvData);

	typedef HRESULT (__stdcall* ZP_PORT_OPEN)(PHANDLE pHandle, PZP_PORT_OPEN_PARAMS pParams);
	typedef HRESULT (__stdcall* ZP_PORT_SETBAUDANDEVCHAR)(HANDLE hHandle, UINT nBaud, CHAR chEvChar);
	typedef HRESULT (__stdcall* ZP_PORT_GETBAUDANDEVCHAR)(HANDLE hHandle, LPUINT pBaud, PCHAR pEvChar);
	typedef HRESULT (__stdcall* ZP_PORT_GETCONNECTIONSTATUS)(HANDLE hHandle, ZP_CONNECTION_STATUS* pValue, UINT* pSessionId);
	typedef HRESULT (__stdcall* ZP_PORT_SETNOTIFICATION)(HANDLE hHandle, HANDLE hEvent, HWND hWnd, UINT nMsgId, ZP_PN_FLAGS nMsgMask);
	typedef HRESULT (__stdcall* ZP_PORT_ENUMMESSAGES)(HANDLE hHandle, PUINT pMsgs);
	typedef HRESULT (__stdcall* ZP_PORT_CLEAR)(HANDLE hHandle, BOOL fIn, BOOL fOut);
	typedef HRESULT (__stdcall* ZP_PORT_WRITE)(HANDLE hHandle, LPCVOID pBuf, UINT nCount);
	typedef HRESULT (__stdcall* ZP_PORT_READ)(HANDLE hHandle, LPVOID pBuf, UINT nCount, PUINT pRead);
	typedef HRESULT (__stdcall* ZP_PORT_GETINCOUNT)(HANDLE hHandle, PUINT pCount);
	typedef HRESULT (__stdcall* ZP_PORT_SETDTR)(HANDLE hHandle, BOOL fState);
	typedef HRESULT (__stdcall* ZP_PORT_SETRTS)(HANDLE hHandle, BOOL fState);
	typedef HRESULT (__stdcall* ZP_REGSERIALDEVICE)(PZP_USB_DEVICE pParams);
	typedef HRESULT (__stdcall* ZP_REGIPDEVICE)(PZP_IP_DEVICE pParams);
#ifdef ZP_LOG
	typedef HRESULT (__stdcall* ZP_SETLOG)(LPCWSTR pszSvrAddr, LPCWSTR pszFileName, UINT nFileTypeMask);
	typedef HRESULT (__stdcall* ZP_GETLOG)(LPWSTR pszSvrAddrBuf, UINT nSABufSize, LPWSTR pszFileNameBuf, UINT nFNBufSize, PUINT pFileTypeMask);
	typedef HRESULT (__stdcall* ZP_ADDLOG)(WCHAR chSrc, UINT nType, UINT nMsgId, LPCWSTR pszText);
#endif // ZP_LOG
} // extern "C"

extern ZP_GETVERSION ZP_GetVersion;
extern ZP_INITIALIZE ZP_Initialize;
extern ZP_FINALYZE ZP_Finalyze;
extern ZP_CLOSEHANDLE ZP_CloseHandle;
extern ZP_GETPORTINFOLIST ZP_GetPortInfoList;
extern ZP_GETPORTINFO ZP_GetPortInfo;
extern ZP_SEARCHDEVICES ZP_SearchDevices;
extern ZP_FINDNEXTDEVICE ZP_FindNextDevice;
extern ZP_DD_SETNOTIFICATION ZP_DD_SetNotification;
extern ZP_DD_GETNEXTMESSAGE ZP_DD_GetNextMessage;
extern ZP_DD_SETGLOBALSETTINGS ZP_DD_SetGlobalSettings;
extern ZP_DD_GETGLOBALSETTINGS ZP_DD_GetGlobalSettings;
extern ZP_DD_REFRESH ZP_DD_Refresh;
extern ZP_SETSERVICECTRLHANDLE ZP_SetServiceCtrlHandle;
extern ZP_DEVICEEVENTNOTIFY ZP_DeviceEventNotify;
extern ZP_PORT_OPEN ZP_Port_Open;
extern ZP_PORT_SETBAUDANDEVCHAR ZP_Port_SetBaudAndEvChar;
extern ZP_PORT_GETBAUDANDEVCHAR ZP_Port_GetBaudAndEvChar;
extern ZP_PORT_GETCONNECTIONSTATUS ZP_Port_GetConnectionStatus;
extern ZP_PORT_SETNOTIFICATION ZP_Port_SetNotification;
extern ZP_PORT_ENUMMESSAGES ZP_Port_EnumMessages;
extern ZP_PORT_CLEAR ZP_Port_Clear;
extern ZP_PORT_WRITE ZP_Port_Write;
extern ZP_PORT_READ ZP_Port_Read;
extern ZP_PORT_GETINCOUNT ZP_Port_GetInCount;
extern ZP_PORT_SETDTR ZP_Port_SetDtr;
extern ZP_PORT_SETRTS ZP_Port_SetRts;
extern ZP_REGSERIALDEVICE ZP_RegSerialDevice;
extern ZP_REGIPDEVICE ZP_RegIpDevice;
#ifdef ZP_LOG
extern ZP_SETLOG ZP_SetLog;
extern ZP_GETLOG ZP_GetLog;
extern ZP_ADDLOG ZP_AddLog;
#else
inline HRESULT ZP_AddLog(WCHAR /*chSrc*/, UINT /*nType*/, UINT /*nMsgId*/, LPCWSTR /*pszText*/) { return 0; };
#endif // ZP_LOG

extern HMODULE	hZpLib;
extern INT nZpLoadCount;

#endif // !ZPORT_LINKONREQUEST

#ifndef ZPORT_EXPORTS
inline BOOL IsZPortLoaded()
{
#ifdef ZPORT_LINKONREQUEST
	return hZpLib != 0;
#else
	return TRUE;
#endif // ZPORT_LINKONREQUEST
}

HRESULT LoadZPort(LPCTSTR pszPath=NULL);
VOID UnloadZPort();

#endif // !ZPORT_EXPORTS

DEPRECATED_FN
inline HRESULT ZP_EnumSerialPorts(UINT nDevTypes,
	ZP_ENUMPORTSPROC pEnumProc, PVOID pUserData)
{
	HANDLE hList;
	int nPortCount;
	HRESULT hr = ZP_GetPortInfoList(&hList, &nPortCount, nDevTypes, 0);
	if (FAILED(hr))
		return hr;
	__try
	{
		_ZP_PORT_INFO rPI;
		for (int i = 0; i < nPortCount; i++)
		{
			if (FAILED(hr = ZP_GetPortInfo(hList, i, &rPI)))
				return hr;
			if (!pEnumProc(&rPI, pUserData))
				return ZP_S_CANCELLED;
		}
	}
	__finally
	{
		ZP_CloseHandle(hList);
	}
	return hr;
}
DEPRECATED_FN
inline HRESULT ZP_EnumMessages(HANDLE hHandle, ZP_NOTIFYPROC pEnumProc, PVOID pUserData)
{
	HRESULT hr;
	UINT nMsg;
	LPARAM nMsgParam;
	while ((hr = ZP_DD_GetNextMessage(hHandle, &nMsg, &nMsgParam)) == S_OK)
		pEnumProc(nMsg, nMsgParam, pUserData);
	if (hr == ZP_S_NOTFOUND)
		hr = S_OK;
	return hr;
}

#pragma deprecated(ZP_CloseNotification)
#define ZP_CloseNotification ZP_CloseHandle
#pragma deprecated(ZP_ProcessMessages)
#define ZP_ProcessMessages ZP_EnumMessages
#pragma deprecated(ZP_Open)
#define ZP_Open ZP_Port_Open
#pragma deprecated(ZP_Close)
#define ZP_Close ZP_CloseHandle
#pragma deprecated(ZP_SetBaudAndEvChar)
#define ZP_SetBaudAndEvChar ZP_Port_SetBaudAndEvChar
#pragma deprecated(ZP_GetBaudAndEvChar)
#define ZP_GetBaudAndEvChar ZP_Port_GetBaudAndEvChar
#pragma deprecated(ZP_GetStatus)
#define ZP_GetStatus ZP_Port_GetStatus
#pragma deprecated(ZP_SetStatusCallback)
#define ZP_SetStatusCallback ZP_Port_EnumMessages
#pragma deprecated(ZP_Clear)
#define ZP_Clear ZP_Port_Clear
#pragma deprecated(ZP_Write)
#define ZP_Write ZP_Port_Write
#pragma deprecated(ZP_Read)
#define ZP_Read ZP_Port_Read
#pragma deprecated(ZP_GetInCount)
#define ZP_GetInCount ZP_Port_GetInCount
#pragma deprecated(ZP_StartWaitEvent)
#define ZP_StartWaitEvent ZP_Port_SetNotification
#pragma deprecated(ZP_SetDtr)
#define ZP_SetDtr ZP_Port_SetDtr
#pragma deprecated(ZP_SetRts)
#define ZP_SetRts ZP_Port_SetRts
#pragma deprecated(ZP_SetNotification)
#define ZP_SetNotification ZP_DD_SetNotification
#pragma deprecated(ZP_GetNextMessage)
#define ZP_GetNextMessage ZP_DD_GetNextMessage
#pragma deprecated(ZP_SetDetectorSettings)
#define ZP_SetDetectorSettings ZP_DD_SetGlobalSettings
#pragma deprecated(ZP_GetDetectorSettings)
#define ZP_GetDetectorSettings ZP_DD_GetGlobalSettings
#pragma deprecated(ZP_UpdateDetector)
#define ZP_UpdateDetector ZP_DD_Refresh
