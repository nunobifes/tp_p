#ifndef CLI_H
#define CLI_H

#include "utils.h"

typedef struct cliente cliente, *pCliente;
typedef struct aluguer aluguer, *pAluguer;
typedef struct date data;

struct date{
    int dia, mes, ano;
};

struct cliente{
    int NIF;
    char nome[100];
    bool banido;
    int nGuitarras;
    pCliente prox;
    pAluguer alug;
};

struct aluguer{
    guitar *gui;
    data inicio;
    data fimPrev;
    data fim;
    pAluguer prox;

};



#endif