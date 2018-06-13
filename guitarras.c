/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.h"

void listarGuitarra(guitar *arr, int tam) {
    system("cls");
    //int o;
    printf(" |--------------Listar Guitarras--------------|\n\n");
    if (tam == 0)
        printf("\tNao ha guitarras registadas");
    else
        for (int i = 0; i < tam; i++) {
            printf("\tID: %d", arr[i].id);
            printf("\tEstado: %d", arr[i].estado);
            printf("\tValor: %d", arr[i].valor);
            printf("\tPreco por dia: %d", arr[i].pdia);
            printf("\tNome: %s", arr[i].nome);
            printf("\n");
        }
    
    
    getch();
    
}

void listarGuitarraAlugada(guitar *arr, int tam) {
    system("cls");
    int flag;
    printf(" |--------------Listar Guitarras Alugadas--------------|\n\n");
    for (int i = 0; i < tam; i++) {
        if (arr[i].estado != 1) {
            flag = 1;
        }
        else {
            flag = 0;
            break;
        }
    }
    
    if (flag == 1 || tam == 0)
        printf("\tNao ha guitarras alugadas");
    else {
        for (int i = 0; i < tam; i++) {
            if (arr[i].estado == 1) {
                printf("\tID: %d", arr[i].id);
                printf("\tEstado: %d", arr[i].estado);
                printf("\tValor: %d", arr[i].valor);
                printf("\tPreco por dia: %d", arr[i].pdia);
                printf("\tNome: %s", arr[i].nome);
                printf("\n");
            }
        }
    }
    
    
    getch();
    
}

void infoGuitarra(guitar *new, int *tam) {
    //clrscr();
    fflush(stdin);
    system("cls");
    
    printf(" |--------------Adicionar Guitarra------------|\n\n");
    if (*tam > 1)
        new[(*tam) - 1].id = new[(*tam) - 2].id + 1;
    else
        new[(*tam) - 1].id = 0;
    new[(*tam) - 1].estado = 0;
    fflush(stdout);
    printf("Nome: ");
    scanf(" %49[^\n]", &new[(*tam) - 1].nome);
    printf("Valor: ");
    scanf("%d", &new[(*tam) - 1].valor);
    printf("Preco: ");
    scanf("%d", &new[(*tam) - 1].pdia);
}

guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer) {
    guitar *new = arr;
    
    new = (guitar *)realloc(new, sizeof(guitar) * ((*TAM) + 1));
    
    if (!new) {
        return arr;
    }
    else if (vaiLer == 0) {
        (*TAM)++;
        infoGuitarra(new, TAM);
    }
    else {
        (*TAM)++;
        return new;
    }
    
    return new;
}

guitar * leTXT(int *tam) {
    FILE *f;
    guitar *aux = NULL;
    int id, est, val, pre, i;
    char nom[50];
    
    f = fopen("guitarras.txt", "rt");
    if (!f) {
        printf("Erro no acesso ao ficheiro\n");
        return aux;
    }
    
    while (true) {
        int ler = fscanf(f, "%d %d %d %d %[^\n]", &id, &est, &val, &pre, nom);
        
        if (ler == 5) {
            
            aux = novaGuitarra(aux, tam, 1);
            
            if (!aux)
                return NULL;
            
            i = (*tam) - 1;
            
            aux[i].id = id;
            aux[i].estado = est;
            aux[i].valor = val;
            aux[i].pdia = pre;
            strcpy(aux[i].nome, nom);
        }
        else if (ler == EOF) {
            break;
        }
    }
    
    fclose(f);
    return aux;
}

void GuitarraAluguer(guitar *member) {
    printf("\n\t\tNome: %s\tValor: %d euros\tPreco dia: %d euros", member->nome, member->valor, member->pdia);
    getch();
}