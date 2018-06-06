#include "utils.h"

void infoAluguer(pAluguer new, guitar *g, int *tam) {

	int pos, IDg, flag = false, dias;

	do {
		fflush(stdin);
		system("cls");
		printf(" |-----Criar Aluguer----|\n\n");

		for (pos = 0; pos < *tam; pos++)
			if (g[pos].estado == 0)
				mostraGuit(&g[pos]);

		printf("\n\nAlugar a guitarra com o ID: ");
		scanf("%d", &IDg);

		for (pos = 0; pos < *tam; pos++) {
			if (IDg == g[pos].id) {
				new->gui = &g[pos];
				flag = true;
			}
		}

		if (!flag)
			printf("Guitarra nao existe!\n");

	} while (!flag);

	printf("Data de Inicio[DD/MM/AAAA]: ");
	scanf("%d/%d/%d", &new->inicio.dia, &new->inicio.mes, &new->inicio.ano);

	do {
		printf("Data prevista de entrega[DD/MM/AAAA]: ");
		scanf("%d/%d/%d", &new->fimPrev.dia, &new->fimPrev.mes, &new->fimPrev.ano);

		if ((dias = calculaDif(&new->inicio, &new->fimPrev)) >= 8)
			printf("\n\n\t\tGuitarra so pode ser alugada ate um maximo de 7 dias.\n\n");

	} while (dias >= 8);

	int valorAPagar = calculaDif(&new->inicio, &new->fimPrev) * new->gui->pdia;
	printf("\n Valor previsto a pagar: %d euros.\n", valorAPagar);

	new->fim.dia = new->fim.mes = new->fim.ano = 0;
	new->gui->estado = 1;
	new->estado = 0;
	new->prox = NULL;

	_getch();

}

void novoAlug(pCliente p, guitar *g, int *tam, int *NIF) {

	pAluguer atual = NULL, new = NULL, aux = NULL;

	while (p != NULL && *NIF != p->NIF)
		p = (pCliente)p->prox;

	if (p) {
		atual = (pAluguer)p->alug;

		new = (pAluguer)malloc(sizeof(aluguer));

		if (!new)
			return;

		infoAluguer(new, g, tam);

		//new->prox = p->alug;
		p->alug = new;
		//p->prox->alug = NULL;
		p->nGuitarras++;
	}
}

void terminarAluguer(pCliente p, int *NIF) {

	pAluguer i = NULL;
	char dano;

	while (p != NULL) {
		if (p->NIF == *NIF)
			break;
		else
			p = p->prox;
	}

	i = p->alug;

	fflush(stdin);
	system("cls");
	printf(" |---Concluir Aluguer---|\n\n");

	if(i == NULL)
	{
		printf("Esse cliente nao tem alugueres por entregar.");
		_getch();
		return;
	}
	else
	{
		printf("Data de entrega [DD/MM/AAAA]: ");
		scanf("%d/%d/%d", &i->fim.dia, &i->fim.mes, &i->fim.ano);


		int atraso = calculaDif(&i->fimPrev, &i->fim);

		if (atraso > 0 && atraso <20) {
			printf("Atraso: %d dias, vai pagar uma multa de %d euros.", atraso, atraso * 10);
			i->gui->estado = 0;
			i->estado = 1;
		}
		else if (atraso >= 20) {
			printf("Atraso: %d dias, vai pagar uma multa de %d euros e vai ser banido por atraso na entrega.", atraso, atraso * 10);
			i->gui->estado = 0;
			i->estado = 1;
			p->banido = true;
		}

		printf("Guitarra danificada[S/N]: ");
		scanf("%c", &dano);

		if (dano == 'S' || dano == 's') {
			i->gui->estado = 2;
			i->estado = 2;
			p->banido = true;
			/*p->nGuitDan++;
			if (p->nGuitDan > 4 && p->banido != true) {
			printf("Foi banido por ja ter danificado mais de 3 guitarras.\n");

			}*/
		}
		else {
			i->gui->estado = 0;
			p->banido = false;
		}
	}

}
