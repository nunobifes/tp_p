#include "utils.h"

void mostraGuit(guitar *m) {

	printf("\tID: %d", m->id);
	printf("\tEstado: %d", m->estado);
	printf("\tValor: %d", m->valor);
	printf("\tPreco por dia: %d", m->pdia);
	printf("\tNome: %s", m->nome);
	printf("\n");

	_getch();

}

void guardaClientes(pCliente p)
{
	FILE *cInfo, *bInfo;
	pAluguer i = NULL;
	int total = 0;

	cInfo = fopen("clientes.txt", "wt");
	if (!cInfo)
		return;
	bInfo = fopen("banidos.dat", "wb");
	if (!bInfo)
		return;

	while(p != NULL)
	{
		if(p->banido == true)
		{
			fwrite(p, sizeof(cliente), 1, bInfo);
			p = (pCliente)p->prox;
			total++;
		}
		else
		{
			fprintf(cInfo, "%d %d %s\n", (int)p->NIF, (int)p->nGuitarras, p->nome);

			i = p->alug;

			
			while (i != NULL){
				fprintf(cInfo, "%d %d %d %d %d %d %d %d %d %d %d\n", (int)(i)->gui->id, (int)(i)->estado, (int)(i)->inicio.dia, (int)(i)->inicio.mes, (int)(i)->inicio.ano, (int)(i)->fimPrev.dia, (int)(i)->fimPrev.mes, (int)(i)->fimPrev.ano, (int)(i)->fim.dia, (int)(i)->fim.mes, (int)(i)->fim.ano);
				i = (i)->prox;
			} 
			p = (pCliente)p->prox;
		}
	}
	fwrite(&total, sizeof(int), 1, bInfo);

	fclose(cInfo);
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

	return b - a;
}

void sair(guitar *arr, pCliente list, int tam) {
	guarda_dados_txt(arr, tam);
	guardaClientes(list);
	free(arr);
	free(list);
	exit(0);
}



