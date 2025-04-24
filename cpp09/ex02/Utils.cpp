#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

/*
    Autiliser
    std::ptrdiff_t p = -10;
    int i = static_cast<int>(p); 
*/
void sort_pair(std::pair<int *, int *> *tab, int nbr_container)
{
    int save_one;
    for (int i = 0; i != nbr_container; ++i)
    {
        if (tab[i].second == NULL)
            break;
        printf("\n1first|%d|second|%d|", *tab[i].first, *tab[i].second);
        if (*tab[i].first < *tab[i].second)
        {
            save_one = *tab[i].first;
            *tab[i].first = *tab[i].second;
            *tab[i].second = save_one;
        }
    }
}

// A supprimer par la suite
void printab(std::pair<int *, int *> *tab, int nbr_container, const std::list<int> &out)
{
    // (void)out;
    printf("nbr_container | %d |\n", nbr_container);
    for (int i = 0; i < nbr_container; ++i)
    {
        if (tab[i].second == NULL)
        {
            printf("Just one number solo | %d |\n", *tab[i].first);
        }
        else
            printf("first | %d | second | %d | i | %d |\n", *tab[i].first, *tab[i].second, i);
        // printf(" second | %d | i | %d |\n",  *tab[i].second, i);
    }

    // // Affichage de la liste out
    printf("out list : ");
    for (std::list<int>::const_iterator it = out.begin(); it != out.end(); ++it)
        printf("| %d | ", *it);
    printf("\n");
}

void step_one(char **arg, int iterateur, std::pair<int *, int *> &tab)
{
    int *b;
    int *a = new int(atoi(arg[iterateur++]));
    if (arg[iterateur] != 0)
        b = new int(atoi(arg[iterateur++]));
    else
        b = NULL;
    tab = std::make_pair(a, b);
}

void tabInit(std::pair<int *, int *> *tab, int nbr_container)
{
    int i;
    for (i = 0; i != nbr_container; i++)
        tab[i] = std::pair<int *, int *>(NULL, NULL);
}

void insertTab(std::pair<int *, int *> *tab, std::pair<int *, int *> *new_tab, int nbr_container, std::list<int> &out)
{
    int i;
    int j;
    (void)j;
    int index_newTab = 0;
    for (i = 0; i < nbr_container; ++i)
    {
        int *b = tab[i].first;
        int *j = tab[i].second;
        if (i % 2 == 0)
        {
            new_tab[index_newTab].first = b;
            if (j == NULL)
                break;
        }
        else
        {
            new_tab[index_newTab].second = b;
            index_newTab++;
            if (j == NULL)
                break;
        }
        if (j != NULL)
        {
            out.push_back(*j);
        }
    }
    return;
}

void printList(const std::list<int> &lst)
{
    std::cout << "Contenu de la liste : ";
    std::list<int>::const_iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void insertFinality(std::pair<int *, int *> *tab, std::list<int> &finality)
{
    int *b = tab[0].first;
    int *a = tab[0].second;

    finality.push_back(*a);
    finality.push_back(*b);
}

// Fonction pour calculer le nᵉ terme de la suite de Jacobsthal
int jacobsthal(int n)
{
    if (n == 0 || n == 1)
        return 2;
    return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void changePair(std::pair<int *, int *> *new_tab, int one, int two)
{
    // Simple échange des paires complètes
    std::pair<int *, int *> temp = new_tab[one];
    new_tab[one] = new_tab[two];
    new_tab[two] = temp;
}
// Pour inverser de l'indice start à l'indice end (exclusif)
void reverseRange(std::pair<int *, int *> *new_tab, int start, int end)
{
    if (end < start || end == start)
        return;

    // printf("\nInversion de la plage : start = |%d| à end = |%d|\n", start, end);
    std::reverse(new_tab + start, new_tab + end + 1);

    printf("\n");
}

void jacobIndexUtils(std::pair<int *, int *> *new_tab, int nbr_container, std::list<int> &finality)
{
    printf("\nBig SmillCONTAINER = |%d| \n", nbr_container);
    printab(new_tab, nbr_container, finality);
    int i = 0;
    int index_jacob = 0;
    int j = 0;
    int save = 0;
    while (jacobsthal(j))
    {
        int result1;
        int result2;
        int index_container = nbr_container;
        i = jacobsthal(j) - 1;
        if (i + save >= nbr_container)
            i = nbr_container - save - 1;
        // printf("\nSave= |%d|, jacobIndex[j](i)=|%d|, index-container=|%d| i=|%d|", save, i, index_container, i);
        result1 = save + index_jacob;
        result2 = save + i;
        // printf("\nResult|1=|%d|I|%d|index-container|%d|", result1, result2, index_container);
        if (result2 >= nbr_container)
            break;
        reverseRange(new_tab, result1, result2);
        if (save >= index_container)
            break;
        save =jacobsthal(j) + save;
        j++;
    }
    printab(new_tab, nbr_container, finality);
}

void searchpair(std::list<int> &finality, std::pair<int *, int *> *new_tab, int nbr_container, int nbr)
{
    int i = 0;
    printf("\nBig SmillCONTAINER = |%d| \n", nbr_container);
    jacobIndexUtils(new_tab, nbr_container, finality);

    if (nbr_container == 1)
        return;

    for (i = 0; i != nbr_container; i++)
    {
        int *b;
        int ok = 0;
        std::list<int>::iterator it;
        int *j = new_tab[i].first;
        if (new_tab[i].second != NULL)
        {
            b = new_tab[i].second;
            it = std::find(finality.begin(), finality.end(), *j);
        }
        else
        {
            it = std::find(finality.begin(), finality.end(), *j);
            if (it != finality.end())
                printf("\nVoici le nbr non mis|%d|\n", *j);
            continue; // J'hesite a mettre un break
        }
        
        while (it != finality.begin())
        {
            if (new_tab[i].second == NULL)
            {
                if (*j > *it)
                {
                    ++it;

                    finality.insert(it, *j);
                    printf("\nVoici le nbr Normal bizare|%d|\n", *j);
                    ok++;
                    break;
                }
            }
            else
            {
                if (*b > *it)
                {
                    ++it;
                    finality.insert(it, *b);
                    ok++;
                    break;
                }
            }
            --it;
        }
        if (it == finality.begin() && ok == 0)
        {
            if (*it < *b)
                ++it;
            finality.insert(it, *b);
        }
        printf("\nVoici le nbrsecond normal|%d|\n", *b);
    }
}

void deepCopyTab(const std::pair<int *, int *> src[], std::pair<int *, int *> dest[], int nbr_container)
{
    for (int i = 0; i < nbr_container; i++)
    {
        if (src[i].first != NULL)
        {
            dest[i].first = new int(*src[i].first);
        }
        else
        {
            dest[i].first = NULL;
        }

        if (src[i].second != NULL)
        {
            dest[i].second = new int(*src[i].second);
        }
        else
        {
            dest[i].second = NULL;
        }
    }
}

void freetab(std::pair<int *, int *> *tab, int nbr_container)
{
    for (int i = 0; i < nbr_container; i++)
    {
        delete tab[i].first;
        if (tab[i].second != NULL)
            delete tab[i].second;
    }
}
void recursif_tab(int nbr_container, std::pair<int *, int *> *tab, std::list<int> &finality, int nbr)
{
    int new_nbr_container;
    std::list<int> out;

    new_nbr_container = (nbr_container / 2);
    if (nbr_container % 2 != 0)
        new_nbr_container++;

    std::pair<int *, int *> new_tab[new_nbr_container];
    tabInit(new_tab, new_nbr_container);
    insertTab(tab, new_tab, nbr_container, out);

    if (new_nbr_container == 1)
    {
        sort_pair(new_tab, new_nbr_container);
        insertFinality(new_tab, finality);
    }
    else
    {
        sort_pair(new_tab, new_nbr_container);
        std::pair<int *, int *> recursive_tab[new_nbr_container];
        deepCopyTab(new_tab, recursive_tab, new_nbr_container);
        recursif_tab(new_nbr_container, recursive_tab, finality, nbr);
        freetab(recursive_tab, new_nbr_container);
    }
    searchpair(finality, tab, nbr_container, nbr);
}

void init(char **arg, int ac, std::list<int> &finality)
{
    int i = 0;
    int j = 0;
    int iterator;
    int nbr_container;
    int save;

    iterator = 1;
    nbr_container = ((ac - 1) / 2);
    if ((ac - 1) % 2 != 0)
        nbr_container++;
    std::pair<int *, int *> tab[nbr_container];
    tabInit(tab, nbr_container);
    for (i = 0; i != nbr_container; i++)
    {
        step_one(arg, iterator, tab[i]);
        j++;
        iterator = iterator + 2;
    }
    // Mise en place du tri
    sort_pair(tab, nbr_container);
    // Save with free
    save = nbr_container;
    recursif_tab(nbr_container, tab, finality,  save);
    printList(finality);
    freetab(tab, save);
}