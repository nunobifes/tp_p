#include "utils.h"

void infoGuitarra(guitar *new, int *TAM, int *ids){
    //clrscr();
    system("cls");
    
    printf(" |--------------Adicionar Guitarra------------|\n\n");
    new[(*TAM) -1].id = ++(*ids);
    printf("Nome: ");
    scanf(" %49[^\n]", &new[(*TAM) -1].nome);
    new[(*TAM) -1].estado = 0;
    printf("Valor: ");
    scanf("%d", &new[(*TAM) -1].valor);
    printf("Preco: ");
    scanf("%d", &new[(*TAM) -1].pdia);
}
    
void listarGuitarra(guitar *arr, int tam){
    system("cls");
        //int o;
        printf(" |--------------Listar Guitarras--------------|\n\n");
        if(tam == 0)
            printf("\tNao ha guitarras registadas");
        else
            for(int i = 0; i < tam; i++){
                printf("\tID: %d", arr[i].id);
                printf("\tNome: %s", arr[i].nome);
                printf("\tEstado: %d", arr[i].estado);
                printf("\tValor: %d", arr[i].valor);
                printf("\tPreco por dia: %d", arr[i].pdia);
                printf("\n");
            }
        
        
    getch();

}

guitar * novaGuitarra(guitar *arr, int *TAM, int *ids){
    guitar *new = arr;

    new = (guitar *) realloc(new, sizeof(guitar) * ((*TAM)+1));
    
    if(!new){
        return arr;
    }
    (*TAM)++;
    infoGuitarra(new, TAM, ids);

    return new;
}

guitar * leTXT(guitar *arr, int *tam, int *ids){
    FILE *f;
    
    f = fopen("guitarras.txt", "r");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return arr;
    }
    guitar *new = arr;
    fseek(f, 0, SEEK_END); // seek to end of file
    size_t size = ftell(f); // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    // proceed with allocating memory and reading the file
    int ch=0;
    int lines=0;
    lines++;
    while(!feof(f))
    {
        ch = fgetc(f);
        if(ch == '\n')
            lines++;
    }


    if(size > 0){

       for((*tam) = 0; (*tam) < lines; (*tam)++){
            new = (guitar *) realloc(new, sizeof(guitar) * ((*tam)+1));
    
        
            if(!new){
                return arr;
            }
            
            fscanf(f, "%d %[^ ] %d %d %d", &new[(*tam)].id+1, new[(*tam)].nome, &new[(*tam)].estado, &new[(*tam)].valor, &new[(*tam)].pdia);
        }
        (*ids)=new[(*tam)].id+1;
    }
    else{ 
        fclose(f);
        return arr;
    }
    fclose(f);
    return new;
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
            printf("\t\t 7-|-----------listar guitarras alugadas--------|\n");
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

void escreve_info_txt(guitar a, FILE *f, int i, int tam)
{
    if(i+1 == tam)
        fprintf(f, "%d %s %d %d %d", a.id, a.nome, a.estado, a.valor, a.pdia);
    else
        fprintf(f, "%d %s %d %d %d\n", a.id, a.nome, a.estado, a.valor, a.pdia);    
}

void guarda_dados_txt(guitar *arr, int tam)
{
    int i;
    FILE *f;
    f = fopen("guitarras.txt", "w");
    if(f==NULL)
        return;
    for(i=0; i<tam; i++)
        escreve_info_txt(arr[i], f, i, tam);
    fclose(f);
}




void sair(guitar *arr, int tam){
    guarda_dados_txt(arr, tam);
    free(arr);
    exit(0);
}