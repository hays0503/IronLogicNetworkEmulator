#include "header/Controller/controllerutility.h"


char my_toupper(char ch)
{
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

std::string str_toupper(string s) {
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c) { return std::toupper(c); });
    return s;
}

std::string readKeyInBufferHex(Z_KEYNUM &pNum) {

    //Конвертация ключа в вид который можно прочесть.
    //На примере ключа 7cd96f = 8182127

    //6f
    std::stringstream ssOneByte;
    ssOneByte << std::hex <<  WORD(pNum[1]);
    std::string sOneByte = ssOneByte.str();
    //Сделанно с целью предотвращение "схлопывание ключа"
    // Например "0D" без этого будет просто "D"
    if(sOneByte.length()<2){
        sOneByte="0"+sOneByte;
    };


    //d9
    std::stringstream ssTwoByte;
    ssTwoByte << std::hex <<  WORD(pNum[2]);
    std::string sTwoByte = ssTwoByte.str();
    //Сделанно с целью предотвращение "схлопывание ключа"
    // Например "0D" без этого будет просто "D"
    if(sTwoByte.length()<2){
        sTwoByte="0"+sTwoByte;
    };

    //6f
    std::stringstream ssThreeByte;
    ssThreeByte << std::hex <<  WORD(pNum[3]);
    std::string sThreeByte = ssThreeByte.str();
    //Сделанно с целью предотвращение "схлопывание ключа"
    // Например "0D" без этого будет просто "D"
    if(sThreeByte.length()<2){
        sThreeByte="0"+sThreeByte;
    };

    std::string sResult = "000000"+sThreeByte+sTwoByte+sOneByte;
    std::string uppercasestr = str_toupper(sResult);

    return uppercasestr;
}
