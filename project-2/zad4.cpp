// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "font.h"
#include <time.h>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

void narysuj()
{	//zczytuje rozmiar macierzy i macierz
	std::fstream plik;
	plik.open("wynik.txt");
	int n;
	plik >> n;
	int **A = new int*[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			plik >> A[i][j];

	//tworze okno 
	sf::RenderWindow window(sf::VideoMode(600, 600), "Graf", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	//tworze n-kat
	sf::CircleShape main_circle(200, n);
	//ustalam jego pozycje i inne parametry
	main_circle.setPosition(100, 100);
	main_circle.setRadius(200);
	main_circle.setFillColor(sf::Color::Transparent);
	main_circle.setOutlineColor(sf::Color::Transparent);
	main_circle.setOutlineThickness(2.0f);

	//tworze czcionke
	sf::Font font;
	sf::Text **text = new sf::Text*[n];
	font.loadFromMemory(font_data, font_data_size);

	for (int i = 0; i < n; i++)
	{
		text[i] = new sf::Text;
		text[i]->setFont(font);
		text[i]->setCharacterSize(30);
		text[i]->setFillColor(sf::Color::Black);
	}

	int x, y;
	x = 280;
	y = 80;

	//zliczam ile ma byc krawedzi
	int line_counter = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (A[i][j] == 1)
				line_counter++;
		}
	}

	//tworze tablice lini i ustalam jej parametry podstawowe
	sf::VertexArray *lines = new sf::VertexArray[line_counter];

	for (int i = 0; i < line_counter; i++)
	{
		lines[i] = sf::VertexArray(sf::LinesStrip, 2);
		lines[i][0].color = sf::Color::Black;
		lines[i][1].color = sf::Color::Black;
	}

	//tworze tablice okregow, ustalam podstawowe parametry i pozycje
	sf::CircleShape *vertex = new sf::CircleShape[n];
	for (int i = 0; i < n; i++)
	{
		sf::Vector2f tmp;
		tmp = main_circle.getPoint(i);
		tmp.x = tmp.x + 80;
		tmp.y = tmp.y + 80;
		vertex[i].setRadius(20);
		vertex[i].setPosition(tmp);
		vertex[i].setFillColor(sf::Color::White);
		vertex[i].setOutlineColor(sf::Color::Black);
		vertex[i].setOutlineThickness(2.0f);

		//wypisuje tekst 
		std::string b = "0";
		b = std::to_string(i + 1);
		if (i + 1 < 10)
		{
			tmp.x = tmp.x + 12;
			tmp.y = tmp.y;
		}
		else
		{
			tmp.x = tmp.x + 3;
			tmp.y = tmp.y;
		}
		text[i]->setPosition(tmp);
		text[i]->setString(b);
	}

	//pobieram pozycje tekstu zeby wiedziec gdzie zaczepic krawdzi i ustalam ich pozycje
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (A[i][j] == 1)
			{
				sf::Vector2f temp;
				temp = text[i]->getPosition();
				temp.x = temp.x + 3;
				temp.y = temp.y + 15;
				lines[c][0].position = temp;
				temp = text[j]->getPosition();
				temp.x = temp.x + 3;
				temp.y = temp.y + 15;
				lines[c][1].position = temp;
				c++;
			}
		}
	}

	//wypisuje na ekran 
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
		window.draw(main_circle);
		for (int i = 0; i < line_counter; i++)
		{
			window.draw(lines[i]);
		}
		for (int i = 0; i < n; i++) {
			window.draw(vertex[i]);
			window.draw(*text[i]);
		}



		window.display();
	}


	for (int i = 0; i < n; i++)
		delete[] A[i];
	delete[] A;
	for (int i = 0; i < n; i++)
		delete[] text[i];
	delete[] text;
	delete[] lines;
	delete[] vertex;
}

void zamiana(int **A, int n)
{
	int a = 0, b = 0, c = 0, d = 0;

	while (a == b || a == c || a == d || b == c || b == d || c == d || A[a][b] == 0 || A[c][d] == 0 || A[a][d] == 1 || A[b][c] == 1)
	{
		a = rand() % n;
		b = rand() % n;
		c = rand() % n;
		d = rand() % n;
	}

	A[a][b] = 0;
	A[b][a] = 0;
	A[c][d] = 0;
	A[d][c] = 0;
	A[a][d] = 1;
	A[d][a] = 1;
	A[b][c] = 1;
	A[c][b] = 1;

	FILE *fp;
	fp = fopen("wynik.txt", "w");
	fprintf(fp, "%d\n", n);
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			fprintf(fp, "%d ", A[i][j]);
		fprintf(fp, "\r\n");
	}
	fclose(fp);

	cout << endl << "  Zamienione krawedzie:" << endl;
	cout << "  " << a + 1 << "-" << b + 1 << " oraz " << c + 1 << "-" << d + 1 << "  na  " << a + 1 << "-" << d + 1 << " oraz " << b + 1 << "-" << c + 1 << endl;

}

bool WszystkoZero(int CIAG[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (CIAG[i] != 0)
			return false;
	}
	return true;
}

bool CzyGraficzny(int CIAG[], int n)
{
	while (true)
	{
		if (WszystkoZero(CIAG, n))
			return true;
		if (CIAG[0] < 0 || CIAG[0] >= n)
			return false;
		for (int i = 1; i <= CIAG[0]; i++)
		{
			CIAG[i] = CIAG[i] - 1;
		}
		CIAG[0] = 0;
		sort(CIAG, CIAG + n);
		reverse(CIAG, CIAG + n);
	}
}

void generuj_ciag(int CIAG[], int CIAG_kopia[], int CIAG_kopia2[], int n)
{
	int a, i;
	for (i = 0; i < n; i++)
	{
		a = (rand() % n/2) * 2 + 2;
		CIAG[i] = a;
		CIAG_kopia[i] = CIAG[i];
		CIAG_kopia2[i] = CIAG[i];
	}

	sort(CIAG, CIAG + n);
	sort(CIAG_kopia, CIAG_kopia + n);
	sort(CIAG_kopia2, CIAG_kopia2 + n);
	reverse(CIAG, CIAG + n);
	reverse(CIAG_kopia, CIAG_kopia + n);
	reverse(CIAG_kopia2, CIAG_kopia2 + n);
}

void cykl_eulera(int **A, int CIAG[], int n)
{
	int a, b;
	string cykl = "";

	a = rand() % n;
	b = rand() % n;

	int pierwszy = a;

	while (CIAG[a]>0)
	{
		while (b==a || A[b][a]==0 || (CIAG[b]==1 && CIAG[a]!=1))
		{
			b = rand() % n;
		}

		A[a][b] = 0;
		A[b][a] = 0;
		CIAG[a]--;
		CIAG[b]--;

		cykl += to_string(a+1);
		cykl += " ";

		a = b;
	}

	cykl += to_string(pierwszy+1);

	cout << "Cykl Eulera: " << cykl << endl;
	
}

int main()
{
	srand((unsigned)time(NULL));
	int n, i, j;
	char g, g2;

	cout << "Podaj liczbe wierzcholkow: ";
	cin >> n;

	int *CIAG = new int[n];
	int *CIAG_kopia = new int[n];
	int *CIAG_kopia2 = new int[n];

	do
	{
		generuj_ciag(CIAG, CIAG_kopia, CIAG_kopia2, n);
	}
	while (CzyGraficzny(CIAG_kopia, n) == false);

	cout << "\nLosowy graf eulerowski: " << endl;
	for (i = 0; i < n; i++)
		cout << CIAG[i] << " ";
		

	int **A = new int *[n];
	for (i = 0; i < n; i++)
		A[i] = new int[n];


	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			A[i][j] = 0;


	int a = 0, b = 0, c = 0, d = 0; 

	for (i = 0; i < n; i++)
	{
		j = 0;
		while (j < CIAG[i])
		{
			a = rand() % n;

			if (a > i && A[a][i] != 1 && CIAG[a] != 0)
			{
				A[a][i] = 1;
				A[i][a] = 1;
				CIAG[a] = CIAG[a] - 1;
				j++;
			}
		}
		CIAG[i] = 0;
	}


	cout << "\nOtrzymana macierz sasiedztwa: \n";
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}


	FILE *fp;
	fp = fopen("wynik.txt", "w");
	fprintf(fp, "%d\n", n);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			fprintf(fp, "%d ", A[i][j]);
		fprintf(fp, "\r\n");
	}
	fclose(fp);



	cout << "\nCzy chcesz narysowac otrzymany graf? \na) tak: t\nb) nie: n\n";
	cin >> g;
	if (g == 't')
		narysuj();


	cout << "\nCzy chcesz zamienic losowa pare krawedzi? \na) tak: t \nb) nie: n \n";
	cin >> g2;

	while (g2 != 'n')
	{
		zamiana(A, n);

		cout << "\nPowtorzyc? \na) tak: t \nb) nie: n \n";
		cin >> g2;

		cout << "\nNarysowac? \na) tak: t\nb) nie: n\n";
		cin >> g;
		if (g == 't')
			narysuj();
	}



	cykl_eulera(A, CIAG_kopia2, n);







	delete[] A;
	//for (i = 0; i < n; i++)
	//	delete[] A[i];

	_CrtDumpMemoryLeaks();

	system("PAUSE");
	return 0;
}

