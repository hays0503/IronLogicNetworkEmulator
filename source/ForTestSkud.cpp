//#include <chrono>
//#include <thread>
//#include <typeinfo>
//#include <ctime>
//#include <string>
//#include <iostream>
//#include <locale.h>
//#include <tchar.h>

//#include "../../IronLogic/header/ZGuard.h"
//#include "../../IronLogic/header/ZPort.h"
//#include "../../IronLogic/header/Utils.h"
//#include "../../IronLogic/header/ForTestSkud.h"


//BOOL g_fThreadActive;
//HANDLE g_hEvent[2];
//HANDLE hCvt = NULL;// Конвертер описатель
//HANDLE g_hCtr[2]; // Контролер описатель
//INT g_nCtrMaxEvents;
//INT g_nAppReadEventIdx;
//HANDLE g_hThread[2];
//BOOL g_fProximity;

//void CurrentTime() {
//    // Получение текущего времени в стандарте UTC
//    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

//    // Преобразование времени в строку
//    char buffer[80];
//    struct tm timeInfo;
//    gmtime_s(&timeInfo, &currentTime);
//    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);


//    // Вывод времени в стандарте UTC
//    std::cout << "Время срабатывание события из Windows Api[ Текущее время (UTC)] : " << buffer << std::endl;
//}

//std::string str_toupper(std::string s) {
//    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
//    return s;
//}

//void ShowEvents(int nStart, int nCount,int indexController)
//{
//    _ZG_CTR_EVENT aEvents[6];
//    PZG_CTR_EVENT pEv;
//    int i, j, nIdx, nCnt;

//    i = 0;


//    while (i < nCount)
//    {
//        nIdx = (nStart + i) % g_nCtrMaxEvents;
//        nCnt = (nCount - i);
//        if (nCnt > _countof(aEvents))
//            nCnt = _countof(aEvents);

//        if ((nIdx + nCnt) > g_nCtrMaxEvents)
//            nCnt = (g_nCtrMaxEvents - nIdx);

//        if (!CheckZGError(ZG_Ctr_ReadEvents(g_hCtr[indexController], nIdx, aEvents, nCnt, NULL, NULL), _T("ZG_Ctr_ReadEvents")))
//            return;
//        for (j = 0; j < nCnt; j++)
//        {
//            pEv = &aEvents[j];
//            switch (pEv->nType)
//            {
//            case ZG_EV_ELECTRO_ON:
//            case ZG_EV_ELECTRO_OFF:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_EC_SUB_EV nSubEvent;
//                DWORD nPowerFlags;
//                ZG_Ctr_DecodeEcEvent(g_hCtr[indexController], pEv->aData, &rTime, &nSubEvent, &nPowerFlags);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s Sub_event: %s, Power flags: %d\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         EvTypeStrs[pEv->nType],
//                         EcSubEvStrs[nSubEvent], nPowerFlags);
//            }
//            break;
//            case ZG_EV_FIRE_STATE:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_FIRE_SUB_EV nSubEvent;
//                DWORD nFireFlags;
//                ZG_Ctr_DecodeFireEvent(g_hCtr[indexController], pEv->aData, &rTime, &nSubEvent, &nFireFlags);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s Sub_event: %s, Fire flags: %d\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         EvTypeStrs[pEv->nType],
//                         FireSubEvStrs[nSubEvent], nFireFlags);
//            }
//            break;
//            case ZG_EV_SECUR_STATE:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_SECUR_SUB_EV nSubEvent;
//                DWORD nSecurFlags;
//                ZG_Ctr_DecodeSecurEvent(g_hCtr[indexController], pEv->aData, &rTime, &nSubEvent, &nSecurFlags);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s Sub_event: %s, Security flags: %.2Xh\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         EvTypeStrs[pEv->nType],
//                         SecurSubEvStrs[nSubEvent], nSecurFlags);
//            }
//            break;
//            case ZG_EV_MODE_STATE:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_CTR_MODE nMode;
//                ZG_MODE_SUB_EV nSubEvent;
//                ZG_Ctr_DecodeModeEvent(g_hCtr[indexController], pEv->aData, &rTime, &nMode, &nSubEvent);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s Mode: %s, Sub_event: %s\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         EvTypeStrs[pEv->nType],
//                         ModeStrs[nMode],
//                         ModeSubEvStrs[nSubEvent]);
//            }
//            break;
//            case ZG_EV_KEY_OPEN:
//            case ZG_EV_KEY_ACCESS:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_CTR_DIRECT nDirect;
//                INT nKeyIdx, nKeyBank;
//                ZG_Ctr_DecodePassEvent(g_hCtr[indexController], pEv->aData, &rTime, &nDirect, &nKeyIdx, &nKeyBank);
//                PZG_CTR_KEY pBuf = new _ZG_CTR_KEY;
//                ZG_Ctr_ReadKeys(
//                    g_hCtr[indexController],
//                    nKeyIdx,
//                    pBuf,
//                    1,
//                    *ZG_PROCESSCALLBACK(NULL),
//                    NULL,
//                    nKeyBank
//                    );
//                //				std::cout << readKeyInBufferHex(pBuf->rNum) << std::endl;

//            }
//            break;
//            case ZG_EV_UNKNOWN_KEY:
//            {
//                Z_KEYNUM rNum;
//                ZG_Ctr_DecodeUnkKeyEvent(g_hCtr[indexController], pEv->aData, &rNum);
//                _tprintf(TEXT("%.4d. Key \"%s\"\n"),
//                         nIdx + j,
//                         ZKeyNumToStr(rNum, g_fProximity).c_str());
//            }
//            break;
//            case ZG_EV_HOTEL40:
//            case ZG_EV_HOTEL41:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_HOTEL_MODE nMode;
//                ZG_HOTEL_SUB_EV nSubEvent;
//                DWORD nFlags;
//                ZG_DecodeHotelEvent(pEv->aData, &rTime, &nMode, &nSubEvent, &nFlags);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s Mode: %s, Sub_event: %s, flags: %.2Xh\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         EvTypeStrs[pEv->nType],
//                         HModeStrs[nMode],
//                         HotelSubEvStrs[nSubEvent],
//                         nFlags);
//            }
//            break;
//            default:
//            {
//                _ZG_EV_TIME rTime;
//                ZG_CTR_DIRECT nDirect;
//                INT nKeyIdx, nKeyBank;
//                ZG_Ctr_DecodePassEvent(g_hCtr[indexController], pEv->aData, &rTime, &nDirect, &nKeyIdx, &nKeyBank);
//                _tprintf(TEXT("%.4d. %.2d.%.2d %.2d:%.2d:%.2d %s %s (key_idx: %d, bank#: %d)\n"),
//                         nIdx + j,
//                         rTime.nDay, rTime.nMonth,
//                         rTime.nHour, rTime.nMinute, rTime.nSecond,
//                         DirectStrs[nDirect],
//                         EvTypeStrs[pEv->nType],
//                         nKeyIdx, nKeyBank);
//            }
//            break;
//            }
//        }
//        i += nCnt;
//    }
//}

//HRESULT CheckNotifyMsgs(int indexController)
//{
//    std::cout << "CheckNotifyMsgs!" << std::endl;
//    HRESULT hr;
//    UINT nMsg;
//    LPARAM nMsgParam;
//    while ((hr = ZG_Ctr_GetNextMessage(g_hCtr[indexController], &nMsg, &nMsgParam)) == S_OK)
//    {
//        std::cout << "ZG_Ctr_GetNextMessage!" << std::endl;
//        std::cout << "nMsg " << nMsg << std::endl;
//        switch (nMsg)
//        {
//        case ZG_N_CTR_NEW_EVENT:
//        {
//            PZG_N_NEW_EVENT_INFO pInfo = PZG_N_NEW_EVENT_INFO(nMsgParam);

//            _tprintf(TEXT("==> New Events: %d\n"), pInfo->nNewCount);
//            ShowEvents(pInfo->nReadIdx, pInfo->nNewCount, indexController);
//            g_nAppReadEventIdx = pInfo->nWriteIdx;
//        }
//        break;
//        }
//    }
//    if (hr == ZP_S_NOTFOUND)
//        hr = S_OK;
//    return hr;
//}

//void StopNotifyThread()
//{
//    if (g_hThread[0] == NULL)
//        return;
//    if (g_hThread[1] == NULL)
//        return;
//    g_fThreadActive = FALSE;
//    SetEvent(g_hEvent[0]);
//    SetEvent(g_hEvent[1]);
//    WaitForSingleObject(g_hThread[0], INFINITE);
//    WaitForSingleObject(g_hThread[1], INFINITE);
//    CloseHandle(g_hThread[0]);
//    CloseHandle(g_hThread[1]);
//    g_hThread[0] = NULL;
//    g_hThread[1] = NULL;
//}

//DWORD WINAPI NotifyThreadProc(LPVOID lpParameter)
//{
//    int* indexController = ((int*)lpParameter);
//    std::cout << "NotifyThreadProc=>indexController! " << *indexController << std::endl;
//    std::cout << "NotifyThreadProc!" << std::endl;
//    while (g_fThreadActive)
//    {
//        std::cout << "Nachalsya tsikl sobytiy!" << std::endl;
//        if (WaitForSingleObject(g_hEvent[*indexController], INFINITE) == WAIT_OBJECT_0)
//        {
//            CurrentTime();
//            ResetEvent(g_hEvent[*indexController]);
//            if (g_hCtr[*indexController] != NULL)
//                CheckNotifyMsgs(*indexController);
//        }
//    }
//    return 0;
//}

//void createTreadController(int *indexController,int adress) {

//    _ZG_CTR_INFO rCtrInfo;
//    ZeroMemory(&rCtrInfo, sizeof(rCtrInfo));

//    if (!CheckZGError(ZG_Ctr_Open(&g_hCtr[*indexController], hCvt, adress, 0, &rCtrInfo, ZG_CTR_UNDEF), _T("ZG_Ctr_Open")))
//        return;
//    g_nCtrMaxEvents = rCtrInfo.nMaxEvents;
//    g_fProximity = (rCtrInfo.nFlags & ZG_CTR_F_PROXIMITY) != 0;

//    INT nWrIdx, nRdIdx;

//    if (!CheckZGError(ZG_Ctr_ReadEventIdxs(g_hCtr[*indexController], &nWrIdx, &nRdIdx), _T("ZG_Ctr_ReadEventIdxs")))
//        return;
//    std::cout << "Event record pointer." << nWrIdx << std::endl;
//    std::cout << "Event read pointer." << nRdIdx << std::endl;
//    std::cout << "controller address." << adress << std::endl;
//    g_nAppReadEventIdx = nWrIdx;

//    if (g_hEvent[*indexController] == NULL)
//        g_hEvent[*indexController] = CreateEvent(NULL, TRUE, FALSE, NULL);



//    _ZG_CTR_NOTIFY_SETTINGS rNS = { 0 };
//    rNS.nNMask = ZG_NF_CTR_NEW_EVENT;
//    rNS.hEvent = g_hEvent[*indexController];
//    rNS.nReadEvIdx = g_nAppReadEventIdx;
//    rNS.nCheckStatePeriod = 10;

//    if (!CheckZGError(ZG_Ctr_SetNotification(g_hCtr[*indexController], &rNS), _T("ZG_Ctr_SetNotification")))
//        return;


//    if (g_hThread[*indexController] != NULL)
//        return;
//    DWORD nThreadId = 0;
//    g_fThreadActive = TRUE;
//    std::cout << "indexController=> " << *indexController << std::endl;

//    g_hThread[*indexController] = CreateThread(NULL,
//                                               0,
//                                               NotifyThreadProc,
//                                               (PVOID*)indexController,
//                                               0,
//                                               &nThreadId);
//}

////int main_func(void* handle)
//int main_func()
//{
////    setlocale(LC_ALL, "Russian");

//    g_hCtr[0] = NULL;
//    g_hCtr[1] = NULL;

//    g_hEvent[0] = NULL;
//    g_hEvent[1] = NULL;

//    //Инициализация
//    CZGuardLoader* oZGL;
//    LPCWSTR CvtPortName = L"COM6";
//    const ZP_PORT_TYPE CvtPortType = ZP_PORT_COM;

//    oZGL = new CZGuardLoader();
//    if (!oZGL->IsLoaded())
//    {
//        std::cout<< (TEXT("Load ZGuard error 0x%X.\n"), oZGL->m_nStatus);
//        throw std::exception("Problemy s dll vozmozhno ona otsutstvuyet");
//    }

//    if (!CheckZGError(ZG_Initialize(ZP_IF_NO_MSG_LOOP), _T("ZG_Initialize")))
//        return false;

//    _ZG_CVT_OPEN_PARAMS rOp;
//    ZeroMemory(&rOp, sizeof(rOp));
//    rOp.nType = CvtPortType;
//    rOp.pszName = CvtPortName;
//    rOp.nSpeed = ZG_SPEED_57600;
//    if (!CheckZGError(ZG_Cvt_Open(&hCvt, &rOp, NULL), _T("ZG_Cvt_Open")))
//        return false;



//    int* Index0 = new int(0);
//    createTreadController(Index0, 1);
//    int* Index1 = new int(1);
//    createTreadController(Index1, 2);

//    while (1) {
//        ///Лупим программу
//        char ch = getchar();
//        if (ch == '1')
//        {
//            _tprintf(TEXT("Open.\n"));
//            ZG_Ctr_OpenLock(g_hCtr[0], 0);
//        }
//        if (ch == '2')
//        {
//            _tprintf(TEXT("Open.\n"));
//            ZG_Ctr_OpenLock(g_hCtr[1], 0);
//        }
//        if (ch == 'x')
//        {
//            _tprintf(TEXT("Aborted.\n"));
//            return 0;
//        }
//    }
//    //Корректно всё закрываю
//    StopNotifyThread();
//    if (g_hCtr[0] != NULL)
//        ZG_CloseHandle(g_hCtr[0]);
//    if (g_hCtr[1] != NULL)
//        ZG_CloseHandle(g_hCtr[1]);
//    if (hCvt != NULL)
//        ZG_CloseHandle(hCvt);
//    if (g_hEvent[0] != NULL)
//        CloseHandle(g_hEvent[0]);
//    if (g_hEvent[1] != NULL)
//        CloseHandle(g_hEvent[1]);
//    delete Index0;
//    delete Index1;
//    ZG_Finalyze();



//    return true;

//}
