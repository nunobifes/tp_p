/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   guitarras.c
 * Author: Nuno Rocha 21240505
 *
 * Created on 7 de Junho de 2018, 0:41
 */
#include "utils.h"

void historicoAlugGui(guitar *arr, pCliente p,int tam){
    pCliente aux = NULL;
    pAluguer auxa = NULL;
    int id;
    
    aux = p;
    clearscr();
    printf(" |---Historico de Alugueres de uma Guitarra---|\n\n");
    
    printf("\n\tGuitarras Disponivies: \n\n");
    if(tam < 1){
        printf("\t\tNao ha guitarras disponiveis.\n");
        getch();
        return;
    }
    for(int i = 0; i<tam; i++){
        printf("\t\tID: %d\tNome: %s\n", arr[i].id, arr[i].nome);
    }
    printf("\n\tID da guitarra a ver historico: ");
    scanf("%d", &id);
    
    while(aux != NULL){
        auxa = aux->alug;
        if(aux->banido == false && auxa != NULL){
            while(auxa != NULL){
                if(auxa->gui->id == id && auxa->estado != 0){
                    printf("\n\n\t\tNome: %s\tDataInicio: %d/%d/%d\tDataFim: %d/%d/%d\tDias de Atraso: %d\n", aux->nome, auxa->inicio.dia, auxa->inicio.mes, auxa->inicio.ano, auxa->fim.dia, auxa->fim.mes, auxa->fim.ano, calculaDif(&auxa->fim, &auxa->fimPrev));
                }
                auxa = auxa->prox;
                
            }
        }
        aux = aux->prox;
    }
    
    getch();
    
}   


void listarGuitarra(guitar *arr, int tam) {
    clearscr();
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

void listarGuitarraAlugada(guitar *arr, pCliente p, int tam) {
    
    pCliente aux = NULL;
    pAluguer auxa = NULL;
    int flag;
    aux = p;
    
    for (int i = 0; i < tam; i++) {
        if (arr[i].estado != 1) {
            flag = 1;
        }
        else {
            flag = 0;
            break;
        }
    }
    
    clearscr();
    printf(" |----------Listar Guitarras Alugadas---------|\n\n");
    
    printf("\tListagem de Guitarras Alugadas: \n\n");
    
    
    
    if (flag == 1 || tam == 0)
        printf("\t\tNao ha guitarras alugadas");
    else {
        
        if(aux != NULL){
            while(aux != NULL){
                auxa = aux->alug;
                if(aux->banido == false && auxa != NULL){
                    while(auxa != NULL){
                        if(auxa ->estado == 0)
                            printf("\t\tNome: %s\tID: %d\tPreco dia: %d\tValor: %d\tNome Cliente: %s\tNIF: %d\n", auxa->gui->nome, auxa->gui->id, auxa->gui->pdia, auxa->gui->valor, aux->nome, aux->NIF);
                        
                        auxa = auxa->prox;
                    }
                }
                aux = aux->prox;
            }
        }
        
    }
    
    
    getch();
    
}

void infoGuitarra(guitar *new, int *tam) {
    
    clearscr();
    int flag = false;
    
    printf(" |--------------Adicionar Guitarra------------|\n\n");
    if (*tam > 1)
        new[(*tam) - 1].id = new[(*tam) - 2].id + 1;
    else
        new[(*tam) - 1].id = 0;
    new[(*tam) - 1].estado = 0;
    fflush(stdout);
    printf("Nome: ");
    scanf(" %49[^\n]", &new[(*tam) - 1].nome);
    do{
        printf("Valor: ");
        if(scanf("%d", &new[(*tam) - 1].valor) == 1){
            flag = true;
        }
        else
            getchar();
    }while(!flag);
    flag = false;
    do{
        printf("Preco: ");
        if(scanf("%d", &new[(*tam) - 1].pdia) == 1){
            flag = true;
        }else
            getchar();
    }while(!flag);
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
    printf("\n\t\tID: %d\tNome: %s\t", member->id, member->nome);
}