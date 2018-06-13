/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cliente.h
 * Author: nunob
 *
 * Created on 7 de Junho de 2018, 0:57
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include "utils.h"

typedef struct cliente cliente, *pCliente;
typedef struct aluguer aluguer, *pAluguer;
typedef struct date data;

struct date {
    int dia, mes, ano;
};

struct cliente {
    int NIF;
    char nome[100];
    bool banido;
    int nGuitDan;
    int nGuitarras;
    int rBan;
    pCliente prox;
    pAluguer alug;
};

struct aluguer {
    guitar *gui;
    data inicio;
    data fimPrev;
    data fim;
    pAluguer prox;
    int estado;
    int valorAPagar;
};



#endif /* CLIENTE_H */

