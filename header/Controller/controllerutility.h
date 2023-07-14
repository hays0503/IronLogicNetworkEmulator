#ifndef CONTROLLERUTILITY_H
#define CONTROLLERUTILITY_H


#include <windows.h>
#include <iomanip>
#include <locale>


#include <sstream>
#include <iomanip>  // Для std::hex
#include <algorithm>  // Для std::transform
#include <cctype>  // Для std::toupper



#include "header/IronLogicDependency/ZBase.h"


char my_toupper(char ch);

std::string str_toupper(std::string s);

std::string readKeyInBufferHex(Z_KEYNUM& pNum);;

#endif //CONTROLLERUTILITY_H
