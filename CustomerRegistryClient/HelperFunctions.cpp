// Holds any helpful code put into functions due to repetition, any code refactored due to repetition will probably end up in here
#include "HelperFunctions.h"

bool is_digits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}