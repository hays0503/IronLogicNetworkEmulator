#include "header/IronLogicDependency/Utils.h"
#include "header/IronLogicDependency/ZGuard.h"


using namespace std;

LPCTSTR PortTypeStrs[] = {
	TEXT("Unknown"), 
	TEXT("COM"), 
	TEXT("FT"), 
	TEXT("IP"), 
	TEXT("IPS")
};
LPCTSTR CvtTypeStrs[] = {
	TEXT("Unknown"), 
	TEXT("Z-397"), 
	TEXT("Z-397 Guard"), 
	TEXT("Z-397 IP"), 
	TEXT("Z-397 Web"),
	TEXT("Z5R Web"),
	TEXT("Matrix II Wi-Fi")
};

LPCTSTR CtrTypeStrs[] = {
	TEXT(""),
	TEXT("Gate 2000"),
	TEXT("Matrix-II Net"),
	TEXT("Matrix-III Net"),
	TEXT("Z5R Net"),
	TEXT("Z5R Net 8000"),
	TEXT("Guard Net"),
	TEXT("Z-9 EHT Net"),
	TEXT("EuroLock EHT net"),
	TEXT("Z5R Web"),
	TEXT("Matrix II Wi-Fi")
};

std::string CtrTypeStrsStdString[] = {
	"",
	"Gate 2000",
	"Matrix-II Net",
	"Matrix-III Net",
	"Z5R Net",
	"Z5R Net 8000",
	"Guard Net",
	"Z-9 EHT Net",
	"EuroLock EHT net",
	"Z5R Web",
	"Matrix II Wi-Fi"
};

LPCTSTR GuardModeStrs[] = {
	TEXT("Unknown"), 
	TEXT("Normal"), 
	TEXT("Advanced"), 
	TEXT("Test"), 
	TEXT("Accept")
};
LPCTSTR KeyModeStrs[] = {
	TEXT("Touch Memory"),
	TEXT("Proximity")
};
LPCTSTR KeyTypeStrs[] = {
	TEXT(""),
	TEXT("Normal"),
	TEXT("Blocking"),
	TEXT("Master")
};


BOOL CheckZGError(HRESULT nStatus, LPCTSTR pszContext)
{
	if (SUCCEEDED(nStatus))
		return TRUE;	
	std::cout << "{DLLINFO}Ошибка / код ошибки: " << std::hex << nStatus << endl;
	LPTSTR pBuffer = NULL;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | ((HRESULT_FACILITY(nStatus) == 4) ? FORMAT_MESSAGE_FROM_HMODULE : FORMAT_MESSAGE_FROM_SYSTEM),
		GetModuleHandle(_T("ZGuard.dll")), 
		(DWORD)nStatus,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pBuffer, 
		0, 
		NULL);
	if (pBuffer != NULL)
	{
		_tprintf(TEXT("%s fail: %s\n"), pszContext, pBuffer);
		LocalFree(pBuffer);
	}
	return FALSE;
}

std::wstring ZKeyNumToStr(const Z_KEYNUM& rNum, BOOL fProximity)
{
	std::wstring s;

    const int lenKey = 6;

	if (fProximity)
	{
		int n;
		s.resize(128);
		n = _stprintf_s(&s[0], s.size(), TEXT("%d,%d"), rNum[3], *(PWORD)&rNum[1]);
		s.resize(n);
	}
	else
	{
		INT i, j;
        s.resize(lenKey * 2 + 1);
		j = 0;
        for (i = lenKey; i > 0; i--) {
			_stprintf_s(&s[j], s.size() - j, TEXT("%.2X"), rNum[i]);
			j += 2;
		}
        s.resize(lenKey * 2);
	}
	return s;
}


CZGuardLoader::CZGuardLoader()
{
	m_nStatus = LoadZGuard();
}

CZGuardLoader::~CZGuardLoader()
{
	if (SUCCEEDED(m_nStatus))
		UnloadZGuard();
}
