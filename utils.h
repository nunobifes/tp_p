#ifndef UTI_H
#define UTI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "guitar.h"
#include "client.h"


void infoGuitarra(guitar *new, int *TAM, int *ids);
guitar * novaGuitarra(guitar *arr, int *TAM, int *ids);
void sair();
int ecra_principal();
void listarGuitarra(guitar *arr, int tam);
guitar * leTXT(guitar *arr, int *tam, int *ids);

#endif
