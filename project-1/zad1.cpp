#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#include "fun.h"

int main()
{
    cout << "======== ZADANIE 1 ==========" << endl << endl;
    //== wybor rozmiaru grafu - wybieramy rozne pliki, w zaleznosci od tego
    cout << "Male czy duze grafy?" << endl;
    string rozmiar;
    cin >> rozmiar;

    ifstream fp1;
    ifstream fp2;
    ifstream fp3;

    int x;
    if(rozmiar == "male" || rozmiar == "Male" || rozmiar == "MALE")
    {
        x = 5;
        fp1.open("MS2.txt");
        fp2.open("MI2.txt");
        fp3.open("LS2.txt");
    }
    if(rozmiar == "duze")
    {
        x = 7;
        fp1.open("MS.txt");
        fp2.open("MI.txt");
        fp3.open("LS.txt");
    }

    if (fp1.is_open()==0 || fp2.is_open()==0 || fp3.is_open()==0)
    {
        cout << "Unable to open files";
        return -1;
    }



//=============== MACIERZ SASIEDZTWA =================================

    //== liczba wierzcholkow i kolumn odczytana z 1 linii pliku
    int w_MS, k_MS;
    fp1 >> w_MS;   fp1 >> k_MS;

    //== dwuwymiarowa tablica intow - macierz [w][w]
    int tab_MS[w_MS][w_MS];

    //== wypelnianie macierzy danymi z pliku
    for(int i=0; i<w_MS; i++)
        for(int j=0; j<w_MS; j++)
            fp1 >> tab_MS[i][j];

    //== ladne wypisywanie macierzy na ekran
    Print_MS((int *)tab_MS, w_MS, k_MS);



//=============== MACIERZ INCYDENCJI =================================

    //== liczba wierzcholkow i kolumn odczytana z 1 linii pliku
    int w_MI, k_MI;
    fp2 >> w_MI;   fp2 >> k_MI;

    //== dwuwymiarowa tablica intow - macierz [w][k]
    int tab_MI[w_MI][k_MI];

    //== wypelnianie macierzy danymi z pliku
    for(int i=0; i<w_MI; i++)
        for(int j=0; j<k_MI; j++)
            fp2 >> tab_MI[i][j];

    //== ladne wypisywanie macierzy na ekran
    Print_MI((int *)tab_MI, w_MI, k_MI);



//=============== LISTA SASIEDZTWA =================================

    //== liczba wierzcholkow i kolumn odczytana z 1 linii pliku
    int w_LS, k_LS;
    fp3 >> w_LS;   fp3 >> k_LS;

    //== tablica wektorów - nasza implementacja listy sasiedztwa
    vector <int> tab_LS[w_LS];

    //== przejscie na x miejsce w pliku(na poczatek drugiej linii) - z zalezy od rozmiarow macierzy
    fp3.clear();
    fp3.seekg(x, ios::beg);

    //== wypelnianie listy sasiedztwa
    int i = 0, a;
    string str;
    while(getline(fp3, str))
    {
        istringstream ss(str);

        while(ss >> a)
        {
            tab_LS[i].push_back(a);
        }
        i++;
    }

    //== ladne wypisanie listy sasiedztwa na ekran
    Print_LS(tab_LS, w_LS, k_LS);



//=============== INTERFEJS UZYTKOWNIKA ======================================

	int wybor;
	cout << "\n\n\n====== ZAMIANA REPREZENTACJI GRAFOW ======" << endl;
	cout << "1 - Lista sasiedztwa na macierz sasiedztwa." << endl;
	cout << "2 - Lista sasiedztwa na macierz incydencji." << endl;
	cout << "3 - Macierz sasiedztwa na liste sasiedztwa." << endl;
	cout << "4 - Macierz sasiedztwa na macierz incydencji." << endl;
	cout << "5 - Macierz incydencji na liste sasiedztwa." << endl;
	cout << "6 - Macierz incydencji na macierz sasiedztwa." << endl << endl;
	cout << "Wybierz, ktorej zamiany chcesz dokonac" << endl;
	cout << endl;


	//== zamian mozna dokonywac az do zamkniecia programu
	while(wybor)
	{
    cin >> wybor;
    switch (wybor)
	{
		case 1:
		    ls_ms(tab_LS, w_LS, k_LS);
        break;

		case 2:
			ls_mi(tab_LS, w_LS, k_LS);
		break;

		case 3:
			ms_ls((int*)tab_MS, w_MS, k_MS);
		break;

		case 4:
			ms_mi((int*)tab_MS, w_MS, k_MS);
		break;

		case 5:
			mi_ls((int*)tab_MI, w_MI, k_MI);
		break;

		case 6:
			mi_ms((int*)tab_MI, w_MI, k_MI);
		break;

		default:
			cout << "Opcja o podanym numerze nie istnieje" << endl;
		break;
	}
	}


    fp1.close();
    fp2.close();
    fp3.close();

    return 0;
}
