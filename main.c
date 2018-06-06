#include "utils.h"

int main() {
	int tam = 0;
	guitar *gui = leTXT(&tam);
	pCliente list = leClientes(gui, &tam);
	list = leClientesBanidos(list);
	//pCliente list = NULL;
	int opcao, NIF;


	while (1) {
		opcao = ecra_principal();

		if (opcao == 1) {
			NIF = obtemNIF(list);
			novoAlug(list, gui, &tam, &NIF);
			opcao = 0;
		}
		else if (opcao == 2) {
			NIF = obtemNIF(list);
			terminarAluguer(list, &NIF);
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
			NIF = obtemNIF(list);
			listaEstadoCliente(list, NIF);
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
	return 0;

}