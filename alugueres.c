/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   alugueres.c
 * Author: Nuno Rocha 21240505
 *
 * Created on 7 de Junho de 2018, 0:41
 */
#include "utils.h"

void infoAluguer(pAluguer new, guitar *g, int *tam, pCliente p) {
    
    int pos, IDg, flag = false, dias;
    
    
    printf("\n\tGuitarras Disponiveis: \n");
    
    if(*tam<1){
        printf("\n\n\t\tNao existem guitarras para alugar.");
        return;
    }
    
    
    for (pos = 0; pos < *tam; pos++){
        if (g[pos].estado == 0){
            mostraGuit(&g[pos]);
        }
    }
    
    do {
        
        
        printf("\n\nAlugar a guitarra com o ID: ");
        scanf("%d", &IDg);
        
        
        
        for (pos = 0; pos < *tam; pos++) {
            if (IDg == g[pos].id) {
                if(g[pos].valor < valorGuitarraCara(g, tam) && contaGuitarrasBaratas(p, valorGuitarraCara(g, tam)) < 6){
                    new->gui = &g[pos];
                    flag = true;
                }else if(g[pos].valor < valorGuitarraCara(g, tam) && contaGuitarrasBaratas(p, valorGuitarraCara(g, tam)) >= 6){
                    new->gui = &g[pos];
                    flag = true;
                }else if(g[pos].valor > valorGuitarraCara(g, tam) && contaGuitarrasBaratas(p, valorGuitarraCara(g, tam)) >= 6){
                    new->gui = &g[pos];
                    flag = true;
                }
                
            }
        }
        
        if (!flag)
            printf("Nao pode alugar essa guitarra!\n");
        
    } while (!flag);
    flag = false;
    do{
        printf("Data de Inicio[DD/MM/AAAA]: ");
        if(scanf(" %d/%d/%d", &new->inicio.dia, &new->inicio.mes, &new->inicio.ano) == 3){
            flag = true;
        }
        else{
            printf("Por favor insira uma data coerente.\n");
            getchar();
        }
        
    }while(!flag);
    flag = false;
    do {
        do{
            printf("Data prevista de entrega[DD/MM/AAAA]: ");
            if(scanf("%d/%d/%d", &new->fimPrev.dia, &new->fimPrev.mes, &new->fimPrev.ano) == 3){
                flag = true;
            }else{
                printf("Por favor insira uma data coerente.\n");
                getchar();
            }
        }while(!flag);
        
        if ((dias = calculaDif(&new->fimPrev, &new->inicio)) >= 8)
            printf("\n\n\t\tGuitarra so pode ser alugada ate um maximo de 7 dias.\n\n");
        
    } while (dias >= 8);
    
    int valorAPagar = calculaDif(&new->fimPrev, &new->inicio) * new->gui->pdia;
    printf("\n Valor previsto a pagar: %d euros.\n", valorAPagar);
    
    new->fim.dia = new->fim.mes = new->fim.ano = 0;
    new->valorAPagar = valorAPagar;
    new->gui->estado = 1;
    new->estado = 0;
    new->prox = NULL;
    getch();
    
}

void novoAlug(pCliente p, guitar *g, int *tam) {
    
    pAluguer atual = NULL, new = NULL;
    pCliente aux = NULL;
    
    
    clearscr();
    printf(" |----------------Criar Aluguer---------------|\n\n");
    
    aux = p;
    
    if(aux == NULL){
        printf("\t\tNao ha clientes registados ou ativos.");
        getch();
    }
    printf("Clientes Ativos: \n\n");
    while(aux != NULL){
        if(aux->banido == false)
            mostraclie(aux);
        aux = (pCliente)aux->prox;
    }
    
    printf("\n");
    int NIF = obtemNIF(p);
    
    if(NIF == 0){
        return;
    }
    
    
    
    while (p != NULL && NIF != p->NIF)
        p = (pCliente)p->prox;
    
    if (p) {
        if(contaGuitarras(p, 0) == 5){
            printf("Nao e possivel alugar mais que cinco guitarras por cliente.");
            return;
        }
        atual = (pAluguer)p->alug;
        
        new = (pAluguer)malloc(sizeof(aluguer));
        
        if (!new)
            return;
        
        infoAluguer(new, g, tam, p);
        
        new->prox = p->alug;
        p->alug = new;
        p->nGuitarras++;
    }
    
}

void terminarAluguer(pCliente p) {
    
    pAluguer i = NULL, al = NULL;
    pCliente aux = NULL;
    int dano, NIF, id, flag = false;
    
    aux = p;
    
    
    clearscr();
    printf(" |---------------Concluir Aluguer-------------|\n\n");
    
    printf("Clientes Ativos: \n\n");
    while(aux != NULL){
        mostraclie(aux);
        aux = (pCliente)aux->prox;
    }
    
    printf("\n");
    NIF = obtemNIF(p);
    
    if(NIF == 0){
        return;
    }
    
    while (p != NULL) {
        if (p->NIF == NIF)
            break;
        else
            p = p->prox;
    }
    
    i = p->alug;
    
    if(i == NULL)
    {
        printf("Esse cliente nao tem alugueres por entregar.");
        getch();
        return;
    }
    else 
    {
        printf("\tGuitarras alugadas por %d: \n\n", NIF);
        while(i != NULL){
            if(i->estado == 0)
                printf("\t\tID: %d\tData de Inicio: %d/%d/%d\tData Prevista de Entrega: %d/%d/%d\n", i->gui->id, i->inicio.dia, i->inicio.mes, i->inicio.ano, i->fimPrev.dia, i->fimPrev.mes, i->fimPrev.ano);
            i = i->prox;
        }
        printf("\nQue guitarra pretende entregar: ");
        scanf("%d", &id);
        
        i = p->alug;
        
        while(i != NULL){
            if(i->gui->id == id && i->fimPrev.ano != 0){
                
                do{
                    printf("\nData de entrega [DD/MM/AAAA]: ");
                    if(scanf("%d/%d/%d", &i->fim.dia, &i->fim.mes, &i->fim.ano) == 3){
                        flag = true;
                    }else {
                        printf("Por favor insira uma data coerente.\n");
                        getchar();
                    }
                }while(!flag);
                
                
                
                
                int atraso = calculaDif(&i->fim, &i->fimPrev);
                
                if(atraso <= 0 ){
                    i->valorAPagar -= (atraso*i->gui->pdia)*(-1);
                    i->gui->estado = 0;
                    i->estado = 1;
                }else if (atraso > 0 && atraso <20) {
                    printf("Atraso: %d dias, vai pagar uma multa de %d euros.", atraso, atraso * 10);
                    i->gui->estado = 0;
                    i->valorAPagar += atraso*10;
                    i->estado = 2;
                }
                else if (atraso >= 20) {
                    printf("Atraso: %d dias, vai pagar uma multa de %d euros e vai ser banido por atraso na entrega.", atraso, atraso * 10);
                    i->gui->estado = 0;
                    i->estado = 2;
                    i->valorAPagar += atraso*10;
                    p->banido = true;
                    p->rBan = 1;
                    if(contaGuitarras(p, 0) > 0){
                        al = p->alug;
                        while(al != NULL){
                            al->gui->estado = 0;
                            al = al->prox;
                        }
                    }
                }
                
                printf("\n\nGuitarra danificada[1(sim)/0(nao)]: ");
                scanf(" %d", &dano);
                
                if (dano == 1) {
                    i->gui->estado = 2;
                    i->estado = 3;
                    i->valorAPagar += i->gui->valor;
                    if (contaGuitarras(p, 3) == 3 && p->banido != true) {
                        printf("Foi banido por ja ter danificado mais de 3 guitarras.\n");
                        p->banido = true;
                        p->rBan = 2;
                        if(contaGuitarras(p, 0) > 0){
                            al = p->alug;
                            while(al != NULL){
                                al->gui->estado = 0;
                                al = al->prox;
                            }
                        }
                    }
                }   
            }
            i = i->prox;
        }   
    }
    
    getch();
}

void alugueresAtivos(pCliente p){
    
    pCliente aux = NULL;
    pAluguer auxa = NULL;
    
    aux = p;
    
    
    clearscr();
    printf(" |----------------Produzir lista--------------|\n\n");
    
    printf("\n\tLista de Alugueres a Decorrer:\n\n");
    
    if(aux != NULL){
        while(aux != NULL && aux->banido == false){
            auxa = aux->alug;
            
            if(auxa != NULL){
                while(auxa != NULL && auxa->estado == 0){
                    
                    printf("\t\tNome: %s\tNome Guitarra: %s\tDataInicio: %d/%d/%d\tDataPrevista: %d/%d/%d\n", aux->nome, auxa->gui->nome, auxa->inicio.dia, auxa->inicio.mes, auxa->inicio.ano, auxa->fimPrev.dia, auxa->fimPrev.mes, auxa->fimPrev.ano);
                    
                    auxa = auxa->prox;
                }
            }
            
            aux = aux->prox;
        }
    }
    getch();
}