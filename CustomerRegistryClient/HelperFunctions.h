#ifndef HELPERFUNCTIONS
#define HELPERFUNCTIONS

#include "Includes.h"

bool is_digits(const std::string& str);

bool is_email(const std::string& str);

bool is_customer_length_correct
(const int fNameLen, const int lNameLen, const int emailLen, const int phoneLen);

#endif // !HELPERFUNCTIONS
