#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//PROIECTUL NR 5

typedef struct oferte 
{
	char *produs ;
	int pret,cantitate;
	struct oferte *urm;
}sublista_oferte;

typedef struct magazin 
{
	char *magazin;
	struct magazin *urm;
	sublista_oferte *prim;
}lista_magazin;

lista_magazin *rad = NULL;

//FUNCTIA DE ADAUGARE INTR-O SUBLISTA
sublista_oferte *adauga_sublista(sublista_oferte* lista, sublista_oferte *aux)
{
	sublista_oferte *q1, *q2;
	for (q1 = q2 = lista; q1 != NULL && q1->pret > aux->pret; q2 = q1, q1 = q1->urm);
if (q1 == q2)
	{
		aux->urm = lista;
		lista = aux;
	}
	else
	{
		q2->urm = aux;
		aux->urm = q1;
	}
	return lista;
}

//FUNCTIA DE ADAUGARE INTR-O LISTA
lista_magazin *adauga(lista_magazin* lista, lista_magazin*aux, sublista_oferte *aux_s)
{
	lista_magazin *q1, *q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->magazin, aux->magazin) < 0; q2 = q1, q1 = q1->urm);
	if (q1 != NULL && strcmp(q1->magazin,aux->magazin)==0)
		q1->prim = adauga_sublista(q1->prim, aux_s);
	else 
	{
		if (q1 == q2)
		{
			aux->urm = lista;
			lista = aux;
		}
		else
		{
			q2->urm = aux;
			aux->urm = q1;
		}
		aux->prim = adauga_sublista(aux->prim, aux_s);
	}return lista;
}

//FUNCTIA DE CITIRE DINTR-UN FISIER
void citire(void)
{
	FILE *f;
	sublista_oferte *aux_s;
	lista_magazin *aux;
	char magazin[10], produs[15];
	int pret,cantitate;
	if ((f = fopen("magazine.txt", "rt")) == NULL)
	{
		printf("Fisierul nu a fost gasit\n");
		exit(-1);
	}
	while (!feof(f))
	{
		fscanf(f, "%s%s%d%d", magazin, produs, &pret, &cantitate);
		aux_s = (sublista_oferte*)malloc(sizeof(sublista_oferte));
		aux_s->produs = (char*)malloc(strlen(produs) + 1);
		aux_s->pret = pret;
		strcpy(aux_s->produs, produs);
		aux_s->cantitate = cantitate;
		aux = (lista_magazin*)malloc(sizeof(lista_magazin));
		aux->magazin = (char*)malloc(strlen(magazin) + 1);
		strcpy(aux->magazin, magazin);
		aux->prim = NULL;
		rad = adauga(rad, aux, aux_s);
	}
	printf("Baza de date a fost incarcata\n");
}

//FUNCTIA DE AFISARE
void afisare(lista_magazin *lista)
{
	lista_magazin *q;
	sublista_oferte* p;
	printf("\n\n\n-------------------OFERTE--------------------");
	for (q = lista; q != NULL; q = q->urm)
	{
		printf("\n%s:\n", q->magazin);
		for (p = q->prim; p != NULL; p = p->urm)
			printf("Produs:%s | Pret:%d | Cantitate:%d\n", p->produs, p->pret, p->cantitate);
	}
}

//FUNCTIA DE CALCULARE VALORII STOCULUI A UNUI MAGAZIN
void calcul_stoc(lista_magazin *lista)
{
	char magazin_cautat[15];
	int ok = 0 , s = 0;
	lista_magazin*q;
	sublista_oferte*p;
	printf("Introduceti numele magazinului la care vreti sa-i calculati valoarea stocului:");
	scanf("%s", magazin_cautat);
	for(q=lista;q!=NULL;q=q->urm)
		if (strcmp(q->magazin, magazin_cautat) == 0)
		{
			ok = 1;
			for (p = q->prim; p != NULL; p = p->urm)
			{
				s = s + (p->cantitate * p->pret);
			}
			printf("Valoarea stocului a magazinului %s este:%d\n", q->magazin, s);
		}
	if (ok == 0)
		printf("Magazinul nu exista\n");
}

//FUNCTIA DE AFISARE A PRODUSELOR A UNUI MAGAZIN CITIT DE LA TASTATURA
void magazin(lista_magazin*lista)
{
	char magazin_cautat[10];
	int ok = 0;
	lista_magazin *q;
	sublista_oferte* p;
	printf("Introduceti numele magazinului pe care il cautati:");
	scanf("%s", magazin_cautat);
	printf("\n\n");
	for (q = lista; q != NULL; q = q->urm)
		if (strcmp(q->magazin, magazin_cautat) == 0)
		{
			ok = 1;
			for (p = q->prim; p != NULL; p = p->urm)
				printf("Produs:%s | Pret:%d | Cantitate:%d\n", p->produs, p->pret, p->cantitate);
			printf("\n");
		}
		if(ok==0)
		printf("nu s-a gasit\n\n");
}

//FUNCTIE DE ADAUGARE PENTRU UN MAGAZIN NOU
void adaugare_magazin(lista_magazin *lista)
{
	lista_magazin *q,*aux;
	sublista_oferte *aux_s;
	char magazin[10], produs[15];
	int pret, cantitate,i,n,ok=0;
	printf("Magazinul:");
	scanf("%s", magazin);
	aux = (lista_magazin*)malloc(sizeof(lista_magazin));
	aux->magazin = (char*)malloc(strlen(magazin) + 1);
	strcpy(aux->magazin, magazin);
	aux->prim = NULL;
	for (q = lista; q != NULL; q = q->urm)
		if (strcmp(q->magazin, magazin) == 0)
			ok = 1;
	if (ok == 0)
	{
		printf("Cate produse doriti sa aiba magazinul nou:");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			aux_s = (sublista_oferte*)malloc(sizeof(sublista_oferte));
			printf("Produsul:");
			scanf("%s", produs);
			printf("Pretul:");
			scanf("%d", &pret);
			printf("Cantitatea:");
			scanf("%d", &cantitate);
			aux_s->produs = (char*)malloc(strlen(produs) + 1);
			strcpy(aux_s->produs, produs);
			aux_s->pret = pret;
			aux_s->cantitate = cantitate;
			rad = adauga(rad, aux, aux_s);
		}
		afisare(rad);
	}
	else
		printf("Magazinul exista deja in baza de date\n");
}

//FUNCTIE PENTRU ELIBERAREA DE MEMORIE PENTRU SUBLISTA
void eliberare_oferte(sublista_oferte *lista)
{
	sublista_oferte *q, *aux;
	q = lista;
	while (q != NULL)
	{
		aux = q;
		q = q->urm;
		free(aux->produs);
		free(aux);
	}
}

//FUNCTIA DE STERGERE A UNUI MAGAZIN
lista_magazin*stergere(lista_magazin*lista)
{
	lista_magazin *q1, *q2, *aux;
	char magazin_stergere[15];
	printf("Introduceti magazinul pe care il vreti sa-l stergeti:");
	scanf("%s", magazin_stergere);
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->magazin, magazin_stergere) != 0; q2 = q1, q1 = q1->urm);
		if (q1 != NULL)
		{
			aux = q1;
			if (q1 == q2)
			{
				lista = q1->urm;
				free(aux->magazin);
				eliberare_oferte(aux->prim);
				free(aux);
			}
			else
			{
				q2->urm = q1->urm;
				free(aux->magazin);
				eliberare_oferte(aux->prim);
				free(aux);
			}
			afisare(lista);
		}
	else
		printf("Nu s-a gasit magazinul\n");
	return lista;
}

//FUNCTIA DE STERGERE A UNUI PRODUS
void stergere_produs(lista_magazin *lista, char produs[])
{
	sublista_oferte *p1, *p2;
	lista_magazin *q;
	q = lista;
	for (p1 = p2 = q->prim; p1 != NULL && strcmp(p1->produs, produs) != 0; p2 = p1, p1 = p1->urm);
	if (p1 == p2)
		q->prim = p1->urm;
	else
		p2->urm = p1->urm;
	free(p1->produs);
	free(p1);
}

//FUNCTIE DE SCHIMBARE A PRETULUI SI A CANTITATII A UNUI PRODUS
void schimbare_produs(lista_magazin*lista)
{
	lista_magazin *p;
	sublista_oferte *q, *aux_s;
	char magazin[15], produs[15];
	int pret, cantitate;
	printf("Dati numele magazinului la care doriti sa schimbati la un produs pretul si cantitatea:");
	scanf("%s", magazin);
	p = lista;
	while (p != NULL && strcmp(p->magazin, magazin) != 0)
		p = p->urm;
	if (p != NULL)
	{
		printf("Dati un produs la care doriti sa ii schimbati pretul si cantitatea:");
		scanf("%s", produs);
		printf("Dati pretul nou:");
		scanf("%d", &pret);
		printf("Dati cantitatea noua:");
		scanf("%d", &cantitate);
		q = p->prim;
		while (q != NULL && strcmp(q->produs, produs) != 0)
			q = q->urm;
		if (q != NULL)
		{
			if (cantitate != 0)
			{
				stergere_produs(p, produs);
				aux_s = (sublista_oferte*)malloc(sizeof(sublista_oferte));
				aux_s->produs = (char*)malloc(strlen(produs) + 1);
				strcpy(aux_s->produs, produs);
				aux_s->pret = pret;
				aux_s->cantitate = cantitate;
				p->prim = adauga_sublista(p->prim, aux_s);
			}
			else
				stergere_produs(p, produs);
		}
		else
		{
			printf("Produsul cautat nu exista,acesta o sa fie introdus in magazin\n\n\n");
			aux_s = (sublista_oferte*)malloc(sizeof(sublista_oferte));
			aux_s->produs = (char*)malloc(strlen(produs) + 1);
			strcpy(aux_s->produs, produs);
			aux_s->pret = pret;
			aux_s->cantitate = cantitate;
			p->prim = adauga_sublista(p->prim, aux_s);
		}
	}
	else
		printf("Magazinul nu s-a gasit\n");
}

//FUNCTIA MAIN
int main()
{
	int opt,ok=0;
	do {
		
		printf("\n\n");
		printf("0.Iesire\n");
		printf("1.Incarcare oferte\n");
		printf("2.Afisare magazine in ordine alfabetica si preturile in ordine descrescatoare\n");
		printf("3.Calcularea valoarea stocului a unui magazin\n");
		printf("4.Afisarea produselor a unui magazin in ordine descrescatoare\n");
		printf("5.Adaugarea unui magazin\n");
		printf("6.Stergerea unui magazin\n");
		printf("7.Modificarea datelor a unui produs\n");
		printf("Optiunea dumneavoastra:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 0:exit(0);
			break;
		case 1:
			if (ok == 1)
			printf("Fisierul a fost deja incarcat\n\n\n");
			   else
		{
			citire();
			ok = 1;
		}
			break;
		case 2:if (ok == 0)
			printf("Incarcati mai intai baza de date\n\n\n\n");
			   else {
			afisare(rad);
			printf("\n\n");
		}
			break;
		case 3:if (ok == 0)
			printf("Incarcati mai intai baza de date\n");
			   else
			calcul_stoc(rad);
			break;
		case 4:if (ok == 0)
			printf("Incarcati mai intai baza de date\n\n\n");
			   else
		{
			magazin(rad);
			printf("\n\n\n");
		}
			break;
		case 5:if (ok == 0)
			printf("Incarcati mai intai baza de date\n\n\n");
			   else
			adaugare_magazin(rad);
			break;
		case 6:
			if (ok == 0)
			printf("Incarcati mai intai baza de date\n");
			else
			{
				rad = stergere(rad);
				
			}
			break;
		case 7:if (ok == 0)
			printf("Incarcati mai intai baza de date\n");
			   else
			schimbare_produs(rad);
			break;
		default:printf("Optiune gresita!\n");
			break;
		}
	} while (1);
}