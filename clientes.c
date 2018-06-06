#include "utils.h"

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

int obtemNIF(pCliente p) {

	int NIF;
	if (p == NULL)
		return 0;
	else {
		printf("NIF do Cliente: ");
		scanf("%9d", &NIF);
		return NIF;
	}

}

void listaEstadoCliente(pCliente p, int NIF) {
	fflush(stdin);
	system("cls");
	int flag;
	while (p != NULL) {
		if (p->NIF != NIF) {
			flag = 1;
		}
		else {
			flag = 0;
			break;
		}
		p = (pCliente)p->prox;

	}

	printf(" |------Estado de um Cliente-----|\n\n");
	if (NIF == 0)
		printf("\tNao ha clientes registados!\n");
	else if (flag == 1) {
		printf("\tCliente nao encontrado!\n");
	}
	else {
		while (p) {
			if (p->NIF == NIF)
				printf("\tNome: %s\tNIF: %d\tBanido: %d\n", p->nome, p->NIF, p->banido);
			p = (pCliente)p->prox;
		}
	}
	_getch();
}

void listaClientes(pCliente p) {
	pAluguer aux;
	fflush(stdin);
	system("cls");
	printf(" |----Listar Clientes Ativos-----|\n\n");
	if (p == NULL)
		printf("\tNao ha clientes registados");
	else {
		while (p) {
			printf("\nNome: %s\nNIF: %d\nBanido: %d\n", p->nome, p->NIF, p->banido);

			aux = p->alug;

			if (aux != NULL) {
				while (aux != NULL) {
					GuitarraAluguer(aux->gui);
					printf("Data de Inicio: %d/%d/%d\nData de Fim prevista: %d/%d/%d\n", aux->inicio.dia,
						aux->inicio.mes, aux->inicio.ano,
						aux->fimPrev.dia, aux->fimPrev.mes,
						aux->fimPrev.ano);
					_getch();
					aux = aux->prox;
				}
			}

			p = (pCliente)p->prox;
		}

	}
	_getch();
}

void infoCliente(pCliente new) {
	fflush(stdin);
	system("cls");

	printf(" |--------Adicionar Cliente------|\n\n");

	printf("Nome: ");
	scanf_s("\n%[^\n]s", new->nome, 50);
	//gets(new->nome);
	printf("NIF: ");
	scanf("%9d", &new->NIF);
	new->banido = false;
	new->nGuitarras = 0;
	//new->nGuitDan = 0;
	new->alug = NULL;
	new->prox = NULL;

}

void listaCliBan(pCliente p) {
	fflush(stdin);
	system("cls");
	int flag;
	printf(" |----Listar Clientes Banidos----|\n\n");
	while (p != NULL) {
		if (p->banido != 1) {
			flag = 1;
		}
		else {
			flag = 0;
			break;
		}
		p = (pCliente)p->prox;

	}

	if (flag == 1 || p == NULL)
		printf("\tNao ha Clientes banidos!\n");
	else {
		while (p) {
			if (p->banido == 1)
				printf("\tNome: %s\tNIF: %d\n", p->nome, p->NIF);
		}
	}
	_getch();
}

pCliente novoCli(pCliente p) {

	pCliente new = NULL, aux = NULL, atual = p;

	new = (pCliente)malloc(sizeof(cliente));

	if (!new)
		return p;

	infoCliente(new);

	if (verNIF(p, new) == 1) {
		printf("NIF: %d ja existe!\n", new->NIF);
		_getch();
		free(new);
		return p;
	}

	if (atual == NULL)
		atual = new;
	else {
		aux = atual;
		while (aux->prox != NULL)
			aux = (pCliente)aux->prox;
		(pCliente) aux->prox = new;
	}

	return atual;

}

pCliente leClientes(guitar *g, int *tam)
{

	FILE *cInfo, *bInfo;
	pCliente new = NULL, p = NULL, aux = NULL;
	pAluguer novo = NULL;
	int total, size;
	int nif, ng, id;
	char nom[50];

	bInfo = fopen("banidos.dat", "rb");
	cInfo = fopen("clientes.txt", "r");
	
	if (!bInfo && !cInfo)
	{
		return p;
	}

	while (true)
	{
		int ret = fscanf(cInfo, "%d %d %[a-z A-Z ^\n]s\n", &nif, &ng, nom);

		if (ret == 3)
		{
			new = (pCliente)malloc(sizeof(cliente));
			if (!new)
			{
				return p;
			}

			strcpy(new->nome, nom);
			new->NIF = nif;
			new->nGuitarras = ng;
			new->banido = false;
			if (new->nGuitarras > 0)
			{
				for (int i = 0; i < new->nGuitarras; i++)
				{
					novo = (pAluguer)malloc(sizeof(aluguer));
					if (!novo)
						return p;

					fscanf(cInfo, "%d %d %d %d %d %d %d %d %d %d %d\n", &id, &novo->estado, &novo->inicio.dia, &novo->inicio.mes, &novo->inicio.ano,
						&novo->fimPrev.dia, &novo->fimPrev.mes, &novo->fimPrev.ano,
						&novo->fim.dia, &novo->fim.mes, &novo->fim.ano);

					for (int i = 0; i < *tam; i++)
					{
						if (id == g[i].id)
						{
							novo->gui = &g[i];
						}
					}
					novo->prox = new->alug;
					new->alug = novo;
					new->prox = NULL;
				}
			}
			else
			{
				new->alug = NULL;
				new->prox = NULL;
			}
			if (p == NULL) {
				p = new;
			}
			else
			{
				aux = p;
				while (aux->prox != NULL)
					aux = (pCliente)aux->prox;
				(pCliente) aux->prox = new;
			}
			fscanf(cInfo, "\n");
		}
		else if (ret == EOF)
		{
			break;
		}
		else
		{
			printf("não encontrado");
		}
	}

	fclose(cInfo);

	fseek(bInfo, 0, SEEK_END);
	size = ftell(bInfo);

	if (size)
	{
		fseek(bInfo, sizeof(int), SEEK_END);
		fread(&total, sizeof(int), 1, bInfo);

		for (int i = total - 1; i >= 0; i--)
		{
			fseek(bInfo, sizeof(cliente) * i, SEEK_SET);

			new = (pCliente)malloc(sizeof(cliente));
			
			if (!new)
			{
				fclose(bInfo);
				return p;
			}

			fread(new, sizeof(cliente), 1, bInfo);
			new->prox = NULL;

			if (p == NULL)
			{
				p = new;
			}
			else
			{
				aux = p;
				while (aux->prox != NULL)
				{
					aux = (pCliente)aux->prox;
				}
				(pCliente) aux->prox = new;
			}
		}
	}
	fclose(bInfo);

	return p;

}