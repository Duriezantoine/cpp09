#pragma once
#include <iostream>
#include <stack>
#include <iostream>
#include <string>

class Container
{
    private:
        std::stack<int> algebra;
    public:
        Container(int ac, char **arg);
        ~Container();
        Container();
        Container const& operator=(Container const& rhs);
         Container(Container const& obj);
         void ImplementVector(char *arg);
};
#include "Container.tpp"
