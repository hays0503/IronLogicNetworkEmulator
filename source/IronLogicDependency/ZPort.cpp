#include "header/IronLogicDependency/ZPort.h"

#ifdef ZPORT_LINKONREQUEST
ZP_GETVERSION ZP_GetVersion = NULL;
ZP_INITIALIZE ZP_Initialize = NULL;
ZP_FINALYZE ZP_Finalyze = NULL;
ZP_CLOSEHANDLE ZP_CloseHandle = NULL;
ZP_GETPORTINFOLIST ZP_GetPortInfoList = NULL;
ZP_GETPORTINFO ZP_GetPortInfo = NULL;
ZP_SEARCHDEVICES ZP_SearchDevices = NULL;
ZP_FINDNEXTDEVICE ZP_FindNextDevice = NULL;
ZP_DD_SETNOTIFICATION ZP_DD_SetNotification = NULL;
ZP_DD_GETNEXTMESSAGE ZP_DD_GetNextMessage = NULL;
ZP_DD_SETGLOBALSETTINGS ZP_DD_SetGlobalSettings = NULL;
ZP_DD_GETGLOBALSETTINGS ZP_DD_GetGlobalSettings = NULL;
ZP_DD_REFRESH ZP_DD_Refresh = NULL;
ZP_SETSERVICECTRLHANDLE ZP_SetServiceCtrlHandle = NULL;
ZP_DEVICEEVENTNOTIFY ZP_DeviceEventNotify = NULL;
ZP_PORT_OPEN ZP_Port_Open = NULL;
ZP_PORT_SETBAUDANDEVCHAR ZP_Port_SetBaudAndEvChar = NULL;
ZP_PORT_GETBAUDANDEVCHAR ZP_Port_GetBaudAndEvChar = NULL;
ZP_PORT_GETCONNECTIONSTATUS ZP_Port_GetConnectionStatus = NULL;
ZP_PORT_SETNOTIFICATION ZP_Port_SetNotification = NULL;
ZP_PORT_ENUMMESSAGES ZP_Port_EnumMessages = NULL;
ZP_PORT_CLEAR ZP_Port_Clear = NULL;
ZP_PORT_WRITE ZP_Port_Write = NULL;
ZP_PORT_READ ZP_Port_Read = NULL;
ZP_PORT_GETINCOUNT ZP_Port_GetInCount = NULL;
ZP_PORT_SETDTR ZP_Port_SetDtr = NULL;
ZP_PORT_SETRTS ZP_Port_SetRts = NULL;
ZP_REGSERIALDEVICE ZP_RegSerialDevice = NULL;
ZP_REGIPDEVICE ZP_RegIpDevice = NULL;
#ifdef ZP_LOG
ZP_SETLOG ZP_SetLog = NULL;
ZP_GETLOG ZP_GetLog = NULL;
ZP_ADDLOG ZP_AddLog = NULL;
#endif // ZP_LOG

HMODULE	hZpLib = 0;
INT nZpLoadCount = 0;
#endif // ZPORT_LINKONREQUEST

BOOL CheckZpVersion()
{
	DWORD nVersion = ZP_GetVersion();
	return ((nVersion & 0xff) == ZP_SDK_VER_MAJOR) && (((nVersion >> 8) & 0xff) == ZP_SDK_VER_MINOR);
}

HRESULT LoadZPort(LPCTSTR pszPath/*=NULL*/)
{
#ifdef ZPORT_LINKONREQUEST
	HRESULT hr = S_OK;
	if (++nZpLoadCount > 1)
		return hr;
	hZpLib = LoadLibrary(pszPath ? pszPath : ZP_DLLNAME);
	if (hZpLib == 0)
		return HRESULT_FROM_WIN32(GetLastError());
	if (((ZP_GetVersion = reinterpret_cast<ZP_GETVERSION>(GetProcAddress(hZpLib, "ZP_GetVersion"))) != NULL) && 
			CheckZpVersion())
	{
		if (((ZP_Initialize = reinterpret_cast<ZP_INITIALIZE>(GetProcAddress(hZpLib, "ZP_Initialize"))) == NULL) ||
				((ZP_Finalyze = reinterpret_cast<ZP_FINALYZE>(GetProcAddress(hZpLib, "ZP_Finalyze"))) == NULL) ||
				((ZP_CloseHandle = reinterpret_cast<ZP_CLOSEHANDLE>(GetProcAddress(hZpLib, "ZP_CloseHandle"))) == NULL) ||
				((ZP_GetPortInfoList = reinterpret_cast<ZP_GETPORTINFOLIST>(GetProcAddress(hZpLib, "ZP_GetPortInfoList"))) == NULL) ||
				((ZP_GetPortInfo = reinterpret_cast<ZP_GETPORTINFO>(GetProcAddress(hZpLib, "ZP_GetPortInfo"))) == NULL) ||
				((ZP_SearchDevices = reinterpret_cast<ZP_SEARCHDEVICES>(GetProcAddress(hZpLib, "ZP_SearchDevices"))) == NULL) ||
				((ZP_FindNextDevice = reinterpret_cast<ZP_FINDNEXTDEVICE>(GetProcAddress(hZpLib, "ZP_FindNextDevice"))) == NULL) ||
				((ZP_DD_SetNotification = reinterpret_cast<ZP_DD_SETNOTIFICATION>(GetProcAddress(hZpLib, "ZP_DD_SetNotification"))) == NULL) ||
				((ZP_DD_GetNextMessage = reinterpret_cast<ZP_DD_GETNEXTMESSAGE>(GetProcAddress(hZpLib, "ZP_DD_GetNextMessage"))) == NULL) ||
				((ZP_DD_SetGlobalSettings = reinterpret_cast<ZP_DD_SETGLOBALSETTINGS>(GetProcAddress(hZpLib, "ZP_DD_SetGlobalSettings"))) == NULL) ||
				((ZP_DD_GetGlobalSettings = reinterpret_cast<ZP_DD_GETGLOBALSETTINGS>(GetProcAddress(hZpLib, "ZP_DD_GetGlobalSettings"))) == NULL) ||
				((ZP_DD_Refresh = reinterpret_cast<ZP_DD_REFRESH>(GetProcAddress(hZpLib, "ZP_DD_Refresh"))) == NULL) ||
				((ZP_SetServiceCtrlHandle = reinterpret_cast<ZP_SETSERVICECTRLHANDLE>(GetProcAddress(hZpLib, "ZP_SetServiceCtrlHandle"))) == NULL) ||
				((ZP_DeviceEventNotify = reinterpret_cast<ZP_DEVICEEVENTNOTIFY>(GetProcAddress(hZpLib, "ZP_DeviceEventNotify"))) == NULL) ||
				((ZP_Port_Open = reinterpret_cast<ZP_PORT_OPEN>(GetProcAddress(hZpLib, "ZP_Port_Open"))) == NULL) ||
				((ZP_Port_SetBaudAndEvChar = reinterpret_cast<ZP_PORT_SETBAUDANDEVCHAR>(GetProcAddress(hZpLib, "ZP_Port_SetBaudAndEvChar"))) == NULL) ||
				((ZP_Port_GetBaudAndEvChar = reinterpret_cast<ZP_PORT_GETBAUDANDEVCHAR>(GetProcAddress(hZpLib, "ZP_Port_GetBaudAndEvChar"))) == NULL) ||
				((ZP_Port_GetConnectionStatus = reinterpret_cast<ZP_PORT_GETCONNECTIONSTATUS>(GetProcAddress(hZpLib, "ZP_Port_GetConnectionStatus"))) == NULL) ||
				((ZP_Port_SetNotification = reinterpret_cast<ZP_PORT_SETNOTIFICATION>(GetProcAddress(hZpLib, "ZP_Port_SetNotification"))) == NULL) ||
				((ZP_Port_EnumMessages = reinterpret_cast<ZP_PORT_ENUMMESSAGES>(GetProcAddress(hZpLib, "ZP_Port_EnumMessages"))) == NULL) ||
				((ZP_Port_Clear = reinterpret_cast<ZP_PORT_CLEAR>(GetProcAddress(hZpLib, "ZP_Port_Clear"))) == NULL) ||
				((ZP_Port_Write = reinterpret_cast<ZP_PORT_WRITE>(GetProcAddress(hZpLib, "ZP_Port_Write"))) == NULL) ||
				((ZP_Port_Read = reinterpret_cast<ZP_PORT_READ>(GetProcAddress(hZpLib, "ZP_Port_Read"))) == NULL) ||
				((ZP_Port_GetInCount = reinterpret_cast<ZP_PORT_GETINCOUNT>(GetProcAddress(hZpLib, "ZP_Port_GetInCount"))) == NULL) ||
				((ZP_Port_SetDtr = reinterpret_cast<ZP_PORT_SETDTR>(GetProcAddress(hZpLib, "ZP_Port_SetDtr"))) == NULL) || 
				((ZP_Port_SetRts = reinterpret_cast<ZP_PORT_SETRTS>(GetProcAddress(hZpLib, "ZP_Port_SetRts"))) == NULL) ||
				((ZP_RegSerialDevice = reinterpret_cast<ZP_REGSERIALDEVICE>(GetProcAddress(hZpLib, "ZP_RegSerialDevice"))) == NULL) ||
				((ZP_RegIpDevice = reinterpret_cast<ZP_REGIPDEVICE>(GetProcAddress(hZpLib, "ZP_RegIpDevice"))) == NULL))
			hr = E_NOINTERFACE;
#ifdef ZP_LOG
		if ((hr == S_OK) && (
				((ZP_SetLog = reinterpret_cast<ZP_SETLOG>(GetProcAddress(hZpLib, "ZP_SetLog"))) == NULL) ||
				((ZP_GetLog = reinterpret_cast<ZP_GETLOG>(GetProcAddress(hZpLib, "ZP_GetLog"))) == NULL) ||
				((ZP_AddLog = reinterpret_cast<ZP_ADDLOG>(GetProcAddress(hZpLib, "ZP_AddLog"))) == NULL)))
			hr = E_NOINTERFACE;
#endif // ZP_LOG
	}
	else
		hr = E_NOINTERFACE;

	if (FAILED(hr))
		UnloadZPort();
	return hr;
#else
	if (CheckZpVersion())
		return S_OK;
	else
		return E_NOINTERFACE;
#endif // ZPORT_LINKONREQUEST
}

VOID UnloadZPort()
{
#ifdef ZPORT_LINKONREQUEST
	if (--nZpLoadCount > 0)
		return;
	FreeLibrary(hZpLib);
	hZpLib = NULL;
	ZP_GetVersion = NULL;
	ZP_Initialize = NULL;
	ZP_Finalyze = NULL;
	ZP_CloseHandle = NULL;
	ZP_GetPortInfoList = NULL;
	ZP_GetPortInfo = NULL;
	ZP_SearchDevices = NULL;
	ZP_FindNextDevice = NULL;
	ZP_DD_SetNotification = NULL;
	ZP_DD_GetNextMessage = NULL;
	ZP_DD_SetGlobalSettings = NULL;
	ZP_DD_GetGlobalSettings = NULL;
	ZP_DD_Refresh = NULL;
	ZP_SetServiceCtrlHandle = NULL;
	ZP_DeviceEventNotify = NULL;
	ZP_Port_Open = NULL;
	ZP_Port_SetBaudAndEvChar = NULL;
	ZP_Port_GetBaudAndEvChar = NULL;
	ZP_Port_GetConnectionStatus = NULL;
	ZP_Port_SetNotification = NULL;
	ZP_Port_EnumMessages = NULL;
	ZP_Port_Clear = NULL;
	ZP_Port_Write = NULL;
	ZP_Port_Read = NULL;
	ZP_Port_GetInCount = NULL;
	ZP_Port_SetDtr = NULL;
	ZP_Port_SetRts = NULL;
	ZP_RegSerialDevice = NULL;
	ZP_RegIpDevice = NULL;
#ifdef ZP_LOG
	ZP_SetLog = NULL;
	ZP_GetLog = NULL;
	ZP_AddLog = NULL;
#endif // ZP_LOG
#endif // ZPORT_LINKONREQUEST
}
