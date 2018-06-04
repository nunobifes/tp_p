#ifndef UTI_H
#define UTI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "guitar.h"
#include "client.h"

// Alugueres
void novoAlug(pCliente p, guitar *g, int *tam, int *NIF);

// Guitarras
void infoGuitarra(guitar *new, int *TAM);
guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer);
void listarGuitarra(guitar *arr, int tam);
guitar * leTXT(int *tam);
void listarGuitarraAlugada(guitar *arr, int tam);

// Clientes
pCliente novoCli(pCliente p);
void listaClientes(pCliente p);
void listaCliBan(pCliente p);
void listaEstadoCliente(pCliente p, int NIF);

// Misc
void sair(guitar *arr, pCliente list,int tam);
int ecra_principal();
int obtemNIF(pCliente p);



#endif
