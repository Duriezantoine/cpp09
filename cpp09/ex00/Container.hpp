#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib> 
#include <time.h>

class Container
{
    private:
        std::map <std::string ,float> dateNumber;
    public:
        ~Container();
        Container(int ac, char **arg);
        Container(Container const& rhs);
        Container const& operator=(Container const& obj);
        std::string     splite(std::string str, char delimeter, int start);
        void            splitInfile(char **arg);
        void            includeMap(int i, std::string line);
        void            forIncludeMap();
        void            printResult(std::string line_date, std::string line_value, std::map <std::string, float> dateNumber);
        void            printValue(float i, std::string line_value, std::string lineDate);
};