#include "functions.h"


std::string int2str(const int &data)
{
    std::ostringstream buffer;
    buffer << data;
    return buffer.str();
}


int str2int(const std::string &str)
{
    std::istringstream buffer(str);
    int result;
    buffer >> result;
    return result;
}


int twoCharToInt(unsigned char a, unsigned char b)
{
    int i = *(signed char *)(&a);
    i *= 1 << CHAR_BIT;
    i |= b;
    return i;
}

// [0] -> a , [1] -> b
unsigned char *intToTwoChar(int a)
{
    unsigned char *ch = new unsigned char [2];
    ch[0] = a >> 8;
    ch[1] = a & 0xFF;
    return ch;
}
