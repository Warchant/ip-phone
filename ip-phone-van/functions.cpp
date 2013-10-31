#include "functions.h"

const std::string int2str(const int &data)
{
    std::ostringstream buffer;
    buffer << data;
    return buffer.str();
}


const int str2int(const std::string &str)
{
    std::istringstream buffer(str);
    int result;
    buffer >> result;
    return result;
}
