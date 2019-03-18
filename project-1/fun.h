#pragma once
#include <vector>

using namespace std;

/*
**  funkcje wypisujace odpowiednia reprezentacje grafu na ekran - setw() ustawia szerokosc pol
*/
void Print_MS(int *A, int w, int k);
void Print_MI(int *A, int w, int k);
void Print_LS(vector<int> * A, int w, int k);


/*
**  funkcje dokonujace zamian - wszystkie algorytmy wymyslone samodzielnie
*/
void ls_ms(vector<int> * A, int w, int k);

void ls_mi(vector<int> * A, int w, int k);

void ms_ls(int *A, int w, int k);

void ms_mi(int *A, int w, int k);

void mi_ms(int *A, int w, int k);

//== za trudne, zeby normalnie zamieniac - skorzystalismy z poprzednich funkcji: mi_ms -> ms_ls
void mi_ls(int *A, int w, int k);
