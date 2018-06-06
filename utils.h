#pragma once
#ifndef UTI_H
#define UTI_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "guitar.h"
#include "client.h"

// Alugueres
void novoAlug(pCliente p, guitar *g, int *tam, int *NIF);
void terminarAluguer(pCliente p, int *NIF);

// Guitarras
void infoGuitarra(guitar *new, int *TAM);
guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer);
void listarGuitarra(guitar *arr, int tam);
guitar * leTXT(int *tam);
void listarGuitarraAlugada(guitar *arr, int tam);
void GuitarraAluguer(guitar *member);

// Clientes
pCliente novoCli(pCliente p);
pCliente leClientes(guitar *g, int *tam);
void listaClientes(pCliente p);
void listaCliBan(pCliente p);
void listaEstadoCliente(pCliente p, int NIF);
int obtemNIF(pCliente p);
int verNIF(pCliente pointer, pCliente new);
void infoCliente(pCliente new);

// Misc
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

#endif