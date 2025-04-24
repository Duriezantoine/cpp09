#pragma once 

//A supprimer
void printab(std::pair <int*, int*>* tab, int nbr_container, std::list<int> out);

void step_one(char **arg, int iterateur,std::pair<int*, int*>&tab);
void tabInit(std::pair <int*, int*>* tab,int  nbr_container);
void init(char **arg, int ac, std::list<int>&finality);
void recursif_tab(int nbr_container, std::pair<int*, int*>* tab, std::list<int> &finality);
void insertTab(std::pair<int*, int*>*tab,std::pair<int*, int*> *new_tab, int nbr_container, std::list<int> &out);

;