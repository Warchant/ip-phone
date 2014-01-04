#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <sstream>

typedef int packet;
//#define PLACEHOLDER SHRT_MIN
#define STOP_SYMBOL 0

/*
 * @function int2str
 * @brief Converts input int data to std::string;
 */
std::string int2str(const int& data);

/*
 * @function str2int
 * @brief Converts input std::string str into integer;
 */
int str2int(const std::string &str);

int twoCharToInt(unsigned char a, unsigned char b);

unsigned char * intToTwoChar(int a);

extern int PLACEHOLDER;

#endif // FUNCTIONS_H
