#include "utils.h"

//---------------------------------------------Misc--------------------------------------------------------
void mostraGuit(guitar *m){

    printf("\tID: %d", m->id);
    printf("\tEstado: %d", m->estado);
    printf("\tValor: %d", m->valor);
    printf("\tPreco por dia: %d", m->pdia);
    printf("\tNome: %s", m->nome);
    printf("\n");
    
    _getch();

}

void guarda_dados_txt(guitar *arr, int tam){
    int i;
    FILE *f;
    f = fopen("guitarras.txt", "w");
    if(f==NULL)
        return;
    for(i=0; i<tam; i++)
        fprintf(f, "%d %d %d %d %s\n", arr[i].id, arr[i].estado, arr[i].valor, arr[i].pdia, arr[i].nome);
    fclose(f);
}

int ecra_principal(){
    int input, temp, status;

        do{
            system("cls");
            printf("\n\t\tGuitarras p'Alugar\n\n");
            printf("\t |---Alugueres---|\n");
            printf("\t\t 1-|-----Criar Aluguer----|\n");
            printf("\t\t 2-|---Concluir Aluguer---|\n");
            printf("\t\t 3-|----Produzir lista----|\n");
            printf("\t |---Guitarras---|\n");
            printf("\t\t 4-|--------------Adicionar Guitarra------------|\n");
            printf("\t\t 5-|---Historico de Alugueres de uma Guitarra---|\n");
            printf("\t\t 6-|--------------Listar Guitarras--------------|\n");
            printf("\t\t 7-|-----------Listar Guitarras Alugadas--------|\n");
            printf("\t |----Clientes---|\n");
            printf("\t\t 08-|--------Adicionar Cliente------|\n");
            printf("\t\t 09-|------Estado de um Cliente-----|\n");
            printf("\t\t 10-|----Listar Clientes Ativos-----|\n");
            printf("\t\t 11-|----Listar Clientes Banidos----|\n");
            printf("\t 12-|------Sair-----|\n");
        
            printf("\n\n\n\n\nOpcao: ");
            status = scanf("%d", &input);
        }while(temp = getchar() != EOF && temp != '\n' && status < 1 || status > 12);
        
        return input;
}

data dateSet(int y, int m, int d){
    data set;
    set.dia=d;
    set.mes=m;
    set.ano=y;

    return set;
}

int datecmp(data d1, data *d2){
    if(d1.ano > d2->ano) return -1;
    if(d1.ano < d2->ano) return 1;
    if(d1.ano == d2->ano && d1.mes > d2->mes) return -1;
    if(d1.ano == d2->ano && d1.mes < d2->mes) return 1;
    if(d1.ano == d2->ano && d1.mes == d2->mes && d1.dia > d2->dia) return -1;
    if(d1.ano == d2->ano && d1.mes == d2->mes && d1.dia < d2->dia) return 1;


    return 0;
}

int isleap(int ano){
    if ( (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) return 1;

    return 0;
}

int data2dia(data *d){
    //Gregorian Calendar Date Converter to Julian dia Number if Date is after Nov 11th, 4713B.C. (reference: L. E. Doggett, Ch. 12, "Calendars", p. 604, in Seidelmann 1992)
    data nope = dateSet(-4713,11,23);

    if(datecmp(nope, d)!=1)
    {
        printf("Data invalida.\n");
        exit(0);
    }

    int jdn = (1461 * (d->ano + 4800 + (d->mes - 14) / 12)) / 4 + (367 * (d->mes - 2 - 12 * ((d->mes - 14)/12)))/12 - (3 * ((d->ano + 4900 + (d->mes - 14)/12)/100))/4 + d->dia - 32075;

    return jdn;
}

int calculaDif(data *dataI, data *dataP){
    
    int a = data2dia(dataI);
    int b = data2dia(dataP);

    return b-a;
}

void sair(guitar *arr, pCliente list,int tam){
    guarda_dados_txt(arr, tam);
    free(arr);
    free(list);
    exit(0);
}


//-----------------------------------------Alugueres-----------------------------------------------------

void infoAluguer(pAluguer new, guitar *g, int *tam){

    int pos, IDg, flag = false, dias;
    
    do{
        fflush(stdin);
        system("cls");
        printf(" |-----Criar Aluguer----|\n\n");

        for(pos = 0; pos < *tam; pos++)
            if(g[pos].estado == 0)
                mostraGuit(&g[pos]);
        
        printf("\n\nAlugar a guitarra com o ID: ");
        scanf("%d", &IDg);

        for(pos = 0; pos < *tam; pos++){
            if(IDg == g[pos].id){
                new->gui = &g[pos];
                flag = true;
            }
        }

        if(!flag)
            printf("Guitarra nao existe!\n");
        
    } while(!flag);

    printf("Data de Inicio[DD/MM/AAAA]: ");
    scanf("%d/%d/%d", &new->inicio.dia,&new->inicio.mes,&new->inicio.ano);
    
    do{
        printf("Data prevista de entrega[DD/MM/AAAA]: ");
        scanf("%d/%d/%d", &new->fimPrev.dia,&new->fimPrev.mes,&new->fimPrev.ano);
        
        if((dias = calculaDif(&new->inicio, &new->fimPrev)) >= 8)
            printf("\n\n\t\tGuitarra so pode ser alugada ate um maximo de 7 dias.\n\n");
    
    }while(dias >=8);
    
    int valorAPagar = calculaDif(&new->inicio, &new->fimPrev) * new->gui->pdia;
    printf("\n Valor previsto a pagar: %d euros.\n", valorAPagar);

    new->fim.dia = new->fim.mes = new->fim.ano = 0;
    new->gui->estado = 1;

    _getch();

} 

void novoAlug(pCliente p, guitar *g, int *tam, int *NIF){

    pAluguer atual = NULL, new = NULL, aux = NULL;

    while(p != NULL && *NIF != p->NIF)
        p = (pCliente)p->prox;
    
    if(p){
        atual = (pAluguer)p->alug;

        new =(pAluguer)malloc(sizeof(aluguer));

        if(!new)
            return;

        infoAluguer(new, g, tam);

        new->prox = p->alug;
        p->alug = new;
        p->nGuitarras++;
    }
}



//-----------------------------------------Clientes-------------------------------------------------------

int verNIF(pCliente pointer, pCliente new)
{
    pCliente aux = pointer;

    while (aux != NULL)
    {
        if (new->NIF == aux->NIF)
            return 1;
        aux = (pCliente)aux->prox;
    }

    return 0;
}

int obtemNIF(pCliente p){
    
    int NIF;
    if(p == NULL)
        return 0;
    else{
        printf("NIF do Cliente: ");
        scanf("%9d", &NIF);
        return NIF;
    }
    
}

void listaEstadoCliente(pCliente p, int NIF){
    fflush(stdin);
    system("cls");
    int flag;
    while(p != NULL){
        if(p->NIF != NIF){
            flag=1;
        }
        else{
            flag = 0;
            break;
        }
        p = (pCliente)p->prox;

    }    
        
    printf(" |------Estado de um Cliente-----|\n\n");
    if(NIF == 0)
        printf("\tNao ha clientes registados!\n");
    else if(flag == 1){
        printf("\tCliente nao encontrado!\n");
    }else {
        while(p){
            if(p->NIF == NIF)
                printf("\tNome: %s\tNIF: %d\tBanido: %d\n", p->nome, p->NIF, p->banido);
            p = (pCliente)p->prox;
        }
    }
    _getch();
}

void listaClientes(pCliente p){
    fflush(stdin);
    system("cls");
    printf(" |----Listar Clientes Ativos-----|\n\n");
    if(p == NULL)
        printf("\tNao ha clientes registados");
    else{
        while(p){
            printf("\tNome: %s\tNIF: %d\tBanido: %d\n", p->nome, p->NIF, p->banido);
            p = (pCliente)p->prox;
        }
    }
    
    _getch();

}

void infoCliente(pCliente new){
    fflush(stdin);
    system("cls");
    
    printf(" |--------Adicionar Cliente------|\n\n");
    
    printf("Nome: ");
    gets(new->nome);
    printf("NIF: ");
    scanf("%9d", &new->NIF);
    new->banido = 0;
    new->nGuitarras = 0;
    new->alug = NULL;
    new->prox = NULL;
    

}

void listaCliBan(pCliente p){
    fflush(stdin);
    system("cls");
    int flag;
    printf(" |----Listar Clientes Banidos----|\n\n");
    while(p != NULL){
        if(p->banido != 1){
            flag=1;
        }
        else{
            flag = 0;
            break;
        }
        p = (pCliente)p->prox;

    }

    if(flag == 1 || p == NULL)
        printf("\tNao ha Clientes banidos!\n");
    else{
        while(p){
            if(p->banido == 1)
                printf("\tNome: %s\tNIF: %d\n", p->nome, p->NIF);
        }
    }
    _getch();
}

pCliente novoCli(pCliente p){
    
    pCliente new = NULL, aux = NULL, atual = p;

    new = (pCliente)malloc(sizeof(cliente));
    
    if(!new)
        return p;
    
    infoCliente(new);
    
    if(verNIF(p, new) == 1){
        printf("NIF: %d ja existe!\n", new->NIF);
        _getch();
        free(new);
        return p;
    }

    if(atual == NULL)
        atual = new;
    else{
        aux = atual;
        while(aux->prox != NULL)
            aux = (pCliente)aux->prox;
        (pCliente)aux->prox = new;
    }

    return atual;

}



//-----------------------------------Guitarras------------------------------------------------------------
    
void listarGuitarra(guitar *arr, int tam){
    system("cls");
        //int o;
        printf(" |--------------Listar Guitarras--------------|\n\n");
        if(tam == 0)
            printf("\tNao ha guitarras registadas");
        else
            for(int i = 0; i < tam; i++){
                printf("\tID: %d", arr[i].id);
                printf("\tEstado: %d", arr[i].estado);
                printf("\tValor: %d", arr[i].valor);
                printf("\tPreco por dia: %d", arr[i].pdia);
                printf("\tNome: %s", arr[i].nome);
                printf("\n");
            }
        
        
    getch();

}

void listarGuitarraAlugada(guitar *arr, int tam){
    system("cls");
        int flag;
        printf(" |--------------Listar Guitarras Alugadas--------------|\n\n");
        for(int i = 0; i < tam; i++){
                if(arr[i].estado != 1){
                    flag=1;
                }
                else{
                    flag = 0;
                    break;
                }
        }

        if(flag == 1 || tam == 0)
            printf("\tNao ha guitarras alugadas");
        else{
            for(int i = 0; i < tam; i++){
                if(arr[i].estado == 1){
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

void infoGuitarra(guitar *new, int *tam){
    //clrscr();
    fflush(stdin);
    system("cls");
    
    printf(" |--------------Adicionar Guitarra------------|\n\n");
    if(*tam > 1)
        new[(*tam) - 1].id = new[(*tam) - 2].id + 1;
    else
        new[(*tam) - 1].id = 0;
    new[(*tam) -1].estado = 0;
    fflush(stdout);
    printf("Nome: ");
    scanf(" %49[^\n]", &new[(*tam) -1].nome);
    printf("Valor: ");
    scanf("%d", &new[(*tam) -1].valor);
    printf("Preco: ");
    scanf("%d", &new[(*tam) -1].pdia);
}

guitar * novaGuitarra(guitar *arr, int *TAM, int vaiLer){
    guitar *new = arr;

    new = (guitar *) realloc(new, sizeof(guitar) * ((*TAM)+1));
    
    if(!new){
        return arr;
    }else if(vaiLer == 0){
        (*TAM)++;
        infoGuitarra(new, TAM);
    }else{
        (*TAM)++;
        return new;
    }
    
    return new;
}

guitar * leTXT(int *tam){
    FILE *f;
    guitar *aux = NULL;
    int id, est, val, pre, i;
    char nom[50];

    f = fopen("guitarras.txt", "rt");
    if(!f){
        printf("Erro no acesso ao ficheiro\n");
        return aux;
    }
    
    while(true){
        int ler = fscanf(f, "%d %d %d %d %[^\n]", &id, &est, &val, &pre, nom);

        if(ler == 5){

            aux = novaGuitarra(aux, tam, 1);

            if(!aux)
                return NULL;
            
            i = (*tam) - 1;

            aux[i].id = id;
            aux[i].estado = est;
            aux[i].valor = val;
            aux[i].pdia = pre;
            strcpy(aux[i].nome, nom);
        }
        else if(ler == EOF){
            break;
        }
    }

    fclose(f);
    return aux;
}





