#ifndef CLI_H
#define CLI_H

#include "utils.h"

typedef struct cliente cli, *pCli;
typedef struct aluguer alu, *pAlu;
typedef struct date DATA;

struct date{
    int dia, mes, ano;
};

struct cliente{
    int NIF;
    char nome[100];
    bool banido;
    pCli prox;
    pAlu list;
};

struct aluguer{
    guitar *gui;
    DATA inicio;
    DATA fimPrev;
    DATA fim;
    pAlu prox;

};



#endif