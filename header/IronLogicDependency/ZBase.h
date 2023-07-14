#pragma once

#include <tchar.h>
#include <algorithm>

using namespace std;

// Номер ключа контроллера ([0] - длина номера ключа)
typedef std::byte Z_KEYNUM[16];
typedef Z_KEYNUM *PZ_KEYNUM;

using namespace std;

//inline int CompareZKeyNums(const Z_KEYNUM& _Left, const Z_KEYNUM& _Right)
//{
//    int nRes;
//	if (_Left[0] == _Right[0])
//		nRes = (_Left[0] == 0) ? 0 : memcmp(&_Left[1], &_Right[1], _Left[0]);
//	else
//	{
//        int n = min(_Left[0], _Right[0]);
//		if (n > 0)
//			nRes = memcmp(&_Left[1], &_Right[1], n);
//		else
//			nRes = 0;
//		if (nRes == 0)
//			nRes = ((_Left[0] < _Right[0]) ? -1 : +1);
//	}
//	return nRes;
//}

