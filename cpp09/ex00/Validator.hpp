#pragma once
#include <iostream>
#include <exception>
#include <regex.h>
#include <time.h>
#include <string>
#include <cstdlib> 
#include <iomanip>
#include <algorithm>

inline std::string split(std::string str,const char delimiter, int start)
{
    return(str.substr(start, str.find(delimiter)));
}

class Validator
{

    public:
        static void ValidatorFormDate(std::string lineDate, int i) 
        {
            if (i == 0)
            {
                std::string test = lineDate;
                if (test != "date | value")
                {
                    throw std::runtime_error("One line");
                    return;
                }
                return;
            } 
            regex_t date;
            if (regcomp(&date, "[0-9]{4}-[0-9]{2}-[0-9]{2} \\| -?[0-9]+(\\.[0-9]{1,2})?$", REG_EXTENDED) != 0)
            {
                throw std::runtime_error("Regex invalid");
                return;
            }
            if(regexec(&date, lineDate.c_str(), 0, NULL, 0) == 0)
                regfree(&date);
            else
            {
                regfree(&date);
                throw std::runtime_error("Format invalid");
            }
        }
        static void ValidatorDate(std::string lineDate)
        {
            int years = atoi((split(lineDate, '-' , 0)).c_str());
            int month = atoi((split(lineDate, '-', 5)).c_str());
            int days = atoi((split (lineDate, '-', 8)).c_str());
            time_t rawtime;
            struct tm * timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            timeinfo->tm_year = years - 1900;
            timeinfo->tm_mon = month - 1;
            timeinfo->tm_mday = days;
            mktime(timeinfo);            
            if (
                timeinfo->tm_year != years - 1900 || 
                timeinfo->tm_mon != month - 1 || 
                timeinfo->tm_mday != days)
                throw std::runtime_error("Bad Input");
        }
        static void ValidatorValue(std::string stringValu)
        {
            char *end;
            float value = strtod(stringValu.c_str(), &end);
            if (value < 0)
                throw std::runtime_error("Bad value (neg)");
            if(value > 10)
                throw std::runtime_error("Bad value (top)");
        }
        static void verificationFileCsv(int ac)
        {
            std::string  filename = "data.csv";
            if(ac != 2  )
                throw std::runtime_error("Not number arguments");
            std::ifstream file(filename.c_str());
            if(file.is_open())
            {
                file.close();
                return;
            }
            else
                throw std::runtime_error("Not Rights file Csv");
        }
        static void verificationFileTxt(char **arg)
        {
            std::ifstream fileTxt(arg[1]);
            if(fileTxt.is_open() )
                fileTxt.close();
            else
                throw std::runtime_error("Not Rights file Txt");
        }
        static void isTxt(const char *str)
        {
            regex_t csv;
            if(regcomp(&csv, "\\.txt$", REG_EXTENDED) != 0)
                throw std::runtime_error("Error with regex for txt");
            if(regexec(&csv, str, 0, NULL, 0) == 0)
            {
                regfree(&csv);
                return;
            }
            else
            {
                regfree(&csv);    
                throw std::runtime_error("Error not format Valid for Txt");
            }    
        }
        static void verifFormat(int i, std::string line)
        {
            if(i == 1 && line =="date,exchange_rate")
                return;
            regex_t data;
            if (regcomp(&data, "^[0-9]{4}-[0-9]{2}-[0-9]{2},[0-9]+(\\.[0-9]{1,2})?$", REG_EXTENDED) != 0)
                throw std::runtime_error("Regex invalid");
            if(regexec(&data, line.c_str(), 0, NULL, 0) == 0)
                regfree(&data);
            else
            {
                regfree(&data);
                throw std::runtime_error("Format invalid Data");
            }
        }
};
    
