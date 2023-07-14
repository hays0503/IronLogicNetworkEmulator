#include "header/IronLogicDependency/ZGuard.h"


#ifdef ZGUARD_LINKONREQUEST
ZG_GETVERSION ZG_GetVersion = NULL;
ZG_INITIALIZE ZG_Initialize = NULL;
ZG_FINALYZE ZG_Finalyze = NULL;
ZG_GETPROXYCONVERTERS ZG_GetProxyConverters = NULL;
ZG_UPDATECVTFIRMWARE ZG_UpdateCvtFirmware = NULL;
ZG_CVT_OPEN ZG_Cvt_Open = NULL;
ZG_CVT_DETTACHPORT ZG_Cvt_DettachPort = NULL;
ZG_CVT_GETCONNECTIONSTATUS ZG_Cvt_GetConnectionStatus = NULL;
ZG_CVT_GETWAITSETTINGS ZG_Cvt_GetWaitSettings = NULL;
ZG_CVT_SETWAITSETTINGS ZG_Cvt_SetWaitSettings = NULL;
ZG_CVT_SETCAPTURE ZG_Cvt_SetCapture = NULL;
ZG_CVT_RELEASECAPTURE ZG_Cvt_ReleaseCapture = NULL;
ZG_CVT_CLEAR ZG_Cvt_Clear = NULL;
ZG_CVT_SEND ZG_Cvt_Send = NULL;
ZG_CVT_RECEIVE ZG_Cvt_Receive = NULL;
ZG_CVT_EXEC ZG_Cvt_Exec = NULL;
ZG_CVT_ENUMCONTROLLERS ZG_Cvt_EnumControllers = NULL;
ZG_CVT_FINDCONTROLLER ZG_Cvt_FindController = NULL;
ZG_CVT_SEARCHCONTROLLERS ZG_Cvt_SearchControllers = NULL;
ZG_CVT_FINDNEXTCONTROLLER ZG_Cvt_FindNextController = NULL;
ZG_CVT_GETINFORMATION ZG_Cvt_GetInformation = NULL;
ZG_CVT_SETNOTIFICATION ZG_Cvt_SetNotification = NULL;
ZG_CVT_GETNEXTMESSAGE ZG_Cvt_GetNextMessage = NULL;
ZG_CVT_GETSCANCTRSSTATE ZG_Cvt_GetScanCtrsState = NULL;
ZG_CVT_UPDATEFIRMWARE ZG_Cvt_UpdateFirmware = NULL;
ZG_CVT_GETLICENSE ZG_Cvt_GetLicense = NULL;
ZG_CVT_SETLICENSEDATA ZG_Cvt_SetLicenseData = NULL;
ZG_CVT_CLEARALLLICENSES ZG_Cvt_ClearAllLicenses = NULL;
ZG_CVT_GETALLLICENSES ZG_Cvt_GetAllLicenses = NULL;
ZG_CVT_GETSHORTINFO ZG_Cvt_GetShortInfo = NULL;
ZG_CVT_GETLONGINFO ZG_Cvt_GetLongInfo = NULL;
ZG_CVT_UPDATECTRFIRMWARE ZG_Cvt_UpdateCtrFirmware = NULL;
ZG_CVT_SETCTRADDRBYSN ZG_Cvt_SetCtrAddrBySn = NULL;
ZG_CVT_SETCTRADDR ZG_Cvt_SetCtrAddr = NULL;
ZG_CVT_GETCTRINFONORM ZG_Cvt_GetCtrInfoNorm = NULL;
ZG_CVT_GETCTRINFOADV ZG_Cvt_GetCtrInfoAdv = NULL;
ZG_CVT_GETCTRINFOBYSN ZG_Cvt_GetCtrInfoBySn = NULL;
ZG_CVT_GETCTRINFOLINE ZG_Cvt_GetCtrInfoLine = NULL;
ZG_CVT_GETCTRVERSION ZG_Cvt_GetCtrVersion = NULL;
ZG_CTR_OPEN ZG_Ctr_Open = NULL;
ZG_CTR_GETINFORMATION ZG_Ctr_GetInformation = NULL;
ZG_CTR_SETNOTIFICATION ZG_Ctr_SetNotification = NULL;
ZG_CTR_GETNEXTMESSAGE ZG_Ctr_GetNextMessage = NULL;
ZG_CTR_SETNEWADDR ZG_Ctr_SetNewAddr = NULL;
ZG_CTR_ASSIGNADDR ZG_Ctr_AssignAddr = NULL;
ZG_CTR_UPDATEFIRMWARE ZG_Ctr_UpdateFirmware = NULL;
ZG_CTR_OPENLOCK ZG_Ctr_OpenLock = NULL;
ZG_CTR_ENABLEEMERGENCYUNLOCKING ZG_Ctr_EnableEmergencyUnlocking = NULL;
ZG_CTR_ISEMERGENCYUNLOCKINGENABLED ZG_Ctr_IsEmergencyUnlockingEnabled = NULL;
ZG_CTR_READREGS ZG_Ctr_ReadRegs = NULL;
ZG_CTR_READPORTS ZG_Ctr_ReadPorts = NULL;
ZG_CTR_CONTROLDEVICES ZG_Ctr_ControlDevices = NULL;
ZG_CTR_READDATA ZG_Ctr_ReadData = NULL;
ZG_CTR_WRITEDATA ZG_Ctr_WriteData = NULL;
ZG_CTR_READLOCKTIMES ZG_Ctr_ReadLockTimes = NULL;
ZG_CTR_WRITELOCKTIMES ZG_Ctr_WriteLockTimes = NULL;
ZG_CTR_READTIMEZONES ZG_Ctr_ReadTimeZones = NULL;
ZG_CTR_WRITETIMEZONES ZG_Ctr_WriteTimeZones = NULL;
ZG_CTR_ENUMTIMEZONES ZG_Ctr_EnumTimeZones = NULL;
ZG_CTR_READKEYS ZG_Ctr_ReadKeys = NULL;
ZG_CTR_WRITEKEYS ZG_Ctr_WriteKeys = NULL;
ZG_CTR_CLEARKEYS ZG_Ctr_ClearKeys = NULL;
ZG_CTR_GETKEYTOPINDEX ZG_Ctr_GetKeyTopIndex = NULL;
ZG_CTR_SETKEYTOPINDEX ZG_Ctr_SetKeyTopIndex = NULL;
ZG_CTR_ENUMKEYS ZG_Ctr_EnumKeys = NULL;
ZG_CTR_GETCLOCK ZG_Ctr_GetClock = NULL;
ZG_CTR_SETCLOCK ZG_Ctr_SetClock = NULL;
ZG_CTR_READLASTKEYNUM ZG_Ctr_ReadLastKeyNum = NULL;
ZG_CTR_READRTCSTATE ZG_Ctr_ReadRTCState = NULL;
ZG_CTR_READEVENTIDXS ZG_Ctr_ReadEventIdxs = NULL;
ZG_CTR_WRITEEVENTIDXS ZG_Ctr_WriteEventIdxs = NULL;
ZG_CTR_READEVENTS ZG_Ctr_ReadEvents = NULL;
ZG_CTR_ENUMEVENTS ZG_Ctr_EnumEvents = NULL;
ZG_CTR_DECODEPASSEVENT ZG_Ctr_DecodePassEvent = NULL;
ZG_Ctr_DECODEECEVENT ZG_Ctr_DecodeEcEvent = NULL;
ZG_CTR_DECODEUNKKEYEVENT ZG_Ctr_DecodeUnkKeyEvent = NULL;
ZG_CTR_DECODEFIREEVENT ZG_Ctr_DecodeFireEvent = NULL;
ZG_CTR_DECODESECUREVENT ZG_Ctr_DecodeSecurEvent = NULL;
ZG_CTR_DECODEMODEEVENT ZG_Ctr_DecodeModeEvent = NULL;
ZG_DECODEHOTELEVENT ZG_DecodeHotelEvent = NULL;
ZG_CTR_SETFIREMODE ZG_Ctr_SetFireMode = NULL;
ZG_CTR_GETFIREINFO ZG_Ctr_GetFireInfo = NULL;
ZG_CTR_SETFIRECONFIG ZG_Ctr_SetFireConfig = NULL;
ZG_CTR_SETSECURMODE ZG_Ctr_SetSecurMode = NULL;
ZG_CTR_GETSECURINFO ZG_Ctr_GetSecurInfo = NULL;
ZG_CTR_SETSECURCONFIG ZG_Ctr_SetSecurConfig = NULL;
ZG_CTR_SETCTRMODE ZG_Ctr_SetCtrMode = NULL;
ZG_CTR_GETCTRMODEINFO ZG_Ctr_GetCtrModeInfo = NULL;
ZG_CTR_READELECTROCONFIG ZG_Ctr_ReadElectroConfig = NULL;
ZG_CTR_WRITEELECTROCONFIG ZG_Ctr_WriteElectroConfig = NULL;
ZG_CTR_GETELECTROSTATE ZG_Ctr_GetElectroState = NULL;
ZG_CTR_SETELECTROPOWER ZG_Ctr_SetElectroPower = NULL;
ZG_CTR_READAPBTIME ZG_Ctr_ReadApbTime = NULL;
ZG_CTR_WRITEAPBTIME ZG_Ctr_WriteApbTime = NULL;
ZG_CTR_GETCONFIGDATA ZG_Ctr_GetConfigData = NULL;
ZG_CTR_SETCONFIGDATA ZG_Ctr_SetConfigData = NULL;
ZG_GETCTRCONFIGPARAMS ZG_GetCtrConfigParams = NULL;
ZG_SETCTRCONFIGPARAMS ZG_SetCtrConfigParams = NULL;

HMODULE	hZgLib = 0;
INT nZgLoadCount = 0;
#endif // ZGUARD_LINKONREQUEST

BOOL CheckZgVersion()
{
	DWORD nVersion = ZG_GetVersion();
	return ((nVersion & 0xff) == ZG_SDK_VER_MAJOR) && (((nVersion >> 8) & 0xff) == ZG_SDK_VER_MINOR);
}

HRESULT LoadZGuard(LPCTSTR pszPath/*=NULL*/)
{
#ifdef ZGUARD_LINKONREQUEST
	HRESULT hr = S_OK;
	if (++nZgLoadCount > 1)
		return hr;
	hZgLib = LoadLibrary(pszPath ? pszPath : ZG_DLLNAME);
	if (hZgLib == 0)
		return HRESULT_FROM_WIN32(GetLastError());
	hr = LoadZPort();
	if (SUCCEEDED(hr))
	{
		if (((ZG_GetVersion = reinterpret_cast<ZG_GETVERSION>(GetProcAddress(hZgLib, "ZG_GetVersion"))) != NULL) && 
				CheckZgVersion())
		{
			if (((ZG_Initialize = reinterpret_cast<ZG_INITIALIZE>(GetProcAddress(hZgLib, "ZG_Initialize"))) == NULL) ||
					((ZG_Finalyze = reinterpret_cast<ZG_FINALYZE>(GetProcAddress(hZgLib, "ZG_Finalyze"))) == NULL) ||
					((ZG_GetProxyConverters = reinterpret_cast<ZG_GETPROXYCONVERTERS>(GetProcAddress(hZgLib, "ZG_GetProxyConverters"))) == NULL) ||
					((ZG_UpdateCvtFirmware = reinterpret_cast<ZG_UPDATECVTFIRMWARE>(GetProcAddress(hZgLib, "ZG_UpdateCvtFirmware"))) == NULL) ||
					((ZG_Cvt_Open = reinterpret_cast<ZG_CVT_OPEN>(GetProcAddress(hZgLib, "ZG_Cvt_Open"))) == NULL) ||
					((ZG_Cvt_DettachPort = reinterpret_cast<ZG_CVT_DETTACHPORT>(GetProcAddress(hZgLib, "ZG_Cvt_DettachPort"))) == NULL) ||
					((ZG_Cvt_GetConnectionStatus = reinterpret_cast<ZG_CVT_GETCONNECTIONSTATUS>(GetProcAddress(hZgLib, "ZG_Cvt_GetConnectionStatus"))) == NULL) ||
					((ZG_Cvt_GetWaitSettings = reinterpret_cast<ZG_CVT_GETWAITSETTINGS>(GetProcAddress(hZgLib, "ZG_Cvt_GetWaitSettings"))) == NULL) ||
					((ZG_Cvt_SetWaitSettings = reinterpret_cast<ZG_CVT_SETWAITSETTINGS>(GetProcAddress(hZgLib, "ZG_Cvt_SetWaitSettings"))) == NULL) ||
					((ZG_Cvt_SetCapture = reinterpret_cast<ZG_CVT_SETCAPTURE>(GetProcAddress(hZgLib, "ZG_Cvt_SetCapture"))) == NULL) ||
					((ZG_Cvt_ReleaseCapture = reinterpret_cast<ZG_CVT_RELEASECAPTURE>(GetProcAddress(hZgLib, "ZG_Cvt_ReleaseCapture"))) == NULL) ||
					((ZG_Cvt_Clear = reinterpret_cast<ZG_CVT_CLEAR>(GetProcAddress(hZgLib, "ZG_Cvt_Clear"))) == NULL) ||
					((ZG_Cvt_Send = reinterpret_cast<ZG_CVT_SEND>(GetProcAddress(hZgLib, "ZG_Cvt_Send"))) == NULL) ||
					((ZG_Cvt_Receive = reinterpret_cast<ZG_CVT_RECEIVE>(GetProcAddress(hZgLib, "ZG_Cvt_Receive"))) == NULL) ||
					((ZG_Cvt_Exec = reinterpret_cast<ZG_CVT_EXEC>(GetProcAddress(hZgLib, "ZG_Cvt_Exec"))) == NULL) ||
					((ZG_Cvt_EnumControllers = reinterpret_cast<ZG_CVT_ENUMCONTROLLERS>(GetProcAddress(hZgLib, "ZG_Cvt_EnumControllers"))) == NULL) ||
					((ZG_Cvt_FindController = reinterpret_cast<ZG_CVT_FINDCONTROLLER>(GetProcAddress(hZgLib, "ZG_Cvt_FindController"))) == NULL) || 
					((ZG_Cvt_SearchControllers = reinterpret_cast<ZG_CVT_SEARCHCONTROLLERS>(GetProcAddress(hZgLib, "ZG_Cvt_SearchControllers"))) == NULL) ||
					((ZG_Cvt_FindNextController = reinterpret_cast<ZG_CVT_FINDNEXTCONTROLLER>(GetProcAddress(hZgLib, "ZG_Cvt_FindNextController"))) == NULL) ||
					((ZG_Cvt_GetInformation = reinterpret_cast<ZG_CVT_GETINFORMATION>(GetProcAddress(hZgLib, "ZG_Cvt_GetInformation"))) == NULL) ||
					((ZG_Cvt_SetNotification = reinterpret_cast<ZG_CVT_SETNOTIFICATION>(GetProcAddress(hZgLib, "ZG_Cvt_SetNotification"))) == NULL) ||
					((ZG_Cvt_GetNextMessage = reinterpret_cast<ZG_CVT_GETNEXTMESSAGE>(GetProcAddress(hZgLib, "ZG_Cvt_GetNextMessage"))) == NULL) ||
					((ZG_Cvt_GetScanCtrsState = reinterpret_cast<ZG_CVT_GETSCANCTRSSTATE>(GetProcAddress(hZgLib, "ZG_Cvt_GetScanCtrsState"))) == NULL) ||
					((ZG_Cvt_UpdateFirmware = reinterpret_cast<ZG_CVT_UPDATEFIRMWARE>(GetProcAddress(hZgLib, "ZG_Cvt_UpdateFirmware"))) == NULL) ||
					((ZG_Cvt_GetLicense = reinterpret_cast<ZG_CVT_GETLICENSE>(GetProcAddress(hZgLib, "ZG_Cvt_GetLicense"))) == NULL) ||
					((ZG_Cvt_SetLicenseData = reinterpret_cast<ZG_CVT_SETLICENSEDATA>(GetProcAddress(hZgLib, "ZG_Cvt_SetLicenseData"))) == NULL) ||
					((ZG_Cvt_ClearAllLicenses = reinterpret_cast<ZG_CVT_CLEARALLLICENSES>(GetProcAddress(hZgLib, "ZG_Cvt_ClearAllLicenses"))) == NULL) ||
					((ZG_Cvt_GetAllLicenses = reinterpret_cast<ZG_CVT_GETALLLICENSES>(GetProcAddress(hZgLib, "ZG_Cvt_GetAllLicenses"))) == NULL) ||
					((ZG_Cvt_GetShortInfo = reinterpret_cast<ZG_CVT_GETSHORTINFO>(GetProcAddress(hZgLib, "ZG_Cvt_GetShortInfo"))) == NULL) ||
					((ZG_Cvt_GetLongInfo = reinterpret_cast<ZG_CVT_GETLONGINFO>(GetProcAddress(hZgLib, "ZG_Cvt_GetLongInfo"))) == NULL) ||
					((ZG_Cvt_UpdateCtrFirmware = reinterpret_cast<ZG_CVT_UPDATECTRFIRMWARE>(GetProcAddress(hZgLib, "ZG_Cvt_UpdateCtrFirmware"))) == NULL) ||
					((ZG_Cvt_SetCtrAddrBySn = reinterpret_cast<ZG_CVT_SETCTRADDRBYSN>(GetProcAddress(hZgLib, "ZG_Cvt_SetCtrAddrBySn"))) == NULL) ||
					((ZG_Cvt_SetCtrAddr = reinterpret_cast<ZG_CVT_SETCTRADDR>(GetProcAddress(hZgLib, "ZG_Cvt_SetCtrAddr"))) == NULL) ||
					((ZG_Cvt_GetCtrInfoNorm = reinterpret_cast<ZG_CVT_GETCTRINFONORM>(GetProcAddress(hZgLib, "ZG_Cvt_GetCtrInfoNorm"))) == NULL) ||
					((ZG_Cvt_GetCtrInfoAdv = reinterpret_cast<ZG_CVT_GETCTRINFOADV>(GetProcAddress(hZgLib, "ZG_Cvt_GetCtrInfoAdv"))) == NULL) ||
					((ZG_Cvt_GetCtrInfoBySn = reinterpret_cast<ZG_CVT_GETCTRINFOBYSN>(GetProcAddress(hZgLib, "ZG_Cvt_GetCtrInfoBySn"))) == NULL) ||
					((ZG_Cvt_GetCtrInfoLine = reinterpret_cast<ZG_CVT_GETCTRINFOLINE>(GetProcAddress(hZgLib, "ZG_Cvt_GetCtrInfoLine"))) == NULL) ||
					((ZG_Cvt_GetCtrVersion = reinterpret_cast<ZG_CVT_GETCTRVERSION>(GetProcAddress(hZgLib, "ZG_Cvt_GetCtrVersion"))) == NULL) ||
					((ZG_Ctr_Open = reinterpret_cast<ZG_CTR_OPEN>(GetProcAddress(hZgLib, "ZG_Ctr_Open"))) == NULL) ||
					((ZG_Ctr_GetInformation = reinterpret_cast<ZG_CTR_GETINFORMATION>(GetProcAddress(hZgLib, "ZG_Ctr_GetInformation"))) == NULL) ||
					((ZG_Ctr_SetNotification = reinterpret_cast<ZG_CTR_SETNOTIFICATION>(GetProcAddress(hZgLib, "ZG_Ctr_SetNotification"))) == NULL) ||
					((ZG_Ctr_GetNextMessage = reinterpret_cast<ZG_CTR_GETNEXTMESSAGE>(GetProcAddress(hZgLib, "ZG_Ctr_GetNextMessage"))) == NULL) ||
					((ZG_Ctr_SetNewAddr = reinterpret_cast<ZG_CTR_SETNEWADDR>(GetProcAddress(hZgLib, "ZG_Ctr_SetNewAddr"))) == NULL) ||
					((ZG_Ctr_AssignAddr = reinterpret_cast<ZG_CTR_ASSIGNADDR>(GetProcAddress(hZgLib, "ZG_Ctr_AssignAddr"))) == NULL) ||
					((ZG_Ctr_UpdateFirmware = reinterpret_cast<ZG_CTR_UPDATEFIRMWARE>(GetProcAddress(hZgLib, "ZG_Ctr_UpdateFirmware"))) == NULL) ||
					((ZG_Ctr_OpenLock = reinterpret_cast<ZG_CTR_OPENLOCK>(GetProcAddress(hZgLib, "ZG_Ctr_OpenLock"))) == NULL) ||
					((ZG_Ctr_EnableEmergencyUnlocking = reinterpret_cast<ZG_CTR_ENABLEEMERGENCYUNLOCKING>(GetProcAddress(hZgLib, "ZG_Ctr_EnableEmergencyUnlocking"))) == NULL) ||
					((ZG_Ctr_IsEmergencyUnlockingEnabled = reinterpret_cast<ZG_CTR_ISEMERGENCYUNLOCKINGENABLED>(GetProcAddress(hZgLib, "ZG_Ctr_IsEmergencyUnlockingEnabled"))) == NULL) ||
					((ZG_Ctr_ReadRegs = reinterpret_cast<ZG_CTR_READREGS>(GetProcAddress(hZgLib, "ZG_Ctr_ReadRegs"))) == NULL) ||
					((ZG_Ctr_ReadPorts = reinterpret_cast<ZG_CTR_READPORTS>(GetProcAddress(hZgLib, "ZG_Ctr_ReadPorts"))) == NULL) ||
					((ZG_Ctr_ControlDevices = reinterpret_cast<ZG_CTR_CONTROLDEVICES>(GetProcAddress(hZgLib, "ZG_Ctr_ControlDevices"))) == NULL) ||
					((ZG_Ctr_ReadData = reinterpret_cast<ZG_CTR_READDATA>(GetProcAddress(hZgLib, "ZG_Ctr_ReadData"))) == NULL) ||
					((ZG_Ctr_WriteData = reinterpret_cast<ZG_CTR_WRITEDATA>(GetProcAddress(hZgLib, "ZG_Ctr_WriteData"))) == NULL) ||
					((ZG_Ctr_ReadLockTimes = reinterpret_cast<ZG_CTR_READLOCKTIMES>(GetProcAddress(hZgLib, "ZG_Ctr_ReadLockTimes"))) == NULL) ||
					((ZG_Ctr_WriteLockTimes = reinterpret_cast<ZG_CTR_WRITELOCKTIMES>(GetProcAddress(hZgLib, "ZG_Ctr_WriteLockTimes"))) == NULL) ||
					((ZG_Ctr_ReadTimeZones = reinterpret_cast<ZG_CTR_READTIMEZONES>(GetProcAddress(hZgLib, "ZG_Ctr_ReadTimeZones"))) == NULL) ||
					((ZG_Ctr_WriteTimeZones = reinterpret_cast<ZG_CTR_WRITETIMEZONES>(GetProcAddress(hZgLib, "ZG_Ctr_WriteTimeZones"))) == NULL) ||
					((ZG_Ctr_EnumTimeZones = reinterpret_cast<ZG_CTR_ENUMTIMEZONES>(GetProcAddress(hZgLib, "ZG_Ctr_EnumTimeZones"))) == NULL) ||
					((ZG_Ctr_ReadKeys = reinterpret_cast<ZG_CTR_READKEYS>(GetProcAddress(hZgLib, "ZG_Ctr_ReadKeys"))) == NULL) ||
					((ZG_Ctr_WriteKeys = reinterpret_cast<ZG_CTR_WRITEKEYS>(GetProcAddress(hZgLib, "ZG_Ctr_WriteKeys"))) == NULL) ||
					((ZG_Ctr_ClearKeys = reinterpret_cast<ZG_CTR_CLEARKEYS>(GetProcAddress(hZgLib, "ZG_Ctr_ClearKeys"))) == NULL) ||
					((ZG_Ctr_GetKeyTopIndex = reinterpret_cast<ZG_CTR_GETKEYTOPINDEX>(GetProcAddress(hZgLib, "ZG_Ctr_GetKeyTopIndex"))) == NULL) ||
					((ZG_Ctr_SetKeyTopIndex = reinterpret_cast<ZG_CTR_SETKEYTOPINDEX>(GetProcAddress(hZgLib, "ZG_Ctr_SetKeyTopIndex"))) == NULL) ||
					((ZG_Ctr_EnumKeys = reinterpret_cast<ZG_CTR_ENUMKEYS>(GetProcAddress(hZgLib, "ZG_Ctr_EnumKeys"))) == NULL) ||
					((ZG_Ctr_GetClock = reinterpret_cast<ZG_CTR_GETCLOCK>(GetProcAddress(hZgLib, "ZG_Ctr_GetClock"))) == NULL) ||
					((ZG_Ctr_SetClock = reinterpret_cast<ZG_CTR_SETCLOCK>(GetProcAddress(hZgLib, "ZG_Ctr_SetClock"))) == NULL) ||
					((ZG_Ctr_ReadLastKeyNum = reinterpret_cast<ZG_CTR_READLASTKEYNUM>(GetProcAddress(hZgLib, "ZG_Ctr_ReadLastKeyNum"))) == NULL) ||
					((ZG_Ctr_ReadRTCState = reinterpret_cast<ZG_CTR_READRTCSTATE>(GetProcAddress(hZgLib, "ZG_Ctr_ReadRTCState"))) == NULL) ||
					((ZG_Ctr_ReadEventIdxs = reinterpret_cast<ZG_CTR_READEVENTIDXS>(GetProcAddress(hZgLib, "ZG_Ctr_ReadEventIdxs"))) == NULL) ||
					((ZG_Ctr_WriteEventIdxs = reinterpret_cast<ZG_CTR_WRITEEVENTIDXS>(GetProcAddress(hZgLib, "ZG_Ctr_WriteEventIdxs"))) == NULL) ||
					((ZG_Ctr_ReadEvents = reinterpret_cast<ZG_CTR_READEVENTS>(GetProcAddress(hZgLib, "ZG_Ctr_ReadEvents"))) == NULL) ||
					((ZG_Ctr_EnumEvents = reinterpret_cast<ZG_CTR_ENUMEVENTS>(GetProcAddress(hZgLib, "ZG_Ctr_EnumEvents"))) == NULL) ||
					((ZG_Ctr_DecodePassEvent = reinterpret_cast<ZG_CTR_DECODEPASSEVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodePassEvent"))) == NULL) ||
					((ZG_Ctr_DecodeEcEvent = reinterpret_cast<ZG_Ctr_DECODEECEVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodeEcEvent"))) == NULL) ||
					((ZG_Ctr_DecodeUnkKeyEvent = reinterpret_cast<ZG_CTR_DECODEUNKKEYEVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodeUnkKeyEvent"))) == NULL) ||
					((ZG_Ctr_DecodeFireEvent = reinterpret_cast<ZG_CTR_DECODEFIREEVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodeFireEvent"))) == NULL) ||
					((ZG_Ctr_DecodeSecurEvent = reinterpret_cast<ZG_CTR_DECODESECUREVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodeSecurEvent"))) == NULL) ||
					((ZG_Ctr_DecodeModeEvent = reinterpret_cast<ZG_CTR_DECODEMODEEVENT>(GetProcAddress(hZgLib, "ZG_Ctr_DecodeModeEvent"))) == NULL) ||
					((ZG_DecodeHotelEvent = reinterpret_cast<ZG_DECODEHOTELEVENT>(GetProcAddress(hZgLib, "ZG_DecodeHotelEvent"))) == NULL) ||
					((ZG_Ctr_SetFireMode = reinterpret_cast<ZG_CTR_SETFIREMODE>(GetProcAddress(hZgLib, "ZG_Ctr_SetFireMode"))) == NULL) ||
					((ZG_Ctr_GetFireInfo = reinterpret_cast<ZG_CTR_GETFIREINFO>(GetProcAddress(hZgLib, "ZG_Ctr_GetFireInfo"))) == NULL) ||
					((ZG_Ctr_SetFireConfig = reinterpret_cast<ZG_CTR_SETFIRECONFIG>(GetProcAddress(hZgLib, "ZG_Ctr_SetFireConfig"))) == NULL) ||
					((ZG_Ctr_SetSecurMode = reinterpret_cast<ZG_CTR_SETSECURMODE>(GetProcAddress(hZgLib, "ZG_Ctr_SetSecurMode"))) == NULL) ||
					((ZG_Ctr_GetSecurInfo = reinterpret_cast<ZG_CTR_GETSECURINFO>(GetProcAddress(hZgLib, "ZG_Ctr_GetSecurInfo"))) == NULL) ||
					((ZG_Ctr_SetSecurConfig = reinterpret_cast<ZG_CTR_SETSECURCONFIG>(GetProcAddress(hZgLib, "ZG_Ctr_SetSecurConfig"))) == NULL) ||
					((ZG_Ctr_SetCtrMode = reinterpret_cast<ZG_CTR_SETCTRMODE>(GetProcAddress(hZgLib, "ZG_Ctr_SetCtrMode"))) == NULL) ||
					((ZG_Ctr_GetCtrModeInfo = reinterpret_cast<ZG_CTR_GETCTRMODEINFO>(GetProcAddress(hZgLib, "ZG_Ctr_GetCtrModeInfo"))) == NULL) ||
					((ZG_Ctr_ReadElectroConfig = reinterpret_cast<ZG_CTR_READELECTROCONFIG>(GetProcAddress(hZgLib, "ZG_Ctr_ReadElectroConfig"))) == NULL) ||
					((ZG_Ctr_WriteElectroConfig = reinterpret_cast<ZG_CTR_WRITEELECTROCONFIG>(GetProcAddress(hZgLib, "ZG_Ctr_WriteElectroConfig"))) == NULL) ||
					((ZG_Ctr_GetElectroState = reinterpret_cast<ZG_CTR_GETELECTROSTATE>(GetProcAddress(hZgLib, "ZG_Ctr_GetElectroState"))) == NULL) ||
					((ZG_Ctr_SetElectroPower = reinterpret_cast<ZG_CTR_SETELECTROPOWER>(GetProcAddress(hZgLib, "ZG_Ctr_SetElectroPower"))) == NULL) ||
					((ZG_Ctr_ReadApbTime = reinterpret_cast<ZG_CTR_READAPBTIME>(GetProcAddress(hZgLib, "ZG_Ctr_ReadApbTime"))) == NULL) ||
					((ZG_Ctr_WriteApbTime = reinterpret_cast<ZG_CTR_WRITEAPBTIME>(GetProcAddress(hZgLib, "ZG_Ctr_WriteApbTime"))) == NULL) ||
					((ZG_Ctr_GetConfigData = reinterpret_cast<ZG_CTR_GETCONFIGDATA>(GetProcAddress(hZgLib, "ZG_Ctr_GetConfigData"))) == NULL) ||
					((ZG_Ctr_SetConfigData = reinterpret_cast<ZG_CTR_SETCONFIGDATA>(GetProcAddress(hZgLib, "ZG_Ctr_SetConfigData"))) == NULL) ||
					((ZG_GetCtrConfigParams = reinterpret_cast<ZG_GETCTRCONFIGPARAMS>(GetProcAddress(hZgLib, "ZG_GetCtrConfigParams"))) == NULL) ||
					((ZG_SetCtrConfigParams = reinterpret_cast<ZG_SETCTRCONFIGPARAMS>(GetProcAddress(hZgLib, "ZG_SetCtrConfigParams"))) == NULL))
				hr = E_NOINTERFACE;
		}
		else
			hr = E_NOINTERFACE;
	}

	if (FAILED(hr))
		UnloadZGuard();
	return hr;
#else
	if (CheckZgVersion())
		return S_OK;
	else
		return E_NOINTERFACE;
#endif // ZGUARD_LINKONREQUEST
}

VOID UnloadZGuard()
{
#ifdef ZGUARD_LINKONREQUEST
	if (--nZgLoadCount > 0)
		return;
	FreeLibrary(hZgLib);
	hZgLib = NULL;
	UnloadZPort();
	ZG_GetVersion = NULL;
	ZG_Initialize = NULL;
	ZG_Finalyze = NULL;
	ZG_GetProxyConverters = NULL;
	ZG_UpdateCvtFirmware = NULL;
	ZG_Cvt_Open = NULL;
	ZG_Cvt_DettachPort = NULL;
	ZG_Cvt_GetConnectionStatus = NULL;
	ZG_Cvt_GetWaitSettings = NULL;
	ZG_Cvt_SetWaitSettings = NULL;
	ZG_Cvt_SetCapture = NULL;
	ZG_Cvt_ReleaseCapture = NULL;
	ZG_Cvt_Clear = NULL;
	ZG_Cvt_Send = NULL;
	ZG_Cvt_Receive = NULL;
	ZG_Cvt_Exec = NULL;
	ZG_Cvt_EnumControllers = NULL;
	ZG_Cvt_FindController = NULL;
	ZG_Cvt_SearchControllers = NULL;
	ZG_Cvt_FindNextController = NULL;
	ZG_Cvt_GetInformation = NULL;
	ZG_Cvt_SetNotification = NULL;
	ZG_Cvt_GetNextMessage = NULL;
	ZG_Cvt_GetScanCtrsState = NULL;
	ZG_Cvt_UpdateFirmware = NULL;
	ZG_Cvt_GetLicense = NULL;
	ZG_Cvt_SetLicenseData = NULL;
	ZG_Cvt_ClearAllLicenses = NULL;
	ZG_Cvt_GetAllLicenses = NULL;
	ZG_Cvt_GetShortInfo = NULL;
	ZG_Cvt_GetLongInfo = NULL;
	ZG_Cvt_UpdateCtrFirmware = NULL;
	ZG_Cvt_SetCtrAddrBySn = NULL;
	ZG_Cvt_SetCtrAddr = NULL;
	ZG_Cvt_GetCtrInfoNorm = NULL;
	ZG_Cvt_GetCtrInfoAdv = NULL;
	ZG_Cvt_GetCtrInfoBySn = NULL;
	ZG_Cvt_GetCtrInfoLine = NULL;
	ZG_Cvt_GetCtrVersion = NULL;
	ZG_Ctr_Open = NULL;
	ZG_Ctr_GetInformation = NULL;
	ZG_Ctr_SetNotification = NULL;
	ZG_Ctr_GetNextMessage = NULL;
	ZG_Ctr_SetNewAddr = NULL;
	ZG_Ctr_AssignAddr = NULL;
	ZG_Ctr_UpdateFirmware = NULL;
	ZG_Ctr_OpenLock = NULL;
	ZG_Ctr_EnableEmergencyUnlocking = NULL;
	ZG_Ctr_IsEmergencyUnlockingEnabled = NULL;
	ZG_Ctr_ReadRegs = NULL;
	ZG_Ctr_ReadPorts = NULL;
	ZG_Ctr_ControlDevices = NULL;
	ZG_Ctr_ReadData = NULL;
	ZG_Ctr_WriteData = NULL;
	ZG_Ctr_ReadLockTimes = NULL;
	ZG_Ctr_WriteLockTimes = NULL;
	ZG_Ctr_ReadTimeZones = NULL;
	ZG_Ctr_WriteTimeZones = NULL;
	ZG_Ctr_EnumTimeZones = NULL;
	ZG_Ctr_ReadKeys = NULL;
	ZG_Ctr_WriteKeys = NULL;
	ZG_Ctr_ClearKeys = NULL;
	ZG_Ctr_GetKeyTopIndex = NULL;
	ZG_Ctr_SetKeyTopIndex = NULL;
	ZG_Ctr_EnumKeys = NULL;
	ZG_Ctr_GetClock = NULL;
	ZG_Ctr_SetClock = NULL;
	ZG_Ctr_ReadLastKeyNum = NULL;
	ZG_Ctr_ReadRTCState = NULL;
	ZG_Ctr_ReadEventIdxs = NULL;
	ZG_Ctr_WriteEventIdxs = NULL;
	ZG_Ctr_ReadEvents = NULL;
	ZG_Ctr_EnumEvents = NULL;
	ZG_Ctr_DecodePassEvent = NULL;
	ZG_Ctr_DecodeEcEvent = NULL;
	ZG_Ctr_DecodeUnkKeyEvent = NULL;
	ZG_Ctr_DecodeFireEvent = NULL;
	ZG_Ctr_DecodeSecurEvent = NULL;
	ZG_Ctr_DecodeModeEvent = NULL;
	ZG_DecodeHotelEvent = NULL;
	ZG_Ctr_SetFireMode = NULL;
	ZG_Ctr_GetFireInfo = NULL;
	ZG_Ctr_SetFireConfig = NULL;
	ZG_Ctr_SetSecurMode = NULL;
	ZG_Ctr_GetSecurInfo = NULL;
	ZG_Ctr_SetSecurConfig = NULL;
	ZG_Ctr_SetCtrMode = NULL;
	ZG_Ctr_GetCtrModeInfo = NULL;
	ZG_Ctr_ReadElectroConfig = NULL;
	ZG_Ctr_WriteElectroConfig = NULL;
	ZG_Ctr_GetElectroState = NULL;
	ZG_Ctr_SetElectroPower = NULL;
	ZG_Ctr_ReadApbTime = NULL;
	ZG_Ctr_WriteApbTime = NULL;
	ZG_Ctr_GetConfigData = NULL;
	ZG_Ctr_SetConfigData = NULL;
	ZG_GetCtrConfigParams = NULL;
	ZG_SetCtrConfigParams = NULL;
#endif // ZGUARD_LINKONREQUEST
}
