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
	getchar();
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
					getchar();
					aux = aux->prox;
				}
			}

			p = (pCliente)p->prox;
		}

	}
	getchar();
}

void infoCliente(pCliente new) {
	fflush(stdin);
	system("cls");

	printf(" |--------Adicionar Cliente------|\n\n");

	printf("Nome: ");
	scanf("\n%[^\n]s", new->nome);
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
	getchar();
}

pCliente novoCli(pCliente p) {

	pCliente new = NULL, aux = NULL, atual = p;

	new = (pCliente)malloc(sizeof(cliente));

	if (!new)
		return p;

	infoCliente(new);

	if (verNIF(p, new) == 1) {
		printf("NIF: %d ja existe!\n", new->NIF);
		getchar();
		free(new);
		return p;
	}

	if (atual == NULL)
		atual = new;
	else {
		aux = atual;
		while (aux->prox != NULL)
			aux = (pCliente)aux->prox;
		aux->prox = new;
	}

	return atual;

}

pCliente leClientes(guitar *g, int *tam)
{

	FILE *cInfo;
	pCliente new = NULL, p = NULL, aux = NULL;
	pAluguer novo = NULL;
	int id, ret;
	

	
	cInfo = fopen("clientes.txt", "r");
	
	if (!cInfo)
	{
		return p;
	}

	fseek(cInfo, 0, SEEK_END);

	if(ftell(cInfo) != 0)
	{
		rewind(cInfo);

		while(true)
		{
			new = malloc(sizeof(cliente));
			if (!new)
				return NULL;

			ret = fscanf(cInfo, "%d %d %[a-z A-Z ^\n]s", &new->NIF, &new->nGuitarras, new->nome);

			if(ret == 3)
			{
				new->banido = false;
				new->prox = NULL;
				new->alug = NULL;

				if(new->nGuitarras > 0)
				{
					while(true)
					{
						novo = (pAluguer)malloc(sizeof(aluguer));

						if (!novo)
							return p;

						ret = fscanf(cInfo, "%d %d %d %d %d %d %d %d %d %d %d", &id, &novo->estado, &novo->inicio.dia, &novo->inicio.mes, &novo->inicio.ano,
							&novo->fimPrev.dia, &novo->fimPrev.mes, &novo->fimPrev.ano,
							&novo->fim.dia, &novo->fim.mes, &novo->fim.ano);

						if(ret == 11)
						{
							for(int i = 0; i < *tam; i++)
							{
								if (id == g[i].id)
									novo->gui = &g[i];
							}
							novo->prox = new->alug;
							new->alug = novo;
						}else
						{
							free(novo);
							break;
						}
					}
				}
				if (p == NULL)
					p = new;
				else
				{
					aux = p;
					while (aux->prox != NULL)
						aux = (pCliente)aux->prox;
					aux->prox = new;
				}
			}
			else if(ret == EOF)
			{
				free(new);
				break;
			}

		}

		
	}
	fclose(cInfo);
	return p;
}

pCliente leClientesBanidos(pCliente p)
{
	FILE *bInfo;
	pCliente new = NULL, aux = NULL, atual = p;
	int size, total;

	bInfo = fopen("banidos.dat", "rb");
	
	if (!bInfo)
		return p;

	fseek(bInfo, 0, SEEK_END);
	size = ftell(bInfo);

	if(size)
	{
		fseek(bInfo, -sizeof(int), SEEK_END); // volta para traz no ficheiro um int
		fread(&total, sizeof(int), 1, bInfo);

		for(int i = total - 1; i >= 0; i--)
		{
			fseek(bInfo, sizeof(cliente) * i, SEEK_END);

			new = (pCliente)malloc(sizeof(cliente));
			if(!new)
			{
				fclose(bInfo);
				return p;
			}
			fread(new, sizeof(cliente), 1, bInfo);
			new->prox = NULL;
			if (p == NULL)
				p = new;
			else
			{
				aux = p;
				while (aux->prox != NULL)
					aux = (pCliente)aux->prox;
				aux->prox = new;
			}
		}
	}
	fclose(bInfo);
	return p;
}


void libertaCli(pCliente p)
{
	pCliente temp = NULL;

	while(p != NULL)
	{
		temp = (pCliente)p->prox;
		free(p);
		p = temp;
	}
}