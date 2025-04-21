#include <iostream>
#include <regex.h>
#include <stdio.h>
class Validator
{
    public:
        static void validArg(int ac, char **arg)
        {
            if(ac != 2)
                throw std::runtime_error("Argument not correct");
            regex_t formatValid;
            if(regcomp(&formatValid, "[0-9] [0-9]( [*/+-] [0-9])* [*/+-]", REG_EXTENDED) != 0)
            {
                throw std::runtime_error("With Regex");
                return;
            }
            if(regexec(&formatValid, arg[1], 0, NULL, 0) == 0)
                regfree(&formatValid);
            else
            {
                regfree(&formatValid);
                throw std::runtime_error("FormatInvalid");
            }
        }
};