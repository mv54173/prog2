// Ovdje napiši funkcije koje su definirane u header.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Recept *ucitajRecepte(const char *imeDatoteke, int *brojRecepata)
{
	FILE *fp = NULL;
	int brUcitanih = 0;

	fp = fopen(imeDatoteke, "r");

	if (fp == NULL)
	{
		*brojRecepata = 0;
		return NULL;
	}

	if (fscanf(fp, "%d", brojRecepata) != 1)
	{
		*brojRecepata = 0;
		fclose(fp);
		return NULL;
	}

	Recept *recepti = NULL;

	recepti = (Recept *)malloc(*brojRecepata * sizeof(Recept));

	if (recepti == NULL)
	{
		fclose(fp);
		return NULL;
	}

	for (int i = 1; i <= *brojRecepata; i++)
	{
		if (fscanf(fp, " %49[^;];%49[^;];%d;%29[^;];%d", recepti[brUcitanih].naziv, recepti[brUcitanih].kuhinja, &recepti[brUcitanih].godinaObjave, recepti[brUcitanih].kategorija, &recepti[brUcitanih].vrijemePripreme) == 5)
		{
			brUcitanih++;
		}
	}

	fclose(fp);

	*brojRecepata = brUcitanih;

	return recepti;
}

float izracunajProsjecnoVrijeme(Recept *recepti, int brojRecepata, const char *kategorija)
{
	int brojac = 0;
	int i;
	int suma = 0;

	for (i = 0; i < brojRecepata; i++)
	{
		if (strcmp(recepti[i].kategorija, kategorija) == 0)
		{
			brojac++;
			suma += recepti[i].vrijemePripreme;
		}
	}

	if (brojac == 0)
	{
		return -1.0f;
	}

	return (float)suma / brojac;
}

void pretraziPoNazivu(Recept *recepti, int brojRecepata, const char *naziv)
{
	int i;

	for (i = 0; i < brojRecepata; i++)
	{
		if (strcmp(recepti[i].naziv, naziv) == 0)
		{
			printf("Recept: %s, Kuhinja: %s, Godina objave: %d, Kategorija: %s, Vrijeme pripreme: %d min\n",
				   recepti[i].naziv,
				   recepti[i].kuhinja,
				   recepti[i].godinaObjave,
				   recepti[i].kategorija,
				   recepti[i].vrijemePripreme);
			return;
		}
	}

	printf("Recept s nazivom %s nije pronaden.\n", naziv);
}

void swap(Recept *x, Recept *y)
{
	Recept aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

void ispisNajbrzihRecepata(Recept *recepti, int brojRecepata, int n)
{
	int i, j;

	if (n > brojRecepata)
	{
		n = brojRecepata;
	}

	/*
	for (i = 0; i < brojRecepata-1; i++){
		for (j = 0; j < brojRecepata-1-i; j++){
			if (recepti[j+1].vrijemePripreme < recepti[j].vrijemePripreme){
				Recept temp = recepti[j];
				recepti[j] = recepti[j + 1];
				recepti[j + 1] = temp;
			}
		}
	}
	*/
	int i, j;
	for (i = 0; i < brojRecepata - 1; i++)
		for (j = 0; j < brojRecepata - 1 - i; j++)
			if (recepti[j + 1].vrijemePripreme < recepti[j].vrijemePripreme)
				swap(&recepti[j], &recepti[j + 1]);

	for (i = 0; i < n; i++)
	{
		printf("%d. %s (%d min)\n", i + 1, recepti[i].naziv, recepti[i].vrijemePripreme);
	}
}
