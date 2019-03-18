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


using namespace std;

// rysuje graf (w tym zadaniu najmniejszy cykl)
void narysuj()
{	//zczytuje rozmiar macierzy i macierz
	std::fstream plik;
	plik.open("wynik2.txt");										// TUTAJ
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

// zamienia pare krawedzi (a-b i c-d na a-d i b-c)
void zamiana(int **A, int n)
{
	int a = 0, b = 0, c = 0, d = 0;

	while (a == b || a == c || a == d || b == c || b == d || c == d || A[a][b]==0 || A[c][d]==0 || A[a][d]==1 || A[b][c]==1)
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
}

// sumuje wagi wszystkich krawedzi cyklu
int wartosc(int **B, int **A, int n)
{
	int suma = 0;

	for(int i=0; i<n; i++)
		for (int j = i; j < n; j++)
		{
			if (B[i][j] == 1)
				suma += A[i][j];
		}


	return suma;
}

// kopiuje zawartosc tablicy nr 1 do tablicy nr 2)
void skopiuj(int **A, int **COPY, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			COPY[i][j] = A[i][j];
}

// sprawdza, czy graf jest spojny (tak=1, nie=0)
bool czy_spojny(int **B, int n)
{
	int **B_kopia = new int *[n];
	for (int i = 0; i < n; i++)
		B_kopia[i] = new int[n];

	skopiuj(B, B_kopia, n);

	int m = 0;
	int i = 0;
	while (i < n)
	{
		if (B_kopia[m][i] == 0)
		{
			B_kopia[m][i] = 7;
			//cout << "B[" << m << "][" << i << "] = 7\n";
			i++;
		}
		else if (B_kopia[m][i] == 1)
		{
			B_kopia[m][i] = 7;
			B_kopia[i][m] = 7;
			//cout << "B[" << m << "][" << i << "] = 7\n";
			//cout << "B[" << i << "][" << m << "] = 7\n";
			m = i;
			i = 0;
		}
		else if (B_kopia[m][i] == 7)
		{
			i++;
		}
	}
	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << B_kopia[i][j] << " ";
		cout << "\n";
	}
		*/

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (B_kopia[i][j] == 1)
				return false;

	return true;
}

// sprawdza, czy podany wierzcholek znajduje sie w cyklu (tak=1, nie=0)
bool czy_jest(int *CYKL, int x, int n)
{
	for (int i = 0; i <= n; i++)
		if (CYKL[i] == x)
			return true;

	return false;
}

using namespace std;

int main()
{
	std::fstream fp1;
	std::fstream fp2;
	std::fstream fp3;
	fp1.open("wejscie2.txt");				// TUTAJ
	fp2.open("cykl2.txt");					// TUTAJ
	fp3.open("wynik2.txt");					// TUTAJ
	int n, a, b;
	float x;
	srand((unsigned int)time(NULL));

	fp1 >> n;
	// wczytuje caly graf z wagami
	int **A = new int *[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fp1 >> A[i][j];

	// wczytuje cykl poczatkowy
	int *CYKL = new int[n+1];

	for (int i = 0; i <= n; i++)
		fp2 >> CYKL[i];
	

	// tworze tablice sasiedztwa cyklu
	int **B = new int *[n];
	for (int i = 0; i < n; i++)
		B[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			B[i][j] = 0;

	for (int i = 0; i < n; i++)
	{
		a = CYKL[i] - 1;
		b = CYKL[i+1] - 1;
		B[a][b] = 1;
		B[b][a] = 1;
	}





	
	//======================= Algorytm symulowanego wyżarzania =====================================

	int MAX_IT = 20;
	double T;

	int **B_kopia = new int *[n];
	for (int i = 0; i < n; i++)
		B_kopia[i] = new int[n];

	
	for (int i = 100; i >= 1; i--)
	{
		T = 0.001*i*i;

		for (int j = 0; j <= MAX_IT; j++)
		{
			skopiuj(B, B_kopia, n);

			zamiana(B_kopia, n);
			while (czy_spojny(B_kopia, n) == 0)
				zamiana(B_kopia, n);
			
			
			if (wartosc(B_kopia, A, n) < wartosc(B, A, n))
			{
				skopiuj(B_kopia, B, n);
			}
			else
			{
				x = rand() / float(RAND_MAX);
				if (x < exp(-(wartosc(B_kopia, A, n)-wartosc(B, A, n)) / T))
					skopiuj(B_kopia, B, n);
			}
		}
	}


	// =========================================================================================

	// zeruje cykl
	for (int i = 0; i <= n; i++)
		CYKL[i] = 0;

	// tworze cykl z macierzy sasiedztwa cyklu
	int k = 0;
	int m = 0;
	CYKL[k] = 1;
	while (k < n-1)
	{
		for (int i = 0; i < n; i++)
		{
			if (B[m][i] == 1 && czy_jest(CYKL, i+1, n)==0)
			{
				k++;
				CYKL[k] = i + 1;
				m = i;
			}
		}
	}
	CYKL[n] = 1;

	// zapisuje macierz sasiedztwa cyklu do pliku
	fp3 << n << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fp3 << B[i][j] << " ";
		}
		fp3 << std::endl;
	}		


	// wypisuje cykl na ekran i do pliku
	fp2.close();
	fp2.clear();
	fp2.open("cykl2.txt");										// TUTAJ
	std::cout << "Najkrotsza zamknieta droga: ";
	for (int i = 0; i <= n; i++)
	{
		std::cout << CYKL[i] << " ";
		fp2 << CYKL[i] << " ";
	}
	std::cout << " ma dlugosc " << wartosc(B, A, n);
	

	// rysuje graf
	char g;
	std::cout << "\nCzy chcesz narysowac otrzymany graf: \na) tak: t\nb) nie: n\n";
	std::cin >> g;
	if (g == 't')
		narysuj();
		


	// zwalniam pamiec
	for (int i = 0; i < n; i++)
		delete[] A[i];
	delete[] A;

	for (int i = 0; i < n; i++)
		delete[] B[i];
	delete[] B;

	for (int i = 0; i < n; i++)
		delete[] B_kopia[i];
	delete[] B_kopia;

	delete[] CYKL;



	fp1.close();
	fp2.close();
	fp3.close();

	std::system("PAUSE");
	return 0;
}

