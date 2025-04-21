#include "Container.hpp"
#include "Validator.hpp"
#include <map>


Container::~Container()
{
    std::cout << "Destructor class" << std::endl;
}


Container::Container(int ac , char **arg){
    
    try
    {
        
        int i = 1;
        Validator::verificationFileCsv(ac);
        Validator::verificationFileTxt(arg);
        Validator::isTxt(arg[1]);
        std::string line;
        std::ifstream fileTxt("data.csv", std::ios::binary);
        while(std::getline(fileTxt, line))
        {
            Validator::verifFormat(i, line);
            i++;
        }
        forIncludeMap();
        splitInfile(arg);
    }
    catch(std::exception &e){
        std::cerr << "Erreur: " << e.what() << std::endl;
    }
}

Container::Container(Container const& rhs)
{
    if(this != &rhs)
        dateNumber = rhs.dateNumber;
}
Container const& Container::operator=(Container const& obj)
{
    if(this != &obj)
        this->dateNumber = obj.dateNumber;
    return(*this);
}

void Container::printValue(float i, std::string line_value, std::string line_date)
{
    char *end;
    (void)i;
    float result = strtod(line_value.c_str(), &end);
    float d = result * i;
    std::cout << line_date << "=>" << line_value << " = " << d<<std::endl; 
}

void Container::printResult(std::string line_date, std::string line_value, std::map <std::string, float> dateNumber)
{
    (void)line_value;
    (void)line_date;
    (void)dateNumber;
    int years = atoi((split(line_date, '-' , 0)).c_str());
    int month = atoi((split(line_date, '-', 5)).c_str());
    int days = atoi((split (line_date, '-', 8)).c_str());
    
    
    for(std::map <std::string, float>::iterator it = dateNumber.begin(); it != dateNumber.end(); ++it)
    {
        int yearsData = atoi((split(it->first, '-' , 0)).c_str());
        int monthData = atoi((split(it->first, '-', 5)).c_str());
        int daysData= atoi((split (it->first, '-', 8)).c_str());
        if (years < 2009 || (years == 2009 && month < 02) || 
        (years == 2009 && month == 02 && days < 01)) {
            printValue(0, line_value, line_date);
            return;
        }        
        if(years == yearsData)
        {
            if(month == monthData)
            {
                if(days == daysData)
                {
                    printValue(it->second, line_value, line_date);
                    return;
                }
                
                if(days < daysData)
                {
                    --it;
                    printValue(it->second, line_value, line_date);
                    return;
                }
            }
        }
    }
}

void Container::forIncludeMap()
{
    std::string line;
    std::ifstream fileTxt("data.csv", std::ios::binary);
    int i = 1;       
    while(std::getline(fileTxt, line))
    {   
        includeMap(i, line);
        i++;
    }
}

void Container::splitInfile(char **arg)
{
    std::string line_date;
    std::string line_value;
    std::string line;
    std::ifstream fileTxt(arg[1], std::ios::binary);
    int i =0;
    if(fileTxt.is_open())
    {
        while(std::getline(fileTxt, line))
        {
            try
            {
                Validator::ValidatorFormDate(line, i);
                if(i !=0)
                {
                    line_date = split(line, 124 , 0);
                    line_value = split(line, 10, 12);
                    Validator::ValidatorDate(line_date);
                    Validator::ValidatorValue(line_value);
                    printResult( line_date,  line_value,this->dateNumber);
                }
            }
            catch(const std::exception &e)
            {
                std::cerr << "Erreur: " << e.what() << " for: " <<line << std::endl;
            }
            i++;
        }
    }
    fileTxt.close();
}
void Container::includeMap(int i, std::string line)
{
    if(i == 1)
        return;
    char *end;
    std::string save1= (split(line, ',', 0)).c_str();
    float save2 = strtod(split(line, '\0',11).c_str(), &end);
    this->dateNumber.insert(std::pair <std::string, float>(save1, save2));    
}      
