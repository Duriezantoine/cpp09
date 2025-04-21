#pragma once
#include <iostream>
#include <string>
#include <regex.h>

class Validator
{
    public:
        static void validArg(int ac , char **arg)
        {
            if(ac==1)
                throw std::runtime_error("Qu'elle erreur ");
            regex_t format;
            int i = 1;

            if(regcomp(&format,"^[-+]?[0-9]" , REG_EXTENDED) != 0)
                throw std::runtime_error("Regex not ok");
            while(arg[i])
            {
                // std::cout << "Je verifie " << arg[i] << std::endl;
                if(regexec(&format, arg[i], 0, NULL, 0) == 0)
                {
                    // std::cout << "Le regex est ok" << std::endl;
                }
                else
                {
                    regfree(&format);
                    throw std::runtime_error("Format invalid");
                    return;
                }
                i++;
           }
           regfree(&format);
        }
};