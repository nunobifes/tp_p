/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.h"

void mostraGuit(guitar *m) {
    
    printf("\t\tID: %d", m->id);
    printf("\tEstado: %d", m->estado);
    printf("\tValor: %d", m->valor);
    printf("\tPreco por dia: %d", m->pdia);
    printf("\tNome: %s\n", m->nome);
    
    getch();
    
}

void mostraclie(pCliente p) {
    
    printf("\t\tNIF: %d", p->NIF);
    printf("\tNome: %s", p->nome);
    printf("\tGuitarras alugadas: %d", p->nGuitarras);
    printf("\tGuitarras danificadas: %d\n", p->nGuitDan);
    
    getch();
    
}

void guardaClientes(pCliente p)
{
   FILE *cInfo;
    pAluguer ite = NULL;

    cInfo = fopen("clientes.txt", "wt");
    if (!cInfo)
        return;

    while (p != NULL)
    {
        if (!p->banido)
        {
        
             fprintf(cInfo, "%d %d %d %s\n", (int)p->NIF, (int)p->nGuitarras, (int)p->nGuitDan, p->nome);
            
            ite = p->alug;
           
           
            while (ite != NULL)
            {
                fprintf(cInfo, "%d %d %d %d %d %d %d %d %d %d %d %d\n", (int)(ite)->gui->id, (int)(ite)->estado, (int)(ite)->inicio.dia, (int)(ite)->inicio.mes, (int)(ite)->inicio.ano, (int)(ite)->fimPrev.dia, (int)(ite)->fimPrev.mes, (int)(ite)->fimPrev.ano, (int)(ite)->fim.dia, (int)(ite)->fim.mes, (int)(ite)->fim.ano, (int)(ite)->valorAPagar);
                ite = (ite)->prox;
            }
        }
        p = (pCliente)p->prox;
    }
    fclose(cInfo);
}

void guardaBanidos(pCliente p)
{
    FILE *bInfo;
    int total = 0;
    
    bInfo = fopen("banidos", "wb");
    
    if (!bInfo)
        return;
    
    while(p != NULL)
    {
        if(p->banido)
        {
            fwrite(p, sizeof(cliente), 1, bInfo);
            total++;
        }
        p = (pCliente)p->prox;
    }
    fwrite(&total, sizeof(int), 1, bInfo);
    fclose(bInfo);
}

void guarda_dados_txt(guitar *arr, int tam) {
    int i;
    FILE *f;
    f = fopen("guitarras.txt", "w");
    if (f == NULL)
        return;
    for (i = 0; i<tam; i++)
        fprintf(f, "%d %d %d %d %s\n", arr[i].id, arr[i].estado, arr[i].valor, arr[i].pdia, arr[i].nome);
    fclose(f);
}

int ecra_principal() {
    int input, temp, status;
    
    do {
        system("cls");
        printf("\n\t\tGuitarras p'Alugar\n\n");
        printf("\t |---Alugueres---|\n");
        printf("\t\t 1-|-----Criar Aluguer----|\n");
        printf("\t\t 2-|---Concluir Aluguer---|\n");
        printf("\t\t 3-|----Produzir lista----|\n");
        printf("\t |---Guitarras---|\n");
        printf("\t\t 4-|-------------Adicionar Guitarra-------------|\n");
        printf("\t\t 5-|---Historico de Alugueres de uma Guitarra---|\n");
        printf("\t\t 6-|--------------Listar Guitarras--------------|\n");
        printf("\t\t 7-|----------Listar Guitarras Alugadas---------|\n");
        printf("\t |----Clientes---|\n");
        printf("\t\t 08-|-------Adicionar Cliente-------|\n");
        printf("\t\t 09-|--------Remover Cliente--------|\n");
        printf("\t\t 10-|------Estado de um Cliente-----|\n");
        printf("\t\t 11-|----Listar Clientes Ativos-----|\n");
        printf("\t\t 12-|----Listar Clientes Banidos----|\n");
        printf("\t 13-|------Sair-----|\n");
        
        printf("\n\n\n\n\nOpcao: ");
        status = scanf("%d", &input);
    } while (temp = getchar() != EOF && temp != '\n' && status < 1 || status > 12);
    
    return input;
}

data dateSet(int y, int m, int d) {
    data set;
    set.dia = d;
    set.mes = m;
    set.ano = y;
    
    return set;
}

int datecmp(data d1, data *d2) {
    if (d1.ano > d2->ano) return -1;
    if (d1.ano < d2->ano) return 1;
    if (d1.ano == d2->ano && d1.mes > d2->mes) return -1;
    if (d1.ano == d2->ano && d1.mes < d2->mes) return 1;
    if (d1.ano == d2->ano && d1.mes == d2->mes && d1.dia > d2->dia) return -1;
    if (d1.ano == d2->ano && d1.mes == d2->mes && d1.dia < d2->dia) return 1;
    
    
    return 0;
}

int isleap(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) return 1;
    
    return 0;
}

int data2dia(data *d) {
    //Gregorian Calendar Date Converter to Julian dia Number if Date is after Nov 11th, 4713B.C. (reference: L. E. Doggett, Ch. 12, "Calendars", p. 604, in Seidelmann 1992)
    data nope = dateSet(-4713, 11, 23);
    
    if (datecmp(nope, d) != 1)
    {
        printf("Data invalida.\n");
        exit(0);
    }
    
    int jdn = (1461 * (d->ano + 4800 + (d->mes - 14) / 12)) / 4 + (367 * (d->mes - 2 - 12 * ((d->mes - 14) / 12))) / 12 - (3 * ((d->ano + 4900 + (d->mes - 14) / 12) / 100)) / 4 + d->dia - 32075;
    
    return jdn;
}

int calculaDif(data *dataI, data *dataP) {
    
    int a = data2dia(dataI);
    int b = data2dia(dataP);
    
    return a - b;
}

void sair(guitar *arr, pCliente list, int tam) {
    guarda_dados_txt(arr, tam);
    guardaClientes(list);
    guardaBanidos(list);
    free(arr);
    libertaCli(list);
    exit(0);
}



