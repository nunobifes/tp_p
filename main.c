#include "utils.h"

int main(){
    int tam = 0;
    guitar *arr = leTXT(&tam);
    int opcao;
    
    
    while(1){
        opcao = ecra_principal();
        
        if(opcao == 12){
            sair(arr, tam);
        }else if(opcao == 4){
            arr = novaGuitarra(arr, &tam, 0);
            opcao = 0;
        }else if(opcao == 6){
            listarGuitarra(arr, tam);
            opcao = 0;
        }else if(opcao == 7){
            listarGuitarraAlugada(arr, tam);
            opcao = 0;
        }else{
            opcao=0;
        }
    }
    return 0;

}