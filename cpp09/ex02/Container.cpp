#include "Container.hpp"
#include "Validator.hpp"
#include "Utils.hpp"

int ft_searchContainer( int nbr)
{
    int b = 00;
    b = nbr / 2;
    if(nbr % 2 != 0)
        nbr++;
    return(b);
}

Container::~Container()
{
    std::cout << "Destructor de Container" << std::endl;
}
Container::Container(int ac, char **arg)
{
    try
    {
        Validator::validArg(ac, arg);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    init(arg, ac, this->finality);
}   

// Container const& Container::operator=(Container const& obj)
// {
    //     if(this!= &obj)
    //     {
//         this->stackList = obj.stackList;
//         this->stackVector = obj.stackVector;
//     }
//     return(*this);
// }

// Container::Container(Container const& rhs)
// {
//     if(*this != rhs)
//     {
//         this->stackList = rhs.stackList;
//         this->stackVector = rhs.stackVector;
//     }
// }