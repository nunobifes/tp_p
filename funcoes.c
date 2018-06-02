#include "utils.h"


    
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

        if(flag == 1)
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
    system("cls");
    
    printf(" |--------------Adicionar Guitarra------------|\n\n");
    if(*tam > 1)
        new[(*tam) - 1].id = new[(*tam) - 2].id + 1;
    else
        new[(*tam) - 1].id = 0;
    new[(*tam) -1].estado = 1;
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


void guarda_dados_txt(guitar *arr, int tam)
{
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


void sair(guitar *arr, int tam){
    guarda_dados_txt(arr, tam);
    free(arr);
    exit(0);
}