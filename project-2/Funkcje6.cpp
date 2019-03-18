#include <iostream>
#include "Funkcje6.h"
#define W 5

void Hamilton_wypisz(int cykl[], bool graf[W][W]);

//sprawdzanie, czy mozna dodac wierzcholek w do cyklu
bool Hamilton_sprawdz(int w, int cykl[], bool graf[W][W], int index)
{
    //sprawdzanie, czy wierzcholek sasiaduje z poprzednio dodanym
    if (graf[cykl[index-1]][w] == 0)
        return false;


    //sprawdzanie, czy dany wierzcholek nie zostal juz dodany
    for (int i = 0; i < index; i++)
        if (cykl[i] == w)
            return false;

    return true;
}


bool Hamilton_dodaj(int cykl[], bool graf[W][W], int index)
{
    //gdy wszystkie wierzcholki dodane
    if (index == W)
    {
        //sprawdzanie, czy istnieje krawedz miedzy ostatnio dodanym wierzcholkiem a pierwszym
        if (graf[cykl[index-1]][cykl[0]] == 1 )
           return true;
        else
          return false;
    }

    // Sprawdzamy kolejne wierzcholki, bez pierwszego, bo zostal juz dodany w funkcji Hamilton
    for (int w = 0; w < W; w++)
    {
        ///sprawdzamy, czy mozna dodac do cyklu Hamiltona
        if (Hamilton_sprawdz(w, cykl, graf, index))
        {
            cykl[index] = w;

            //rekurencja - to samo dla kolejnych wierzcholkow
            if (Hamilton_dodaj(cykl, graf, index+1) == true)
                return true;

            //usuwanie wierzcholka, gdy nie pasuje
            cykl[index] = -1;
        }
    }


    return false;
}

// Funkcja zwraca false, gdy nie mozna utworzyc cyklu Hamiltona, jeœli mozna - zwraca true i wypisuje go.
bool Hamilton(bool graf[W][W])
{

    int *cykl = new int[W];
    for (int i = 0; i < W; i++)
    	cykl[i] = -1;

    //wybor od ktorego wierzcholka zaczynamy
    //cykl[0] = 0;
    cykl[0] = 3;


	Hamilton_wypisz(cykl, graf);

    return true;
}

void Hamilton_wypisz(int cykl[], bool graf[W][W])
{
	if ( Hamilton_dodaj(cykl, graf, 1) == true )
    {
    	printf("Graf jest Hamiltonowski.\nZnaleziony cykl Hamiltona: ");
   		for (int i = 0; i < W; i++)
       		printf("%d ", cykl[i]);
  		printf("%d ", cykl[0]);
    	printf("\n");

	}
	else
		printf("\nGraf nie jest Hamiltonowski.\n\n");
}


