/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   clientes.c
 * Author: Nuno Rocha 21240505
 *
 * Created on 7 de Junho de 2018, 0:41
 */

#include "utils.h"

pCliente removeCli(pCliente p){
    
    int flag, NIF;
    pCliente atua, ante = NULL, aux;
    pAluguer atuaAlug = NULL;
    
    aux = atua = p;
    
    
    clearscr();
    printf(" |--------Remover Cliente--------|\n\n");
    
    printf("Clientes Ativos: \n\n");
    
    
    while(aux != NULL){
        if(aux->banido == false)
            mostraclie(aux);
        aux = (pCliente)aux->prox;
    }
    printf("\n");
    NIF = obtemNIF(p);
    
    
    
    while(atua != NULL && atua->NIF != NIF){
        ante = atua;
        atua = (pCliente)atua->prox;
    }
    if(atua == NULL || atua->banido == true){
        printf("\nCliente banido ou nao existe.\n");
        return p;
    }
    if(ante == NULL)
        p = (pCliente)atua->prox;
    else
        ante->prox = atua->prox;
    
    while(atua->alug != NULL){
        atuaAlug = atua->alug->prox;
        atua->alug->gui->estado = 0;
        free(atua->alug);
        atua->alug = atuaAlug;
    }
    
    
    free(atua);
    return p;
    
}

void listaEstadoCliente(pCliente p) {
    
    clearscr();
    printf(" |------------Estado de um Cliente------------|\n\n");
    
    int flag = 0, NIF;
    
    pCliente aux = p;
    
    while(aux != NULL){
        if(aux->banido == false)
            mostraclie(aux);
        aux = (pCliente)aux->prox;
    }
    free(aux);
    printf("\n");
    NIF = obtemNIF(p);
    
    while (p != NULL) {
        if (p->NIF != NIF) {
            flag = 1;
        }
        else {
            break;
        }
        p = (pCliente)p->prox;
        
    }
    
    
    if (NIF == 0)
        printf("\tNao ha clientes registados!\n");
    else if (flag == 1) {
        printf("\tCliente nao encontrado!\n");
    }
    else {
        while (p) {
            if (p->NIF == NIF)
                printf("\tNome: %s\tNIF: %d\tNalugadas: %d\tNentregues: %d\tAtraso: %d\tNdanificadas: %d\n", p->nome, p->NIF, contaGuitarras(p, 0), contaGuitarras(p, 1), contaGuitarras(p,2), contaGuitarras(p,3));
            p = (pCliente)p->prox;
        }
    }
    getch();
}

void listaClientes(pCliente p) {
    pAluguer aux;
    pCliente clie = p;
    
    clearscr();
    printf(" |-----------Listar Clientes Ativos-----------|\n\n");
    if (clie == NULL)
        printf("\tNao ha clientes registados");
    else {
        while (clie != NULL) {
            if(clie->banido == false){
                
                printf("\n\tNome: %s\tNIF: %d\tBanido: %d\n", clie->nome, clie->NIF, clie->banido);
                
                aux = clie->alug;
                
                if (aux != NULL) {
                    while (aux != NULL) {
                        GuitarraAluguer(aux->gui);
                        if(aux->estado == 1 || aux->estado == 2)
                            printf("Data de Inicio: %d/%d/%d\tData de Entrega: %d/%d/%d\n", aux->inicio.dia,
                                    aux->inicio.mes, aux->inicio.ano,
                                    aux->fim.dia, aux->fim.mes,
                                    aux->fim.ano);
                        else
                            printf("Data de Inicio: %d/%d/%d\tData Prevista de Entrega: %d/%d/%d\n", aux->inicio.dia,
                                    aux->inicio.mes, aux->inicio.ano,
                                    aux->fimPrev.dia, aux->fimPrev.mes,
                                    aux->fimPrev.ano);
                        
                        
                        getch();
                        aux = aux->prox;
                    }
                }
            }
            clie = (pCliente)clie->prox;
        }
    }
    getch();
}

void infoCliente(pCliente new) {
    
    clearscr();
    
    printf(" |--------------Adicionar Cliente-------------|\n\n");
    
    printf("Nome: ");
    scanf("\n%[^\n]s", new->nome);
    printf("NIF: ");
    scanf("%9d", &new->NIF);
    new->banido = false;
    new->nGuitarras = 0;
    new->rBan = 0;
    new->alug = NULL;
    new->prox = NULL;
    
}

void listaCliBan(pCliente p) {
    
    clearscr();
    int flag;
    printf(" |-----------Listar Clientes Banidos----------|\n\n");
    while (p != NULL) {
        if (p->banido != 1) {
            flag = 1;
        }
        else {
            flag = 0;
            break;
        }
        p = (pCliente)p->prox;
        
    }
    
    if (flag == 1 || p == NULL)
        printf("\tNao ha Clientes banidos!\n");
    else {
        while (p) {
            if (p->banido == 1){
                printf("\tNome: %s\tNIF: %d\n", p->nome, p->NIF);
                switch(p->rBan){
                    case 1:
                        printf("\t\tRazao do ban: Atraso na entrega da guitarra.\n");
                        break;
                    case 2:
                        printf("\t\tRazao do ban: Danificou mais de 3 guitarras.\n");
                        break;
                    default:
                        break;
                }
            }
            p = p->prox;
        }
    }
    getch();
}

pCliente novoCli(pCliente p) {
    
    pCliente new = NULL, aux = NULL, atual = p;
    
    new = (pCliente)malloc(sizeof(cliente));
    
    if (!new)
        return p;
    
    infoCliente(new);
    
    if (verNIF(p, new) == 1) {
        printf("NIF: %d ja existe!\n", new->NIF);
        getch();
        free(new);
        return p;
    }
    
    if (atual == NULL)
        atual = new;
    else {
        aux = atual;
        while (aux->prox != NULL)
            aux = (pCliente)aux->prox;
        aux->prox = new;
    }
    
    return atual;
    
}

pCliente leClientes(guitar *g, int *tam)
{
    
    FILE *cInfo;
    pCliente new = NULL, pointer = NULL, aux = NULL;
    pAluguer novo = NULL;
    int returnedValue, a1;
    
    cInfo = fopen("clientes.txt", "r");
    
    if (!cInfo)
    {
        return NULL;
    }
    
    fseek(cInfo, 0, SEEK_END);
    
    if (ftell(cInfo) != 0)
    {
        rewind(cInfo);
        
        while (true)
        {
            new = malloc(sizeof(cliente));
            
            if (!new)
                return NULL;
            
            returnedValue = fscanf(cInfo, "%d %d %[a-z A-Z]s", &new->NIF, &new->nGuitarras, new->nome);
            
            if (returnedValue == 3)
            {
                new->banido = false;
                new->rBan = 0;
                new->prox = NULL; 
                new->alug = NULL;
                
                
                if (new->nGuitarras > 0)
                {
                    for(int i = 0; i < new->nGuitarras;  i++)
                    {
                        novo = (pAluguer)malloc(sizeof(aluguer));
                        
                        if (!novo)
                            return pointer;
                        
                        returnedValue = fscanf(cInfo, "%d %d %d %d %d %d %d %d %d %d %d %d", &a1, &novo->estado,
                                &novo->inicio.dia, &novo->inicio.mes, &novo->inicio.ano,
                                &novo->fimPrev.dia, &novo->fimPrev.mes, &novo->fimPrev.ano,
                                &novo->fim.dia, &novo->fim.mes, &novo->fim.ano, &novo->valorAPagar);
                        
                        if (returnedValue == 12)
                        {
                            for (int i = 0; i < *tam; i++)
                                if (a1 == g[i].id)
                                {
                                    novo->gui = &g[i];
                                }
                            
                            novo->prox = new->alug;
                            new->alug = novo;
                        }else if(returnedValue == EOF){
                            free(novo);
                        }
                        
                    }
                    
                }
                
                if (pointer == NULL)
                    pointer = new;
                else
                {
                    aux = pointer;
                    while (aux->prox != NULL)
                        aux = (pCliente)aux->prox;
                    aux->prox = new;
                }
            }
            else if (returnedValue == EOF)
            {
                free(new);
                break;
            }
        }
    }
    
    
    fclose(cInfo);
    return pointer;
}

pCliente leClientesBanidos(pCliente p)
{
    FILE *bInfo;
    pCliente new = NULL, aux = NULL, atual = p;
    int size, total;
    
    bInfo = fopen("banidos", "rb");
    
    if (!bInfo)
        return p;
    
    fseek(bInfo, 0, SEEK_END);
    size = ftell(bInfo);
    
    if(size)
    {
        fseek(bInfo, -sizeof(int), SEEK_END); // volta para traz no ficheiro um int
        fread(&total, sizeof(int), 1, bInfo);
        
        for(int i = total - 1; i >= 0; i--)
        {
            fseek(bInfo, sizeof(cliente) * i, SEEK_SET);
            
            new = (pCliente)malloc(sizeof(cliente));
            
            if(!new)
            {
                fclose(bInfo);
                return p;
            }
            
            fread(new, sizeof(cliente), 1, bInfo);
            new->prox = NULL;
            
            if (p == NULL)
                p = new;
            else
            {
                aux = p;
                while (aux->prox != NULL)
                    aux = (pCliente)aux->prox;
                aux->prox = new;
            }
        }
    }
    fclose(bInfo);
    return p;
}


void libertaCli(pCliente p)
{
    pCliente temp = NULL;
    
    while(p != NULL)
    {
        temp = (pCliente)p->prox;
        free(p);
        p = temp;
    }
}