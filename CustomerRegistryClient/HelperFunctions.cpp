// Holds any helpful code put into functions due to repetition, any code refactored due to repetition will probably end up in here
#include "HelperFunctions.h"

bool is_digits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool is_email(const std::string& str)
{
    return str.find('@') == std::string::npos;
}

bool is_customer_length_correct
(const int fNameLen, const int lNameLen, const int emailLen, const int phoneLen)
{
    return fNameLen < 30 and lNameLen < 30 and emailLen < 50 and phoneLen < 20;
}