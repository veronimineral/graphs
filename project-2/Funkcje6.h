#pragma once
#define W 5

bool Hamilton_sprawdz(int w, int cykl[], bool graf[W][W], int index);
bool Hamilton_dodaj(int cykl[], bool graf[W][W], int index);
bool Hamilton(bool graf[W][W]);
void Hamilton_wypisz(int cykl[], bool graf[W][W]);
