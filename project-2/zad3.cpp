#include<iostream>
#include <list>
#include <ctime>
#include <string.h>
#include <fstream>
#include <string>
#include "Funkcje3.h"
using namespace std;

/*
Inicjalizujemy wszystkie wierzcho�ki jako nieodwiedzone.
Dla ka�dego wierzcho�ka w:
	-je�li nie by� odwiedzony - przeszukiwanie w g��b (DFS)
	-nowa linia

Funkcja DFS:
 -zaznaczamy w jako odwiedzony
 -wypisujemy w
 - dla kazdego s�siada s: jesli u nieodwiedzone - DFS rekurencyjnie

*/



int main()
{

   int wierzch, kraw, w1, w2;
   cout << "Podaj liczbe wierzcholkow grafu: ";
   cin >> wierzch;
   cout << "Podaj liczbe krawedzi: ";
   cin >> kraw;

   Graf graf(wierzch);

   cout << "Podaj wierzcholki tworzace krawedz:\n";
   int i;
   for(i = 0; i < kraw; i++ )
	{	cin >> w1 >> w2;
		graf.dodaj_kr(w1, w2);
	}


    cout << "Najwieksza spojna skladowa podanego grafu: \n";
    graf.spojne();




 }



