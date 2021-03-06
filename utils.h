/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: Nuno Rocha 21240505s
 *
 * Created on 7 de Junho de 2018, 0:55
 */

#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include "guitarra.h"
#include "cliente.h"
#include <conio.h>




// Alugueres
void novoAlug(pCliente p, guitar *g, int *tam);
void terminarAluguer(pCliente p);
void alugueresAtivos(pCliente p);

// Guitarras
void infoGuitarra(guitar *new, int *TAM);
guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer);
void listarGuitarra(guitar *arr, int tam);
guitar * leTXT(int *tam);
void listarGuitarraAlugada(guitar *arr, pCliente p, int tam);
void GuitarraAluguer(guitar *member);
void historicoAlugGui(guitar *arr, pCliente p, int tam);

// Clientes
pCliente novoCli(pCliente p);
pCliente leClientes(guitar *g, int *tam);
pCliente leClientesBanidos(pCliente p);
void listaClientes(pCliente p);
void listaCliBan(pCliente p);
void listaEstadoCliente(pCliente p);
int obtemNIF(pCliente p);
int verNIF(pCliente pointer, pCliente new);
void infoCliente(pCliente new);
void libertaCli(pCliente p);
pCliente removeCli(pCliente p);

// Misc
int contaGuitarras(pCliente p, int estado);
void sair(guitar *arr, pCliente list, int tam);
int ecra_principal();
int obtemNIF(pCliente p);
void mostraGuit(guitar *m);
void guardaClientes(pCliente p);
void guarda_dados_txt(guitar *arr, int tam);
data dateSet(int y, int m, int d);
int datecmp(data d1, data *d2);
int isleap(int ano);
int data2dia(data *d);
int calculaDif(data *dataI, data *dataP);
void guardaBanidos(pCliente p);
void mostraclie(pCliente p);
int valorGuitarraCara(guitar *g, int *tam);
int contaGuitarrasBaratas(pCliente p, int valor);
void clearscr();


#endif /* UTILS_H */

