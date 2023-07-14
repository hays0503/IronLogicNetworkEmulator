#pragma once

// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа ZGUARD_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции ZGUARD_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.

// (rom) this is the switch to change between static and dynamic linking.
// (rom) it is enabled by default here.
// (rom) To disable simply change the '$' to a '.'.
//#define ZGUARD_LINKONREQUEST


#ifndef ZGUARD_LINKONREQUEST

#ifdef ZGUARD_EXPORTS
#define ZGUARD_API(type) extern "C" __declspec(dllexport) type __stdcall 
#else
#ifdef ZGUARD_STATIC
#define ZGUARD_API(type) extern "C" type __stdcall 
#else
#define ZGUARD_API(type) extern "C" __declspec(dllimport) type __stdcall
#endif
#endif

#endif // !ZGUARD_LINKONREQUEST

// Совместимая версия SDK
#define ZG_SDK_VER_MAJOR	3
#define ZG_SDK_VER_MINOR	39

#include "ZPort.h"
#include "ZBase.h"

// Коды ошибок
#define ZG_E_TOOLARGEMSG                 ((HRESULT)0x80040301L)	// Слишком большое сообщение для отправки
#define ZG_E_NOANSWER                    ((HRESULT)0x80040303L)	// Нет ответа
#define ZG_E_BADANSWER                   ((HRESULT)0x80040304L)	// Нераспознанный ответ
#define ZG_E_WRONGZPORT                  ((HRESULT)0x80040305L)	// Не правильная версия ZPort.dll
#define ZG_E_CVTBUSY                     ((HRESULT)0x80040306L)	// Конвертер занят (при открытии конвертера в режиме "Proxy")
#define ZG_E_CVTERROR                    ((HRESULT)0x80040307L)	// Другая ошибка конвертера
#define ZG_E_LICNOTFOUND                 ((HRESULT)0x80040308L)	// Ошибка конвертера: Нет такой лицензии
#define ZG_E_LICEXPIRED                  ((HRESULT)0x80040309L)	// Текущая лицензия истекла
#define ZG_E_LICONTROLLERS               ((HRESULT)0x8004030AL)	// Ошибка конвертера: ограничение лицензии на число контроллеров
#define ZG_E_LICREADKEYS                 ((HRESULT)0x8004030BL)	// Ограничение лицензии на число ключей при чтении
#define ZG_E_LICWRITEKEYS                ((HRESULT)0x8004030CL)	// Ограничение лицензии на число ключей при записи
#define ZG_E_LICEXPIRED2                 ((HRESULT)0x8004030DL)	// Срок лицензии истек (определено при установке даты в контроллере)
#define ZG_E_NOCONVERTER                 ((HRESULT)0x8004030EL) // Конвертер не найден (неверный адрес)
#define ZG_E_NOCONTROLLER                ((HRESULT)0x8004030FL)	// Неверный адрес контроллера (контроллер не найден)
#define ZG_E_CTRNACK                     ((HRESULT)0x80040310L) // Контроллер отказал в выполнении команды
#define ZG_E_FWBOOTLOADERNOSTART         ((HRESULT)0x80040311L) // Загрузчик не запустился (при прошивке)
#define ZG_E_FWFILESIZE                  ((HRESULT)0x80040312L) // Некорректный размер файла (при прошивке)
#define ZG_E_FWNOSTART                   ((HRESULT)0x80040313L) // Не обнаружен старт прошивки. Попробуйте перезагрузить устройство. (при прошивке)
#define ZG_E_FWNOCOMPATIBLE              ((HRESULT)0x80040314L) // Не подходит для этого устройства
#define ZG_E_FWINVALIDDEVNUM             ((HRESULT)0x80040315L) // Не подходит для этого номера устройства (при прошивке)
#define ZG_E_FWTOOLARGE                  ((HRESULT)0x80040316L) // Слишком большой размер данных прошивки (при прошивке)
#define ZG_E_FWSEQUENCEDATA              ((HRESULT)0x80040317L) // Некорректная последовательность данных (при прошивке)
#define ZG_E_FWDATAINTEGRITY             ((HRESULT)0x80040318L) // Целостность данных нарушена (при прошивке)
#define ZG_E_WRONGCRC                    ((HRESULT)0x80040319L) // Неверная контрольная сумма
#define ZG_E_CTRISALREADYOPEN            ((HRESULT)0x8004031AL) // Контроллер уже открыт функцией ZG_Ctr_Open

#pragma pack(1)   // turn byte alignment on

#define ZG_IF_LOG						0x100	// Записывать лог

#define ZG_DEVTYPE_GUARD				1
#define ZG_DEVTYPE_Z397					2
#define ZG_DEVTYPE_COM					5
#define ZG_DEVTYPE_IPGUARD				(ZP_MAX_REG_DEV)
#define ZG_DEVTYPE_CVTS					0x26
#define ZG_IPDEVTYPE_CVTS				1

#define ZG_MAX_LICENSES					16	// Максимальное количество лицензий, которое можно установить в конвертер
#define ZG_DEF_CVT_LICN					5	// Номер лицензии конвертера по умолчанию
#define ZG_MAX_TIMEZONES				7	// Максимум временных зон
#define ZG_MODES_TZ0					-2	// Номер первой вр.зоны для переключения режима контроллера, всего 2 зоны
#define ZG_DUAL_ZONE_TZ0				-9	// Номер первой вр.зоны во втором наборе, всего 7 зон

// Значения по умолчанию
#define ZG_CVT_SCANCTRSPERIOD		5000	// Период сканирования контроллеров (в миллисекундах)
#define ZG_CVT_SCANCTRSLASTADDR		31		// Последней сканируемый адрес контроллера (для альтернативного метода сканирования)

#ifndef ZR_DEVTYPE_READERS
// Модель конвертера
enum ZG_CVT_TYPE : INT
{
	ZG_CVT_UNDEF = 0,		// Не определено
	ZG_CVT_Z397,			// Z-397
	ZG_CVT_Z397_GUARD,		// Z-397 Guard
	ZG_CVT_Z397_IP,			// Z-397 IP
	ZG_CVT_Z397_WEB,		// Z-397 Web
	ZG_CVT_Z5R_WEB,			// Z5R Web
	ZG_CVT_MATRIX2WIFI,		// Matrix II Wi-Fi
	ZG_CVT_MATRIX6WIFI,		// Matrix VI Wi-Fi
	ZG_CVT_Z5R_WEB_BT,		// Z5R-WEB BT
	ZG_CVT_Z5R_WIFI,		// Z5R Wi-Fi
	ZG_CVT_MATRIX2EHWEB,	// Matrix-II EH Web
	ZG_CVT_MATRIX6EHWEB,	// Matrix-VI EH Web
	ZG_CVT_Z5R_WEB_MINI		// Z5R Web mini
};

// Режим конвертера Z397 Guard
enum ZG_GUARD_MODE : INT
{
	ZG_GUARD_UNDEF = 0,		// Не определено
	ZG_GUARD_NORMAL,		// Режим "Normal" (эмуляция обычного конвертера Z397)
	ZG_GUARD_ADVANCED,		// Режим "Advanced"
	ZG_GUARD_TEST,			// Режим "Test" (для специалистов)
	ZG_GUARD_ACCEPT			// Режим "Accept" (для специалистов)
};

// Информация о конвертере, возвращаемая функцией ZG_SearchDevices
typedef struct _ZG_ENUM_IPCVT_INFO : _ZP_DEVICE_INFO
{
	ZG_CVT_TYPE nType;		// Модель IP-конвертера
	ZG_GUARD_MODE nMode;	// Режим работы конвертера Guard
	DWORD nFlags;			// Флаги: бит 0 - "VCP", бит 1 - "WEB", 0xFF - "All"
} *PZG_ENUM_IPCVT_INFO;
#endif // !ZR_DEVTYPE_READERS

// Скорость конвертера
enum ZG_CVT_SPEED : UINT
{
	ZG_SPEED_19200	= 19200,
	ZG_SPEED_57600	= 57600
};

// Информация о конвертере, возвращаемая функцией ZG_SearchDevices
typedef struct _ZG_ENUM_CVT_INFO : _ZP_DEVICE_INFO
{
	ZG_CVT_TYPE nType;		// Тип конвертера
	ZG_GUARD_MODE nMode;	// Режим работы конвертера Guard
} *PZG_ENUM_CVT_INFO;


// Информация о конвертере, возвращаемая функциями: ZG_Cvt_Open, ZG_Cvt_AttachPort и ZG_Cvt_GetInformation
typedef struct _ZG_CVT_INFO : _ZP_DEVICE_INFO
{
	ZG_CVT_TYPE nType;		// Тип конвертера
	ZG_CVT_SPEED nSpeed;	// Скорость конвертера

	ZG_GUARD_MODE nMode;	// Режим работы конвертера Guard

	LPWSTR pszLinesBuf;		// Буфер для информационных строк
	INT nLinesBufMax;		// Размер буфера в символах, включая завершающий '\0'
} *PZG_CVT_INFO;

// Флаги для ZG_CVT_OPEN_PARAMS.nFlags
enum _ZG_CVT_OPEN_FLAGS
{
	ZG_OF_NOCHECKLIC	= 0x0001,	// Не проверять/обновлять лицензию
	ZG_OF_NOSCANCTRS	= 0x0002	// Не сканировать контроллеры
};
typedef UINT ZG_CVTO_FLAGS;
// Параметры открытия конвертера (для функции ZG_Cvt_Open)
typedef struct _ZG_CVT_OPEN_PARAMS
{
	ZP_PORT_TYPE nType;			// Тип порта
	LPCWSTR pszName;			// Имя порта. Если =NULL, то используется hPort
	HANDLE hPort;				// Дескриптор порта, полученный функцией ZP_Open
	ZG_CVT_TYPE nCvtType;		// Тип конвертера. Если =ZG_CVT_UNDEF, то автоопределение
	ZG_CVT_SPEED nSpeed;		// Скорость конвертера
	PZP_WAIT_SETTINGS pWait;	// Параметры ожидания. Может быть =NULL.
	BYTE nStopBits;				
	INT nLicN;					// Номер лицензии. Если =0, то используется ZG_DEF_CVT_LICN
	LPCSTR pActCode;			// Код активации для режима "Proxy"
	int nSn;					// С/н конвертера для режима "Proxy"
	ZG_CVTO_FLAGS nFlags;		// Флаги ZG_OF_...
} *PZG_CVT_OPEN_PARAMS;

// Информация о лицензии конвертера Guard
typedef struct _ZG_CVT_LIC_INFO
{
	WORD nStatus;			// Статус лицензии
	WORD Reserved;			// Зарезервировано для выравнивания структуры
	INT nMaxCtrs;			// Максимальное количество контроллеров
	INT nMaxKeys;			// Максимальное количество ключей
	WORD nMaxYear;			// Дата: год (= 0xFFFF дата неограничена)
	WORD nMaxMon;			// Дата: месяц
	WORD nMaxDay;			// Дата: день
	WORD nDownCountTime;	// Оставшееся время жизни лицензии в минутах
} *PZG_CVT_LIC_INFO;

// Краткая информация о лицензии конвертера Guard
typedef struct _ZG_CVT_LIC_SINFO
{
	int nLicN;				// Номер лицензии
	int nMaxCtrs;			// Максимальное количество контроллеров
	INT nMaxKeys;			// Максимальное количество ключей
} *PZG_CVT_LIC_SINFO;

// Модель контроллера
enum ZG_CTR_TYPE : INT
{
	ZG_CTR_UNDEF	= 0,	// Не определено
	ZG_CTR_GATE2K,			// Gate 2000
	ZG_CTR_MATRIX2NET,		// Matrix II Net
	ZG_CTR_MATRIX3NET,		// Matrix III Net
	ZG_CTR_Z5RNET,			// Z5R Net
	ZG_CTR_Z5RNET8K,		// Z5R Net 8000
	ZG_CTR_GUARDNET,		// Guard Net
	ZG_CTR_Z9,				// Z-9 EHT Net
	ZG_CTR_EUROLOCK,		// EuroLock EHT net
	ZG_CTR_Z5RWEB,			// Z5R Web
	ZG_CTR_MATRIX2WIFI,		// Matrix II Wi-Fi
	ZG_CTR_MATRIX6NFC,		// Matrix-VI NFC Net 8k
	ZG_CTR_MATRIX6EHK,		// Matrix-VI EHK Net 2k
	ZG_CTR_MATRIX6WIFI,		// Matrix VI Wi-Fi
	ZG_CTR_Z5R_WEB_BT,		// Z5R-WEB BT
	ZG_CTR_Z5R_WIFI,		// Z5R Wi-Fi
	ZG_CTR_MATRIX2EHWEB,	// Matrix-II EH Web
	ZG_CTR_MATRIX6EHWEB,	// Matrix-VI EH Web
	ZG_CTR_Z5R_WEB_MINI		// Z5R Web mini
};

// Тип точки прохода
enum ZG_CTR_SUB_TYPE: INT
{
	ZG_CS_UNDEF	= 0,			// Не определено
	ZG_CS_DOOR,					// Дверь
	ZG_CS_TURNSTILE,			// Турникет
	ZG_CS_GATEWAY,				// Шлюз
	ZG_CS_BARRIER,				// Шлакбаум
	ZG_CS_ELECTROMAGNETIC,		// Электромагнитный замок
	ZG_CS_ELECTROMECHANICAL,	// Электромеханический замок
	ZG_CS_MOTORTWORELAYS,		// Моторный через два реле
	ZG_CS_MOTORONERELAY,		// Моторный через одно реле
	ZG_CS_ELECTRICAL,			// Электроконтроль
	ZG_CS_AUTOCONTROL			// Автоконтроль
};

// Флаги контроллера
enum _ZG_CTR_INFO_FLAGS
{
	ZG_CTR_F_2BANKS		= 0x0001,	// 2 банка / 1 банк
	ZG_CTR_F_PROXIMITY	= 0x0002,	// Тип ключей: Proximity (Wiegand-26) / TouchMemory (Dallas)
	ZG_CTR_F_JOIN		= 0x0004,	// Объединение двух банков
	ZG_CTR_F_X2			= 0x0008,	// Удвоение ключей
	ZG_CTR_F_ELECTRO	= 0x0010,	// Функция ElectroControl (для Matrix II Net FW 3.X)
	ZG_CTR_F_MODES		= 0x0020,	// Поддержка режимов прохода
	ZG_CTR_F_DUAL_ZONE	= 0x0040,	// Поддержка двух наборов временных зон
	ZG_CTR_F_APB		= 0x0080,	// Поддержка AntiPassBack (APB)
	ZG_CTR_F_BIGTIME	= 0x0100,	// Поддержка больших времен замка
	ZG_CTR_F_EXTASK		= 0x0200,	// Поддержка запроса ExtAsk
	ZG_CTR_F_DUALKEY	= 0x0400,	// Поддержка двойных карт (ключей с флагом ZG_KF_DUAL)
	ZG_CTR_F_BOOTMODE	= 0x8000	// Устройство в режиме "boot"
};
typedef UINT ZG_CTRI_FLAGS;

// Информация о найденном контроллере, возвращаемая функцией ZG_Cvt_FindNextCtr
typedef struct _ZG_FIND_CTR_INFO
{
	ZG_CTR_TYPE nType;			// Тип контроллера
	BYTE nTypeCode;				// Код типа контроллера
	BYTE nAddr;					// Сетевой адрес
	INT nSn;					// Серийный номер (с/н)
	WORD nVersion;				// Версия прошивки
	INT nMaxKeys;				// Максимум ключей
	INT nMaxEvents;				// Максимум событий
	ZG_CTRI_FLAGS nFlags;		// Флаги контроллера (ZG_CTR_F_...)
	ZG_CTR_SUB_TYPE nSubType;	// Подтип контроллера
} *PZG_FIND_CTR_INFO;

// Информация о контроллере, возвращаемая функциями: ZG_Ctr_Open и ZG_Ctr_GetInformation
typedef struct _ZG_CTR_INFO
{
	ZG_CTR_TYPE nType;			// Тип контроллера
	BYTE nTypeCode;				// Код типа контроллера
	BYTE nAddr;					// Сетевой адрес
	INT nSn;					// Серийный номер (с/н)
	WORD nVersion;				// Версия ПО
	INT nInfoLineCount;			// Количество строк с информацией
	INT nMaxKeys;				// Максимум ключей
	INT nMaxEvents;				// Максимум событий
	UINT nFlags;				// Флаги контроллера (ZG_CTR_F_...)
	LPWSTR pszLinesBuf;			// Буфер для информационных строк
	INT nLinesBufMax;			// Размер буфера в символах, включая завершающий '\0'
	ZG_CTR_SUB_TYPE nSubType;	// Подтип контроллера
	INT nOptReadItems;			// Количество элементов, которое может быть считано одним запросом контроллеру 
	INT nOptWriteItems;			// Количество элементов, которое может быть записано одним запросом контроллеру
} *PZG_CTR_INFO;

// Флаги параметров маски для ZG_Ctr_WriteLockTimes
enum _ZG_LOCKTIMES_MASK_FLAGS
{
	ZG_LTMF_OPENTIME		= 0x00000001,	// Время открытия двери
	ZG_LTMF_LETTIME			= 0x00000002,	// Время контроля открытия
	ZG_LTMF_MAXTIME			= 0x00000004,	// Время контроля закрытия
	ZG_LTMF_BIGTIME			= 0x00000008	// Использовать формат большого времени по возможности
};
typedef UINT ZGLTMF;

// Режим прохода контроллера
enum ZG_CTR_MODE: INT
{
	ZG_MODE_UNDEF = 0,
	ZG_MODE_NORMAL,			// Обычный режим работы
	ZG_MODE_BLOCK,			// Блокировка (проходить могут только "блокирующие" карты)
	ZG_MODE_FREE,			// Свободный (замок обесточен, при поднесении карты регистрируются)
	ZG_MODE_WAIT			// Ожидание (обычный режим работы, при поднесении допустимой карты переход в режим "Free")
};

// Режим HOTEL
enum ZG_HOTEL_MODE
{
	ZG_HMODE_UNDEF	= 0,
	ZG_HMODE_NORMAL,		// Норма
	ZG_HMODE_BLOCK,			// Блокирован 
	ZG_HMODE_FREE,			// Свободный проход 
	ZG_HMODE_RESERVED		// Резерв 
};

// Временная зона контроллера
typedef struct _ZG_CTR_TIMEZONE
{
	BYTE nDayOfWeeks;		// Дни недели
	BYTE nBegHour;			// Начало: час
	BYTE nBegMinute;		// Начало: минута
	BYTE nEndHour;			// Конец: час
	BYTE nEndMinute;		// Конец: минута
	BYTE Reserved[3];
	ZG_CTR_MODE nMode;		// Режим контроллера (используется только для вр.зон ZG_MODES_TZ0..ZG_MODES_TZ0+1)
} *PZG_CTR_TIMEZONE;

// Тип ключа контроллера
enum ZG_CTR_KEY_TYPE : INT
{
	ZG_KEY_UNDEF = 0,	// Не определено
	ZG_KEY_NORMAL,		// Обычный
	ZG_KEY_BLOCKING,	// Блокирующий
	ZG_KEY_MASTER		// Мастер
};

// Флаги для ключа
enum _ZG_CTR_KEY_FLAGS
{
	ZG_KF_FUNCTIONAL		= 0x0002,	// Функциональная
	ZG_KF_DUAL				= 0x0004,	// Двойная карта
	ZG_KF_SHORTNUM			= 0x0020	// Короткий номер. Если fProximity=False, то контроллер будет проверять только первые 3 байта номера ключа.
};
typedef UINT ZG_KEY_FLAGS;

// Ключ контроллера
typedef struct _ZG_CTR_KEY
{
	BOOL fErased;				// TRUE, если ключ стерт
	Z_KEYNUM rNum;				// Номер ключа
	ZG_CTR_KEY_TYPE nType;		// Тип ключа
	ZG_KEY_FLAGS nFlags;		// Флаги ZG_KF_...
	UINT nAccess;				// Доступ (маска временных зон)
	BYTE aData1[4];				// Другие данные ключа
} *PZG_CTR_KEY;

// Часы контроллера
typedef struct _ZG_CTR_CLOCK
{
	// флаг "часы остановлены"
	BOOL fStopped;				// TRUE, если часы остановлены
	// дата и время
	WORD nYear;					// Год
	WORD nMonth;				// Месяц
	WORD nDay;					// День
	WORD nHour;					// Час
	WORD nMinute;				// Минута
	WORD nSecond;				// Секунда
} *PZG_CTR_CLOCK;

// Тип события контроллера
enum ZG_CTR_EV_TYPE : INT
{
	ZG_EV_UNKNOWN = 0,			// Неизвестно
	ZG_EV_BUT_OPEN,				// Открыто кнопкой изнутри
	ZG_EV_KEY_NOT_FOUND,		// Ключ не найден в банке ключей
	ZG_EV_KEY_OPEN,				// Ключ найден, дверь открыта
	ZG_EV_KEY_ACCESS,			// Ключ найден, доступ не разрешен
	ZG_EV_REMOTE_OPEN,			// Открыто оператором по сети
	ZG_EV_KEY_DOOR_BLOCK,		// Ключ найден, дверь заблокирована
	ZG_EV_BUT_DOOR_BLOCK,		// Попытка открыть заблокированную дверь кнопкой
	ZG_EV_NO_OPEN,				// Дверь взломана
	ZG_EV_NO_CLOSE,				// Дверь оставлена открытой (timeout)
	ZG_EV_PASSAGE,				// Проход состоялся
	ZG_EV_SENSOR1,				// Сработал датчик 1 (охрана)
	ZG_EV_SENSOR2,				// Сработал датчик 2 (пожар)
	ZG_EV_REBOOT,				// Перезагрузка контроллера
	ZG_EV_BUT_BLOCK,			// Заблокирована кнопка открывания
	ZG_EV_DBL_PASSAGE,			// Попытка двойного прохода
	ZG_EV_OPEN,					// Дверь открыта штатно
	ZG_EV_CLOSE,				// Дверь закрыта
	ZG_EV_POWEROFF,				// Питание (0 – пропало, 1 – появилось)
	ZG_EV_ELECTRO_ON,			// Включение электропитания
	ZG_EV_ELECTRO_OFF,			// Выключение электропитания
	ZG_EV_LOCK_CONNECT,			// Включение замка (триггер)
	ZG_EV_LOCK_DISCONNECT,		// Отключение замка (триггер)
	ZG_EV_MODE_STATE,			// Переключение режимов работы (cм Режим)
	ZG_EV_FIRE_STATE,			// Изменение состояния Пожара
	ZG_EV_SECUR_STATE,			// Изменение состояния Охраны
	ZG_EV_UNKNOWN_KEY,			// Неизвестный ключ
	ZG_EV_GATEWAY_PASS,			// Совершен вход в шлюз
	ZG_EV_GATEWAY_BLOCK,		// Заблокирован вход в шлюз (занят)
	ZG_EV_GATEWAY_ALLOWED,		// Разрешен вход в шлюз
	ZG_EV_ANTIPASSBACK,			// Заблокирован проход (Антипассбек)
	ZG_EV_HOTEL40,				// Hotel (Изменение режима работы)
	ZG_EV_HOTEL41				// Hotel (Отработка карт)
};

// Событие контроллера
typedef struct _ZG_CTR_EVENT
{
	ZG_CTR_EV_TYPE nType;			// Тип события
	union
	{
		struct
		{
			BYTE nCode;				// Код события в контроллере
			BYTE aParams[7];		// Параметры события
		} ep;
		BYTE aData[8];				// Данные события (используйте функцию декодирования, соответстующую типу события, 
									//	ZG_Ctr_DecodePassEvent, ZG_Ctr_DecodeEcEvent, ZG_Ctr_DecodeUnkKeyEvent, ZG_Ctr_DecodeFireEvent, ZG_Ctr_DecodeSecurEvent)
	};
} *PZG_CTR_EVENT;

// Направление прохода контроллера
enum ZG_CTR_DIRECT : INT
{
	ZG_DIRECT_UNDEF = 0,	// Не определено
	ZG_DIRECT_IN,			// Вход
	ZG_DIRECT_OUT			// Выход
};

// Дата и время события
typedef struct _ZG_EV_TIME
{
	BYTE nMonth;				// Месяц
	BYTE nDay;					// День
	BYTE nHour;					// Час
	BYTE nMinute;				// Минута
	BYTE nSecond;				// Секунда
	BYTE Reserved[3];
} *PZG_EV_TIME;

// Условие, вызвавшее событие ElectroControl: ZG_EV_ELECTRO_ON, ZG_EV_ELECTRO_OFF
enum ZG_EC_SUB_EV : INT
{
	ZG_EC_EV_UNDEF = 0,		// Не определено
	ZG_EC_EV_CARD_DELAY,	// Поднесена валидная карта с другой стороны (для входа) запущена задержка
	ZG_EC_EV_RESERVED1,		// (зарезервировано)
	ZG_EC_EV_ON_NET,		// Включено командой по сети
	ZG_EC_EV_OFF_NET,		// Выключено командой по сети
	ZG_EC_EV_ON_SCHED,		// Включено по временной зоне
	ZG_EC_EV_OFF_SHED,		// Выключено по временной зоне
	ZG_EC_EV_CARD,			// Поднесена валидная карта к контрольному устройству
	ZG_EC_EV_RESERVED2,		// (зарезервировано)
	ZG_EC_EV_OFF_TIMEOUT,	// Выключено после отработки таймаута
	ZG_EC_EV_OFF_EXIT		// Выключено по срабатыванию датчика выхода
};

// Условие, вызвавшее событие ZG_EV_FIRE_STATE
enum ZG_FIRE_SUB_EV: INT
{
	ZG_FR_EV_UNDEF = 0,		// Не определено
	ZG_FR_EV_OFF_NET,		// выключено по сети
	ZG_FR_EV_ON_NET,		// Включено по сети
	ZG_FR_EV_OFF_INPUT_F,	// Выключено по входу FIRE
	ZG_FR_EV_ON_INPUT_F,	// Включено по входу FIRE
	ZG_FR_EV_OFF_TEMP,		// Выключено по датчику температуры
	ZG_FR_EV_ON_TEMP		// Включено по датчику температуры
};

// Условие, вызвавшее событие ZG_EV_SECUR_STATE
enum ZG_SECUR_SUB_EV: INT
{
	ZG_SR_EV_UNDEF = 0,		// Не определено
	ZG_SR_EV_OFF_NET,		// выключено по сети
	ZG_SR_EV_ON_NET,		// Включено по сети
	ZG_SR_EV_OFF_INPUT_A,	// Выключено по входу ALARM
	ZG_SR_EV_ON_INPUT_A,	// Включено по входу ALARM
	ZG_SR_EV_OFF_TAMPERE,	// Выключено по тамперу
	ZG_SR_EV_ON_TAMPERE,	// Включено по тамперу
	ZG_SR_EV_OFF_DOOR,		// Выключено по датчику двери
	ZG_SR_EV_ON_DOOR		// Включено по датчику двери
};

// Условие, вызвавшее событие ZG_EV_MODE_STATE
enum ZG_MODE_SUB_EV: INT
{
	ZG_MD_EV_UNDEF = 0,
	ZG_MD_EV_RS485_ALLOW,		// Установка командой по сети 
	ZG_MD_EV_RS485_DENIED,		// Отказано оператору по сети
	ZG_MD_EV_TZ_START,			// Началась временная зона
	ZG_MD_EV_TZ_FINISH,			// Окончилась временная зона
	ZG_MD_EV_CARD_ALLOW,		// Установка картой
	ZG_MD_EV_CARD_DENIED		// Отказано изменению картой
};

// Адреса внешних устройств для функции ZG_Ctr_ControlDevices
#define ZG_DEV_RELE1		0	// реле номер 1
#define ZG_DEV_RELE2		1	// реле номер 2
#define ZG_DEV_SW3			2	// силовой ключ SW3 (ОС) Конт.5 колодки К5
#define ZG_DEV_SW4			3	// силовой ключ SW4 (ОС) Конт.5 колодки К6
#define ZG_DEV_SW0			4	// силовой ключ SW0 (ОС) Конт.1 колодки К4
#define ZG_DEV_SW1			5	// силовой ключ SW1 (ОС) Конт.3 колодки К4
#define ZG_DEV_K65			6	// слаботочный ключ (ОК) Конт.6 колодки К5
#define ZG_DEV_K66			7	// слаботочный ключ (ОК) Конт.6 колодки К6

// Флаги конфигурации электропитания
enum _ZG_CTR_ELECTROCONTROL_CONFIG_FLAGS
{
	ZG_EC_CF_ENABLED		= 0x0001,	// Задействовать управление питанием
	ZG_EC_CF_SCHEDULE		= 0x0002,	// Использовать временную зону 6 для включения питания
	ZG_EC_CF_EXT_READER		= 0x0004,	// Контрольный считыватель: «0» Matrix-II Net, «1» внешний считыватель
	ZG_EC_CF_INVERT			= 0x0008,	// Инвертировать управляющий выход
	ZG_EC_CF_EXIT_OFF		= 0x0010,	// Задействовать датчик двери
	ZG_EC_CF_CARD_OPEN		= 0x0020	// Не блокировать функцию открывания для контрольного считывателя
};
typedef UINT ZG_CTRECC_FLAGS;

// Конфигурация управления электропитанием
typedef struct _ZG_CTR_ELECTRO_CONFIG
{
	ZG_CTRECC_FLAGS nPowerConfig;	// Конфигурация управления питанием
	DWORD nPowerDelay;				// Время задержки в секундах
	_ZG_CTR_TIMEZONE rTz6;			// Временная зона №6 (считаем от 0)
} *PZG_CTR_ELECTRO_CONFIG;

// Флаги состояния электропитания
enum _ZG_CTR_ELECTROCONTROL_STATE_FLAGS
{
	ZG_EC_SF_ENABLED		= 0x0001,	// Состояние питания – 1 вкл/0 выкл
	ZG_EC_SF_SCHEDULE		= 0x0002,	// Активно включение по временной зоне
	ZG_EC_SF_REMOTE			= 0x0004,	// Включено по команде по сети
	ZG_EC_SF_DELAY			= 0x0008,	// Идет отработка задержки
	ZG_EC_SF_CARD			= 0x0010	// Карта в поле контрольного считывателя
};
typedef UINT ZG_CTRECS_FLAGS;

// Состояние электропитания
typedef struct _ZG_CTR_ELECTRO_STATE
{
	ZG_CTRECS_FLAGS nPowerFlags;		// Флаги состояния электропитания
	ZG_CTRECC_FLAGS nPowerConfig;		// Конфигурация управления питанием
	DWORD nPowerDelay;					// Время задержки в секундах
} *PZG_CTR_ELECTRO_STATE;

// Флаги состояния режима Пожар
enum _ZG_CTR_FIRE_STATE_FLAGS
{
	ZG_FR_F_ENABLED			= 0x0001,	// Состояние пожарного режима – 1 вкл/0 выкл
	ZG_FR_F_INPUT_F			= 0x0002,	// Активен пожарный режим по входу FIRE
	ZG_FR_F_TEMP			= 0x0004,	// Активен пожарный режим по превышению температуры
	ZG_FR_F_NET				= 0x0008	// Активен пожарный режим по внешней команде
};
typedef UINT ZG_CTRFS_FLAGS;
// Флаги для маски разрешения источников режима Пожар
enum _ZG_CTR_FIRE_SRC_FLAGS
{
	ZG_FR_SRCF_INPUT_F		= 0x0001,	// Разрешен пожарный режим по входу FIRE
	ZG_FR_SRCF_TEMP			= 0x0002	// Разрешен пожарный режим по превышению температуры
};
typedef UINT ZG_CTRFSR_FLAGS;

// Режим Охрана
enum ZG_SECUR_MODE: INT
{
	ZG_SR_M_UNDEF = 0,		// Не определено
	ZG_SR_M_SECUR_OFF,		// Выключить режим охраны
	ZG_SR_M_SECUR_ON,		// Включить режим охраны
	ZG_SR_M_ALARM_OFF,		// Выключить тревогу
	ZG_SR_M_ALARM_ON		// Включить тревогу
};

// Флаги состояния режима Охрана
enum _ZG_CTR_SECURE_STATE_FLAGS
{
	ZG_SR_F_ENABLED			= 0x0001,	// Состояние охранного режима – 1 вкл/0 выкл
	ZG_SR_F_ALARM			= 0x0002,	// Состояние тревоги
	ZG_SR_F_INPUT_A			= 0x0004,	// Тревога по входу ALARM
	ZG_SR_F_TAMPERE			= 0x0008,	// Тревога по тамперу
	ZG_SR_F_DOOR			= 0x0010,	// Тревога по датчику двери
	ZG_SR_F_NET				= 0x0020	// Тревога включена по сети
};
typedef UINT ZG_CTRSS_FLAGS;

// Флаги для маски разрешения источников режима Охрана
enum _ZG_CTR_SECURE_SRC_FLAGS
{
	ZG_SR_SRCF_INPUT_F		= 0x0001,	// Разрешена тревога по входу FIRE
	ZG_SR_SRCF_TAMPERE		= 0x0002,	// Разрешена тревога по тамперу
	ZG_SR_SRCF_DOOR			= 0x0004	// Разрешена тревога по датчику двери
};
typedef UINT ZG_CTRSSR_FLAGS;

// Условие, вызвавшее события ZG_EV_HOTEL40, ZG_EV_HOTEL41
enum ZG_HOTEL_SUB_EV : INT
{
	ZG_H_EV_UNDEF = 0,		// Не определено
	ZG_H_EV_FREECARD,		// Карта открытия
	ZG_H_EV_BLOCKCARD,		// Карта блокирующая
	ZG_H_EV_EXFUNC,			// Дополнительная функция
	ZG_H_EV_NEWRCARD,		// Создана резервная карта
	ZG_H_EV_NETWORK,
	ZG_H_EV_TIMEZONE,
	ZG_H_EV_COUNTER,		// Обновлен счетчик
	ZG_H_EV_CRYPTOKEY,		// Обновлен криптоключ
	ZG_H_EV_PULSEZ,			// Измененение защелки в течении 2х секунд
	ZG_H_EV_STATE			// Состояние защелки -если нажали ручку и отпустили более чем через 2 секунды 
};

// Флаги для событий ZG_EV_HOTEL40, ZG_EV_HOTEL41
#define ZG_HF_LATCH			1	// Защёлка
#define ZG_HF_LATCH2		2	// Задвижка
#define ZG_HF_KEY			4	// Ключ
#define ZG_HF_CARD			8	// Карта

// Флаги для функции ZG_Cvt_SetNotification и структуры _ZG_CVT_NOTIFY_SETTINGS
enum _ZG_CVTN_FLAGS
{
	ZG_NF_CVT_CTR_EXIST			= 0x0001,	// ZG_N_CVT_CTR_INSERT / ZG_N_CVT_CTR_REMOVE
	ZG_NF_CVT_CTR_CHANGE		= 0x0002,	// Изменение параметров контроллера ZG_N_CVT_CTR_CHANGE
	ZG_NF_CVT_ERROR				= 0x0004,	// ZG_N_CVT_ERROR
	ZG_CVTNF_CONNECTION_CHANGE	= 0x0008,	// ZG_CVN_CONNECTIONSTATUS
	ZG_NF_CVT_CTR_DBL_CHECK		= 0x1000,	// Дважды проверять отключение контроллеров
	ZG_NF_CVT_REASSIGN_ADDRS	= 0x2000,	// Автоматическое переназначение адресов контроллеров (работает только с ZG_NF_CVT_CTR_EXIST)
	ZG_NF_CVT_RESCAN_CTRS		= 0x10000,	// Начать заново сканирование контроллеров (для Z-397 и Z-397 Guard в режиме Normal)
	ZG_NF_CVT_ALT_SCAN			= 0x20000,	// Альтернативный метод скарирования
	ZG_NF_CVT_NOGATE			= 0x40000,	// Не сканировать GATE-контроллеры (все, кроме Eurolock)
	ZG_NF_CVT_NOEUROLOCK		= 0x80000	// Не сканировать Eurolock EHT net
};
typedef UINT ZG_CVTN_FLAGS;

// Уведомления функции ZG_Cvt_SetNotification (wParam - MsgCode, lParam - MsgParam)
typedef enum _ZG_CVT_NOTIFICATIONS
{
	ZG_N_CVT_CTR_INSERT			= 1,	// Контроллер подключен PZG_FIND_CTR_INFO(MsgParam) - информация о контроллере
	ZG_N_CVT_CTR_REMOVE			= 2,	// Контроллер отключен PZG_FIND_CTR_INFO(MsgParam) - информация о контроллере
	ZG_N_CVT_CTR_CHANGE			= 3,	// Изменены параметры контроллера PZG_N_CTR_CHANGE_INFO(MsgParam)
	ZG_N_CVT_ERROR				= 4,	// Возникла ошибка в нити (HRESULT*)nMsgParam - код ошибки
	ZG_CVTN_CONNECTION_CHANGE	= 5		// Изменилось состояние подключения
} ZG_CVT_NOTIFICATIONS;

typedef struct _ZG_N_CTR_CHANGE_INFO
{
	UINT nChangeMask;			// Маска изменений (бит0 addr, бит1 version, бит2 flags)
	_ZG_FIND_CTR_INFO rCtrInfo;	// Измененная информация о контроллере
	WORD nOldVersion;			// Старое значение версии
	BYTE nOldAddr;				// Старое значение адреса
	BYTE Reserved;				// Зарезервировано для выравнивания структуры
} *PZG_N_CTR_CHANGE_INFO;

// Настройки уведомлений конвертера
typedef struct _ZG_CVT_NOTIFY_SETTINGS
{
	ZG_CVTN_FLAGS nNMask;		// Маска типов уведомлений (ZG_NF_CVT_...)

	HANDLE hEvent;				// Событие (объект синхронизации)
	HWND hWindow;				// Окно, принимиющее сообщение nWndMsgId
	UINT nWndMsgId;				// Сообщение для отправки окну hWnd

	DWORD nScanCtrsPeriod;		// Период сканирования списка контроллеров в мс. Если =0, используется значение по умолчанию ZG_CVT_SCANCTRSPERIOD. Если =-1, никогда
	INT nScanCtrsLastAddr;		// Последней сканируемый адрес контроллера. Если =0, используется значение по умолчанию ZG_CVT_SCANCTRSLASTADDR
} *PZG_CVT_NOTIFY_SETTINGS;

// Флаги для функции ZG_Ctr_SetNotification и структуры _ZG_CTR_NOTIFY_SETTINGS
enum _ZG_CTRN_FLAGS
{
	ZG_NF_CTR_NEW_EVENT			= 0x0001,	// ZG_N_CTR_NEW_EVENT
	ZG_NF_CTR_CLOCK				= 0x0002,	// ZG_N_CTR_CLOCK
	ZG_NF_CTR_KEY_TOP			= 0x0004,	// ZG_N_CTR_KEY_TOP
	ZG_NF_CTR_ADDR_CHANGE		= 0x0008,	// ZG_N_CTR_ADDR_CHANGE
	ZG_NF_CTR_ERROR				= 0x0010	// ZG_N_CTR_ERROR
};
typedef UINT ZG_CTRN_FLAGS;

// Уведомления функции ZG_Ctr_SetNotification
typedef enum _ZG_CTR_NOTIFICATIONS
{
	ZG_N_CTR_NEW_EVENT			= 1,	// Новые события PZG_N_NEW_EVENT_INFO(MsgParam) - информация
	ZG_N_CTR_CLOCK				= 2,	// Величина рассинхронизации в секундах PINT64(MsgParam)
	ZG_N_CTR_KEY_TOP			= 3,	// Изменилась верхняя граница ключей PZG_N_KEY_TOP_INFO(MsgParam) - информация
	ZG_N_CTR_ADDR_CHANGE		= 4,	// Изменен сетевой адрес контроллера PBYTE(MsgParam) = новый адрес
	ZG_N_CTR_ERROR				= 5		// Возникла ошибка в нити PHRESULT(MsgParam) - код ошибки
} ZG_CTR_NOTIFICATIONS;

// Информация для уведомления ZG_N_CTR_NEW_EVENT
typedef struct _ZG_N_NEW_EVENT_INFO
{
	INT nNewCount;		// Количество новых событий
	INT nWriteIdx;		// Указатель записи
	INT nReadIdx;		// Указатель чтения
	Z_KEYNUM rLastNum;	// Номер последнего поднесенного ключа
} *PZG_N_NEW_EVENT_INFO;

// Информация для уведомления ZG_N_CTR_KEY_TOP
typedef struct _ZG_N_KEY_TOP_INFO
{
	INT nBankN;			// Номер банка ключей
	INT nNewTopIdx;		// Новое значение верхней границы ключей
	INT nOldTopIdx;		// Старое значение верхней границы ключей
} *PZG_N_KEY_TOP_INFO;

// Настройки уведомлений контроллера
typedef struct _ZG_CTR_NOTIFY_SETTINGS
{
	ZG_CTRN_FLAGS nNMask;		// Маска типов уведомлений (ZG_NF_CTR_...)

	HANDLE hEvent;          	// Событие (объект синхронизации)
	HWND hWnd;              	// Окно, принимиющее сообщение nWndMsgId
	UINT nWndMsgId;         	// Сообщение для отправки окну hWnd

	INT nReadEvIdx;				// Указатель чтения событий
	DWORD nCheckStatePeriod;	// Период проверки состояния контроллера (новых событий, часов, верхней границы ключей) в мс (=0 использовать значение по умолчанию, 1000)

	DWORD nClockOffs;			// Смещение часов контроллера от часов ПК в секундах
} *PZG_CTR_NOTIFY_SETTINGS;

// Флаги маски для ZG_CTR_CONFIGURATION::nMask
enum _ZG_CTRCONFIGURATION_MASK
{
	ZG_CTRCFGM_RDWIEGAND		= 0x00000001,	// Режим считывателей: =True Wiegand, иначе - Dallas
	ZG_CTRCFGM_WIEGAND26		= 0x00000002,	// Wiegand-26
	ZG_CTRCFGM_DUALBANK			= 0x00000004,	// 2 банка
	ZG_CTRCFGM_JOIN				= 0x00000008,	// Режим Join
	ZG_CTRCFGM_APB				= 0x00000010,	// Антипассбэк
	ZG_CTRCFGM_DUALZONE			= 0x00000020,	// Два набора временных зон
	ZG_CTRCFGM_FLAGS			= 0x0000003F,	// nFlags. Флаги
	ZG_CTRCFGM_BANKSIZEN		= 0x00010000,	// Номер размера 1 банка: =0 512, =1 1024, =2 2048, =3 4096, =4 8192
	ZG_CTRCFGM_PASSPTTYPE		= 0x00020000,	// Тип точки прохода
	ZG_CTRCFGM_NOCHECKCRC		= 0x80000000	// Не проверять контрольную сумму
};
typedef UINT ZGCTRCFGM;

// Флаги конфигурации контроллера
enum _ZG_CTRCONFIGURATION_FLAGS
{
	ZG_CTRCFGF_RDWIEGAND		= 0x00000001,	// Режим считывателей: =True Wiegand, иначе - Dallas
	ZG_CTRCFGF_WIEGAND26		= 0x00000002,	// Wiegand-26
	ZG_CTRCFGF_DUALBANK			= 0x00000004,	// 2 банка
	ZG_CTRCFGF_JOIN				= 0x00000008,	// Режим Join
	ZG_CTRCFGF_APB				= 0x00000010,	// Антипассбэк
	ZG_CTRCFGF_DUALZONE			= 0x00000020	// Два набора временных зон
};
typedef UINT ZGCTRCFGF;

// Конфигурация контроллера
typedef struct _ZG_CTR_CONFIGURATION
{
	ZG_CTR_TYPE nModel;				// [in,out] Модель контроллера
	ZGCTRCFGM nMask;				// [in] Маска параметров для получения/установки

	ZGCTRCFGF nFlags;				// [in,out] Флаги конфигурации контроллера
	INT nBankSizeN;					// [in,out] Номер размера 1 банка: =0 512, =1 1024, =2 2048, =3 4096, =4 8192
	ZG_CTR_SUB_TYPE nPassPtType;	// [in,out] Тип точки прохода

} *PZG_CTR_CONFIGURATION;

enum _ZG_CVT_SEARCH_FLAGS
{
	ZG_CVTSF_DETECTOR			= 0x0001,	// Использовать готовый список найденных контроллеров детектора (ZG_Cvt_SetNotification)
	ZG_CVTSF_NO_GATE			= 0x0004,	// Не искать GATE-контроллеры
	ZG_CVTSF_NO_EUROLOCK		= 0x0008	// Не искать замки: Eurolock EHT net и Z-9 EHT net
};
typedef UINT ZG_CVTS_FLAGS;

// Callback-функции
typedef BOOL (CALLBACK* ZG_PROCESSCALLBACK) (INT nPos, INT nMax, PVOID pUserData);
typedef BOOL (CALLBACK* ZG_ENUMCTRSPROC) (PZG_FIND_CTR_INFO pInfo, INT nPos, INT nMax, PVOID pUserData);
typedef BOOL (CALLBACK* ZG_ENUMCTRTIMEZONESPROC) (INT nIdx, PZG_CTR_TIMEZONE pTz, PVOID pUserData);
typedef BOOL (CALLBACK* ZG_ENUMCTRKEYSPROC) (INT nIdx, PZG_CTR_KEY pKey, INT nPos, INT nMax, PVOID pUserData);
typedef BOOL (CALLBACK* ZG_ENUMCTREVENTSPROC) (INT nIdx, PZG_CTR_EVENT pEvent, INT nPos, INT nMax, PVOID pUserData);

// Устаревшие типы
typedef BOOL (CALLBACK* ZG_ENUMCVTSPROC) (PZG_ENUM_CVT_INFO pInfo, PZP_PORT_INFO pPort, PVOID pUserData);
typedef BOOL (CALLBACK* ZG_ENUMIPCVTSPROC) (PZG_ENUM_IPCVT_INFO pInfo, PZP_PORT_INFO pPort, PVOID pUserData);

#pragma pack() // turn byte alignment off

#ifndef ZGUARD_LINKONREQUEST

// Возвращает версию библиотеки ZGuard.dll
ZGUARD_API(DWORD) ZG_GetVersion();

// Инициализация/финализация библиотеки
ZGUARD_API(HRESULT) ZG_Initialize(UINT nFlags);
ZGUARD_API(HRESULT) ZG_Finalyze();

//////////////////////////////////////////////////////////////////////////
// Функции для работы с конвертером
//

// Возвращает список с/н конвертеров, подключенных к Proxy-серверу
ZGUARD_API(HRESULT) ZG_GetProxyConverters(INT *pSnBuf, int nBufSize, LPINT pRCount, LPCWSTR pIpAddr, LPCSTR pActCode, PZP_WAIT_SETTINGS pWait=NULL);

// Загружает новую прошивку в конвертер
ZGUARD_API(HRESULT) ZG_UpdateCvtFirmware(PZG_CVT_OPEN_PARAMS pParams, 
	LPCVOID pData, INT nCount, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);

// Открывает/закрывает конвертер
ZGUARD_API(HRESULT) ZG_Cvt_Open(PHANDLE pHandle, PZG_CVT_OPEN_PARAMS pParams, PZG_CVT_INFO pInfo=NULL);
// Отключается от конвертера, не закрывая порт, возвращает дескриптор порта, полученный функцией ZP_Open
ZGUARD_API(HRESULT) ZG_Cvt_DettachPort(HANDLE hHandle, PHANDLE pPortHandle);
// Возвращает состояние подключения
ZGUARD_API(HRESULT) ZG_Cvt_GetConnectionStatus(HANDLE hHandle, ZP_CONNECTION_STATUS* pValue);

// Возвращает/устанавливает параметры ожидания исполнения функции
ZGUARD_API(HRESULT) ZG_Cvt_GetWaitSettings(HANDLE hHandle, PZP_WAIT_SETTINGS pSetting);
ZGUARD_API(HRESULT) ZG_Cvt_SetWaitSettings(HANDLE hHandle, PZP_WAIT_SETTINGS pSetting);

// Захватить порт (приостанавливает фоновые операции с портом)
ZGUARD_API(HRESULT) ZG_Cvt_SetCapture(HANDLE hHandle);
// Отпустить порт (возобновляет фоновые операции с портом)
ZGUARD_API(HRESULT) ZG_Cvt_ReleaseCapture(HANDLE hHandle);
// Очищает порт конвертера
ZGUARD_API(HRESULT) ZG_Cvt_Clear(HANDLE hHandle);
// Отправляет запрос конвертеру
ZGUARD_API(HRESULT) ZG_Cvt_Send(HANDLE hHandle, LPCVOID pData, INT nCount);
// Возвращает ответ от конвертера
ZGUARD_API(HRESULT) ZG_Cvt_Receive(HANDLE hHandle, LPVOID pBuf, INT nBufSize, INT nMinRead, LPINT pRCount);
// Отправляет запрос и возвращает ответ от конвертера
ZGUARD_API(HRESULT) ZG_Cvt_Exec(HANDLE hHandle, LPCVOID pData, INT nCount, 
	LPVOID pBuf, INT nBufSize, INT nMinRead, LPINT pRCount);

// Перечислить все подключенные контроллеры (для не Guard-конвертеров нужно предварительно настроить уведомления о подкл/откл. контроллеров)
#define ZG_F_UPDATE		1	// Обновить список сейчас
#define ZG_F_REASSIGN	2	// Переназначить конфликтующие адреса
#define ZG_F_NOGATE		4	// Не искать GATE-контроллеры
#define ZG_F_NOEUROLOCK	8	// Не искать Eurolock EHT net
ZGUARD_API(HRESULT) ZG_Cvt_EnumControllers(HANDLE hHandle, ZG_ENUMCTRSPROC pEnumProc, PVOID pUserData, UINT nFlags=ZG_F_UPDATE);
// Поиск контроллера по сетевому адресу
ZGUARD_API(HRESULT) ZG_Cvt_FindController(HANDLE hHandle, BYTE nAddr, PZG_FIND_CTR_INFO pInfo, 
	UINT nFlags=ZG_F_UPDATE, PZP_WAIT_SETTINGS pWait=NULL);

ZGUARD_API(HRESULT) ZG_Cvt_SearchControllers(HANDLE hHandle, INT nMaxCtrs, ZG_CVTS_FLAGS nFlags=0);
ZGUARD_API(HRESULT) ZG_Cvt_FindNextController(HANDLE hHandle, PZG_FIND_CTR_INFO pInfo);

// Возвращает информацию о конвертере
ZGUARD_API(HRESULT) ZG_Cvt_GetInformation(HANDLE hHandle, PZG_CVT_INFO pInfo);

// Настраивает уведомления от конвертера
ZGUARD_API(HRESULT) ZG_Cvt_SetNotification(HANDLE hHandle, PZG_CVT_NOTIFY_SETTINGS pSettings);
ZGUARD_API(HRESULT) ZG_Cvt_GetNextMessage(HANDLE hHandle, PUINT pMsg, LPARAM* pMsgParam);
ZGUARD_API(HRESULT) ZG_Cvt_GetScanCtrsState(HANDLE hHandle, LPINT pNextAddr);

// Загружает в конвертер новую прошивку
ZGUARD_API(HRESULT) ZG_Cvt_UpdateFirmware(HANDLE hHandle, LPCVOID pData, INT nCount, 
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);

// Возвращает информацию о лицензии конвертера
ZGUARD_API(HRESULT) ZG_Cvt_GetLicense(HANDLE hHandle, BYTE nLicN, PZG_CVT_LIC_INFO pInfo);
// Устанавливает новую лицензию
ZGUARD_API(HRESULT) ZG_Cvt_SetLicenseData(HANDLE hHandle, BYTE nLicN, LPCVOID pData, INT nCount, LPWORD pLicStatus=NULL);
// Очищает все лицензии в конвертере
ZGUARD_API(HRESULT) ZG_Cvt_ClearAllLicenses(HANDLE hHandle);
// Возвращает информацию о всех лицензиях, установленных в конвертер
ZGUARD_API(HRESULT) ZG_Cvt_GetAllLicenses(HANDLE hHandle, PZG_CVT_LIC_SINFO pBuf, INT nBufSize, LPINT pCount);

// Возвращает с/н конвертера и режим (только Guard)
ZGUARD_API(HRESULT) ZG_Cvt_GetShortInfo(HANDLE hHandle, INT *pSn, ZG_GUARD_MODE* pMode);
// Возвращает информационные строки конвертера (только Guard)
ZGUARD_API(HRESULT) ZG_Cvt_GetLongInfo(HANDLE hHandle, INT *pSn, PDWORD pVersion, ZG_GUARD_MODE* pMode,
	LPSTR pBuf, INT nBufSize, LPINT pLen); // посылает 'i'

// Загружает в контроллер новую прошивку
ZGUARD_API(HRESULT) ZG_Cvt_UpdateCtrFirmware(HANDLE hHandle, INT nCtrSn, LPCVOID pData, INT nCount, LPCSTR pszInfoStr, 
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);

// Установить новый сетевой адрес контроллера по с/н
ZGUARD_API(HRESULT) ZG_Cvt_SetCtrAddrBySn(HANDLE hHandle, INT nSn, BYTE nNewAddr, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);
ZGUARD_API(HRESULT) ZG_Cvt_SetCtrAddr(HANDLE hHandle, BYTE nOldAddr, BYTE nNewAddr, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);

// Запрашивает информацию о контроллере по сетевому адресу
ZGUARD_API(HRESULT) ZG_Cvt_GetCtrInfoNorm(HANDLE hHandle, BYTE nAddr, PBYTE pTypeCode, INT *pSn, LPWORD pVersion, LPINT pInfoLines, PUINT pFlags, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);
ZGUARD_API(HRESULT) ZG_Cvt_GetCtrInfoAdv(HANDLE hHandle, BYTE nAddr, PBYTE pTypeCode, INT *pSn, LPWORD pVersion, PUINT pFlags, PINT pEvWrIdx, PINT pEvRdIdx);
// Запрашивает информацию о контроллере по серийному номеру
ZGUARD_API(HRESULT) ZG_Cvt_GetCtrInfoBySn(HANDLE hHandle, INT nSn, PBYTE pTypeCode, LPBYTE pAddr, LPWORD pVersion, LPINT pInfoLines, PUINT pFlags, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);
// Возвращает информационную строку контроллера
ZGUARD_API(HRESULT) ZG_Cvt_GetCtrInfoLine(HANDLE hHandle, INT nSn, INT nLineN, LPSTR pBuf, INT nBufSize, LPINT pLen=NULL, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);
// Возвращает информацию о версии контроллера (можно использовать для проверки подключения контроллера)
ZGUARD_API(HRESULT) ZG_Cvt_GetCtrVersion(HANDLE hHandle, BYTE nAddr, LPBYTE pVerData5, PZP_WAIT_SETTINGS pWS=NULL);

//////////////////////////////////////////////////////////////////////////
// Функции для работы с контроллером
//

// Открывает/закрывает контроллер
ZGUARD_API(HRESULT) ZG_Ctr_Open(PHANDLE pHandle, HANDLE hCvtHandle, BYTE nAddr, INT nSn, PZG_CTR_INFO pInfo=NULL, ZG_CTR_TYPE nModel=ZG_CTR_UNDEF);
// Возвращает информацию о контроллере
ZGUARD_API(HRESULT) ZG_Ctr_GetInformation(HANDLE hHandle, PZG_CTR_INFO pInfo);
// Настраивает уведомления от контроллера
ZGUARD_API(HRESULT) ZG_Ctr_SetNotification(HANDLE hHandle, PZG_CTR_NOTIFY_SETTINGS pSettings);
ZGUARD_API(HRESULT) ZG_Ctr_GetNextMessage(HANDLE hHandle, PUINT pMsg, LPARAM* pMsgParam);
// Устанавливает сетевой адрес контроллера (не поддерживается в режиме Advanced конвертера)
ZGUARD_API(HRESULT) ZG_Ctr_SetNewAddr(HANDLE hHandle, BYTE nNewAddr);
// Связывает дескриптор контроллера с новым сетевым адресом контроллера
ZGUARD_API(HRESULT) ZG_Ctr_AssignAddr(HANDLE hHandle, BYTE nAddr);
// Загружает новую прошивку в контроллер
ZGUARD_API(HRESULT) ZG_Ctr_UpdateFirmware(HANDLE hHandle, LPCVOID pData, INT nCount, LPCSTR pszInfoStr, 
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);

// Открыть замок
ZGUARD_API(HRESULT) ZG_Ctr_OpenLock(HANDLE hHandle, INT nLockN=0);
// Включить режим аварийного открывания дверей (старая команда)
ZGUARD_API(HRESULT) ZG_Ctr_EnableEmergencyUnlocking(HANDLE hHandle, BOOL fEnable);
// Определить состояние режима аварийного открывания дверей
ZGUARD_API(HRESULT) ZG_Ctr_IsEmergencyUnlockingEnabled(HANDLE hHandle, PBOOL pEnabled);

// Считать регистры контроллера
ZGUARD_API(HRESULT) ZG_Ctr_ReadRegs(HANDLE hHandle, DWORD nAddr, INT nCount, LPVOID pBuf);
// Считать состояние портов
ZGUARD_API(HRESULT) ZG_Ctr_ReadPorts(HANDLE hHandle, LPDWORD pData);
// Управление внешними устройствами (nDevType - адрес устройства ZG_DEV_..)
ZGUARD_API(HRESULT) ZG_Ctr_ControlDevices(HANDLE hHandle, DWORD nDevType, BOOL fActive, DWORD nTimeMs=0);

// Чтение / запись памяти контроллера (nBankN - Адрес на шине: =0 Вход, =1 Выход, =2 События
ZGUARD_API(HRESULT) ZG_Ctr_ReadData(HANDLE hHandle, INT nBankN, DWORD nAddr, INT nCount, LPVOID pBuf, 
	LPINT pReaded, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
ZGUARD_API(HRESULT) ZG_Ctr_WriteData(HANDLE hHandle, INT nBankN, DWORD nAddr, LPCVOID pData, INT nCount, 
	LPINT pWritten, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);

// Возвращает времена для дверей контроллера
ZGUARD_API(HRESULT) ZG_Ctr_ReadLockTimes(HANDLE hHandle, LPDWORD pOpenMs, LPDWORD pLetMs, LPDWORD pMaxMs, INT nBankN=0);
// Устанавливает времена для дверей контроллера
ZGUARD_API(HRESULT) ZG_Ctr_WriteLockTimes(HANDLE hHandle, ZGLTMF nMask, DWORD nOpenMs, DWORD nLetMs, DWORD nMaxMs, INT nBankN=0);

// Возвращает одну или несколько временных зон
ZGUARD_API(HRESULT) ZG_Ctr_ReadTimeZones(HANDLE hHandle, INT nIdx, PZG_CTR_TIMEZONE pBuf, INT nCount, 
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN=0);
// Устанавливает одну или несколько временных зон
ZGUARD_API(HRESULT) ZG_Ctr_WriteTimeZones(HANDLE hHandle, INT nIdx, PZG_CTR_TIMEZONE pTzs, INT nCount,
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN=0);
// Перечисляет временные зоны в контроллере
ZGUARD_API(HRESULT) ZG_Ctr_EnumTimeZones(HANDLE hHandle, INT nStart, ZG_ENUMCTRTIMEZONESPROC fnEnumProc, PVOID pUserData, INT nBankN=0);

// Возвращает один или несколько ключей
ZGUARD_API(HRESULT) ZG_Ctr_ReadKeys(HANDLE hHandle, INT nIdx, PZG_CTR_KEY pBuf, INT nCount,
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN=0);
// Устанавливает один или несколько ключей
ZGUARD_API(HRESULT) ZG_Ctr_WriteKeys(HANDLE hHandle, INT nIdx, PZG_CTR_KEY pKeys, INT nCount,
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN=0);
// Удаляет один или несколько ключей
ZGUARD_API(HRESULT) ZG_Ctr_ClearKeys(HANDLE hHandle, INT nIdx, INT nCount, 
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN=0);
// Возвращает позицию верхней границы ключей
ZGUARD_API(HRESULT) ZG_Ctr_GetKeyTopIndex(HANDLE hHandle, LPINT pIdx, INT nBankN=0);
// Устанавливает позицию верхней границы ключей
ZGUARD_API(HRESULT) ZG_Ctr_SetKeyTopIndex(HANDLE hHandle, INT nIdx, INT nBankN=0);
// Перечислить ключи в контроллере
ZGUARD_API(HRESULT) ZG_Ctr_EnumKeys(HANDLE hHandle, INT nStart, ZG_ENUMCTRKEYSPROC fnEnumProc, PVOID pUserData, INT nBankN=0);

// Возвращает часы контроллера
ZGUARD_API(HRESULT) ZG_Ctr_GetClock(HANDLE hHandle, PZG_CTR_CLOCK pClock);
// Устанавливает часы контроллера
ZGUARD_API(HRESULT) ZG_Ctr_SetClock(HANDLE hHandle, PZG_CTR_CLOCK pClock);

// Возвращает номер последнего поднесенного ключа
ZGUARD_API(HRESULT) ZG_Ctr_ReadLastKeyNum(HANDLE hHandle, Z_KEYNUM* pNum);
// Возвращает указатели событий и номер последнего поднесенного ключа (если *pWrIdx или *pRdIdx == -1, то указатель некорректный)
ZGUARD_API(HRESULT) ZG_Ctr_ReadRTCState(HANDLE hHandle, PZG_CTR_CLOCK pClock, 
	LPINT pWrIdx, LPINT pRdIdx, Z_KEYNUM* pNum);
// Возвращает указатели событий
ZGUARD_API(HRESULT) ZG_Ctr_ReadEventIdxs(HANDLE hHandle, LPINT pWrIdx, LPINT pRdIdx);
// Устанавливает указатели событий
ZGUARD_API(HRESULT) ZG_Ctr_WriteEventIdxs(HANDLE hHandle, UINT nMask, INT nWrIdx, INT nRdIdx);
// Возвращает одно или несколько событий
ZGUARD_API(HRESULT) ZG_Ctr_ReadEvents(HANDLE hHandle, INT nIdx, PZG_CTR_EVENT pBuf, INT nCount,
	ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
// Перечисляет события контроллера
// nStart - индекс первого события, если =-1, используется указатель чтения,
// nCount - количество перечисляемых событий, если =-1, то используется количество событий с nStart до указателя записи,
//			если =INT_MAX, то перечисляются все события
ZGUARD_API(HRESULT) ZG_Ctr_EnumEvents(HANDLE hHandle, INT nStart, INT nCount,
	ZG_ENUMCTREVENTSPROC fnEnumProc, PVOID pUserData);
// Декодирование событий прохода
ZGUARD_API(HRESULT) ZG_Ctr_DecodePassEvent(HANDLE hHandle, PBYTE pData8, 
	PZG_EV_TIME pTime, ZG_CTR_DIRECT* pDirect, PINT pKeyIdx, PINT pKeyBank);
// Декодирование событий ElectoControl: ZG_EV_ELECTRO_ON, ZG_EV_ELECTRO_OFF
ZGUARD_API(HRESULT) ZG_Ctr_DecodeEcEvent(HANDLE hHandle, PBYTE pData8, 
	PZG_EV_TIME pTime, ZG_EC_SUB_EV* pSubEvent, PDWORD pPowerFlags);
// Декодирование события "Неизвестный ключ": ZG_EV_UNKNOWN_KEY
ZGUARD_API(HRESULT) ZG_Ctr_DecodeUnkKeyEvent(HANDLE hHandle, PBYTE pData8, PZ_KEYNUM pKeyNum);
// Декодирование события "Изменение состояния Пожара": ZG_EV_FIRE_STATE
ZGUARD_API(HRESULT) ZG_Ctr_DecodeFireEvent(HANDLE hHandle, PBYTE pData8, 
	PZG_EV_TIME pTime, ZG_FIRE_SUB_EV* pSubEvent, PDWORD pFireFlags);
// Декодирование события "Изменение состояния Охрана": ZG_EV_SECUR_STATE
ZGUARD_API(HRESULT) ZG_Ctr_DecodeSecurEvent(HANDLE hHandle, PBYTE pData8, 
	PZG_EV_TIME pTime, ZG_SECUR_SUB_EV* pSubEvent, PDWORD pSecurFlags);
// Декодирование события "Изменение состояния Режим": ZG_EV_MODE_STATE
ZGUARD_API(HRESULT) ZG_Ctr_DecodeModeEvent(HANDLE hHandle, PBYTE pData8,
	PZG_EV_TIME pTime, ZG_CTR_MODE* pCurrMode, ZG_MODE_SUB_EV* pSubEvent);
// Декодирование событий HOTEL: ZG_EV_HOTEL40 и ZG_EV_HOTEL41
ZGUARD_API(HRESULT) ZG_DecodeHotelEvent(PBYTE pData8, 
	PZG_EV_TIME pTime, ZG_HOTEL_MODE* pMode, ZG_HOTEL_SUB_EV* pSubEvent, LPDWORD pFlags);

// Управление пожарным режимом по сети
ZGUARD_API(HRESULT) ZG_Ctr_SetFireMode(HANDLE hHandle, BOOL fOn);
// Запрос состояния пожарного режима
// pFireFlags - флаги состояния ZG_FR_F_...
// pCurrTemp - текущая температура (в градусах)
// pSrcMask - маска разрешенных источников ZG_FR_SRCF_...
// pLimitTemp - пороговая температура (в градусах)
ZGUARD_API(HRESULT) ZG_Ctr_GetFireInfo(HANDLE hHandle, ZG_CTRFS_FLAGS* pFireFlags, 
	PDWORD pCurrTemp, ZG_CTRFSR_FLAGS* pSrcMask, PDWORD pLimitTemp);
// Установка параметров пожарного режима
ZGUARD_API(HRESULT) ZG_Ctr_SetFireConfig(HANDLE hHandle, ZG_CTRFSR_FLAGS nSrcMask, DWORD nLimitTemp, 
	ZG_CTRFS_FLAGS* pFireFlags, PDWORD pCurrTemp);

// Управление режимом Охрана по сети
ZGUARD_API(HRESULT) ZG_Ctr_SetSecurMode(HANDLE hHandle, ZG_SECUR_MODE nMode);
// Запрос состояния режима Охрана
// pSecurFlags - флаги состояния ZG_SR_F_
// pSrcMask - маска разрешенных источников ZG_SR_SRCF_...
// pAlarmTime - время звучания сирены (в секундах)
ZGUARD_API(HRESULT) ZG_Ctr_GetSecurInfo(HANDLE hHandle, ZG_CTRSS_FLAGS* pSecurFlags, 
	ZG_CTRSSR_FLAGS* pSrcMask, PDWORD pAlarmTime);
// Установка параметров режима Охрана
ZGUARD_API(HRESULT) ZG_Ctr_SetSecurConfig(HANDLE hHandle, ZG_CTRSSR_FLAGS nSrcMask, DWORD nAlarmTime, 
	ZG_CTRSS_FLAGS* pSecurFlags=NULL);

// Управление режимами прохода контроллера
ZGUARD_API(HRESULT) ZG_Ctr_SetCtrMode(HANDLE hHandle, ZG_CTR_MODE nMode);
ZGUARD_API(HRESULT) ZG_Ctr_GetCtrModeInfo(HANDLE hHandle, ZG_CTR_MODE* pCurrMode, PDWORD pFlags);

// Функционал "ElectroControl" для Matrix II Net FW v3.X
// Возвращает параметры электропитания (вр.зона с индексом 6)
ZGUARD_API(HRESULT) ZG_Ctr_ReadElectroConfig(HANDLE hHandle, PZG_CTR_ELECTRO_CONFIG pConfig);
// Устанавливает новые параметры электропитания (вр.зона с индексом 6)
ZGUARD_API(HRESULT) ZG_Ctr_WriteElectroConfig(HANDLE hHandle, PZG_CTR_ELECTRO_CONFIG pConfig, BOOL fSetTz=TRUE);
// Возвращает статус электропитания
ZGUARD_API(HRESULT) ZG_Ctr_GetElectroState(HANDLE hHandle, PZG_CTR_ELECTRO_STATE pState);
// Вкл./Выкл. электропитание
ZGUARD_API(HRESULT) ZG_Ctr_SetElectroPower(HANDLE hHandle, BOOL fOn);
// Возвращает время антипассбэк в минутах. Актуально, когда установлен флаг ZG_CTR_F_APB
// Если Minutes =-1, то не используется
ZGUARD_API(HRESULT) ZG_Ctr_ReadApbTime(HANDLE hHandle, UINT* pMinutes);
// Устанавливает время антипассбэк в минутах
ZGUARD_API(HRESULT) ZG_Ctr_WriteApbTime(HANDLE hHandle, UINT nMinutes);
// Возвращает двоичных данные конфигурации контроллера
ZGUARD_API(HRESULT) ZG_Ctr_GetConfigData(HANDLE hHandle, LPVOID pBuf, UINT nBufSize, PUINT pReaded);
// Устанавливает двоичных данные конфигурации контроллера
ZGUARD_API(HRESULT) ZG_Ctr_SetConfigData(HANDLE hHandle, LPCVOID pData, UINT nDataSize);
// Возвращает значения параметров из двоичных данных конфигурации контроллера
ZGUARD_API(HRESULT) ZG_GetCtrConfigParams(LPCVOID pCfgData, UINT nCfgDataSize, _ZG_CTR_CONFIGURATION *pParams);
// Устанавливает значения параметров в двоичных данных конфигурации контроллера
ZGUARD_API(HRESULT) ZG_SetCtrConfigParams(LPVOID pCfgData, UINT nCfgDataSize, _ZG_CTR_CONFIGURATION *pParams);

#else

#define ZG_DLLNAME       _T("ZGuard.dll")

extern "C"
{
	typedef DWORD (__stdcall* ZG_GETVERSION)();
	typedef HRESULT (__stdcall* ZG_INITIALIZE)(UINT nFlags);
	typedef HRESULT (__stdcall* ZG_FINALYZE)();
	typedef HRESULT (__stdcall* ZG_GETPROXYCONVERTERS)(INT *pSnBuf, int nBufSize, LPINT pRCount, LPCWSTR pIpAddr, 
		LPCSTR pActCode, PZP_WAIT_SETTINGS pWait/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_UPDATECVTFIRMWARE)(PZG_CVT_OPEN_PARAMS pParams, 
		LPCVOID pData, INT nCount, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CVT_OPEN)(PHANDLE pHandle, PZG_CVT_OPEN_PARAMS pParams, PZG_CVT_INFO pInfo/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_CVT_DETTACHPORT)(HANDLE hHandle, PHANDLE pPortHandle);
	typedef HRESULT (__stdcall* ZG_CVT_GETCONNECTIONSTATUS)(HANDLE hHandle, ZP_CONNECTION_STATUS* pValue);
	typedef HRESULT (__stdcall* ZG_CVT_GETWAITSETTINGS)(HANDLE hHandle, PZP_WAIT_SETTINGS pSetting);
	typedef HRESULT (__stdcall* ZG_CVT_SETWAITSETTINGS)(HANDLE hHandle, PZP_WAIT_SETTINGS pSetting);
	typedef HRESULT (__stdcall* ZG_CVT_SETCAPTURE)(HANDLE hHandle);
	typedef HRESULT (__stdcall* ZG_CVT_RELEASECAPTURE)(HANDLE hHandle);
	typedef HRESULT (__stdcall* ZG_CVT_CLEAR)(HANDLE hHandle);
	typedef HRESULT (__stdcall* ZG_CVT_SEND)(HANDLE hHandle, LPCVOID pData, INT nCount);
	typedef HRESULT (__stdcall* ZG_CVT_RECEIVE)(HANDLE hHandle, LPVOID pBuf, INT nBufSize, INT nMinRead, LPINT pRCount);
	typedef HRESULT (__stdcall* ZG_CVT_EXEC)(HANDLE hHandle, LPCVOID pData, INT nCount, 
		LPVOID pBuf, INT nBufSize, INT nMinRead, LPINT pRCount);
	typedef HRESULT (__stdcall* ZG_CVT_ENUMCONTROLLERS)(HANDLE hHandle, ZG_ENUMCTRSPROC pEnumProc, PVOID pUserData, UINT nFlags/*=ZG_F_UPDATE*/);
	typedef HRESULT (__stdcall* ZG_CVT_FINDCONTROLLER)(HANDLE hHandle, BYTE nAddr, PZG_FIND_CTR_INFO pInfo, 
		UINT nFlags/*=ZG_F_UPDATE*/, PZP_WAIT_SETTINGS pWait/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_CVT_SEARCHCONTROLLERS)(HANDLE hHandle, INT nMaxCtrs, ZG_CVTS_FLAGS nFlags/*=0*/);
	typedef HRESULT (__stdcall* ZG_CVT_FINDNEXTCONTROLLER)(HANDLE hHandle, PZG_FIND_CTR_INFO pInfo);
	typedef HRESULT (__stdcall* ZG_CVT_GETINFORMATION)(HANDLE hHandle, PZG_CVT_INFO pInfo);
	typedef HRESULT (__stdcall* ZG_CVT_SETNOTIFICATION)(HANDLE hHandle, PZG_CVT_NOTIFY_SETTINGS pSettings);
	typedef HRESULT (__stdcall* ZG_CVT_GETNEXTMESSAGE)(HANDLE hHandle, PUINT pMsg, LPARAM* pMsgParam);
	typedef HRESULT (__stdcall* ZG_CVT_GETSCANCTRSSTATE)(HANDLE hHandle, LPINT pNextAddr);
	typedef HRESULT (__stdcall* ZG_CVT_UPDATEFIRMWARE)(HANDLE hHandle, LPCVOID pData, INT nCount, 
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CVT_GETLICENSE)(HANDLE hHandle, BYTE nLicN, PZG_CVT_LIC_INFO pInfo);
	typedef HRESULT (__stdcall* ZG_CVT_SETLICENSEDATA)(HANDLE hHandle, BYTE nLicN, LPCVOID pData, INT nCount, LPWORD pLicStatus/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_CVT_CLEARALLLICENSES)(HANDLE hHandle);
	typedef HRESULT (__stdcall* ZG_CVT_GETALLLICENSES)(HANDLE hHandle, PZG_CVT_LIC_SINFO pBuf, INT nBufSize, LPINT pCount);
	typedef HRESULT (__stdcall* ZG_CVT_GETSHORTINFO)(HANDLE hHandle, INT *pSn, ZG_GUARD_MODE* pMode);
	typedef HRESULT (__stdcall* ZG_CVT_GETLONGINFO)(HANDLE hHandle, INT *pSn, PDWORD pVersion, ZG_GUARD_MODE* pMode,
		LPSTR pBuf, INT nBufSize, LPINT pLen);
	typedef HRESULT (__stdcall* ZG_CVT_UPDATECTRFIRMWARE)(HANDLE hHandle, INT nCtrSn, LPCVOID pData, INT nCount, LPCSTR pszInfoStr, 
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_SETCTRADDRBYSN)(HANDLE hHandle, INT nSn, BYTE nNewAddr, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_SETCTRADDR)(HANDLE hHandle, BYTE nOldAddr, BYTE nNewAddr, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_GETCTRINFONORM)(HANDLE hHandle, BYTE nAddr, PBYTE pTypeCode, INT *pSn, LPWORD pVersion, LPINT pInfoLines, PUINT pFlags, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_GETCTRINFOADV)(HANDLE hHandle, BYTE nAddr, PBYTE pTypeCode, INT *pSn, LPWORD pVersion, PUINT pFlags, PINT pEvWrIdx, PINT pEvRdIdx);
	typedef HRESULT (__stdcall* ZG_CVT_GETCTRINFOBYSN)(HANDLE hHandle, INT nSn, PBYTE pTypeCode, LPBYTE pAddr, LPWORD pVersion, LPINT pInfoLines, PUINT pFlags, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_GETCTRINFOLINE)(HANDLE hHandle, INT nSn, INT nLineN, LPSTR pBuf, INT nBufSize, LPINT pLen/*=NULL*/, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CVT_GETCTRVERSION)(HANDLE hHandle, BYTE nAddr, LPBYTE pVerData5, PZP_WAIT_SETTINGS pWS/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_CTR_OPEN)(PHANDLE pHandle, HANDLE hCvtHandle, BYTE nAddr, INT nSn, PZG_CTR_INFO pInfo/*=NULL*/, ZG_CTR_TYPE nModel/*=ZG_CTR_UNDEF*/);
	typedef HRESULT (__stdcall* ZG_CTR_GETINFORMATION)(HANDLE hHandle, PZG_CTR_INFO pInfo);
	typedef HRESULT (__stdcall* ZG_CTR_SETNOTIFICATION)(HANDLE hHandle, PZG_CTR_NOTIFY_SETTINGS pSettings);
	typedef HRESULT (__stdcall* ZG_CTR_GETNEXTMESSAGE)(HANDLE hHandle, PUINT pMsg, LPARAM* pMsgParam);
	typedef HRESULT (__stdcall* ZG_CTR_SETNEWADDR)(HANDLE hHandle, BYTE nNewAddr);
	typedef HRESULT (__stdcall* ZG_CTR_ASSIGNADDR)(HANDLE hHandle, BYTE nAddr);
	typedef HRESULT (__stdcall* ZG_CTR_UPDATEFIRMWARE)(HANDLE hHandle, LPCVOID pData, INT nCount, LPCSTR pszInfoStr, 
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CTR_OPENLOCK)(HANDLE hHandle, INT nLockN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_ENABLEEMERGENCYUNLOCKING)(HANDLE hHandle, BOOL fEnable);
	typedef HRESULT (__stdcall* ZG_CTR_ISEMERGENCYUNLOCKINGENABLED)(HANDLE hHandle, PBOOL pEnabled);
	typedef HRESULT (__stdcall* ZG_CTR_READREGS)(HANDLE hHandle, DWORD nAddr, INT nCount, LPVOID pBuf);
	typedef HRESULT (__stdcall* ZG_CTR_READPORTS)(HANDLE hHandle, LPDWORD pData);
	typedef HRESULT (__stdcall* ZG_CTR_CONTROLDEVICES)(HANDLE hHandle, DWORD nDevType, BOOL fActive, DWORD nTimeMs/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_READDATA)(HANDLE hHandle, INT nBankN, DWORD nAddr, INT nCount, LPVOID pBuf, 
		LPINT pReaded, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CTR_WRITEDATA)(HANDLE hHandle, INT nBankN, DWORD nAddr, LPCVOID pData, INT nCount, 
		LPINT pWritten, ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CTR_READLOCKTIMES)(HANDLE hHandle, LPDWORD pOpenMs, LPDWORD pLetMs, LPDWORD pMaxMs, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_WRITELOCKTIMES)(HANDLE hHandle, ZGLTMF nMask, DWORD nOpenMs, DWORD nLetMs, DWORD nMaxMs, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_READTIMEZONES)(HANDLE hHandle, INT nIdx, PZG_CTR_TIMEZONE pBuf, INT nCount, 
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_WRITETIMEZONES)(HANDLE hHandle, INT nIdx, PZG_CTR_TIMEZONE pTzs, INT nCount,
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_ENUMTIMEZONES)(HANDLE hHandle, INT nStart, ZG_ENUMCTRTIMEZONESPROC fnEnumProc, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_READKEYS)(HANDLE hHandle, INT nIdx, PZG_CTR_KEY pBuf, INT nCount,
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_WRITEKEYS)(HANDLE hHandle, INT nIdx, PZG_CTR_KEY pKeys, INT nCount,
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_CLEARKEYS)(HANDLE hHandle, INT nIdx, INT nCount, 
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_GETKEYTOPINDEX)(HANDLE hHandle, LPINT pIdx, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_SETKEYTOPINDEX)(HANDLE hHandle, INT nIdx, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_ENUMKEYS)(HANDLE hHandle, INT nStart, ZG_ENUMCTRKEYSPROC fnEnumProc, PVOID pUserData, INT nBankN/*=0*/);
	typedef HRESULT (__stdcall* ZG_CTR_GETCLOCK)(HANDLE hHandle, PZG_CTR_CLOCK pClock);
	typedef HRESULT (__stdcall* ZG_CTR_SETCLOCK)(HANDLE hHandle, PZG_CTR_CLOCK pClock);
	typedef HRESULT (__stdcall* ZG_CTR_READLASTKEYNUM)(HANDLE hHandle, Z_KEYNUM* pNum);
	typedef HRESULT (__stdcall* ZG_CTR_READRTCSTATE)(HANDLE hHandle, PZG_CTR_CLOCK pClock, 
		LPINT pWrIdx, LPINT pRdIdx, Z_KEYNUM* pNum);
	typedef HRESULT (__stdcall* ZG_CTR_READEVENTIDXS)(HANDLE hHandle, LPINT pWrIdx, LPINT pRdIdx);
	typedef HRESULT (__stdcall* ZG_CTR_WRITEEVENTIDXS)(HANDLE hHandle, UINT nMask, INT nWrIdx, INT nRdIdx);
	typedef HRESULT (__stdcall* ZG_CTR_READEVENTS)(HANDLE hHandle, INT nIdx, PZG_CTR_EVENT pBuf, INT nCount,
		ZG_PROCESSCALLBACK pfnCallback, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CTR_ENUMEVENTS)(HANDLE hHandle, INT nStart, INT nCount,
		ZG_ENUMCTREVENTSPROC fnEnumProc, PVOID pUserData);
	typedef HRESULT (__stdcall* ZG_CTR_DECODEPASSEVENT)(HANDLE hHandle, PBYTE pData8, 
		PZG_EV_TIME pTime, ZG_CTR_DIRECT* pDirect, PINT pKeyIdx, PINT pKeyBank);
	typedef HRESULT (__stdcall* ZG_Ctr_DECODEECEVENT)(HANDLE hHandle, PBYTE pData8, 
		PZG_EV_TIME pTime, ZG_EC_SUB_EV* pSubEvent, PDWORD pPowerFlags);
	typedef HRESULT (__stdcall* ZG_CTR_DECODEUNKKEYEVENT)(HANDLE hHandle, PBYTE pData8, PZ_KEYNUM pKeyNum);
	typedef HRESULT (__stdcall* ZG_CTR_DECODEFIREEVENT)(HANDLE hHandle, PBYTE pData8, 
		PZG_EV_TIME pTime, ZG_FIRE_SUB_EV* pSubEvent, PDWORD pFireFlags);
	typedef HRESULT (__stdcall* ZG_CTR_DECODESECUREVENT)(HANDLE hHandle, PBYTE pData8, 
		PZG_EV_TIME pTime, ZG_SECUR_SUB_EV* pSubEvent, PDWORD pSecurFlags);
	typedef HRESULT (__stdcall* ZG_CTR_DECODEMODEEVENT)(HANDLE hHandle, PBYTE pData8,
		PZG_EV_TIME pTime, ZG_CTR_MODE* pCurrMode, ZG_MODE_SUB_EV* pSubEvent);
	typedef HRESULT (__stdcall* ZG_DECODEHOTELEVENT)(PBYTE pData8, 
		PZG_EV_TIME pTime, ZG_HOTEL_MODE* pMode, ZG_HOTEL_SUB_EV* pSubEvent, LPDWORD pFlags);
	typedef HRESULT (__stdcall* ZG_CTR_SETFIREMODE)(HANDLE hHandle, BOOL fOn);
	typedef HRESULT (__stdcall* ZG_CTR_GETFIREINFO)(HANDLE hHandle, ZG_CTRFS_FLAGS* pFireFlags, 
		PDWORD pCurrTemp, ZG_CTRFSR_FLAGS* pSrcMask, PDWORD pLimitTemp);
	typedef HRESULT (__stdcall* ZG_CTR_SETFIRECONFIG)(HANDLE hHandle, ZG_CTRFSR_FLAGS nSrcMask, DWORD nLimitTemp, 
		ZG_CTRFS_FLAGS* pFireFlags, PDWORD pCurrTemp);
	typedef HRESULT (__stdcall* ZG_CTR_SETSECURMODE)(HANDLE hHandle, ZG_SECUR_MODE nMode);
	typedef HRESULT (__stdcall* ZG_CTR_GETSECURINFO)(HANDLE hHandle, ZG_CTRSS_FLAGS* pSecurFlags, 
		ZG_CTRSSR_FLAGS* pSrcMask, PDWORD pAlarmTime);
	typedef HRESULT (__stdcall* ZG_CTR_SETSECURCONFIG)(HANDLE hHandle, ZG_CTRSSR_FLAGS nSrcMask, DWORD nAlarmTime, 
		ZG_CTRSS_FLAGS* pSecurFlags/*=NULL*/);
	typedef HRESULT (__stdcall* ZG_CTR_SETCTRMODE)(HANDLE hHandle, ZG_CTR_MODE nMode);
	typedef HRESULT (__stdcall* ZG_CTR_GETCTRMODEINFO)(HANDLE hHandle, ZG_CTR_MODE* pCurrMode, PDWORD pFlags);
	typedef HRESULT (__stdcall* ZG_CTR_READELECTROCONFIG)(HANDLE hHandle, PZG_CTR_ELECTRO_CONFIG pConfig);
	typedef HRESULT (__stdcall* ZG_CTR_WRITEELECTROCONFIG)(HANDLE hHandle, PZG_CTR_ELECTRO_CONFIG pConfig, BOOL fSetTz/*=TRUE*/);
	typedef HRESULT (__stdcall* ZG_CTR_GETELECTROSTATE)(HANDLE hHandle, PZG_CTR_ELECTRO_STATE pState);
	typedef HRESULT (__stdcall* ZG_CTR_SETELECTROPOWER)(HANDLE hHandle, BOOL fOn);
	typedef HRESULT(__stdcall* ZG_CTR_READAPBTIME)(HANDLE hHandle, UINT* pMinutes);
	typedef HRESULT(__stdcall* ZG_CTR_WRITEAPBTIME)(HANDLE hHandle, UINT nMinutes);
	typedef HRESULT(__stdcall* ZG_CTR_GETCONFIGDATA)(HANDLE hHandle, LPVOID pBuf, UINT nBufSize, PUINT pReaded);
	typedef HRESULT(__stdcall* ZG_CTR_SETCONFIGDATA)(HANDLE hHandle, LPCVOID pData, UINT nDataSize);
	typedef HRESULT(__stdcall* ZG_GETCTRCONFIGPARAMS)(LPCVOID pCfgData, UINT nCfgDataSize, _ZG_CTR_CONFIGURATION *pParams);
	typedef HRESULT(__stdcall* ZG_SETCTRCONFIGPARAMS)(LPVOID pCfgData, UINT nCfgDataSize, _ZG_CTR_CONFIGURATION *pParams);
} // extern "C"

extern ZG_GETVERSION ZG_GetVersion;
extern ZG_INITIALIZE ZG_Initialize;
extern ZG_FINALYZE ZG_Finalyze;
extern ZG_GETPROXYCONVERTERS ZG_GetProxyConverters;
extern ZG_UPDATECVTFIRMWARE ZG_UpdateCvtFirmware;
extern ZG_CVT_OPEN ZG_Cvt_Open;
extern ZG_CVT_DETTACHPORT ZG_Cvt_DettachPort;
extern ZG_CVT_GETCONNECTIONSTATUS ZG_Cvt_GetConnectionStatus;
extern ZG_CVT_GETWAITSETTINGS ZG_Cvt_GetWaitSettings;
extern ZG_CVT_SETWAITSETTINGS ZG_Cvt_SetWaitSettings;
extern ZG_CVT_SETCAPTURE ZG_Cvt_SetCapture;
extern ZG_CVT_RELEASECAPTURE ZG_Cvt_ReleaseCapture;
extern ZG_CVT_CLEAR ZG_Cvt_Clear;
extern ZG_CVT_SEND ZG_Cvt_Send;
extern ZG_CVT_RECEIVE ZG_Cvt_Receive;
extern ZG_CVT_EXEC ZG_Cvt_Exec;
extern ZG_CVT_ENUMCONTROLLERS ZG_Cvt_EnumControllers;
extern ZG_CVT_FINDCONTROLLER ZG_Cvt_FindController;
extern ZG_CVT_SEARCHCONTROLLERS ZG_Cvt_SearchControllers;
extern ZG_CVT_FINDNEXTCONTROLLER ZG_Cvt_FindNextController;
extern ZG_CVT_GETINFORMATION ZG_Cvt_GetInformation;
extern ZG_CVT_SETNOTIFICATION ZG_Cvt_SetNotification;
extern ZG_CVT_GETNEXTMESSAGE ZG_Cvt_GetNextMessage;
extern ZG_CVT_GETSCANCTRSSTATE ZG_Cvt_GetScanCtrsState;
extern ZG_CVT_UPDATEFIRMWARE ZG_Cvt_UpdateFirmware;
extern ZG_CVT_GETLICENSE ZG_Cvt_GetLicense;
extern ZG_CVT_SETLICENSEDATA ZG_Cvt_SetLicenseData;
extern ZG_CVT_CLEARALLLICENSES ZG_Cvt_ClearAllLicenses;
extern ZG_CVT_GETALLLICENSES ZG_Cvt_GetAllLicenses;
extern ZG_CVT_GETSHORTINFO ZG_Cvt_GetShortInfo;
extern ZG_CVT_GETLONGINFO ZG_Cvt_GetLongInfo;
extern ZG_CVT_UPDATECTRFIRMWARE ZG_Cvt_UpdateCtrFirmware;
extern ZG_CVT_SETCTRADDRBYSN ZG_Cvt_SetCtrAddrBySn;
extern ZG_CVT_SETCTRADDR ZG_Cvt_SetCtrAddr;
extern ZG_CVT_GETCTRINFONORM ZG_Cvt_GetCtrInfoNorm;
extern ZG_CVT_GETCTRINFOADV ZG_Cvt_GetCtrInfoAdv;
extern ZG_CVT_GETCTRINFOBYSN ZG_Cvt_GetCtrInfoBySn;
extern ZG_CVT_GETCTRINFOLINE ZG_Cvt_GetCtrInfoLine;
extern ZG_CVT_GETCTRVERSION ZG_Cvt_GetCtrVersion;
extern ZG_CTR_OPEN ZG_Ctr_Open;
extern ZG_CTR_GETINFORMATION ZG_Ctr_GetInformation;
extern ZG_CTR_SETNOTIFICATION ZG_Ctr_SetNotification;
extern ZG_CTR_GETNEXTMESSAGE ZG_Ctr_GetNextMessage;
extern ZG_CTR_SETNEWADDR ZG_Ctr_SetNewAddr;
extern ZG_CTR_ASSIGNADDR ZG_Ctr_AssignAddr;
extern ZG_CTR_UPDATEFIRMWARE ZG_Ctr_UpdateFirmware;
extern ZG_CTR_OPENLOCK ZG_Ctr_OpenLock;
extern ZG_CTR_ENABLEEMERGENCYUNLOCKING ZG_Ctr_EnableEmergencyUnlocking;
extern ZG_CTR_ISEMERGENCYUNLOCKINGENABLED ZG_Ctr_IsEmergencyUnlockingEnabled;
extern ZG_CTR_READREGS ZG_Ctr_ReadRegs;
extern ZG_CTR_READPORTS ZG_Ctr_ReadPorts;
extern ZG_CTR_CONTROLDEVICES ZG_Ctr_ControlDevices;
extern ZG_CTR_READDATA ZG_Ctr_ReadData;
extern ZG_CTR_WRITEDATA ZG_Ctr_WriteData;
extern ZG_CTR_READLOCKTIMES ZG_Ctr_ReadLockTimes;
extern ZG_CTR_WRITELOCKTIMES ZG_Ctr_WriteLockTimes;
extern ZG_CTR_READTIMEZONES ZG_Ctr_ReadTimeZones;
extern ZG_CTR_WRITETIMEZONES ZG_Ctr_WriteTimeZones;
extern ZG_CTR_ENUMTIMEZONES ZG_Ctr_EnumTimeZones;
extern ZG_CTR_READKEYS ZG_Ctr_ReadKeys;
extern ZG_CTR_WRITEKEYS ZG_Ctr_WriteKeys;
extern ZG_CTR_CLEARKEYS ZG_Ctr_ClearKeys;
extern ZG_CTR_GETKEYTOPINDEX ZG_Ctr_GetKeyTopIndex;
extern ZG_CTR_SETKEYTOPINDEX ZG_Ctr_SetKeyTopIndex;
extern ZG_CTR_ENUMKEYS ZG_Ctr_EnumKeys;
extern ZG_CTR_GETCLOCK ZG_Ctr_GetClock;
extern ZG_CTR_SETCLOCK ZG_Ctr_SetClock;
extern ZG_CTR_READLASTKEYNUM ZG_Ctr_ReadLastKeyNum;
extern ZG_CTR_READRTCSTATE ZG_Ctr_ReadRTCState;
extern ZG_CTR_READEVENTIDXS ZG_Ctr_ReadEventIdxs;
extern ZG_CTR_WRITEEVENTIDXS ZG_Ctr_WriteEventIdxs;
extern ZG_CTR_READEVENTS ZG_Ctr_ReadEvents;
extern ZG_CTR_ENUMEVENTS ZG_Ctr_EnumEvents;
extern ZG_CTR_DECODEPASSEVENT ZG_Ctr_DecodePassEvent;
extern ZG_Ctr_DECODEECEVENT ZG_Ctr_DecodeEcEvent;
extern ZG_CTR_DECODEUNKKEYEVENT ZG_Ctr_DecodeUnkKeyEvent;
extern ZG_CTR_DECODEFIREEVENT ZG_Ctr_DecodeFireEvent;
extern ZG_CTR_DECODESECUREVENT ZG_Ctr_DecodeSecurEvent;
extern ZG_CTR_DECODEMODEEVENT ZG_Ctr_DecodeModeEvent;
extern ZG_DECODEHOTELEVENT ZG_DecodeHotelEvent;
extern ZG_CTR_SETFIREMODE ZG_Ctr_SetFireMode;
extern ZG_CTR_GETFIREINFO ZG_Ctr_GetFireInfo;
extern ZG_CTR_SETFIRECONFIG ZG_Ctr_SetFireConfig;
extern ZG_CTR_SETSECURMODE ZG_Ctr_SetSecurMode;
extern ZG_CTR_GETSECURINFO ZG_Ctr_GetSecurInfo;
extern ZG_CTR_SETSECURCONFIG ZG_Ctr_SetSecurConfig;
extern ZG_CTR_SETCTRMODE ZG_Ctr_SetCtrMode;
extern ZG_CTR_GETCTRMODEINFO ZG_Ctr_GetCtrModeInfo;
extern ZG_CTR_READELECTROCONFIG ZG_Ctr_ReadElectroConfig;
extern ZG_CTR_WRITEELECTROCONFIG ZG_Ctr_WriteElectroConfig;
extern ZG_CTR_GETELECTROSTATE ZG_Ctr_GetElectroState;
extern ZG_CTR_SETELECTROPOWER ZG_Ctr_SetElectroPower;
extern ZG_CTR_READAPBTIME ZG_Ctr_ReadApbTime;
extern ZG_CTR_WRITEAPBTIME ZG_Ctr_WriteApbTime;
extern ZG_CTR_GETCONFIGDATA ZG_Ctr_GetConfigData;
extern ZG_CTR_SETCONFIGDATA ZG_Ctr_SetConfigData;
extern ZG_GETCTRCONFIGPARAMS ZG_GetCtrConfigParams;
extern ZG_SETCTRCONFIGPARAMS ZG_SetCtrConfigParams;

extern HMODULE	hZgLib;
extern INT nZgLoadCount;

#endif // !ZGUARD_LINKONREQUEST

#ifndef ZGUARD_EXPORTS
inline BOOL IsZGuardLoaded()
{
#ifdef ZGUARD_LINKONREQUEST
	return hZgLib != 0;
#else
	return TRUE;
#endif // ZGUARD_LINKONREQUEST
}

HRESULT LoadZGuard(LPCTSTR pszPath=NULL);
VOID UnloadZGuard();
#endif // !ZGUARD_EXPORTS

#ifndef ZGUARD_EXPORTS
#define ZG_GetPortInfoList(pHandle, pCount) (HRESULT)ZP_GetPortInfoList(pHandle, pCount, ZG_DEVTYPE_CVTS, 0)
#define ZG_GetPortInfo	ZP_GetPortInfo
// Найти все подключенные конвертеры
inline HRESULT ZG_SearchDevices(PHANDLE pHandle, PZP_SEARCH_PARAMS pParams, BOOL fSerial=TRUE, BOOL fIP=TRUE)
{
	if (fSerial)
		pParams->nDevMask |= ZG_DEVTYPE_CVTS;
	if (fIP)
		pParams->nIpDevMask |= ZG_IPDEVTYPE_CVTS;
	return ZP_SearchDevices(pHandle, pParams);
};
inline HRESULT ZG_FindNextDevice(HANDLE hHandle, PZG_ENUM_IPCVT_INFO pInfo, 
	PZP_PORT_INFO pPortArr, INT nArrLen, PINT pPortCount, UINT nTimeout=INFINITE)
{
	pInfo->cbSize = sizeof(_ZG_ENUM_IPCVT_INFO);
	return ZP_FindNextDevice(hHandle, pInfo, pPortArr, nArrLen, pPortCount, nTimeout);
}
// Настраивает уведомления
inline HRESULT ZG_SetNotification(PHANDLE pHandle, PZP_DD_NOTIFY_SETTINGS pSettings, BOOL fSerial, BOOL fIP)
{
	if (fSerial)
		pSettings->nSDevTypes |= ZG_DEVTYPE_CVTS; 
	if (fIP)
		pSettings->nIpDevTypes |= ZG_IPDEVTYPE_CVTS;
	return ZP_DD_SetNotification(pHandle, pSettings);
}
#define ZG_GetNextMessage	ZP_DD_GetNextMessage
#endif // !ZGUARD_EXPORTS

#define ZG_CloseHandle ZP_CloseHandle

