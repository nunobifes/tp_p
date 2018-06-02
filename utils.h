#ifndef UTI_H
#define UTI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "guitar.h"
#include "client.h"


void infoGuitarra(guitar *new, int *TAM);
guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer);
void sair();
int ecra_principal();
void listarGuitarra(guitar *arr, int tam);
void listarGuitarraAlugada(guitar *arr, int tam);
guitar * leTXT(int *tam);

#endif
