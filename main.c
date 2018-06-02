#include "utils.h"

int main(){
    guitar *arr = NULL;
    int tam = 0;
    int ids = 0;
    arr = leTXT(arr, &tam, &ids);
    int opcao;
    
    
    while(1){
        opcao = ecra_principal();
        
        if(opcao == 12){
            sair(arr, tam);
        }else if(opcao == 4){
            arr = novaGuitarra(arr, &tam, &ids);
            opcao = 0;
        }else if(opcao == 6){
            listarGuitarra(arr, tam);
            opcao = 0;
        }else{
            opcao=0;
        }
    }
    return 0;

}