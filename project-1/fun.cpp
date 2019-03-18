#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "fun.h"

using namespace std;

void Print_MS(int *A, int w, int k)
{
    cout << "\nMACIERZ SASIEDZTWA" << endl << endl;
    cout << "    ";
    for(int j=0; j<w; j++)
        cout << setw(2) << j+1 << " ";
    cout << endl << endl;
    for(int i=0; i<w; i++)
    {
        cout << setw(2) << i+1 << "  ";
        for(int j=0; j<w; j++)
            cout << setw(2) << *((A+i*w) + j) << " ";
        cout << endl;
    }
    cout << endl;
}


void Print_MI(int *A, int w, int k)
{
    cout << "\nMACIERZ INCYDENCJI" << endl << endl;
    cout << "    ";
    for(int j=0; j<k; j++)
        cout << setw(2) << j+1 << " ";
    cout << endl << endl;
    for(int i=0; i<w; i++)
    {
        cout << setw(2) << i+1 << "  ";
        for(int j=0; j<k; j++)
            cout << setw(2) << *((A+i*k) + j) << " ";
        cout << endl;
    }
    cout << endl;
}


void Print_LS(vector<int> *A, int w, int k)
{
    cout << "\nLISTA SASIEDZTWA" << endl << endl;
    for(int i=0; i<w; i++)
    {
        cout << i+1 << ": ";
        for(unsigned int j=0; j<A[i].size(); j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void ls_ms(vector<int> * A, int w, int k)
{
    int WYNIK[w][w] = {};   // macierz sasiedztwa wypelniona zerami
    int temp = 0;

    // przechodzimy po liscie sasiedztwa
    for(int i=0; i<w; i++)
        for(unsigned int j=0; j<A[i].size(); j++)
        {
            temp = A[i][j];             // kolejne wartosci ls
            WYNIK[i][temp-1] = 1;
        }

    Print_MS((int *)WYNIK, w, k);
}

void ls_mi(vector<int> * A, int w, int k)
{
    int WYNIK[w][k] = {};   // macierz incydencji wypelniona zerami
    int temp = 0, m = 0;

    // przechodzimy po liscie sasiedztwa
    for(int i=0; i<w; i++)
        for(unsigned int j=0; j<A[i].size(); j++)
        {
            temp = A[i][j];
            if(temp>i)          // optymalizacja - zeby nie zapisywac
            {
                WYNIK[i][m] = 1;
                WYNIK[temp-1][m] = 1;
                m++;
            }
        }

    Print_MI((int *)WYNIK, w, k);
}

void ms_ls(int *A, int w, int k)
{
    vector <int> WYNIK[w] = {};
    int temp = 0;

    for(int i=0; i<w; i++)
        for(int j=0; j<w; j++)
        {
            temp = *((A+i*w) + j);
            if(temp == 1)
            {
                WYNIK[i].push_back(j+1);
            }
        }

    Print_LS(WYNIK, w, k);
}

void ms_mi(int *A, int w, int k)
{
    int WYNIK[w][k] = {};
    int temp = 0, m = 0, diagonala = 0;

    for(int i=0; i<w; i++)
    {
        for(int j=w-1; j>=diagonala; j--)   // petla przechodzi tylko po gornej macierzy trojkatnej
        {
            temp = *((A+i*w) + j);
            if(temp == 1)
            {
                WYNIK[i][m] = 1;
                WYNIK[j][m] = 1;
                m++;
            }
        }
        diagonala++;
    }

    Print_MI((int*)WYNIK, w, k);
}

void mi_ls(int *A, int w, int k)
{
    //== dokladna kopia funkcji mi_ms() - (bez wypisywania)
    int WYNIK[w][w] = {};
    int index[2];
    int temp = 0, a =0;

    for(int i=0; i<k; i++)
    {
        for(int j=0; j<w; j++)
        {
            temp = *((A+j*k) + i);
            if(temp == 1)
            {
                index[a] = j;
                a++;
            }
        }
        WYNIK[(index[0])][(index[1])] = 1;
        WYNIK[(index[1])][(index[0])] = 1;
        a = 0;
    }
    //== koniec kopii

    ms_ls((int*)WYNIK, w, k);
}

void mi_ms(int *A, int w, int k)
{
    int WYNIK[w][w] = {};
    int index[2];
    int temp = 0, a =0;

    for(int i=0; i<k; i++)
    {
        for(int j=0; j<w; j++)
        {
            temp = *((A+j*k) + i);
            if(temp == 1)
            {
                index[a] = j;
                a++;
            }
        }
        WYNIK[(index[0])][(index[1])] = 1;
        WYNIK[(index[1])][(index[0])] = 1;
        a = 0;
    }

    Print_MS((int *)WYNIK, w, k);
}


