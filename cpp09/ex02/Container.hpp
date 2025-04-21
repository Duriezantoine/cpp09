#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <stdio.h>
class Container
{
    private:
        // std::vector<int> stackVector;
        // std::list <int> stackList;
        std::list<int> finality;
        std::list<int> out;
    public:
        ~Container();
        Container(int ac, char **arg);
        void includeTab(int ac, char **arg);
        // Container const& operator=(Container const& rhs);
        // Container(Container const& obj);

        //Methode demande par l'exercice
        // int *tab step_one(char **arg, int i);
        void    sort_pair(int **tab, int nbr_container);
        void recursif_tab(int nbr_container, int **tab, std::list<int> &finality, std::list<int> &out, int g);
};