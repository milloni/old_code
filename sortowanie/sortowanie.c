// gcc -std=c99 -g -Wall -Wpedantic -o sortowanie sortowanie.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define TAB_ROZMIAR (50000)
#define LIS_ROZMIAR (50000)

typedef struct _WezelInteger {
	struct _WezelInteger *nastepny;
	int                   dane;
} WezelInteger;

typedef struct _ListaInteger {
	WezelInteger *pierwszy;
} ListaInteger;

typedef struct _WezelDouble {
	struct _WezelDouble *nastepny;
	double               dane;
} WezelDouble;

typedef struct _ListaDouble {
	WezelDouble *pierwszy;
} ListaDouble;

void zamien_integer(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void zamien_double(double *a, double *b) {
	double t = *a;
	*a = *b;
	*b = t;
}

ListaInteger lista_integer_dodaj_poczatek(ListaInteger lis, WezelInteger *w) {
	assert(w != NULL);
	WezelInteger *pierwszy = lis.pierwszy;
	w->nastepny = NULL;
	if (pierwszy == NULL) {
		lis.pierwszy = w;
	} else {
		WezelInteger *t = lis.pierwszy;
		lis.pierwszy = w;
		w->nastepny = t;
	}

	return lis;
}

ListaDouble lista_double_dodaj_poczatek(ListaDouble lis, WezelDouble *w) {
	assert(w != NULL);
	WezelDouble *pierwszy = lis.pierwszy;
	w->nastepny = NULL;
	if (pierwszy == NULL) {
		lis.pierwszy = w;
	} else {
		WezelDouble *t = lis.pierwszy;
		lis.pierwszy = w;
		w->nastepny = t;
	}

	return lis;
}

ListaInteger sortowanie_lista_integer(ListaInteger lis) {
	ListaInteger wynik;
	wynik.pierwszy = NULL;
	while (lis.pierwszy != NULL) {
		WezelInteger *eMaxPoprz = NULL;
		WezelInteger *eMax = lis.pierwszy;
		WezelInteger *ePoprz = NULL;
		WezelInteger *e = lis.pierwszy;
		while (e != NULL) {
			if (e->dane < eMax->dane) {
				eMaxPoprz = ePoprz;
				eMax = e;
			}
			ePoprz = e;
			e = e->nastepny;
		}
		
		if (eMaxPoprz == NULL) {
			lis.pierwszy = NULL;
		} else {
			eMaxPoprz->nastepny = eMax->nastepny;
		}

		wynik = lista_integer_dodaj_poczatek(wynik, eMax);
	}

	return wynik;
}

ListaDouble sortowanie_lista_double(ListaDouble lis) {
	ListaDouble wynik;
	wynik.pierwszy = NULL;
	while (lis.pierwszy != NULL) {
		WezelDouble *eMaxPoprz = NULL;
		WezelDouble *eMax = lis.pierwszy;
		WezelDouble *ePoprz = NULL;
		WezelDouble *e = lis.pierwszy;
		while (e != NULL) {
			if (e->dane < eMax->dane) {
				eMaxPoprz = ePoprz;
				eMax = e;
			}
			ePoprz = e;
			e = e->nastepny;
		}
		
		if (eMaxPoprz == NULL) {
			lis.pierwszy = NULL;
		} else {
			eMaxPoprz->nastepny = eMax->nastepny;
		}

		wynik = lista_double_dodaj_poczatek(wynik, eMax);
	}

	return wynik;
}

void sortowanie_tablica_integer(int *tab, int dl) {
	for (int i = 0; i < dl; i++) {
		int pozMax = i;
		for (int j = i + 1; j < dl; j++) {
			if (tab[j] > tab[pozMax]) {
				pozMax = j;
			}
		}
		zamien_integer(&tab[i], &tab[pozMax]);
	}
}

void sortowanie_tablica_double(double *tab, int dl) {
	for (int i = 0; i < dl; i++) {
		int pozMax = i;
		for (int j = i + 1; j < dl; j++) {
			if (tab[j] > tab[pozMax]) {
				pozMax = j;
			}
		}
		zamien_double(&tab[i], &tab[pozMax]);
	}
}

void tablica_wypelnij_integer(int *tab, int dl) {
	srand(time(NULL));
	for (int i = 0; i < dl; i++) {
		tab[i] = rand();
	}
}

void tablica_wypelnij_double(double *tab, int dl) {
	srand(time(NULL));
	for (int i = 0; i < dl; i++) {
		tab[i] = (double)rand() / (double)RAND_MAX;
	}
}

ListaInteger lista_wypelnij_integer(ListaInteger lis, int ile) {
	srand(time(NULL));
	lis.pierwszy = malloc(sizeof(WezelInteger));
	lis.pierwszy->dane = rand();
	WezelInteger *poprzedni = lis.pierwszy;
	poprzedni->nastepny = NULL;
	for (int i = 0; i < ile - 2; i++) {
		WezelInteger *obecny = malloc(sizeof(WezelInteger));
		obecny->dane = rand();
		obecny->nastepny = NULL;
		poprzedni->nastepny = obecny;
		poprzedni = obecny;
	}
	poprzedni->nastepny = NULL;

	assert(lis.pierwszy != NULL);
	return lis;
}

ListaDouble lista_wypelnij_double(ListaDouble lis, int ile) {
	srand(time(NULL));
	lis.pierwszy = malloc(sizeof(WezelDouble));
	lis.pierwszy->dane = rand();
	WezelDouble *poprzedni = lis.pierwszy;
	poprzedni->nastepny = NULL;
	for (int i = 0; i < ile - 2; i++) {
		WezelDouble *obecny = malloc(sizeof(WezelDouble));
		obecny->dane = (double)rand() / (double)RAND_MAX;
		obecny->nastepny = NULL;
		poprzedni->nastepny = obecny;
		poprzedni = obecny;
	}
	poprzedni->nastepny = NULL;

	assert(lis.pierwszy != NULL);
	return lis;
}

void lista_integer_zwolnij(ListaInteger lis) {
	WezelInteger *e = lis.pierwszy;
	while (e != NULL) {
		WezelInteger *d = e;
		e = e->nastepny;
		free(d);
	}
}

void lista_double_zwolnij(ListaDouble lis) {
	WezelDouble *e = lis.pierwszy;
	while (e != NULL) {
		WezelDouble *d = e;
		e = e->nastepny;
		free(d);
	}
}

int main(void) {
	int tab_integer[TAB_ROZMIAR];
	tablica_wypelnij_integer(tab_integer, TAB_ROZMIAR);
	clock_t t1 = clock(), t2 = 0;
	sortowanie_tablica_integer(tab_integer, TAB_ROZMIAR);
	t2 = clock();
	double delta = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("Czas sortowania tablicy integer: %lf\n", delta);
	
	double tab_double[TAB_ROZMIAR];
	tablica_wypelnij_double(tab_double, TAB_ROZMIAR);
	t1 = clock();
	sortowanie_tablica_double(tab_double, TAB_ROZMIAR);
	t2 = clock();
	delta = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("Czas sortowania tablicy double: %lf\n", delta);

	ListaInteger lisi;
	lisi = lista_wypelnij_integer(lisi, LIS_ROZMIAR);
	t1 = clock();
	lisi = sortowanie_lista_integer(lisi);
	t2 = clock();
	delta = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("Czas sortowania listy integer: %lf\n", delta);

	ListaDouble lisd;
	lisd = lista_wypelnij_double(lisd, LIS_ROZMIAR);
	t1 = clock();
	lisd = sortowanie_lista_double(lisd);
	t2 = clock();
	delta = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("Czas sortowania listy double: %lf\n", delta);

	lista_integer_zwolnij(lisi);
	lista_double_zwolnij(lisd);
	
	return 0;
}
