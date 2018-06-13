/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nunob
 *
 * Created on 7 de Junho de 2018, 0:41
 */

#include "utils.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    int tam = 0;
    guitar *gui = leTXT(&tam);
    pCliente list = leClientes(gui, &tam);
    list = leClientesBanidos(list);
    
    int opcao;
    
    
    while (1) {
        opcao = ecra_principal();
        
        if (opcao == 1) {
            
            novoAlug(list, gui, &tam);
            opcao = 0;
        }
        else if (opcao == 2) {
            terminarAluguer(list);
            opcao = 0;
        }
        else if (opcao == 3) {
            opcao = 0;
        }
        else if (opcao == 4) {
            gui = novaGuitarra(gui, &tam, 0);
            opcao = 0;
        }
        else if (opcao == 6) {
            listarGuitarra(gui, tam);
            opcao = 0;
        }
        else if (opcao == 7) {
            listarGuitarraAlugada(gui, tam);
            opcao = 0;
        }
        else if (opcao == 8) {
            list = novoCli(list);
            opcao = 0;
        }
        else if (opcao == 9) {
            
            listaEstadoCliente(list);
            opcao = 0;
        }
        else if (opcao == 10) {
            listaClientes(list);
            opcao = 0;
        }
        else if (opcao == 11) {
            listaCliBan(list);
            opcao = 0;
        }
        else if (opcao == 12) {
            sair(gui, list, tam);
        }
        else {
            opcao = 0;
        }
    }
    
    return (EXIT_SUCCESS);
}

